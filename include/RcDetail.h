#pragma once
// =============================================================================
// RcDetail.h - internal shared implementation for the rcParams
// Modern C++23 matplotlib wrapper built on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 16/08/2024
// =============================================================================

#include "Detail.h"
#include "RcConfigs.h"
#include "PyPtr.h"
#include "Helper.h"

#include <iostream>
#include <map>
#include <string>
#include <numeric>
#include <print>

namespace matplotlibcpp {

    namespace detail {
    
    /**
    * @brief Converts RcValue to a Python object
    * @param rv input RcValue
    * @return PyObject* Python object 
    */
    inline void rcImpl(PyObject* pyplotObj, const RcConfig& config){
        PyPtr args(PyTuple_New(1));
        
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(config.group.c_str()));
        
        PyPtr kwargs(PyDict_New());

        for (const auto& [key, value] : config.kwargs) {

            PyDict_SetItemString(kwargs.get(), key.c_str(), rcValueToPython(value));
        }



        PyPtr rc(PyObject_GetAttrString(pyplotObj, "rc"));
        checkAttr(rc.get(), "rc");
        
        PyPtr res(PyObject_Call(rc.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "rc");
        
    }

    /**
    * @brief Shared implementation of grid rc
    * @param pyplotObj matplotlib pyplot object
    * @param config grid rc config
    * @throws std::runtime_error if rc fails
    */
    inline void rcImpl(PyObject* pyplotObj, const GridRcConfig& config){

        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(config.group.c_str()));

        PyPtr kwargs(PyDict_New());

        if (config.color.has_value())
            PyDict_SetItemString(kwargs.get(), "color",
                PyUnicode_FromString(config.color.value().c_str()));
        if (config.linestyle.has_value())
            PyDict_SetItemString(kwargs.get(), "linestyle",
                PyUnicode_FromString(config.linestyle.value().c_str()));
        if (config.linewidth.has_value())
            PyDict_SetItemString(kwargs.get(), "linewidth",
                PyFloat_FromDouble(config.linewidth.value()));
        if (config.alpha.has_value())
            PyDict_SetItemString(kwargs.get(), "alpha",
                PyFloat_FromDouble(config.alpha.value()));

        PyPtr grid(PyObject_GetAttrString(pyplotObj, "rc"));
        checkAttr(grid.get(), "rc");
        
        PyPtr res(PyObject_Call(grid.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "rc");

        

    }

    /**
    * @brief Shared implementation of legend rc
    * @param pyplotObj matplotlib pyplot object
    * @param config legend rc config
    * @throws std::runtime_error if rc fails
    */
    inline void rcImpl(PyObject* pyplotObj, const LegendRcConfig& config){
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(config.group.c_str())); 

        PyPtr kwargs(PyDict_New());

