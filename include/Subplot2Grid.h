#pragma once
// =============================================================================
// Subplot2Grid.h - C++ wrapper for matplotlib.pyplot.subplot2grid
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 10/06/2024
// =============================================================================

#include "Interpreter.h"
#include "PyPtr.h"
#include "numpy_utils.h"
#include "configs.h"

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


        void plot(const PlotConfig& config) {

            PyPtr xarray(toNumpy(config.x));
            PyPtr yarray(toNumpy(config.y));
            PyPtr fmt(PyUnicode_FromString(config.fmt.c_str()));

            PyPtr args(PyTuple_New(3));
            PyTuple_SetItem(args.get(), 0, xarray.get());
            PyTuple_SetItem(args.get(), 1, yarray.get());
            PyTuple_SetItem(args.get(), 2, fmt.get());
            
            PyPtr plot(PyObject_GetAttrString(s2g_.get(), "plot"));
            if (!plot) throw std::runtime_error("Failed to get plot function");
            
            PyPtr res(PyObject_Call(plot.get(), args.get(), nullptr));
            if (!res) throw std::runtime_error("Call to plot() failed.");
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



        void errorbar(const ErrorbarConfig& config) {

            PyPtr xarray(dataValueToNumpy(config.x));
            PyPtr yarray(dataValueToNumpy(config.y));

            PyPtr args(PyTuple_New(2));
            PyTuple_SetItem(args.get(), 0, xarray.get());
            PyTuple_SetItem(args.get(), 1, yarray.get());

            PyPtr kwargs(PyDict_New());

        
            if (config.yerr.has_value()) {
                PyPtr yerrarray(errorValueToNumpy(config.yerr.value()));
                PyDict_SetItemString(kwargs.get(), "yerr", yerrarray.get());
            }

        
            if (config.xerr.has_value()) {
                PyPtr xerrarray(errorValueToNumpy(config.xerr.value()));
                PyDict_SetItemString(kwargs.get(), "xerr", xerrarray.get());
            }

            if (!config.fmt.empty())
                PyDict_SetItemString(kwargs.get(), "fmt",
                    PyUnicode_FromString(config.fmt.c_str()));

            if (!config.label.empty())
                PyDict_SetItemString(kwargs.get(), "label",
                    PyUnicode_FromString(config.label.c_str()));

            if (!config.ecolor.empty())
                PyDict_SetItemString(kwargs.get(), "ecolor",
                    PyUnicode_FromString(config.ecolor.c_str()));

            PyDict_SetItemString(kwargs.get(), "alpha",
                PyFloat_FromDouble(config.alpha));
            PyDict_SetItemString(kwargs.get(), "linewidth",
                PyFloat_FromDouble(config.linewidth));
            PyDict_SetItemString(kwargs.get(), "elinewidth",
                PyFloat_FromDouble(config.elinewidth));

            PyPtr fn(PyObject_GetAttrString(s2g_.get(), "errorbar"));
            if (!fn) throw std::runtime_error("Failed to get errorbar function");

            PyPtr res(PyObject_Call(fn.get(), args.get(), kwargs.get()));
            if (!res) throw std::runtime_error("Call to errorbar() failed");
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