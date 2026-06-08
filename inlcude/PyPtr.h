#pragma once

// =============================================================================
// PyPtr.h - Smart pointer for PyObject* with automatic reference counting
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 07/06/2024
// =============================================================================


#include <Python.h>
#include <memory>

namespace matplotlibcpp{

    struct PyDecRef {
    void operator()(PyObject* obj) const {
        if (obj) Py_DECREF(obj);
    }
    }; 

    using PyPtr = std::unique_ptr<PyObject, PyDecRef>;
}

