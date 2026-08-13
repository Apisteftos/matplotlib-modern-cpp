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
     * @brief Extracts the current Python exception message as a std::string.
     *        Clears the Python error state afterward.
     * @return the exception text, or empty string if no error is set
     */
    inline std::string fetchPythonError() {
        if (!PyErr_Occurred()) {
            return "";
        }

        PyObject *type = nullptr, *value = nullptr, *traceback = nullptr;
        PyErr_Fetch(&type, &value, &traceback);
        PyErr_NormalizeException(&type, &value, &traceback);

        std::string msg;
        if (value) {
            PyPtr strObj(PyObject_Str(value));
            if (strObj.get()) {
                const char* cstr = PyUnicode_AsUTF8(strObj.get());
                if (cstr) msg = cstr;
            }
        }

        Py_XDECREF(type);
        Py_XDECREF(value);
        Py_XDECREF(traceback);
        PyErr_Clear();

        return msg;
    }

    /**
     * @brief Checks a PyObject* result and throws if null.
     * @param res result from PyObject_Call
     * @param funcName name of the Python function called (for error message)
     * @throws std::runtime_error with the underlying Python error message if res is nullptr
     */
    inline void checkResult(PyObject* res, const char* funcName) {
        if (!res) {
            std::string errorMsg = std::string("Call to ") + funcName + "() failed";
            std::string pyError = fetchPythonError();
            if (!pyError.empty()) {
                errorMsg += ": " + pyError;
            }
            throw std::runtime_error(errorMsg);
        }
    }

    /**
    * @brief Check if PyPlot returns a valid object
    * @param obj object returned by PyPlot
    * @param attrName name of the attribute to check
    * @throws std::runtime_error with the underlying Python error message if obj is nullptr
    */
    inline void checkAttr(PyObject* obj, const char* attrName) {
        if (!obj) {
            std::string errorMsg = std::string("Failed to get ") + attrName + " function";
            std::string pyError = fetchPythonError();
            if (!pyError.empty()) {
                errorMsg += ": " + pyError;
            }
            throw std::runtime_error(errorMsg);
        }
    }

} // namespace matplotlibcpp