        if (config.loc.has_value())
            PyDict_SetItemString(kwargs.get(), "loc",
                legendLocValueToPython(config.loc.value()));
        if (config.frameon.has_value())
            PyDict_SetItemString(kwargs.get(), "frameon",
                config.frameon.value() ? Py_True : Py_False);
        if (config.framealpha.has_value())
            PyDict_SetItemString(kwargs.get(), "framealpha",
                PyFloat_FromDouble(config.framealpha.value()));
        if (config.facecolor.has_value())
            PyDict_SetItemString(kwargs.get(), "facecolor",
                PyUnicode_FromString(config.facecolor.value().c_str()));
        if (config.edgecolor.has_value())
            PyDict_SetItemString(kwargs.get(), "edgecolor",
                PyUnicode_FromString(config.edgecolor.value().c_str()));
        if (config.linewidth.has_value())
            PyDict_SetItemString(kwargs.get(), "linewidth",
                PyFloat_FromDouble(config.linewidth.value()));
        if (config.fancybox.has_value())
            PyDict_SetItemString(kwargs.get(), "fancybox",
                config.fancybox.value() ? Py_True : Py_False);
        if (config.numpoints.has_value())
            PyDict_SetItemString(kwargs.get(), "numpoints",
                PyLong_FromLong(config.numpoints.value()));
        if (config.scatterpoints.has_value())
            PyDict_SetItemString(kwargs.get(), "scatterpoints",
                PyLong_FromLong(config.scatterpoints.value()));
        if (config.fontsize.has_value())
            PyDict_SetItemString(kwargs.get(), "fontsize",
                fontsizeValueToPython(config.fontsize.value()));
        if (config.labelcolor.has_value())
            PyDict_SetItemString(kwargs.get(), "labelcolor",
                labelcolorValueToPython(config.labelcolor.value()));
        if (config.title_fontsize.has_value())
            PyDict_SetItemString(kwargs.get(), "title_fontsize",
                titleFontsizeValueToPython(config.title_fontsize.value()));
        if (config.borderpad.has_value())
            PyDict_SetItemString(kwargs.get(), "borderpad",
                PyFloat_FromDouble(config.borderpad.value()));
        if (config.labelspacing.has_value())
            PyDict_SetItemString(kwargs.get(), "labelspacing",
                PyFloat_FromDouble(config.labelspacing.value()));
        if (config.handlelength.has_value())
            PyDict_SetItemString(kwargs.get(), "handlelength",
                PyFloat_FromDouble(config.handlelength.value()));
        if (config.handleheight.has_value())
            PyDict_SetItemString(kwargs.get(), "handleheight",
                PyFloat_FromDouble(config.handleheight.value()));
        if (config.handletextpad.has_value())
            PyDict_SetItemString(kwargs.get(), "handletextpad",
                PyFloat_FromDouble(config.handletextpad.value()));
        if (config.borderaxespad.has_value())
            PyDict_SetItemString(kwargs.get(), "borderaxespad",
                PyFloat_FromDouble(config.borderaxespad.value()));
        if (config.columnspacing.has_value())
            PyDict_SetItemString(kwargs.get(), "columnspacing",
                PyFloat_FromDouble(config.columnspacing.value()));

        PyPtr legend(PyObject_GetAttrString(pyplotObj, "rc"));
        checkAttr(legend.get(), "rc");
        
        PyPtr res(PyObject_Call(legend.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "rc");

        
    }

    /**
    * @brief Shared implementation of ticks rc
    * @param pyplotObj matplotlib pyplot object
    * @param config ticks rc config
    * @throws std::runtime_error if rc fails    
    */
    inline void rcImpl(PyObject* pyplotObj, const TicksRcConfig& config){
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(config.group.c_str()));

        PyPtr kwargs(PyDict_New());

        if (config.top.has_value())
            PyDict_SetItemString(kwargs.get(), "top",
                config.top.value() ? Py_True : Py_False);
        if (config.bottom.has_value())
            PyDict_SetItemString(kwargs.get(), "bottom",
                config.bottom.value() ? Py_True : Py_False);
        if (config.labeltop.has_value())
            PyDict_SetItemString(kwargs.get(), "labeltop",
                config.labeltop.value() ? Py_True : Py_False);
        if (config.labelbottom.has_value())
            PyDict_SetItemString(kwargs.get(), "labelbottom",
                config.labelbottom.value() ? Py_True : Py_False);
        if (config.size.has_value())
            PyDict_SetItemString(kwargs.get(), "size",
                PyLong_FromLong(config.size.value()));
        if (config.width.has_value())
            PyDict_SetItemString(kwargs.get(), "width",
                PyFloat_FromDouble(config.width.value()));
        if (config.pad.has_value())
            PyDict_SetItemString(kwargs.get(), "pad",
                PyFloat_FromDouble(config.pad.value()));
        if (config.color.has_value())
            PyDict_SetItemString(kwargs.get(), "color",
                PyUnicode_FromString(config.color.value().c_str()));
        if (config.labelcolor.has_value())
            PyDict_SetItemString(kwargs.get(), "labelcolor",
                PyUnicode_FromString(config.labelcolor.value().c_str()));
        if (config.labelsize.has_value())
            PyDict_SetItemString(kwargs.get(), "labelsize",
                fontsizeValueToPython(config.labelsize.value()));
        if (config.direction.has_value())
            PyDict_SetItemString(kwargs.get(), "direction",
                PyUnicode_FromString(config.direction.value().c_str()));
        if (config.visible.has_value())
            PyDict_SetItemString(kwargs.get(), "visible",
                config.visible.value() ? Py_True : Py_False);
        if (config.ndivs.has_value())
            PyDict_SetItemString(kwargs.get(), "ndivs",
                tickNdivsToPython(config.ndivs.value()));
        if (config.alignment.has_value())
            PyDict_SetItemString(kwargs.get(), "alignment",
                PyUnicode_FromString(config.alignment.value().c_str()));
        if (config.left.has_value())
            PyDict_SetItemString(kwargs.get(), "left",
                config.left.value() ? Py_True : Py_False);
        if (config.right.has_value())
            PyDict_SetItemString(kwargs.get(), "right",
                config.right.value() ? Py_True : Py_False);
        if (config.labelleft.has_value())
            PyDict_SetItemString(kwargs.get(), "labelleft",
                config.labelleft.value() ? Py_True : Py_False);
        if (config.labelright.has_value())
            PyDict_SetItemString(kwargs.get(), "labelright",
                config.labelright.value() ? Py_True : Py_False);

