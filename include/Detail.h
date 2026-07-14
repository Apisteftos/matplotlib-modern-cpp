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


#include <map>
#include <string>


namespace matplotlibcpp {

    class Axes;
    class Figure;

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
        inline void kwargsPolygonImpl(PyObject* pyObj, const T& config) {

            if (config.color.has_value())
                PyDict_SetItemString(pyObj, "color", 
            PyUnicode_FromString(config.color->c_str()));
            if (config.facecolor.has_value())
                PyDict_SetItemString(pyObj, "facecolor", 
            PyUnicode_FromString(config.facecolor->c_str()));
            if (config.edgecolor.has_value())
                PyDict_SetItemString(pyObj, "edgecolor",
            PyUnicode_FromString(config.edgecolor->c_str()));
            if (config.label.has_value())
                PyDict_SetItemString(pyObj, "label",                
            PyUnicode_FromString(config.label->c_str()));
            if (config.alpha.has_value())
                PyDict_SetItemString(pyObj, "alpha",                
            PyFloat_FromDouble(*config.alpha));
            if (config.linewidth.has_value())
                PyDict_SetItemString(pyObj, "linewidth",
            PyFloat_FromDouble(*config.linewidth));
            if (config.linestyle.has_value())
                PyDict_SetItemString(pyObj, "linestyle",                
            PyUnicode_FromString(config.linestyle->c_str()));
            if (config.hatch.has_value())
                PyDict_SetItemString(pyObj, "hatch",
            PyUnicode_FromString(config.hatch->c_str()));
            if (config.fill.has_value())
                PyDict_SetItemString(pyObj, "fill",                
            *config.fill ? Py_True : Py_False);
            if (config.zorder.has_value())
                PyDict_SetItemString(pyObj, "zorder",
            PyFloat_FromDouble(*config.zorder));
             
        }


        template<typename T>
        inline void kwargsFillBetweenImpl(PyObject* pyObj, const T& config) {

             if (config.alpha.has_value())
                PyDict_SetItemString(pyObj, "alpha",
                    PyFloat_FromDouble(*config.alpha));
            if (config.animated.has_value())
                    PyDict_SetItemString(pyObj, "animated",
                        *config.animated ? Py_True : Py_False);
            if (config.array.has_value())
                PyDict_SetItemString(pyObj, "array",
                    toNumpy(*config.array));
            if (config.clim.has_value()) {
                PyObject* t = climToTuple(*config.clim);
                PyDict_SetItemString(pyObj, "clim", t);
                Py_DECREF(t);
            }
            if (config.clip_on.has_value())
                PyDict_SetItemString(pyObj, "clip_on",
                    *config.clip_on ? Py_True : Py_False);
            if (config.cmap.has_value())
                PyDict_SetItemString(pyObj, "cmap",
                    PyUnicode_FromString(config.cmap.value().c_str()));
            if (config.color.has_value())
                PyDict_SetItemString(pyObj, "color",
                    PyUnicode_FromString(config.color.value().c_str()));
            if (config.edgecolor.has_value())
                PyDict_SetItemString(pyObj, "edgecolor",
                    PyUnicode_FromString(config.edgecolor.value().c_str()));
            if (config.facecolor.has_value())
                PyDict_SetItemString(pyObj, "facecolor",
                    PyUnicode_FromString(config.facecolor.value().c_str()));
            if (config.gid.has_value())
                PyDict_SetItemString(pyObj, "gid",
                    PyUnicode_FromString(config.gid.value().c_str()));
            if (config.hatch.has_value())
                PyDict_SetItemString(pyObj, "hatch",
                    PyUnicode_FromString(config.hatch.value().c_str()));
            if (config.in_layout.has_value())
                PyDict_SetItemString(pyObj, "in_layout",
                    *config.in_layout ? Py_True : Py_False);
            if (config.label.has_value())
                PyDict_SetItemString(pyObj, "label",
                    PyUnicode_FromString(config.label.value().c_str()));
            if (config.linestyle.has_value())
                PyDict_SetItemString(pyObj, "linestyle",
                    PyUnicode_FromString(config.linestyle.value().c_str()));
            if (config.linewidth.has_value())
                PyDict_SetItemString(pyObj, "linewidth",
                    linewidthValueToPython(*config.linewidth));
            if (config.mouseover.has_value())
                PyDict_SetItemString(pyObj, "mouseover",
                    *config.mouseover ? Py_True : Py_False);
            if (config.pickradius.has_value())
                PyDict_SetItemString(pyObj, "pickradius",
                    PyFloat_FromDouble(*config.pickradius));
            if (config.rasterized.has_value())
                PyDict_SetItemString(pyObj, "rasterized",
                    *config.rasterized ? Py_True : Py_False);
            if (config.snap.has_value())
                PyDict_SetItemString(pyObj, "snap",
                    *config.snap ? Py_True : Py_False);
            if (config.url.has_value())
                PyDict_SetItemString(pyObj, "url",
                    PyUnicode_FromString(config.url.value().c_str()));
            if (config.visible.has_value())
                PyDict_SetItemString(pyObj, "visible",
                    *config.visible ? Py_True : Py_False);
            if (config.zorder.has_value())
                PyDict_SetItemString(pyObj, "zorder",
                    PyFloat_FromDouble(*config.zorder));
        }


