#pragma once

// =============================================================================
// Figure.h - C++ wrapper for matplotlib.figure.Figure
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 07/06/2024
// =============================================================================

#include "Axes.h"
#include "Interpreter.h"
#include "PyPtr.h"

#include <vector>

namespace matplotlibcpp {

    class Figure
    {
    private:
        PyPtr fig_;
    public:
        explicit Figure(PyObject* fig) : fig_(fig) {}

        void suptitle(const std::string& title) {
            PyObject_CallMethod(fig_.get(), "suptitle", "s", title.c_str());
        }

        void save(const std::string& filename, const int dpi=0) {
            if(dpi > 0)
                PyObject_CallMethod(fig_.get(), "savefig", "si", filename.c_str(), dpi);
            else
                PyObject_CallMethod(fig_.get(), "savefig", "s", filename.c_str());
        }


        void tight_layout() {
            PyObject_CallMethod(fig_.get(), "tight_layout", nullptr);
        }

        void clf() {
            PyObject_CallMethod(fig_.get(), "clf", nullptr);
        }
        
    };


}