        PyPtr ticks(PyObject_GetAttrString(pyplotObj, "rc"));
        checkAttr(ticks.get(), "rc");
        
        PyPtr res(PyObject_Call(ticks.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "rc");

        
    }   

    /**
    * @brief Shared implementation of boxplot rc
    * @param pyplotObj matplotlib pyplot object
    * @param config boxplot rc config
    * @throws std::runtime_error if rc fails
    */
    inline void rcImpl(PyObject* pyplotObj, const BoxplotRcConfig& config){
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(config.group.c_str()));

        PyPtr kwargs(PyDict_New());

        if (config.notch.has_value())
            PyDict_SetItemString(kwargs.get(), "notch",
                config.notch.value() ? Py_True : Py_False);
        if (config.vertical.has_value())
            PyDict_SetItemString(kwargs.get(), "vertical",
                config.vertical.value() ? Py_True : Py_False);
        if (config.whisker.has_value())
            PyDict_SetItemString(kwargs.get(), "whisker",
                whiskerValueToPython(config.whisker.value()));
        if (config.bootstrap.has_value())
            PyDict_SetItemString(kwargs.get(), "bootstrap",
                config.bootstrap.value() ? Py_True : Py_False);
        if (config.patchartist.has_value())
            PyDict_SetItemString(kwargs.get(), "patchartist",
                config.patchartist.value() ? Py_True : Py_False);
        if (config.showmeans.has_value())
            PyDict_SetItemString(kwargs.get(), "showmeans",
                config.showmeans.value() ? Py_True : Py_False);
        if (config.showcaps.has_value())
            PyDict_SetItemString(kwargs.get(), "showcaps",
                config.showcaps.value() ? Py_True : Py_False);
        if (config.showbox.has_value())
            PyDict_SetItemString(kwargs.get(), "showbox",
                config.showbox.value() ? Py_True : Py_False);
        if (config.showfliers.has_value())
            PyDict_SetItemString(kwargs.get(), "showfliers",
                config.showfliers.value() ? Py_True : Py_False);
        if (config.meanline.has_value())
            PyDict_SetItemString(kwargs.get(), "meanline",
                config.meanline.value() ? Py_True : Py_False);
        if (config.color.has_value())
            PyDict_SetItemString(kwargs.get(), "color",
                PyUnicode_FromString(config.color.value().c_str()));
        if (config.marker.has_value())
            PyDict_SetItemString(kwargs.get(), "marker",
                PyUnicode_FromString(config.marker.value().c_str()));
        if (config.markerfacecolor.has_value())
            PyDict_SetItemString(kwargs.get(), "markerfacecolor",
                PyUnicode_FromString(config.markerfacecolor.value().c_str()));
        if (config.markeredgecolor.has_value())
            PyDict_SetItemString(kwargs.get(), "markeredgecolor",
                PyUnicode_FromString(config.markeredgecolor.value().c_str()));
        if (config.markeredgewidth.has_value())
            PyDict_SetItemString(kwargs.get(), "markeredgewidth",
                PyFloat_FromDouble(config.markeredgewidth.value()));
        if (config.markersize.has_value())
            PyDict_SetItemString(kwargs.get(), "markersize",
                PyFloat_FromDouble(config.markersize.value()));
        if (config.linestyle.has_value())
            PyDict_SetItemString(kwargs.get(), "linestyle",
                PyUnicode_FromString(config.linestyle.value().c_str()));
        if (config.linewidth.has_value())
            PyDict_SetItemString(kwargs.get(), "linewidth",                
                PyFloat_FromDouble(config.linewidth.value()));      
        

