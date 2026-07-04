#pragma once

// =============================================================================
// detail.h - internal shared implementation between Axes and Pyplot
// Modern C++23 matplotlib wrapper built on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 16/06/2024
// =============================================================================

#include "Interpreter.h"
#include "PyPtr.h"
#include "NumpyUtils.h"
#include "Configs.h"
#include "Helper.h"


namespace matplotlibcpp {

    namespace detail {


        /**
        * @brief Applies kwargs to plot() function        
        * @param kwargs kwargs dictionary        
        * @param config kwargs config
        */
        template<typename T>
        inline void kwargsImpl(PyObject* kwargs, const T& config)  {

            if (config.color)
                PyDict_SetItemString(kwargs, "color",
                    PyUnicode_FromString(config.color->c_str()));
            if (config.label)
                PyDict_SetItemString(kwargs, "label",
                    PyUnicode_FromString(config.label->c_str()));
            if (config.alpha)
                PyDict_SetItemString(kwargs, "alpha",
                    PyFloat_FromDouble(*config.alpha));
            if (config.linewidth)
                PyDict_SetItemString(kwargs, "linewidth",
                    PyFloat_FromDouble(*config.linewidth));
            if (config.linestyle)
                PyDict_SetItemString(kwargs, "linestyle",
                    PyUnicode_FromString(config.linestyle->c_str()));
            if (config.marker)
                PyDict_SetItemString(kwargs, "marker",
                    PyUnicode_FromString(config.marker->c_str()));
            if (config.markersize)
                PyDict_SetItemString(kwargs, "markersize",
                    PyFloat_FromDouble(*config.markersize));
            if (config.markerfacecolor)
                PyDict_SetItemString(kwargs, "markerfacecolor",
                    PyUnicode_FromString(config.markerfacecolor->c_str()));
            if (config.markeredgecolor)
                PyDict_SetItemString(kwargs, "markeredgecolor",
                    PyUnicode_FromString(config.markeredgecolor->c_str()));
            if (config.markeredgewidth)
                PyDict_SetItemString(kwargs, "markeredgewidth",
                    PyFloat_FromDouble(*config.markeredgewidth));
            if (config.drawstyle)
                PyDict_SetItemString(kwargs, "drawstyle",
                    PyUnicode_FromString(config.drawstyle->c_str()));
            if (config.fillstyle)
                PyDict_SetItemString(kwargs, "fillstyle",
                    PyUnicode_FromString(config.fillstyle->c_str()));
        }

        /**
        * @brief Shared implementation of fill() function
        * @param pyObj axes object
        * @param config fill configuration
        * @throws std::runtime_error if fill fails
        */
        template<typename T>
        inline void kwardsPolygonImpl(PyObject* pyObj, const T& config) {

            if (config.color)
                PyDict_SetItemString(pyObj, "color",
                    PyUnicode_FromString(config.color->c_str()));
            if (config.facecolor)
                PyDict_SetItemString(pyObj, "facecolor",
                    PyUnicode_FromString(config.facecolor->c_str()));
            if (config.edgecolor)
                PyDict_SetItemString(pyObj, "edgecolor",
                    PyUnicode_FromString(config.edgecolor->c_str()));
            if (config.label)
                PyDict_SetItemString(pyObj, "label",
                    PyUnicode_FromString(config.label->c_str()));
            if (config.alpha)
                PyDict_SetItemString(pyObj, "alpha",
                    PyFloat_FromDouble(*config.alpha));
            if (config.linewidth)
                PyDict_SetItemString(pyObj, "linewidth",
                    PyFloat_FromDouble(*config.linewidth));
            if (config.linestyle)
                PyDict_SetItemString(pyObj, "linestyle",
                    PyUnicode_FromString(config.linestyle->c_str()));
            if (config.hatch)
                PyDict_SetItemString(pyObj, "hatch",
                    PyUnicode_FromString(config.hatch->c_str()));
            if (config.fill)
                PyDict_SetItemString(pyObj, "fill",
                    *config.fill ? Py_True : Py_False);
            if (config.zorder)
                PyDict_SetItemString(pyObj, "zorder",
                    PyFloat_FromDouble(*config.zorder));    

        }

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

            kwargsImpl(kwargs.get(), config);

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
            
            kwargsImpl(kwargs.get(), config);

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


