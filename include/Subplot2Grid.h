#pragma once
// =============================================================================
// Subplot2Grid.h - C++ wrapper for matplotlib.pyplot.subplot2grid
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 10/06/2024
// =============================================================================

#include "Interpreter.h"
#include "PyPtr.h"
#include "NumpyUtils.h"
#include "Configs.h"
#include "Helper.h"
#include "Detail.h"

#include <string>
#include <vector>

namespace matplotlibcpp {

    class Subplot2Grid
    {
        
    private:

        PyPtr s2g_;

    public:
        explicit Subplot2Grid(PyObject* s2g) : s2g_(s2g) {}

        PyObject* get_subplot2grid() const { return s2g_.get(); }


        /**
        * @brief Plots a line graph.
        * @param config plot configuration
        * @throws std::runtime_error if plot fails
        */
        void plot(const PlotConfig& config) {
            detail::plotImpl(s2g_.get(), config);
        }

        void grid(bool flag = true) {
            PyObject_CallMethod(s2g_.get(), "grid", "O", flag ? Py_True : Py_False);
        }

        void set_title(const std::string& title) {
            PyObject_CallMethod(s2g_.get(), "set_title", "s", title.c_str());
        }

        void set_xlabel(const std::string& label) {
            PyObject_CallMethod(s2g_.get(), "set_xlabel", "s", label.c_str());
        }

        void set_ylabel(const std::string& label) {
            PyObject_CallMethod(s2g_.get(), "set_ylabel", "s", label.c_str());
        }

        void set_xlim(double left, double right) {
            PyObject_CallMethod(s2g_.get(), "set_xlim", "dd", left, right);
        }

        void set_ylim(double bottom, double top) {
            PyObject_CallMethod(s2g_.get(), "set_ylim", "dd", bottom, top);
        }

        void set_aspect(const std::string& aspect) {
            PyObject_CallMethod(s2g_.get(), "set_aspect", "s", aspect.c_str());
        }


        /**
         * @brief Plots a line graph.
         * @param config plot configuration
         * @throws std::runtime_error if plot fails
         */
        void errorbar(const ErrorbarConfig& config) {
            detail::errorbarImpl(s2g_.get(), config);
        }


        void scatter(const ScatterConfig& config) {
            
            PyPtr xarray(toNumpy(config.x));
            PyPtr yarray(toNumpy(config.y));

            PyPtr args(PyTuple_New(2));
            PyTuple_SetItem(args.get(), 0, xarray.get());
            PyTuple_SetItem(args.get(), 1, yarray.get());

            PyPtr kwargs(PyDict_New());



        
        }


        void step(const std::vector<double>& x, const std::vector<double>& y, const std::string& fmt = "b") {
            
            PyPtr xarray(toNumpy(x));
            PyPtr yarray(toNumpy(y));
            
            PyObject_CallMethod(s2g_.get(), "step", "OOs", xarray.get(), yarray.get(), fmt.c_str());
            
        }



    };

}