        PyPtr boxplot(PyObject_GetAttrString(pyplotObj, "rc"));
        checkAttr(boxplot.get(), "rc");
        
        PyPtr res(PyObject_Call(boxplot.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "rc");   
    }


    /**
    * @brief Shared implementation of font rc
    * @param pyplotObj matplotlib pyplot object
    * @param config font rc config
    * @throws std::runtime_error if rc fails
    */
    inline void rcImpl(PyObject* pyplotObj, const FontRcConfig& config){
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(config.group.c_str()));

        PyPtr kwargs(PyDict_New());

        if (config.family.has_value())
            PyDict_SetItemString(kwargs.get(), "family",
                PyUnicode_FromString(config.family.value().c_str()));
        if (config.style.has_value())
            PyDict_SetItemString(kwargs.get(), "style",
                PyUnicode_FromString(config.style.value().c_str()));
        if (config.variant.has_value())
            PyDict_SetItemString(kwargs.get(), "variant",
                PyUnicode_FromString(config.variant.value().c_str()));
        if (config.weight.has_value())
            PyDict_SetItemString(kwargs.get(), "weight",
                fontWeightValueToPython(config.weight.value()));
        if (config.stretch.has_value())
            PyDict_SetItemString(kwargs.get(), "stretch",
                fontStretchValueToPython(config.stretch.value()));
        if (!config.serif.empty())
            PyDict_SetItemString(kwargs.get(), "serif",
                    toStringList(config.serif));
        if (!config.sansserif.empty())
            PyDict_SetItemString(kwargs.get(), "sans-serif",
                    toStringList(config.sansserif));
        if (!config.cursive.empty())
            PyDict_SetItemString(kwargs.get(), "cursive",
                    toStringList(config.cursive));
        if (!config.fantasy.empty())
            PyDict_SetItemString(kwargs.get(), "fantasy",
                    toStringList(config.fantasy));
        if (!config.monospace.empty())
            PyDict_SetItemString(kwargs.get(), "monospace",
                toStringList(config.monospace));
        if (config.enable_last_resort.has_value())
            PyDict_SetItemString(kwargs.get(), "enable_last_resort",
                config.enable_last_resort.value() ? Py_True : Py_False);

        PyPtr font(PyObject_GetAttrString(pyplotObj, "rc"));
        checkAttr(font.get(), "rc");
        
        PyPtr res(PyObject_Call(font.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "rc");

    }   


    /**
    * @brief Shared implementation of lines rc
    * @param pyplotObj matplotlib pyplot object
    * @param config lines rc config
    * @throws std::runtime_error if rc fails
    */
    inline void rcImpl(PyObject* pyplotObj, const LinesRcConfig& config){
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(config.group.c_str()));

        PyPtr kwargs(PyDict_New());

