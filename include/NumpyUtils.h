#pragma once

// =============================================================================
// numpy_utils.h - C++ wrapper for matplotlib.pyplot.numpy_utils
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 09/06/2024
// =============================================================================

#include "Interpreter.h"
#include "PyPtr.h"
#include "Configs.h"

#include <string>
#include <vector>
#include <cstring>

namespace matplotlibcpp {


    // ============================================================
    // Type mapping from C++ types to NumPy type numbers
    // ============================================================



    /**
     * @brief Maps C++ types to corresponding NumPy type numbers for array creation.
     * @tparam T C++ type to map.
     * @note Specializations must be provided for each supported type.
     */
    template<typename T> struct NumpyType; 
    template<> struct NumpyType<double>                 { static constexpr int typenum = NPY_DOUBLE;    };
    template<> struct NumpyType<float>                  { static constexpr int typenum = NPY_FLOAT;     };
    template<> struct NumpyType<int8_t>                 { static constexpr int typenum = NPY_INT8;      };
    template<> struct NumpyType<int16_t>                { static constexpr int typenum = NPY_INT16;     };
    template<> struct NumpyType<int32_t>                { static constexpr int typenum = NPY_INT32;     };
    template<> struct NumpyType<int64_t>                { static constexpr int typenum = NPY_INT64;     };
    template<> struct NumpyType<uint8_t>                { static constexpr int typenum = NPY_UINT8;     };
    template<> struct NumpyType<uint16_t>               { static constexpr int typenum = NPY_UINT16;    };
    template<> struct NumpyType<uint32_t>               { static constexpr int typenum = NPY_UINT32;    };
    template<> struct NumpyType<uint64_t>               { static constexpr int typenum = NPY_UINT64;    };
    template<> struct NumpyType<bool>                   { static constexpr int typenum = NPY_BOOL;      };
    template<> struct NumpyType<long long>              { static constexpr int typenum = NPY_LONGLONG;  };
    template<> struct NumpyType<unsigned long long>     { static constexpr int typenum = NPY_ULONGLONG; };





    // ============================================================
    // Conversion functions
    // ============================================================

    /**
     * @brief Converts a std::vector to a 1D numpy array.
     * @tparam T numeric type — must have a NumpyType specialization
     * @param v input vector
     * @return PyObject* numpy array — caller must Py_XDECREF
     * @throws std::runtime_error if array creation fails
     */
    template<typename T>
    PyObject* toNumpy(const std::vector<T>& v) {
        Interpreter::getInstance(); 

        npy_intp size = static_cast<npy_intp>(v.size());

        PyObject* array = PyArray_SimpleNew(1, &size, NumpyType<T>::typenum);

        if (!array) throw std::runtime_error("Failed to create numpy array");

        std::memcpy(PyArray_DATA(reinterpret_cast<PyArrayObject*>(array)),
                v.data(),
                v.size() * sizeof(T));

        return array;
    }


    /** 
     * @brief Converts a pair<T1, T2> to a Python tuple
     * @tparam T1 first element type
     * @tparam T2 second element type
     * @param p input pair
     * @return PyObject* Python tuple
     */
    template<typename T1, typename T2>
    inline PyObject* pairToTuple(const std::pair<T1, T2>& p) {
        PyObject* tuple = PyTuple_New(2);
        
        // first element (double, int, string)
        if constexpr (std::is_same_v<T1, double>)
            PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(p.first));
        else if constexpr (std::is_integral_v<T1>)
            PyTuple_SetItem(tuple, 0, PyLong_FromLong(p.first));
        else if constexpr (std::is_same_v<T1, std::string>)
            PyTuple_SetItem(tuple, 0, PyUnicode_FromString(p.first.c_str()));