        /**
        * @brief Shared implementation of bar() and barh() functions
        * @param pyObj axes object
        * @param config bar configuration
        * @throws std::runtime_error if bar fails
        */
        template<typename T>
        inline void kwargsBarImpl(PyObject* pyObj, const T& config) {
            if (config.align.has_value())
                PyDict_SetItemString(pyObj, "align",
                    PyUnicode_FromString(config.align->c_str()));
            if (config.xerr.has_value())
                PyDict_SetItemString(pyObj, "xerr",
                    errorValueToNumpy(*config.xerr));
            if (config.yerr.has_value())
                PyDict_SetItemString(pyObj, "yerr",
                    errorValueToNumpy(*config.yerr));   
            if (config.color.has_value())
                PyDict_SetItemString(pyObj, "color",
                    PyUnicode_FromString(config.color->c_str()));
            if (config.facecolor.has_value())
                PyDict_SetItemString(pyObj, "facecolor",
                    PyUnicode_FromString(config.facecolor->c_str()));
            if (config.edgecolor.has_value())
                PyDict_SetItemString(pyObj, "edgecolor",
                    PyUnicode_FromString(config.edgecolor->c_str()));
            if (config.linewidth.has_value())
                PyDict_SetItemString(pyObj, "linewidth",
                    linewidthValueToPython(*config.linewidth));
            if (config.tick_label.has_value())
                PyDict_SetItemString(pyObj, "tick_label",
                    tickLabelValueToPython(*config.tick_label));
            if (config.label.has_value())
                PyDict_SetItemString(pyObj, "label",
                    PyUnicode_FromString(config.label->c_str()));
            if (config.ecolor.has_value())
                PyDict_SetItemString(pyObj, "ecolor",
                    PyUnicode_FromString(config.ecolor->c_str()));
            if (config.capsize.has_value())
                PyDict_SetItemString(pyObj, "capsize",
                    PyFloat_FromDouble(*config.capsize));
            if (config.log.has_value())
                PyDict_SetItemString(pyObj, "log",
                    *config.log ? Py_True : Py_False);

        }