        if (config.linewidth.has_value())
            PyDict_SetItemString(kwargs.get(), "linewidth",
                PyFloat_FromDouble(config.linewidth.value()));
        if (config.linestyle.has_value())
            PyDict_SetItemString(kwargs.get(), "linestyle",
                PyUnicode_FromString(config.linestyle.value().c_str()));
        if (config.color.has_value())
            PyDict_SetItemString(kwargs.get(), "color",
                PyUnicode_FromString(config.color.value().c_str()));
        if (config.marker.has_value())
            PyDict_SetItemString(kwargs.get(), "marker",
                PyUnicode_FromString(config.marker.value().c_str()));
        if (config.markerfacecolor.has_value())
            PyDict_SetItemString(kwargs.get(), "markerfacecolor",
                PyUnicode_FromString(config.markerfacecolor.value().c_str()));
        if (config.markeredgecolor.has_value())
            PyDict_SetItemString(kwargs.get(), "markeredgecolor",
                PyUnicode_FromString(config.markeredgecolor.value().c_str()));
        if (config.markeredgewidth.has_value())
            PyDict_SetItemString(kwargs.get(), "markeredgewidth",
                PyFloat_FromDouble(config.markeredgewidth.value()));
        if (config.markersize.has_value())
            PyDict_SetItemString(kwargs.get(), "markersize",
                PyFloat_FromDouble(config.markersize.value()));
        if (config.dash_joinstyle.has_value())
            PyDict_SetItemString(kwargs.get(), "dash_joinstyle",
                PyUnicode_FromString(config.dash_joinstyle.value().c_str()));
        if (config.dash_capstyle.has_value())
            PyDict_SetItemString(kwargs.get(), "dash_capstyle",
                PyUnicode_FromString(config.dash_capstyle.value().c_str()));
        if (config.solid_joinstyle.has_value())
            PyDict_SetItemString(kwargs.get(), "solid_joinstyle",
                PyUnicode_FromString(config.solid_joinstyle.value().c_str()));
        if (config.solid_capstyle.has_value())
            PyDict_SetItemString(kwargs.get(), "solid_capstyle",
                PyUnicode_FromString(config.solid_capstyle.value().c_str()));
        if (config.antialiased.has_value())
            PyDict_SetItemString(kwargs.get(), "antialiased",
                config.antialiased.value() ? Py_True : Py_False);
        if (!config.dashed_pattern.empty())
            PyDict_SetItemString(kwargs.get(), "dashed_pattern",
                    toNumpy(config.dashed_pattern));
        if (!config.dashdot_pattern.empty())
            PyDict_SetItemString(kwargs.get(), "dashdot_pattern",
                    toNumpy(config.dashdot_pattern));
        if (!config.dotted_pattern.empty())
            PyDict_SetItemString(kwargs.get(), "dotted_pattern",                
                    toNumpy(config.dotted_pattern));    
        if (config.scale_dashes.has_value())
            PyDict_SetItemString(kwargs.get(), "scale_dashes",
                config.scale_dashes.value() ? Py_True : Py_False);
       

        PyPtr lines(PyObject_GetAttrString(pyplotObj, "rc"));
        checkAttr(lines.get(), "rc");
        
        PyPtr res(PyObject_Call(lines.get(), args.get(), kwargs.get()));        
        checkResult(res.get(), "rc");
    }   

    /**
    * @brief Shared implementation of axes rc
    * @param pyplotObj matplotlib pyplot object
    * @param config axes rc config
    * @throws std::runtime_error if rc fails    
    */
    inline void rcImpl(PyObject* pyplotObj, const AxesRcConfig& config){
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(config.group.c_str()));

        PyPtr kwargs(PyDict_New());
        
