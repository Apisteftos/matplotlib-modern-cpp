#pragma once

// =============================================================================
// Figure.h - C++ wrapper for matplotlib.figure.Figure
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 07/06/2024
// =============================================================================


#include "Interpreter.h"
#include "PyPtr.h"
#include "Configs.h"
#include "Detail.h"

#include <vector>

namespace matplotlibcpp {

    class Figure
    {
    private:
        PyPtr fig_;
    public:
        explicit Figure(PyObject* fig) : fig_(fig) {}

        PyObject* get_figure() const { return fig_.get(); }

        /**
        * @brief Sets the suptitle.
        * @param config suptitle configuration
        * @throws std::runtime_error if suptitle fails
        */
        void suptitle(const SupTitleConfig& config) {
            detail::suptitleImpl(fig_.get(), config);
        }

        void savefig(const std::string& filename, const int dpi=0) {
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


