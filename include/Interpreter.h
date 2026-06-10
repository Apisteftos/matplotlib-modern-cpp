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




} // namespace matplotlibcpp





