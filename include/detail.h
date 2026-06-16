#pragma once

// =============================================================================
// detail.h - internal shared implementation between Axes and Pyplot
// Modern C++23 matplotlib wrapper built on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 16/06/2024
// =============================================================================

#include "Interpreter.h"
#include "PyPtr.h"
#include "numpy_utils.h"
#include "configs.h"
#include "helper.h"


namespace matplotlibcpp {

    namespace detail {



        /**
        * @brief Shared implementation of plot() function
        * @param pyObj axes object
        * @param config plot configuration
        * @throws std::runtime_error if plot fails
        */
        inline void plotImpl(PyObject* pyObj, const PlotConfig& config) {

            PyPtr args;
            if (config.x.has_value()) {
                if (config.fmt.has_value()) {
                    args.reset(PyTuple_New(3));
                    PyTuple_SetItem(args.get(), 0, dataValueToNumpy(config.x.value()));
                    PyTuple_SetItem(args.get(), 1, dataValueToNumpy(config.y));
                    PyTuple_SetItem(args.get(), 2,
                        PyUnicode_FromString(config.fmt.value().c_str()));
                } else {
                    args.reset(PyTuple_New(2));
                    PyTuple_SetItem(args.get(), 0, dataValueToNumpy(config.x.value()));
                    PyTuple_SetItem(args.get(), 1, dataValueToNumpy(config.y));
                }
            } else {
                if (config.fmt.has_value()) {
                    args.reset(PyTuple_New(2));
                    PyTuple_SetItem(args.get(), 0, dataValueToNumpy(config.y));
                    PyTuple_SetItem(args.get(), 1,
                        PyUnicode_FromString(config.fmt.value().c_str()));
                } else {
                    args.reset(PyTuple_New(1));
                    PyTuple_SetItem(args.get(), 0, dataValueToNumpy(config.y));
                }
            }

            PyPtr kwargs(PyDict_New());

            if (config.label)
                PyDict_SetItemString(kwargs.get(), "label",
                    PyUnicode_FromString(config.label->c_str()));
            if (config.color)
                PyDict_SetItemString(kwargs.get(), "color",
                    PyUnicode_FromString(config.color->c_str()));
            if (config.alpha)
                PyDict_SetItemString(kwargs.get(), "alpha",
                    PyFloat_FromDouble(*config.alpha));
            if (config.linewidth)
                PyDict_SetItemString(kwargs.get(), "linewidth",
                    PyFloat_FromDouble(*config.linewidth));
            if (config.marker)
                PyDict_SetItemString(kwargs.get(), "marker",
                    PyUnicode_FromString(config.marker->c_str()));
            if (config.markersize)
                PyDict_SetItemString(kwargs.get(), "markersize",
                    PyFloat_FromDouble(*config.markersize));
            if (config.linestyle)
                PyDict_SetItemString(kwargs.get(), "linestyle",
                    PyUnicode_FromString(config.linestyle->c_str()));

            PyDict_SetItemString(kwargs.get(), "scalex",
                config.scalex ? Py_True : Py_False);
            PyDict_SetItemString(kwargs.get(), "scaley",
                config.scaley ? Py_True : Py_False);

            PyPtr fn(PyObject_GetAttrString(pyObj, "plot"));
            checkAttr(fn.get(), "plot");

            PyPtr res(PyObject_Call(fn.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "plot");



        }



        inline void stepImpl(PyObject* pyObj, const StepConfig& config) {


            PyPtr args(PyTuple_New(2));
            PyTuple_SetItem(args.get(), 0, toNumpy(config.x));
            PyTuple_SetItem(args.get(), 1, toNumpy(config.y));

                
            PyPtr kwargs(PyDict_New());
            
            if (config.fmt.has_value()) {
                PyDict_SetItemString(kwargs.get(), "fmt",
                    PyUnicode_FromString(config.fmt.value().c_str()));
            }
            if (config.where.has_value()) {
                PyDict_SetItemString(kwargs.get(), "where",
                    PyUnicode_FromString(config.where.value().c_str()));
            }
            if (config.label.has_value()) {
                PyDict_SetItemString(kwargs.get(), "label",
                    PyUnicode_FromString(config.label.value().c_str()));
            }
            if (config.color.has_value()) {
                PyDict_SetItemString(kwargs.get(), "color",
                    PyUnicode_FromString(config.color.value().c_str()));
            }
            if (config.alpha.has_value()) {
                PyDict_SetItemString(kwargs.get(), "alpha",
                    PyFloat_FromDouble(config.alpha.value()));
            }
            if (config.linewidth.has_value()) {
                PyDict_SetItemString(kwargs.get(), "linewidth",
                    PyFloat_FromDouble(config.linewidth.value()));
            }
            if (config.marker.has_value()) {
                PyDict_SetItemString(kwargs.get(), "marker",
                    PyUnicode_FromString(config.marker.value().c_str()));
            }
            if (config.markersize.has_value()) {
                PyDict_SetItemString(kwargs.get(), "markersize",
                    PyFloat_FromDouble(config.markersize.value()));
            }
            if (config.linestyle.has_value()) {
                PyDict_SetItemString(kwargs.get(), "linestyle",
                    PyUnicode_FromString(config.linestyle.value().c_str()));
            }

            PyPtr step(PyObject_GetAttrString(pyObj, "step"));
            checkAttr(step.get(), "step");

            PyPtr res(PyObject_Call(step.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "step");

        }


        /**
        * @brief Plots a line graph.
        * @param config plot configuration
        * @throws std::runtime_error if plot fails
        */
        inline void tickParamsImpl(PyObject* pyObj, const TickParamsConfig& config) {

            PyPtr args(PyTuple_New(0));
            PyPtr kwargs(PyDict_New());

            PyDict_SetItemString(kwargs.get(), "axis",
                PyUnicode_FromString(config.axis.c_str()));
            PyDict_SetItemString(kwargs.get(), "which",
                PyUnicode_FromString(config.which.c_str()));
            PyDict_SetItemString(kwargs.get(), "reset",
                config.reset ? Py_True : Py_False);

            if (config.direction)
                PyDict_SetItemString(kwargs.get(), "direction",
                    PyUnicode_FromString(config.direction->c_str()));

            if (config.length)
                PyDict_SetItemString(kwargs.get(), "length",
                    PyFloat_FromDouble(*config.length));

            if (config.width)
                PyDict_SetItemString(kwargs.get(), "width",
                    PyFloat_FromDouble(*config.width));

            if (config.color)
                PyDict_SetItemString(kwargs.get(), "color",
                    PyUnicode_FromString(config.color->c_str()));

            if (config.pad)
                PyDict_SetItemString(kwargs.get(), "pad",
                    PyFloat_FromDouble(*config.pad));

            if (config.labelsize.has_value()) {
                std::visit([&](const auto& val) {
                    using T = std::decay_t<decltype(val)>;
                    if constexpr (std::is_same_v<T, double>) {
                        PyDict_SetItemString(kwargs.get(), "labelsize",
                            PyFloat_FromDouble(val));
                    } else { 
                        PyDict_SetItemString(kwargs.get(), "labelsize",
                            PyUnicode_FromString(val.c_str()));
                    }
                }, config.labelsize.value());
            }

            if (config.labelcolor)
                PyDict_SetItemString(kwargs.get(), "labelcolor",
                    PyUnicode_FromString(config.labelcolor->c_str()));

            if (config.colors)
                PyDict_SetItemString(kwargs.get(), "colors",
                    PyUnicode_FromString(config.colors->c_str()));

            if (config.labelrotation)
                PyDict_SetItemString(kwargs.get(), "labelrotation",
                    PyFloat_FromDouble(*config.labelrotation));

            if (config.bottom)
                PyDict_SetItemString(kwargs.get(), "bottom",
                    *config.bottom ? Py_True : Py_False);
            if (config.top)
                PyDict_SetItemString(kwargs.get(), "top",
                    *config.top ? Py_True : Py_False);
            if (config.left)
                PyDict_SetItemString(kwargs.get(), "left",
                    *config.left ? Py_True : Py_False);
            if (config.right)
                PyDict_SetItemString(kwargs.get(), "right",
                    *config.right ? Py_True : Py_False);

            if (config.labelbottom)
                PyDict_SetItemString(kwargs.get(), "labelbottom",
                    *config.labelbottom ? Py_True : Py_False);
            if (config.labeltop)
                PyDict_SetItemString(kwargs.get(), "labeltop",
                    *config.labeltop ? Py_True : Py_False);
            if (config.labelleft)
                PyDict_SetItemString(kwargs.get(), "labelleft",
                    *config.labelleft ? Py_True : Py_False);
            if (config.labelright)
                PyDict_SetItemString(kwargs.get(), "labelright",
                    *config.labelright ? Py_True : Py_False);

            if (config.labelrotation)
                PyDict_SetItemString(kwargs.get(), "labelrotation",
                    PyFloat_FromDouble(*config.labelrotation));


            if (config.grid_color)
                PyDict_SetItemString(kwargs.get(), "grid_color",
                    PyUnicode_FromString(config.grid_color->c_str()));

            if (config.grid_alpha)
                PyDict_SetItemString(kwargs.get(), "grid_alpha",
                    PyFloat_FromDouble(*config.grid_alpha));

            if (config.grid_linewidth)
                PyDict_SetItemString(kwargs.get(), "grid_linewidth",
                    PyFloat_FromDouble(*config.grid_linewidth));

            if (config.grid_linestyle)
                PyDict_SetItemString(kwargs.get(), "grid_linestyle",
                    PyUnicode_FromString(config.grid_linestyle->c_str()));

            PyPtr res(PyObject_Call(
                PyObject_GetAttrString(pyObj, "tick_params"), args.get(), kwargs.get()));
            checkResult(res.get(), "tick_params");

        }



        




    } // namespace detail
} // namespace matplotlibcpp