        if (config.facecolor.has_value())
            PyDict_SetItemString(kwargs.get(), "facecolor",
                PyUnicode_FromString(config.facecolor.value().c_str()));
        if (config.edgecolor.has_value())
            PyDict_SetItemString(kwargs.get(), "edgecolor",
                PyUnicode_FromString(config.edgecolor.value().c_str()));
        if (config.linewidth.has_value())
            PyDict_SetItemString(kwargs.get(), "linewidth",
                PyFloat_FromDouble(config.linewidth.value()));
        if (config.grid.has_value())
            PyDict_SetItemString(kwargs.get(), "grid",
                config.grid.value() ? Py_True : Py_False);
        if (config.axis.has_value())
            PyDict_SetItemString(kwargs.get(), "axis",
                PyUnicode_FromString(config.axis.value().c_str()));
        if (config.which.has_value())
            PyDict_SetItemString(kwargs.get(), "which",
                PyUnicode_FromString(config.which.value().c_str()));
        if (config.titlelocation.has_value())
            PyDict_SetItemString(kwargs.get(), "titlelocation",
                PyUnicode_FromString(config.titlelocation.value().c_str()));
        if (config.titlesize.has_value())
            PyDict_SetItemString(kwargs.get(), "titlesize",
                PyUnicode_FromString(config.titlesize.value().c_str()));
        if (config.titleweight.has_value())
            PyDict_SetItemString(kwargs.get(), "titleweight",
                PyUnicode_FromString(config.titleweight.value().c_str()));
        if (config.titlecolor.has_value())
            PyDict_SetItemString(kwargs.get(), "titlecolor",
                PyUnicode_FromString(config.titlecolor.value().c_str()));
        if (config.titley.has_value())
            PyDict_SetItemString(kwargs.get(), "titley",
                PyUnicode_FromString(config.titley.value().c_str()));
        if (config.titlepad.has_value())            
            PyDict_SetItemString(kwargs.get(), "titlepad",
                PyFloat_FromDouble(config.titlepad.value()));
        if (config.labelsize.has_value())
            PyDict_SetItemString(kwargs.get(), "labelsize",
                PyUnicode_FromString(config.labelsize.value().c_str()));
        if (config.labelpad.has_value())
            PyDict_SetItemString(kwargs.get(), "labelpad",
                PyFloat_FromDouble(config.labelpad.value()));
        if (config.labelweight.has_value())
            PyDict_SetItemString(kwargs.get(), "labelweight",
                PyUnicode_FromString(config.labelweight.value().c_str()));
        if (config.labelcolor.has_value())
            PyDict_SetItemString(kwargs.get(), "labelcolor",
                PyUnicode_FromString(config.labelcolor.value().c_str()));
        if (config.axisbelow.has_value())
            PyDict_SetItemString(kwargs.get(), "axisbelow",
                PyUnicode_FromString(config.axisbelow.value().c_str()));
        if (!config.limits.empty())
            PyDict_SetItemString(kwargs.get(), "limits",                
                    toNumpy(config.limits));
        if (config.use_locale.has_value())
            PyDict_SetItemString(kwargs.get(), "use_locale",
                config.use_locale.value() ? Py_True : Py_False);
        if (config.use_mathtext.has_value())
            PyDict_SetItemString(kwargs.get(), "use_mathtext",
                config.use_mathtext.value() ? Py_True : Py_False);
        if (config.min_exponent.has_value())
            PyDict_SetItemString(kwargs.get(), "min_exponent",
                PyLong_FromLong(config.min_exponent.value()));
        if (config.useoffset.has_value())
            PyDict_SetItemString(kwargs.get(), "useoffset",
                config.useoffset.value() ? Py_True : Py_False);
        if (config.offset_threshold.has_value())
            PyDict_SetItemString(kwargs.get(), "offset_threshold",
                PyLong_FromLong(config.offset_threshold.value()));
        if (config.left.has_value())
            PyDict_SetItemString(kwargs.get(), "left",
                config.left.value() ? Py_True : Py_False);
        if (config.bottom.has_value())
            PyDict_SetItemString(kwargs.get(), "bottom",
                config.bottom.value() ? Py_True : Py_False);
        if (config.top.has_value())
            PyDict_SetItemString(kwargs.get(), "top",
                config.top.value() ? Py_True : Py_False);
        if (config.right.has_value())
            PyDict_SetItemString(kwargs.get(), "right",
                config.right.value() ? Py_True : Py_False);
        if (config.xmargin.has_value())
            PyDict_SetItemString(kwargs.get(), "xmargin",
                PyFloat_FromDouble(config.xmargin.value()));
        if (config.ymargin.has_value())
            PyDict_SetItemString(kwargs.get(), "ymargin",
                PyFloat_FromDouble(config.ymargin.value()));        
        if (config.zmargin.has_value())
            PyDict_SetItemString(kwargs.get(), "zmargin",
                PyFloat_FromDouble(config.zmargin.value()));
        if (config.autolimit_mode.has_value())
            PyDict_SetItemString(kwargs.get(), "autolimit_mode",
                PyUnicode_FromString(config.autolimit_mode.value().c_str()));       

        PyPtr axesrc(PyObject_GetAttrString(pyplotObj, "rc"));
        checkAttr(axesrc.get(), "rc");
        