        // second element (double, int, string)
        if constexpr (std::is_same_v<T2, double>)
            PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(p.second));
        else if constexpr (std::is_integral_v<T2>)
            PyTuple_SetItem(tuple, 1, PyLong_FromLong(p.second));
        else if constexpr (std::is_same_v<T2, std::string>)
            PyTuple_SetItem(tuple, 1, PyUnicode_FromString(p.second.c_str()));

        return tuple;
    }



    /**
    * @brief Converts a std::vector<bool> to a numpy bool array
    * @param v input vector
    * @return PyObject* numpy array — caller must Py_XDECREF
    * @throws std::runtime_error if array creation fails
    */
    inline PyObject* toBoolArray(const std::vector<bool>& v) {
        Interpreter::getInstance();

        npy_intp size = static_cast<npy_intp>(v.size());
        
        PyObject* array = PyArray_SimpleNew(1, &size, NPY_BOOL);
        if (!array) throw std::runtime_error("Failed to create numpy bool array");

        npy_bool* data = reinterpret_cast<npy_bool*>(
            PyArray_DATA(reinterpret_cast<PyArrayObject*>(array)));

        // Convert bool to npy_bool
        for (size_t i = 0; i < v.size(); ++i)
            data[i] = v[i] ? 1 : 0;

        return array;
    }   


    /**
     * @brief Converts an ErrorValue to a numpy array
     * @param ev input ErrorValue
     * @return PyObject* numpy array
     */
    inline PyObject* errorValueToNumpy(const ErrorValue& ev) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, double>) {
                return PyFloat_FromDouble(val);
            } else if constexpr (std::is_same_v<T, std::vector<double>>) {
                return toNumpy(val);
            } else {
                // shape(2,N) — list of two numpy arrays
                PyObject* list = PyList_New(2);
                PyList_SetItem(list, 0, toNumpy(val[0]));
                PyList_SetItem(list, 1, toNumpy(val[1]));
                return list;
            }
        }, ev);
    }


    /** 
    *@brief Converts a LimValue to a Python object
    * @param val input LimValue
    * @return PyObject* Python object
    */
    inline PyObject* limValueToPython(const LimValue& val) {
        return std::visit([](const auto& v) -> PyObject* {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, bool>) {
                return v ? Py_True : Py_False;
            } else if constexpr (std::is_same_v<T, std::vector<bool>>) {
                return toBoolArray(v);
            } 
        }, val);
    }

    /**
     * @brief Converts an ErrorEveryValue to a Python object
     * @param val input ErrorEveryValue
     * @return PyObject* Python object
     */
    inline PyObject* errorEveryValueToPython(const ErrorEveryValue& val) {
        return std::visit([](const auto& v) -> PyObject* {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, int>) {
                return PyLong_FromLong(v);
            } else if constexpr (std::is_same_v<T, std::pair<int, int>>) {
                PyObject* tuple = PyTuple_New(2);
                PyTuple_SetItem(tuple, 0, PyLong_FromLong(v.first));
                PyTuple_SetItem(tuple, 1, PyLong_FromLong(v.second));
                return tuple;
            }
        }, val);
    }


    /**
     * @brief Converts a DataValue to a numpy array
     * @param dv input DataValue
     * @return PyObject* numpy array
     */
    inline PyObject* dataValueToNumpy(const DataValue& dv) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, double>) {
                return PyFloat_FromDouble(val);
            } else {
                return toNumpy(val);
            }
        }, dv);
    }


    /**
    * @brief Converts a vector of strings to a Python list of strings
    * @param v input vector
    * @return PyObject* Python list of strings
    */
    inline PyObject* toStringList(const std::vector<std::string>& v) {
        PyObject* list = PyList_New(static_cast<Py_ssize_t>(v.size()));
        if (!list) throw std::runtime_error("Failed to create Python list");
        for (size_t i = 0; i < v.size(); ++i)
            PyList_SetItem(list, i, PyUnicode_FromString(v[i].c_str()));
        return list;
    }


    /**
    * @brief Converts std::vector<double> to Python tuple for subs parameter.
    * subs expects a sequence of floats between 1 and 10 representing
    * minor tick locations on a log scale.
    * @param v vector of sub-decade positions e.g. {2, 3, 4, 5, 6, 7, 8, 9}
    * @return PyObject* Python tuple — caller must Py_XDECREF
    * @throws std::runtime_error if tuple creation fails
    */
    inline PyObject* toSubs(const std::vector<double>& v) {
        PyObject* tuple = PyTuple_New(static_cast<Py_ssize_t>(v.size()));
        if (!tuple) throw std::runtime_error("Failed to create subs tuple");
        for (size_t i = 0; i < v.size(); ++i)
            PyTuple_SetItem(tuple, i, PyFloat_FromDouble(v[i]));
        return tuple;
    }



    /**
     * @brief Converts a SizeValue in points to a Python object
     * @param sv input SizeValue
     * @return PyObject* Python object
     */
    inline PyObject* sizeInPointsValueToPython(const SizeValue& sv) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, double>) {
                return PyFloat_FromDouble(val);
            } else {
                return toNumpy(val);
            }
        }, sv);
    }


    /**
     * @brief Converts linewidths to a Python object
     * @param lw input linewidths
     * @return PyObject* Python object
     */
    inline PyObject* linewidthsToPython(const LinewidthsValue& lw) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, double>) {
                return PyFloat_FromDouble(val);
            } else {
                return toNumpy(val);
            }
        }, lw);
    }


    
    /**
     * @brief Converts a ColorValue in points to a Python object
     * @param cv input ColorValue
     * @return PyObject* Python object
     */
    inline PyObject* colorValueToPython(const ColorValue& cv) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, std::string>) {
                return PyUnicode_FromString(val.c_str());
            } else {
                return toNumpy(val);
            }
        }, cv);
    }


    /** @brief Converts a MosaicValue to a Python object
     * @param mv input MosaicValue
     * @return PyObject* Python object
     */
    inline PyObject* mosaicValueToPython(const MosaicValue& mv) {
    return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            // 1D list form
            if constexpr (std::is_same_v<T, std::string>) {
                return PyUnicode_FromString(val.c_str());
            } else {
                // 2D list form — list of lists of strings
                PyObject* outer = PyList_New(val.size());
                for (size_t i = 0; i < val.size(); ++i) {
                    PyObject* inner = PyList_New(val[i].size());
                    for (size_t j = 0; j < val[i].size(); ++j)
                        PyList_SetItem(inner, j,
                            PyUnicode_FromString(val[i][j].c_str()));
                    PyList_SetItem(outer, i, inner);
                }
                return outer;
            }
        }, mv);
    }


    /** 
     * @brief Converts a BarXValue in points to a Python object
     * @param bv input BarXValue
     * @return PyObject* Python object
     */
    inline PyObject* barXValueToPython(const BarXValue& bx) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, double>) {
                return PyFloat_FromDouble(val);
            } else if constexpr (std::is_same_v<T, Vec>) {
                return toNumpy(val);
            } else {
                return toStringList(val);
            }
        }, bx);
    }

    /** 
     * @brief Converts a BarYValue in points to a Python object
     * @param bv input BarYValue
     * @return PyObject* Python object
     */
    inline PyObject* barYValueToPython(const BarYValue& bv) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, double>) {
                return PyFloat_FromDouble(val);
            } else if constexpr (std::is_same_v<T, Vec>) {
                return toNumpy(val);
            } else {
                return toStringList(val);
            }
        }, bv);
    }

    
    /** 
     * @brief Converts a BarValue in points to a Python object
     * @param bv input BarValue
     * @return PyObject* Python object
     */
    inline PyObject* barValueToPython(const BarValue& bv) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, double>) {
                return PyFloat_FromDouble(val);
            } else {
                return toNumpy(val);
            }
        }, bv);
    }

    
    /** 
     * @brief Converts a LinewidthValue either in double or vector<double> to a Python object
     * @param lwv input LinewidthValue
     * @return PyObject* Python object
     */
    inline PyObject* linewidthValueToPython(const LinewidthValue& lwv) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, double>) {
                return PyFloat_FromDouble(val);
            } else {
                return toNumpy(val);
            }
        }, lwv);
    }

    /**
     * @brief Converts TickLabelValue to a Python object
     * @param tlv input TickLabelValue
     * @return PyObject* Python object
     */
    inline PyObject* tickLabelValueToPython(const TickLabelValue& tlv) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, std::string>) {
                return PyUnicode_FromString(val.c_str());
            } else {
                return toStringList(val);
            }
        }, tlv);
    }




    

    /**
    * @brief Converts FontSizeValue to a Python object
    * @param fsv input FontSizeValue
    * @return PyObject* Python object
    */
    inline PyObject* fontSizeValueToPython(const FontSizeValue& fsv) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, double>)
                return PyFloat_FromDouble(val);
            else
                return toStringList(val);
        }, fsv);
    }


    /** 
     * @brief Converts FontSizeValue to a Python object
     * @param fsv input FontSizeValue
     * @return PyObject* Python object
     */
    inline PyObject* fontStretchValueToPython(const FontStretchValue& fsv) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, int>)
                return PyLong_FromLong(val);
            else
                return PyUnicode_FromString(val.c_str());
        }, fsv);
    }

    /**
     * @brief Converts FontWeightValue to a Python object
     * @param fwv input FontWeightValue
     * @return PyObject* Python object
     */
    inline PyObject* fontWeightValueToPython(const FontWeightValue& fwv) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, int>)
                return PyLong_FromLong(val);
            else
                return PyUnicode_FromString(val.c_str());
        }, fwv);
    }


    /**
     * @brief Converts lineSpacingValue to a Python object
     * @param lsv input lineSpacingValue
     * @return PyObject* Python object
     */
    inline PyObject* lineSpacingValueToPython(const LineSpacingValue& lsv) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, double>)
                return PyFloat_FromDouble(val);
            else
                return PyUnicode_FromString(val.c_str());
        }, lsv);
    }


    /**
    * @brief Converts RotationValue to a Python object
    * @param rv input RotationValue
    * @return PyObject* Python object
    */
    inline PyObject* rotationValueToPython(const RotationValue& rv) {
        return std::visit([](const auto& val) -> PyObject* {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, double>)
                return PyFloat_FromDouble(val);
            else
                return PyUnicode_FromString(val.c_str());
        }, rv);
    }


    

    /** @brief Scalar multiplication operator
     * @param scalar input scalar
     * @param v input vector
     * @return Vec result of scalar multiplication
     */
    inline Vec operator*(double scalar, const Vec& v) { return v * scalar; }


    /** @brief Scalar addition operator
     * @param scalar input scalar
     * @param v input vector
     * @return Vec result of scalar addition
     */
    inline Vec operator+(double scalar, const Vec& v) { return v + scalar; }


    // ============================================================
    // Generic conversion functions
    // ============================================================


    /**
    * @brief Converts sketchParams to a Python object
    * @param sp input sketchParams
    * @return PyObject* Python object
    */
    inline PyObject* sketchParamsToPython(const SketchParams& sp) {
        PyObject* tuple = PyTuple_New(3);
        PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(sp.scale));
        PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(sp.length));
        PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(sp.randomness));

        return tuple;
    }



    /**
    * @brief Converts a Clim to a Python tuple
    * @param c input Clim
    * @return PyObject* Python tuple
    */
    inline PyObject* climToTuple(const Clim& c) {
        PyObject* t = PyTuple_New(2);
        PyTuple_SetItem(t, 0, PyFloat_FromDouble(c.vmin));
        PyTuple_SetItem(t, 1, PyFloat_FromDouble(c.vmax));
        return t;
    }


    /**
    * @brief Converts a XY to a Python tuple
    * @param xy input XY
    * @return PyObject* Python tuple
    */
    inline PyObject* xyToTuple(const XY& xy) {
        PyObject* t = PyTuple_New(2);
        PyTuple_SetItem(t, 0, PyFloat_FromDouble(xy.x));
        PyTuple_SetItem(t, 1, PyFloat_FromDouble(xy.y));
        return t;
    }

    /**
    * @brief Converts a Position to a Python tuple
    * @param p input Position
    * @return PyObject* Python tuple
    */
    inline PyObject* positionToTuple(const Position& p) {
        PyObject* t = PyTuple_New(2);
        PyTuple_SetItem(t, 0, PyFloat_FromDouble(p.x));
        PyTuple_SetItem(t, 1, PyFloat_FromDouble(p.y));
        return t;
    }

    

    

}