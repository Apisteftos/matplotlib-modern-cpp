#pragma once
// =============================================================================
// helper.h - C++ wrapper for matplotlib.pyplot.helper
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 14/06/2024
// =============================================================================

#include "Interpreter.h"
#include "PyPtr.h"

#include <future>
#include <string>
#include <vector>
#include <memory.h>

namespace matplotlibcpp {



    // ============================================================
    // Helper functions
    // ============================================================

    /**
     * @brief Checks a PyObject* result and throws if null.
     * @param res result from PyObject_Call
     * @param funcName name of the Python function called (for error message)
     * @throws std::runtime_error if res is nullptr
     */
    inline void checkResult(PyObject* res, const char* funcName) {
        if (!res) {
            PyErr_Print();
            throw std::runtime_error(std::string("Call to ") + funcName + "() failed");
        }
    }


} // namespace matplotlibcpp