        PyPtr res(PyObject_Call(axesrc.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "rc");
        
    }

    /**
    * @brief Shared implementation of figure rc
    * @param pyplotObj matplotlib pyplot object
    * @param config figure rc config
    * @throws std::runtime_error if rc fails
    */
    inline void rcImpl(PyObject* pyplotObj, const FigureRcConfig& config){
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(config.group.c_str()));

        PyPtr kwargs(PyDict_New());
        
        if (config.titlesize.has_value())
            PyDict_SetItemString(kwargs.get(), "titlesize",
                PyUnicode_FromString(config.titlesize.value().c_str()));
        if (config.titleweight.has_value())
            PyDict_SetItemString(kwargs.get(), "titleweight",
                PyUnicode_FromString(config.titleweight.value().c_str()));
        if (config.labelsize.has_value())
            PyDict_SetItemString(kwargs.get(), "labelsize",
                PyUnicode_FromString(config.labelsize.value().c_str()));
        if (config.labelweight.has_value())
            PyDict_SetItemString(kwargs.get(), "labelweight",
                PyUnicode_FromString(config.labelweight.value().c_str()));
        if (!config.figsize.empty())
            PyDict_SetItemString(kwargs.get(), "figsize",
                    toNumpy(config.figsize));
        if (config.dpi.has_value())
            PyDict_SetItemString(kwargs.get(), "dpi",
                PyFloat_FromDouble(config.dpi.value()));
        if (config.facecolor.has_value())
            PyDict_SetItemString(kwargs.get(), "facecolor",
                PyUnicode_FromString(config.facecolor.value().c_str()));
        if (config.edgecolor.has_value())
            PyDict_SetItemString(kwargs.get(), "edgecolor",
                PyUnicode_FromString(config.edgecolor.value().c_str()));
        if (config.frameon.has_value())
            PyDict_SetItemString(kwargs.get(), "frameon",
                config.frameon.value() ? Py_True : Py_False);
        if (config.max_open_warning.has_value())
            PyDict_SetItemString(kwargs.get(), "max_open_warning",
                PyLong_FromLong(config.max_open_warning.value()));
        if (config.raise_window.has_value())
            PyDict_SetItemString(kwargs.get(), "raise_window",
                config.raise_window.value() ? Py_True : Py_False);
        if (config.left.has_value())
            PyDict_SetItemString(kwargs.get(), "left",
                PyFloat_FromDouble(config.left.value()));
        if (config.right.has_value())
            PyDict_SetItemString(kwargs.get(), "right",
                PyFloat_FromDouble(config.right.value()));
        if (config.top.has_value())
            PyDict_SetItemString(kwargs.get(), "top",
                PyFloat_FromDouble(config.top.value()));
        if (config.bottom.has_value())
            PyDict_SetItemString(kwargs.get(), "bottom",
                PyFloat_FromDouble(config.bottom.value()));
        if (config.wspace.has_value())
            PyDict_SetItemString(kwargs.get(), "wspace",
                PyFloat_FromDouble(config.wspace.value()));
        if (config.hspace.has_value())
            PyDict_SetItemString(kwargs.get(), "hspace",
                PyFloat_FromDouble(config.hspace.value()));
        if (config.autolayout.has_value())
            PyDict_SetItemString(kwargs.get(), "autolayout",
                config.autolayout.value() ? Py_True : Py_False);
        if (config.use.has_value())
            PyDict_SetItemString(kwargs.get(), "use",
                config.use.value() ? Py_True : Py_False);
        if (config.h_pad.has_value())
            PyDict_SetItemString(kwargs.get(), "h_pad",
                PyFloat_FromDouble(config.h_pad.value()));
        if (config.w_pad.has_value())
            PyDict_SetItemString(kwargs.get(), "w_pad",
                PyFloat_FromDouble(config.w_pad.value()));

        PyPtr figurerc(PyObject_GetAttrString(pyplotObj, "rc"));
        checkAttr(figurerc.get(), "rc");
        
        PyPtr res(PyObject_Call(figurerc.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "rc");
        
    }   




    } // namespace detail
} // namespace matplotlibcpp