        /**
         * @brief Shared implementation of rectangle() function
         * @param pyObj axes object
         * @param config rectangle configuration
         * @throws std::runtime_error if rectangle fails
         */
        template<typename T>
        inline void kwargsRectangleImpl(PyObject* pyObj, const T& config) {

            
            if (config.alpha.has_value())
                PyDict_SetItemString(pyObj, "alpha",
                    PyFloat_FromDouble(*config.alpha));
            if (config.animated.has_value())
                PyDict_SetItemString(pyObj, "animated",
                    *config.animated ? Py_True : Py_False);
            if (config.antialiased.has_value())
                PyDict_SetItemString(pyObj, "antialiased",
                    *config.antialiased ? Py_True : Py_False);
            if (config.bounds.has_value()) {
                PyObject* t = boundsToPython(*config.bounds);
                PyDict_SetItemString(pyObj, "bounds", t);
                Py_DECREF(t);
            }
            if (config.capstyle.has_value())
                PyDict_SetItemString(pyObj, "capstyle",
                    PyUnicode_FromString(config.capstyle->c_str()));
            if (config.clip_on.has_value())
                PyDict_SetItemString(pyObj, "clip_on",
                    *config.clip_on ? Py_True : Py_False);
            if (config.edgegapcolor.has_value())
                PyDict_SetItemString(pyObj, "edgegapcolor",
                    PyUnicode_FromString(config.edgegapcolor->c_str()));
            if (config.fill.has_value())
                PyDict_SetItemString(pyObj, "fill",
                    *config.fill ? Py_True : Py_False);
            if (config.gid.has_value())
                PyDict_SetItemString(pyObj, "gid",
                    PyUnicode_FromString(config.gid->c_str()));
            if (config.hatch.has_value())
                PyDict_SetItemString(pyObj, "hatch",
                    PyUnicode_FromString(config.hatch->c_str()));
            if (config.in_layout.has_value())
                PyDict_SetItemString(pyObj, "in_layout",
                    *config.in_layout ? Py_True : Py_False);
            if (config.joinstyle.has_value())
                PyDict_SetItemString(pyObj, "joinstyle",
                    PyUnicode_FromString(config.joinstyle->c_str()));
            if (config.linestyle.has_value())
                PyDict_SetItemString(pyObj, "linestyle",
                    PyUnicode_FromString(config.linestyle->c_str()));
            if (config.mouseover.has_value())
                PyDict_SetItemString(pyObj, "mouseover",
                    *config.mouseover ? Py_True : Py_False);
            if (config.rasterized.has_value())
                PyDict_SetItemString(pyObj, "rasterized",
                    *config.rasterized ? Py_True : Py_False);
            if (config.snap.has_value())
                PyDict_SetItemString(pyObj, "snap",
                    *config.snap ? Py_True : Py_False);
            if (config.url.has_value())
                PyDict_SetItemString(pyObj, "url",
                    PyUnicode_FromString(config.url->c_str()));
            if (config.visible.has_value())
                PyDict_SetItemString(pyObj, "visible",
                    *config.visible ? Py_True : Py_False);
            if (config.xy.has_value())
                PyDict_SetItemString(pyObj, "xy",
                    xyToTuple(config.xy.value()));
            if (config.zorder.has_value())
                PyDict_SetItemString(pyObj, "zorder",                
                    PyFloat_FromDouble(config.zorder.value())); 


        }




        /**
        * @brief Shared implementation of figure() function
        * @param pyObj axes object
        * @param config plot configuration
        * @throws std::runtime_error if plot fails
        */
        template<typename T>
        inline void kwargsFigImpl(PyObject* pyObj, const T& config) {

            if (config.alpha)
                PyDict_SetItemString(pyObj, "alpha",
                    PyFloat_FromDouble(*config.alpha));
            if (config.animated)
                PyDict_SetItemString(pyObj, "animated",
                    *config.animated ? Py_True : Py_False);
            if (config.clip_on)
                PyDict_SetItemString(pyObj, "clip_on",
                    PyUnicode_FromString(config.clip_on->c_str()));
            if (config.dpi)
                PyDict_SetItemString(pyObj, "dpi",
                    PyFloat_FromDouble(*config.dpi));
            if (config.edgecolor)
                PyDict_SetItemString(pyObj, "edgecolor",
                    PyUnicode_FromString(config.edgecolor->c_str()));
            if (config.facecolor)
                PyDict_SetItemString(pyObj, "facecolor",
                    PyUnicode_FromString(config.facecolor->c_str()));
            if (config.figheight)
                PyDict_SetItemString(pyObj, "figheight",
                    PyFloat_FromDouble(*config.figheight));
            if (config.figwidth)
                PyDict_SetItemString(pyObj, "figwidth",
                    PyFloat_FromDouble(*config.figwidth));
            if (config.frameon)
                PyDict_SetItemString(pyObj, "frameon",
                    *config.frameon ? Py_True : Py_False);
            if (config.gid)
                PyDict_SetItemString(pyObj, "gid",
                    PyUnicode_FromString(config.gid->c_str()));
            if (config.mouseover)
                PyDict_SetItemString(pyObj, "mouseover",
                    *config.mouseover ? Py_True : Py_False);
            if (config.rasterized)
                PyDict_SetItemString(pyObj, "rasterized",
                    *config.rasterized ? Py_True : Py_False);
            if (config.url)
                PyDict_SetItemString(pyObj, "url",
                    PyUnicode_FromString(config.url->c_str()));
            if (config.visible)
                PyDict_SetItemString(pyObj, "visible",
                    *config.visible ? Py_True : Py_False);
            if (config.zorder)
                PyDict_SetItemString(pyObj, "zorder",
                    PyFloat_FromDouble(*config.zorder));

        }


