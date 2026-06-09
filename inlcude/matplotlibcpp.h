#pragma once

#include "PyPtr.h"

#include <Python.h>
#include <stdexcept>
#include <string>
#include <vector>

#include <numpy/arrayobject.h>


namespace matplotlibcpp {


// ============================================================
// Interpreter — singleton
// Initializes Python and imports matplotlib modules once
// ============================================================

/**
 * @brief Manages the Python interpreter lifecycle via RAII.
 *
 * Initializes the interpreter on construction and finalizes it on destruction,
 * ensuring resources are always released even if exceptions occur.
 *
 * Implemented as a Meyers' Singleton — only one interpreter instance
 * may exist per process (Python limitation).
 *
 * @note Not copyable or movable.
 */
class Interpreter {

public: 

    static Interpreter& getInstance() {
        static Interpreter instance;
        return instance;
    }


    PyObject* getPyplot() const { return pyplot_; }
    PyObject* getMatplotlib() const { return matplotlib_; }
    PyObject* getCM() const { return cm_; }
    PyObject* getPylab() const { return pylab_; }



private: 

    PyObject* pyplot_ = nullptr; 
    PyObject* matplotlib_ = nullptr; 
    PyObject* cm_ = nullptr; 
    PyObject* pylab_ = nullptr;


    void* initNumpy() {
        import_array();  
        return nullptr;
    }
    

    /**
     * @brief Initializes the Python interpreter and imports necessary modules.
     * @throws std::runtime_error if any import fails.
     */
    Interpreter() { 

        Py_Initialize();

        initNumpy();  // initializes numpy C API


        pyplot_ = PyImport_ImportModule("matplotlib.pyplot");
        if (!pyplot_) throw std::runtime_error("Failed to import matplotlib.pyplot module.");

        matplotlib_ = PyImport_ImportModule("matplotlib");
        if (!matplotlib_) throw std::runtime_error("Failed to import matplotlib module.");

        cm_ = PyImport_ImportModule("matplotlib.cm");
        if (!cm_) throw std::runtime_error("Failed to import matplotlib.cm module.");

        pylab_ = PyImport_ImportModule("matplotlib.pylab");
        if (!pylab_) throw std::runtime_error("Failed to import matplotlib.pylab module.");


    }

    Interpreter(const Interpreter&) = delete;
    Interpreter& operator=(const Interpreter&) = delete;


    ~Interpreter() {
        Py_XDECREF(pyplot_);
        Py_XDECREF(matplotlib_);
        Py_XDECREF(cm_);
        Py_XDECREF(pylab_);
        Py_Finalize();
    }
    

};



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

    return array;
}



// ============================================================
// Free functions - pyplot wrappers
// ============================================================

/**
 * @brief Shows the plots.
 * @param block if true, waits for user input.
 */
inline void show( bool block = true)
{
    Interpreter::getInstance(); 

    PyPtr args(PyTuple_New(0));

    PyObject* show = PyObject_GetAttrString(
        Interpreter::getInstance().getPyplot(), "show");
    if (!show) throw std::runtime_error("Failed to get show function");

    PyPtr res;
    if(block)
    {
        res.reset(PyObject_Call(show, args.get(), nullptr));
    }
    else
    {
        PyPtr kwargs(PyDict_New());
        PyDict_SetItemString(kwargs.get(), "block", Py_False);
        res.reset(PyObject_Call(show, args.get(), kwargs.get()));
      
    }

    Py_XDECREF(show); 

    if (!res) throw std::runtime_error("Call to show() failed.");

}

//TODO: add more parameters to plot


/**
 * @brief Plots a line graph.
 * @param x x coordinates
 * @param y y coordinates
 * @param format format string
 */
inline void plot(const std::vector<double>& x, 
                 const std::vector<double>& y, 
                 const std::string& fmt = "b") 
{
    Interpreter::getInstance(); 

    PyPtr args(PyTuple_New(3));
    PyPtr kwargs(PyDict_New());

    PyTuple_SetItem(args.get(), 0, toNumpy(x));
    PyTuple_SetItem(args.get(), 1, toNumpy(y));
    PyTuple_SetItem(args.get(), 2, PyUnicode_FromString(fmt.c_str()));
    
    PyDict_SetItemString(kwargs.get(), "format", PyUnicode_FromString(fmt.c_str()));
    

    PyPtr plot(PyObject_GetAttrString(
        Interpreter::getInstance().getPyplot(), "plot"));
    if (!plot) throw std::runtime_error("Failed to get plot function");

    PyPtr res(PyObject_Call(plot.get(), args.get(), nullptr));
    if (!res) throw std::runtime_error("Call to plot() failed.");
}



/**
 * @brief Calls tight_layout() function.
 */
inline void tight_layout() {
    Interpreter::getInstance();

    PyPtr args(PyTuple_New(0));

    PyPtr tight_layout(PyObject_GetAttrString(
        Interpreter::getInstance().getPyplot(), "tight_layout"));
    if (!tight_layout) throw std::runtime_error("Failed to get tight_layout function"); 

    PyPtr res(PyObject_Call(tight_layout.get(), args.get(), nullptr));
    if (!res) throw std::runtime_error("Call to tight_layout() failed.");
}




} // namespace matplotlibcpp