        /**
        * @brief Plots a line graph.
        * @param config plot configuration
        * @throws std::runtime_error if plot fails
        */
        inline void legendImpl(PyObject* pyObj, const LegendConfig& config ) {

            PyPtr args(PyTuple_New(0));
            PyPtr kwargs(PyDict_New());
            
            if (config.labels.has_value()) {
                PyDict_SetItemString(kwargs.get(), "labels",
                    toStringList(*config.labels));
            }

            if (config.ncol.has_value()) {
                PyDict_SetItemString(kwargs.get(), "ncol",
                    PyLong_FromLong(config.ncol.value()));
            }
            if (config.reverse.has_value()) {
                PyDict_SetItemString(kwargs.get(), "reverse",
                    *config.reverse ? Py_True : Py_False);
            }


            PyPtr legend(PyObject_GetAttrString(pyObj, "legend"));
            checkAttr(legend.get(), "legend");
            
            PyPtr res(PyObject_Call(legend.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "legend");
        std::optional<std::string> color = std::nullopt;

            
        }


        /**
         * @brief Sets the grid on or off.
         * @param config grid configuration
         * @throws std::runtime_error if grid fails
         */
        inline void gridImpl(PyObject* pyObj, const GridConfig& config) {

            PyPtr args(PyTuple_New(0));
            PyPtr kwargs(PyDict_New());
            
            if (config.visible.has_value()) {
                PyDict_SetItemString(kwargs.get(), "visible",
                    config.visible.value() ? Py_True : Py_False);
            }

            if (config.which.has_value()) {
                PyDict_SetItemString(kwargs.get(), "which",
                    PyUnicode_FromString(config.which->c_str()));
            }
            if (config.axis.has_value()) {
                PyDict_SetItemString(kwargs.get(), "axis",
                    PyUnicode_FromString(config.axis->c_str()));
            }
            
            kwargsImpl(kwargs.get(), config);


            PyPtr grid(PyObject_GetAttrString(pyObj, "grid"));
            checkAttr(grid.get(), "grid");
            
            PyPtr res(PyObject_Call(grid.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "grid");

        }

        /**
         * @brief Plots a step graph.
         * @param config step configuration
         * @throws std::runtime_error if step fails
         */
        inline void loglogImpl(PyObject* pyObj, const LogLogConfig& config) {

            PyPtr args(PyTuple_New(3));
            PyTuple_SetItem(args.get(), 0, toNumpy(config.x));
            PyTuple_SetItem(args.get(), 1, toNumpy(config.y));
            PyTuple_SetItem(args.get(), 2, PyUnicode_FromString(config.fmt.value().c_str()));

            PyPtr kwargs(PyDict_New());
            
          
            PyDict_SetItemString(kwargs.get(), "base",PyFloat_FromDouble(config.base));
            
            if (!config.nonpositive.empty()) {
                PyDict_SetItemString(kwargs.get(), "nonpositive",
                    PyUnicode_FromString(config.nonpositive.c_str()));
            }
            if (config.subs.has_value()) {
                PyDict_SetItemString(kwargs.get(), "subs",
                    toSubs(*config.subs));
            }

            kwargsImpl(kwargs.get(), config);

            PyPtr loglog(PyObject_GetAttrString(pyObj, "loglog"));
            checkAttr(loglog.get(), "loglog");

            PyPtr res(PyObject_Call(loglog.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "loglog");
            

        }

        /**
         * @brief Plots a step graph.
         * @param config step configuration
         * @throws std::runtime_error if step fails
         */
        inline void semilogxImpl(PyObject* pyObj, const SemiLogxConfig& config) {

            PyPtr args(PyTuple_New(3));
            PyTuple_SetItem(args.get(), 0, toNumpy(config.x));
            PyTuple_SetItem(args.get(), 1, toNumpy(config.y));
            PyTuple_SetItem(args.get(), 2, PyUnicode_FromString(config.fmt.value().c_str()));

            PyPtr kwargs(PyDict_New());

            PyDict_SetItemString(kwargs.get(), "base",PyFloat_FromDouble(config.base));

            
            if (!config.nonpositive.empty()) {
                PyDict_SetItemString(kwargs.get(), "nonpositive",
                    PyUnicode_FromString(config.nonpositive.c_str()));
            }
            if (config.subs.has_value()) {
                PyDict_SetItemString(kwargs.get(), "subs",
                    toSubs(*config.subs));
            }

            kwargsImpl(kwargs.get(), config);

            PyPtr semilogx(PyObject_GetAttrString(pyObj, "semilogx"));
            checkAttr(semilogx.get(), "semilogx");

            PyPtr res(PyObject_Call(semilogx.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "semilogx");


        }


        /**
         * @brief Plots a step graph.
         * @param config step configuration
         * @throws std::runtime_error if step fails 
         */
        inline void semilogyImpl(PyObject* pyObj, const SemiLogyConfig& config) {

            PyPtr args(PyTuple_New(3));
            PyTuple_SetItem(args.get(), 0, toNumpy(config.x));
            PyTuple_SetItem(args.get(), 1, toNumpy(config.y));
            PyTuple_SetItem(args.get(), 2, PyUnicode_FromString(config.fmt.value().c_str()));

            PyPtr kwargs(PyDict_New());
            
            PyDict_SetItemString(kwargs.get(), "base",PyFloat_FromDouble(config.base));
            
            if (!config.nonpositive.empty()) {
                PyDict_SetItemString(kwargs.get(), "nonpositive",
                    PyUnicode_FromString(config.nonpositive.c_str()));
            }
            if (config.subs.has_value()) {
                PyDict_SetItemString(kwargs.get(), "subs",
                    toSubs(*config.subs));
            }

            kwargsImpl(kwargs.get(), config);

            PyPtr semilogy(PyObject_GetAttrString(pyObj, "semilogy"));
            checkAttr(semilogy.get(), "semilogy");

            PyPtr res(PyObject_Call(semilogy.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "semilogy");

        }


        /**
        * @brief Plots a step graph.
        * @param config step configuration
        * @throws std::runtime_error if step fails  
        */
        inline void fillImpl(PyObject* pyObj, const FillConfig& config) {   

            PyPtr args(PyTuple_New(2));
            PyTuple_SetItem(args.get(), 0, toNumpy(config.x));
            PyTuple_SetItem(args.get(), 1, toNumpy(config.y));
        

            PyPtr kwargs(PyDict_New());
            
            kwardsPolygonImpl(kwargs.get(), config);


            PyPtr fill(PyObject_GetAttrString(pyObj, "fill"));
            checkAttr(fill.get(), "fill");
            
            PyPtr res(PyObject_Call(fill.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "fill");


        }

        /**
        * @brief Plots a step graph.
        * @param config step configuration
        * @throws std::runtime_error if step fails  
        */
        inline void fillBetweenImpl(PyObject* pyObj, const FillBetweenConfig& config) {

            PyPtr args(PyTuple_New(3));
            PyTuple_SetItem(args.get(), 0, toNumpy(config.x));
            PyTuple_SetItem(args.get(), 1, dataValueToNumpy(config.y1));
            PyTuple_SetItem(args.get(), 2, dataValueToNumpy(config.y2));

            PyPtr kwargs(PyDict_New());
            
            if (config.fmt.has_value()) {
                PyDict_SetItemString(kwargs.get(), "fmt",
                    PyUnicode_FromString(config.fmt.value().c_str()));
            }   
            
            kwargsImpl(kwargs.get(), config);

            PyPtr fill(PyObject_GetAttrString(pyObj, "fill_between"));
            checkAttr(fill.get(), "fill_between");
            
            PyPtr res(PyObject_Call(fill.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "fill_between");


        }

        /**
        * @brief Plots a step graph.
        * @param config step configuration
        * @throws std::runtime_error if step fails  
        */
        inline void fillBetweenxImpl(PyObject* pyObj, const FillBetweenxConfig& config) {

            PyPtr args(PyTuple_New(3));
            PyTuple_SetItem(args.get(), 0, toNumpy(config.y));
            PyTuple_SetItem(args.get(), 1, dataValueToNumpy(config.x1));
            PyTuple_SetItem(args.get(), 2, dataValueToNumpy(config.x2));

            PyPtr kwargs(PyDict_New());
            
            if (config.fmt.has_value()) {
                PyDict_SetItemString(kwargs.get(), "fmt",
                    PyUnicode_FromString(config.fmt.value().c_str()));
            }   
            
            kwargsImpl(kwargs.get(), config);
           
            PyDict_SetItemString(kwargs.get(), "interpolate",
                    config.interpolate ? Py_True : Py_False);
            
            PyPtr fill(PyObject_GetAttrString(pyObj, "fill_betweenx"));
            checkAttr(fill.get(), "fill_betweenx");
            
            PyPtr res(PyObject_Call(fill.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "fill_betweenx");
            

        }


        /**
         * @brief Implementation for plotting error bars.
         * @param pyObj the Python object representing the axes
         * @param config the error bar configuration
         * @throws std::runtime_error if error bar fails
         */
        inline void errorbarImpl(PyObject* pyObj, const ErrorbarConfig& config) {

            PyPtr args(PyTuple_New(2));
            PyTuple_SetItem(args.get(), 0, dataValueToNumpy(config.x));
            PyTuple_SetItem(args.get(), 1, dataValueToNumpy(config.y));
            

           

            PyPtr kwargs(PyDict_New());
            
            if (config.fmt.has_value())
                PyDict_SetItemString(kwargs.get(), "fmt",
                    PyUnicode_FromString(config.fmt.value().c_str()));
            if (config.yerr.has_value())
                PyDict_SetItemString(kwargs.get(), "yerr",
                    errorValueToNumpy(config.yerr.value()));
            if (config.xerr.has_value())
                PyDict_SetItemString(kwargs.get(), "xerr",
                    errorValueToNumpy(config.xerr.value()));
            if (config.ecolor.has_value())
                PyDict_SetItemString(kwargs.get(), "ecolor",
                    PyUnicode_FromString(config.ecolor.value().c_str()));
            if (config.elinewidth.has_value())
                PyDict_SetItemString(kwargs.get(), "elinewidth",
                    PyFloat_FromDouble(config.elinewidth.value()));
            if (config.capsize.has_value())
                PyDict_SetItemString(kwargs.get(), "capsize",
                    PyFloat_FromDouble(config.capsize.value()));   
            if (config.capthick.has_value())
                PyDict_SetItemString(kwargs.get(), "capthick",
                    PyFloat_FromDouble(config.capthick.value()));
            if (config.barsabove.has_value())
                PyDict_SetItemString(kwargs.get(), "barsabove",
                    config.barsabove.value() ? Py_True : Py_False);
            if (config.lolims.has_value())
                PyDict_SetItemString(kwargs.get(), "lolims",
                    limValueToPython(config.lolims.value()));
            if (config.uplims.has_value())
                PyDict_SetItemString(kwargs.get(), "uplims",
                    limValueToPython(config.uplims.value()));
            if (config.xlolims.has_value())
                PyDict_SetItemString(kwargs.get(), "xlolims",
                    limValueToPython(config.xlolims.value()));
            if (config.xuplims.has_value())
                PyDict_SetItemString(kwargs.get(), "xuplims",
                    limValueToPython(config.xuplims.value()));
            if (config.errorevery.has_value())
                PyDict_SetItemString(kwargs.get(), "errorevery",
                    errorEveryValueToPython(config.errorevery.value()));

            // rest of kwargs
            kwargsImpl(kwargs.get(), config);

            PyPtr errorbar(PyObject_GetAttrString(pyObj, "errorbar"));
            checkAttr(errorbar.get(), "errorbar");

            // print kwargs
            //PyObject_Print(kwargs.get(), stdout, 0);
            
            PyPtr res(PyObject_Call(errorbar.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "errorbar");


        }

        /**
        * @brief Plots a line graph.
        * @param config plot configuration
        * @throws std::runtime_error if plot fails
        */
        inline void scatterImpl(PyObject* pyObj, const ScatterConfig& config) {

            PyPtr args(PyTuple_New(2));
            PyTuple_SetItem(args.get(), 0, toNumpy(config.x));
            PyTuple_SetItem(args.get(), 1, toNumpy(config.y));

            PyPtr kwargs(PyDict_New());

            if (config.fmt.has_value()) {
                PyDict_SetItemString(kwargs.get(), "fmt",
                    PyUnicode_FromString(config.fmt.value().c_str()));
            }

            kwargsImpl(kwargs.get(), config);

            PyPtr scatter(PyObject_GetAttrString(pyObj, "scatter"));
            checkAttr(scatter.get(), "scatter");

            PyPtr res(PyObject_Call(scatter.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "scatter");
        }


    } // namespace detail
} // namespace matplotlibcpp