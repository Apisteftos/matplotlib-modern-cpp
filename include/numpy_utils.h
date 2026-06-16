#pragma once

// =============================================================================
// numpy_utils.h - C++ wrapper for matplotlib.pyplot.numpy_utils
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 09/06/2024
// =============================================================================

#include "Interpreter.h"
#include "PyPtr.h"
#include "configs.h"

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
    // toNumpy - converts std::vector to numpy array
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

        PyObject* array = PyArray_SimpleNewFromData(
            1, &size,
            NumpyType<T>::typenum,
            const_cast<T*>(v.data()));

        if (!array) throw std::runtime_error("Failed to create numpy array");

        std::memcpy(PyArray_DATA(reinterpret_cast<PyArrayObject*>(array)),
                v.data(),
                v.size() * sizeof(T));

        return array;
    }


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
    

}