        /**
        * @brief Shared implementation of text() function
        * @param pyObj axes object
        * @param config text configuration
        * @throws std::runtime_error if text fails
        */
        template<typename T>
        inline void kwargsTextImpl(PyObject* pyObj, const T& config) {

            if (config.alpha.has_value())
                PyDict_SetItemString(pyObj, "alpha",
                    PyFloat_FromDouble(config.alpha.value()));
            if (config.animated.has_value())
                PyDict_SetItemString(pyObj, "animated",
                    config.animated.value() ? Py_True : Py_False);
            if (config.antialiased.has_value())
                PyDict_SetItemString(pyObj, "antialiased",
                    config.antialiased.value() ? Py_True : Py_False);
            if (config.clip_on.has_value())
                PyDict_SetItemString(pyObj, "clip_on",
                    config.clip_on.value() ? Py_True : Py_False);
            if (config.color.has_value())
                PyDict_SetItemString(pyObj, "color",
                    PyUnicode_FromString(config.color.value().c_str()));
            if (config.fontFamily.has_value())
                PyDict_SetItemString(pyObj, "fontFamily",
                    PyUnicode_FromString(config.fontFamily.value().c_str()));
            if (config.fontSize.has_value())
                PyDict_SetItemString(pyObj, "fontSize",
                    fontSizeValueToPython(config.fontSize.value()));
            if (config.fontStretch.has_value())
                PyDict_SetItemString(pyObj, "fontStretch",
                    fontStretchValueToPython(config.fontStretch.value()));
            if (config.fontStyle.has_value())
                PyDict_SetItemString(pyObj, "fontStyle",
                    PyUnicode_FromString(config.fontStyle.value().c_str()));
            if (config.fontVariant.has_value())
                PyDict_SetItemString(pyObj, "fontVariant",
                    PyUnicode_FromString(config.fontVariant.value().c_str()));
            if (config.fontWeight.has_value())
                PyDict_SetItemString(pyObj, "fontWeight",
                    fontWeightValueToPython(config.fontWeight.value()));
            if (config.in_layout.has_value())
                PyDict_SetItemString(pyObj, "in_layout",                
                    config.in_layout.value() ? Py_True : Py_False);
            if (config.label.has_value())
                PyDict_SetItemString(pyObj, "label",
                    PyUnicode_FromString(config.label.value().c_str()));
            if (config.language.has_value())
                PyDict_SetItemString(pyObj, "language",
                    PyUnicode_FromString(config.language.value().c_str()));
            if (config.linespacing.has_value())
                PyDict_SetItemString(pyObj, "linespacing",
                    lineSpacingValueToPython(config.linespacing.value()));
            if (config.math_fontfamily.has_value())
                PyDict_SetItemString(pyObj, "math_fontfamily",
                    PyUnicode_FromString(config.math_fontfamily.value().c_str()));
            if (config.mouseover.has_value())
                PyDict_SetItemString(pyObj, "mouseover",
                    config.mouseover.value() ? Py_True : Py_False);
            if (config.multialignment.has_value())
                PyDict_SetItemString(pyObj, "multialignment",
                    PyUnicode_FromString(config.multialignment.value().c_str()));
            if (config.parse_math.has_value())
                PyDict_SetItemString(pyObj, "parse_math",
                    PyUnicode_FromString(config.parse_math.value().c_str()));
            if (config.position.has_value())
                PyDict_SetItemString(pyObj, "position",
                    positionToTuple(config.position.value()));
            if (config.rasterized.has_value())
                PyDict_SetItemString(pyObj, "rasterized",
                    config.rasterized.value() ? Py_True : Py_False);
            if (config.rotation.has_value())
                PyDict_SetItemString(pyObj, "rotation",
                    rotationValueToPython(config.rotation.value()));
            if (config.rotation_mode.has_value())
                PyDict_SetItemString(pyObj, "rotation_mode",
                    PyUnicode_FromString(config.rotation_mode.value().c_str()));
            if (config.sketch_params.has_value())
                PyDict_SetItemString(pyObj, "sketch_params",
                    sketchParamsToPython(config.sketch_params.value()));
            if (config.snap.has_value())
                PyDict_SetItemString(pyObj, "snap",
                    config.snap.value() ? Py_True : Py_False);
            if (config.text.has_value())
                PyDict_SetItemString(pyObj, "text",
                    PyUnicode_FromString(config.text.value().c_str()));
            if (config.transform_rotates_text.has_value())
                PyDict_SetItemString(pyObj, "transform_rotates_text",
                    config.transform_rotates_text.value() ? Py_True : Py_False);
            if (config.url.has_value())
                PyDict_SetItemString(pyObj, "url",
                    PyUnicode_FromString(config.url.value().c_str()));
            if (config.verticalalignment.has_value())
                PyDict_SetItemString(pyObj, "verticalalignment",
                    PyUnicode_FromString(config.verticalalignment.value().c_str()));
            if (config.visible.has_value())
                PyDict_SetItemString(pyObj, "visible",
                    config.visible.value() ? Py_True : Py_False);
            if (config.wrap.has_value())
                PyDict_SetItemString(pyObj, "wrap",
                    config.wrap.value() ? Py_True : Py_False);
            if (config.x.has_value())
                PyDict_SetItemString(pyObj, "x",
                    PyFloat_FromDouble(config.x.value()));
            if (config.y.has_value())
                PyDict_SetItemString(pyObj, "y",
                    PyFloat_FromDouble(config.y.value()));
            if (config.zorder.has_value())
                PyDict_SetItemString(pyObj, "zorder",                
                    PyFloat_FromDouble(config.zorder.value()));     

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

    
        /**
        * @brief Shared implementation of step() function
        * @param pyObj axes object
        * @param config step configuration
        * @throws std::runtime_error if step fails
        */
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
            
            kwargsPolygonImpl(kwargs.get(), config);


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
         
            
            kwargsFillBetweenImpl(kwargs.get(), config);

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
            
        
            
            kwargsFillBetweenImpl(kwargs.get(), config);
           
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

            if (config.fmt.has_value())
                PyDict_SetItemString(kwargs.get(), "fmt",
                    PyUnicode_FromString(config.fmt.value().c_str()));
            if (config.s.has_value())
                PyDict_SetItemString(kwargs.get(), "s",
                    sizeInPointsValueToPython(config.s.value()));
            if (config.c.has_value())
                PyDict_SetItemString(kwargs.get(), "c",
                    colorValueToPython(config.c.value()));
            if (config.cmap.has_value())
                PyDict_SetItemString(kwargs.get(), "cmap",
                    PyUnicode_FromString(config.cmap.value().c_str()));
            if (config.vmin.has_value())
                PyDict_SetItemString(kwargs.get(), "vmin",
                    PyFloat_FromDouble(config.vmin.value()));
            if (config.vmax.has_value())
                PyDict_SetItemString(kwargs.get(), "vmax",
                    PyFloat_FromDouble(config.vmax.value()));
            if (config.linewidths.has_value())
                PyDict_SetItemString(kwargs.get(), "linewidths",
                    linewidthsToPython(config.linewidths.value()));
            if (config.plotnonfinite.has_value())
                PyDict_SetItemString(kwargs.get(), "plotnonfinite",
                    config.plotnonfinite.value() ? Py_True : Py_False);
            if (config.edgecolors.has_value())
                PyDict_SetItemString(kwargs.get(), "edgecolors",
                    PyUnicode_FromString(config.edgecolors.value().c_str()));
        
            // rest kwargs
            kwargsImpl(kwargs.get(), config);

            PyPtr scatter(PyObject_GetAttrString(pyObj, "scatter"));
            checkAttr(scatter.get(), "scatter");

            PyPtr res(PyObject_Call(scatter.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "scatter");
        }



        /**
        * @brief Plots a bar graph.
        * @param config bar configuration
        * @throws std::runtime_error if bar fails  
        */
        inline void barImpl(PyObject* pyObj, const BarConfig& config) {

            PyPtr args(PyTuple_New(2));
            PyTuple_SetItem(args.get(), 0, barXValueToPython(config.x));
            PyTuple_SetItem(args.get(), 1, barValueToPython(config.height));

            PyPtr kwargs(PyDict_New());


            if (config.width.has_value())
                PyDict_SetItemString(kwargs.get(), "width",
                    barValueToPython(*config.width));
            if (config.bottom.has_value())
                PyDict_SetItemString(kwargs.get(), "bottom",
                    barValueToPython(*config.bottom));
            
            // rest of bar kwargs
            kwargsBarImpl(kwargs.get(), config);
            
            // rest of rectangle kwargs
            kwargsRectangleImpl(kwargs.get(), config);

            PyPtr bar(PyObject_GetAttrString(pyObj, "bar"));
            checkAttr(bar.get(), "bar");

            PyPtr res(PyObject_Call(bar.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "bar");

        }


        inline void barhImpl(PyObject* pyObj, const BarhConfig& config) {

            PyPtr args(PyTuple_New(2));
            PyTuple_SetItem(args.get(), 0, barYValueToPython(config.y));
            PyTuple_SetItem(args.get(), 1, barValueToPython(config.width));

            PyPtr kwargs(PyDict_New());

            if (config.height.has_value())
                PyDict_SetItemString(kwargs.get(), "height",
                    barValueToPython(*config.height));
            if (config.left.has_value())
                PyDict_SetItemString(kwargs.get(), "left",
                    barValueToPython(*config.left));

            // rest of barh kwargs
            kwargsBarImpl(kwargs.get(), config);
            

            // rest of rectangle kwargs
            kwargsRectangleImpl(kwargs.get(), config);

            PyPtr barh(PyObject_GetAttrString(pyObj, "barh"));
            checkAttr(barh.get(), "barh");

            PyPtr res(PyObject_Call(barh.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "barh");
            
        }

        /**
        * @brief Shared implementation of set_xticks() function
        * @param pyObj axes object
        * @param config set_xticks configuration
        * @throws std::runtime_error if set_xticks fails
        */
        inline void set_xticksImpl(PyObject* pyObj, const XTicksConfig& config) {

            PyPtr args(PyTuple_New(1));
            PyTuple_SetItem(args.get(), 0, toNumpy(config.ticks));

            PyPtr kwargs(PyDict_New());

            if (config.minor.has_value())
                PyDict_SetItemString(kwargs.get(), "minor",
                    config.minor.value() ? Py_True : Py_False);
            
            
            kwargsTextImpl(kwargs.get(), config);

            PyPtr set_xticks(PyObject_GetAttrString(pyObj, "set_xticks"));
            checkAttr(set_xticks.get(), "set_xticks");

            PyPtr res(PyObject_Call(set_xticks.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "set_xticks");
            

        }


        /**
        * @brief Shared implementation of set_yticks() function
        * @param pyObj axes object
        * @param config set_yticks configuration
        * @throws std::runtime_error if set_yticks fails
        */
        inline void set_yticksImpl(PyObject* pyObj, const YTicksConfig& config) {

            PyPtr args(PyTuple_New(1));
            PyTuple_SetItem(args.get(), 0, toNumpy(config.ticks));

            PyPtr kwargs(PyDict_New());
            
            if (config.minor.has_value())
                PyDict_SetItemString(kwargs.get(), "minor",
                    config.minor.value() ? Py_True : Py_False);
            
            kwargsTextImpl(kwargs.get(), config);

            PyPtr set_yticks(PyObject_GetAttrString(pyObj, "set_yticks"));
            checkAttr(set_yticks.get(), "set_yticks");

            PyPtr res(PyObject_Call(set_yticks.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "set_yticks");

        }


        /**
        * @brief Set tick labels — DISCOURAGED by matplotlib.
        * Prefer set_xticks({.ticks = x, .labels = categories}) instead.
        * Use only when tick positions are already fixed.   
        */
        inline void set_xticklabelsImpl(PyObject* pyObj, const XTickLabelsConfig& config) {

            PyPtr args(PyTuple_New(1));
            PyTuple_SetItem(args.get(), 0, toStringList(config.labels));

            PyPtr kwargs(PyDict_New());
            
            if (config.minor.has_value())
                PyDict_SetItemString(kwargs.get(), "minor",
                    config.minor.value() ? Py_True : Py_False);
            
         

            PyPtr set_xticklabels(PyObject_GetAttrString(pyObj, "set_xticklabels"));
            checkAttr(set_xticklabels.get(), "set_xticklabels");
            
            PyPtr res(PyObject_Call(set_xticklabels.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "set_xticklabels");
            
        }


        /**
        * @brief Set tick labels — DISCOURAGED by matplotlib.
        * Prefer set_xticks({.ticks = y, .labels = categories}) instead.
        * Use only when tick positions are already fixed.
        */
        inline void set_yticklabelsImpl(PyObject* pyObj, const YTickLabelsConfig& config) {

            PyPtr args(PyTuple_New(1));
            PyTuple_SetItem(args.get(), 0, toStringList(config.labels));

            PyPtr kwargs(PyDict_New());
            
            if (config.minor.has_value())
                PyDict_SetItemString(kwargs.get(), "minor",
                    config.minor.value() ? Py_True : Py_False);
            

            PyPtr set_yticklabels(PyObject_GetAttrString(pyObj, "set_yticklabels"));
            checkAttr(set_yticklabels.get(), "set_yticklabels");
            
            PyPtr res(PyObject_Call(set_yticklabels.get(), args.get(), kwargs.get()));
            checkResult(res.get(), "set_yticklabels");
            
        }



        


    } // namespace detail
} // namespace matplotlibcpp