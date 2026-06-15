#pragma once

// =============================================================================
// Axes.h - C++ wrapper for matplotlib.axes.Axes
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 07/06/2024
// =============================================================================

#include "Interpreter.h"
#include "PyPtr.h"
#include "numpy_utils.h"
#include "configs.h"
#include "helper.h"
#include "pythonrun.h"

#include <memory>
#include <string>
#include <vector>

namespace matplotlibcpp {

class Axes
{
private: 
    PyPtr ax_;

public:

    explicit Axes(PyObject* ax) : ax_(ax) {}

    PyObject* get_axes() const { return ax_.get(); }

    std::pair<double,double> get_xlim() const { 
        
        PyPtr args(PyTuple_New(0));

        PyPtr fn(PyObject_GetAttrString(ax_.get(), "get_xlim"));
        checkAttr(fn.get(), "get_xlim");

        PyPtr res(PyObject_Call(fn.get(), args.get(), nullptr));
        checkResult(res.get(), "get_xlim");

        double left  = PyFloat_AsDouble(PyTuple_GetItem(res.get(), 0));
        double right = PyFloat_AsDouble(PyTuple_GetItem(res.get(), 1));

        return std::make_pair(left, right);
    
    }


    std::pair<double,double> get_ylim() const { 
        
        PyPtr args(PyTuple_New(0));

        PyPtr fn(PyObject_GetAttrString(ax_.get(), "get_ylim"));
        checkAttr(fn.get(), "get_ylim");

        PyPtr res(PyObject_Call(fn.get(), args.get(), nullptr));
        checkResult(res.get(), "get_ylim");

        double bottom  = PyFloat_AsDouble(PyTuple_GetItem(res.get(), 0));
        double top = PyFloat_AsDouble(PyTuple_GetItem(res.get(), 1));

        return std::make_pair(bottom, top);
    
    }


    void plot(const PlotConfig& config) {
    
        PyPtr xarray(toNumpy(config.x));
        PyPtr yarray(toNumpy(config.y));
        
        PyObject_CallMethod(ax_.get(), "plot",      "OOs", xarray.get(), yarray.get(), config.fmt.c_str());

    }

    void grid(bool flag = true){
        PyObject_CallMethod(ax_.get(), "grid", "O", flag ? Py_True : Py_False);
    }

    void set_title(const std::string& title) {
        PyObject_CallMethod(ax_.get(), "set_title", "s", title.c_str());
    }

    void set_xlabel(const XLabelConfig& config) {

        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(config.xlabel.c_str()));
        
        PyPtr kwargs(PyDict_New());
        PyDict_SetItemString(kwargs.get(), "labelpad",
            PyFloat_FromDouble(config.labelpad));
        if (!config.color.empty())
            PyDict_SetItemString(kwargs.get(), "color",
                PyUnicode_FromString(config.color.c_str()));

        PyPtr res(PyObject_Call(
            PyObject_GetAttrString(ax_.get(), "set_xlabel"), args.get(), kwargs.get()));
        checkResult(res.get(), "set_xlabel");

    }

    void set_ylabel(const YLabelConfig& config) {

        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(config.ylabel.c_str()));

        PyPtr kwargs(PyDict_New());
        PyDict_SetItemString(kwargs.get(), "labelpad",
            PyFloat_FromDouble(config.labelpad));
        if (!config.color.empty())
            PyDict_SetItemString(kwargs.get(), "color",
                PyUnicode_FromString(config.color.c_str()));

        PyPtr res(PyObject_Call(
            PyObject_GetAttrString(ax_.get(), "set_ylabel"), args.get(), kwargs.get()));
        checkResult(res.get(), "set_ylabel");
    }

    std::pair<double, double> set_xlim(const SetXlimConfig& config) {

        PyPtr args(PyTuple_New(0));
        PyPtr kwargs(PyDict_New());

        if (config.left)
            PyDict_SetItemString(kwargs.get(), "left", PyFloat_FromDouble(*config.left));
        if (config.right)
            PyDict_SetItemString(kwargs.get(), "right", PyFloat_FromDouble(*config.right));
        if (config.xmin)
            PyDict_SetItemString(kwargs.get(), "xmin", PyFloat_FromDouble(*config.xmin));
        if (config.xmax)
            PyDict_SetItemString(kwargs.get(), "xmax", PyFloat_FromDouble(*config.xmax));
        if (config.auto_.has_value())
            PyDict_SetItemString(kwargs.get(), "auto", config.auto_ ? Py_True : Py_False);

       
        PyDict_SetItemString(kwargs.get(), "emit",config.emit ? Py_True : Py_False);
        

        PyPtr set_xlim(PyObject_GetAttrString(ax_.get(), "set_xlim"));
        checkAttr(set_xlim.get(), "set_xlim");
        
        
        PyPtr res(PyObject_Call(set_xlim.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "set_xlim");
        
        return std::make_pair(PyFloat_AsDouble(PyTuple_GetItem(res.get(), 0)), PyFloat_AsDouble(PyTuple_GetItem(res.get(), 1)));

    }

    std::pair<double, double> set_ylim(const SetYlimConfig& config) {

        PyPtr args(PyTuple_New(0));
        PyPtr kwargs(PyDict_New());

        if (config.bottom)
            PyDict_SetItemString(kwargs.get(), "bottom", PyFloat_FromDouble(*config.bottom));
        if (config.top)
            PyDict_SetItemString(kwargs.get(), "top", PyFloat_FromDouble(*config.top));
        if (config.ymin)
            PyDict_SetItemString(kwargs.get(), "ymin", PyFloat_FromDouble(*config.ymin));
        if (config.ymax)
            PyDict_SetItemString(kwargs.get(), "ymax", PyFloat_FromDouble(*config.ymax));
        if (config.auto_.has_value())
            PyDict_SetItemString(kwargs.get(), "auto", config.auto_ ? Py_True : Py_False);

       
        PyDict_SetItemString(kwargs.get(), "emit",config.emit ? Py_True : Py_False);
        

        PyPtr set_ylim(PyObject_GetAttrString(ax_.get(), "set_ylim"));
        checkAttr(set_ylim.get(), "set_ylim");
        
        PyPtr res(PyObject_Call(set_ylim.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "set_ylim");
        
        return std::make_pair(PyFloat_AsDouble(PyTuple_GetItem(res.get(), 0)), PyFloat_AsDouble(PyTuple_GetItem(res.get(), 1)));

    }

    void set_aspect(const std::string& aspect) {
        PyObject_CallMethod(ax_.get(), "set_aspect", "s", aspect.c_str());
    }


    void errorbar(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& yerr, const std::string& fmt = "b") {

        PyPtr xarray(toNumpy(x));
        PyPtr yarray(toNumpy(y));
        PyPtr yerrarray(toNumpy(yerr));
        
        PyObject_CallMethod(ax_.get(), "errorbar", "OOOs", xarray.get(), yarray.get(), yerrarray.get(), fmt.c_str());
        
    }


    void scatter(const std::vector<double>& x, const std::vector<double>& y, const std::string& fmt = "b") {
        
        PyPtr xarray(toNumpy(x));
        PyPtr yarray(toNumpy(y));
        
        PyObject_CallMethod(ax_.get(), "scatter", "OOs", xarray.get(), yarray.get(), fmt.c_str());
    
    }


    void step(const std::vector<double>& x, const std::vector<double>& y, const std::string& fmt = "b") {
        
        PyPtr xarray(toNumpy(x));
        PyPtr yarray(toNumpy(y));
        
        PyObject_CallMethod(ax_.get(), "step", "OOs", xarray.get(), yarray.get(), fmt.c_str());
        
    }

    void loglog(const std::vector<double>& x, const std::vector<double>& y, const std::string& fmt = "b") {
        
        PyPtr xarray(toNumpy(x));
        PyPtr yarray(toNumpy(y));
        
        PyObject_CallMethod(ax_.get(), "loglog", "OOs", xarray.get(), yarray.get(), fmt.c_str());
        
    }

    void semilogx(const std::vector<double>& x, const std::vector<double>& y, const std::string& fmt = "b") {
        
        PyPtr xarray(toNumpy(x));
        PyPtr yarray(toNumpy(y));
        
        PyObject_CallMethod(ax_.get(), "semilogx", "OOs", xarray.get(), yarray.get(), fmt.c_str());
        
    }


    void semilogy(const std::vector<double>& x, const std::vector<double>& y, const std::string& fmt = "b") {
        
        PyPtr xarray(toNumpy(x));
        PyPtr yarray(toNumpy(y));
        
        PyObject_CallMethod(ax_.get(), "semilogy", "OOs", xarray.get(), yarray.get(), fmt.c_str());

    }


    void fill_between(const std::vector<double>& x, const std::vector<double>& y1, const std::vector<double>& y2, const std::string& fmt = "b") {

        PyPtr xarray(toNumpy(x));
        PyPtr y1array(toNumpy(y1));
        PyPtr y2array(toNumpy(y2));

        
        PyObject_CallMethod(ax_.get(), "fill_between", "OOOs", xarray.get(), y1array.get(), y2array.get(), fmt.c_str());
        
    }


    void fill_betweenx(const std::vector<double>& y, const std::vector<double>& x1, const std::vector<double>& x2, const std::string& fmt = "b") {
       
        PyPtr yarray(toNumpy(y)); 
        PyPtr x1array(toNumpy(x1));
        PyPtr x2array(toNumpy(x2));
        
        PyObject_CallMethod(ax_.get(), "fill_betweenx", "OOOs", yarray.get(), x1array.get(), x2array.get(), fmt.c_str());
        
   
    }


    void bar(const std::vector<double>& x, const std::vector<double>& height, const std::string& fmt = "b") {
        PyPtr xarray(toNumpy(x));
        PyPtr heightarray(toNumpy(height));
        
        PyObject_CallMethod(ax_.get(), "bar", "OOs", xarray.get(), heightarray.get(), fmt.c_str());
        
    }

    void barh(const std::vector<double>& y, const std::vector<double>& width, const std::string& fmt = "b") {

        PyPtr yarray(toNumpy(y));
        PyPtr widtharray(toNumpy(width)); 

        PyObject_CallMethod(ax_.get(), "barh", "OOs", yarray.get(), widtharray.get(), fmt.c_str());
        
    }

    void bar_label(const std::vector<double>& bars, const std::vector<std::string>& labels) {
   
        PyPtr barsarray(toNumpy(bars));
        PyPtr labelslist(PyList_New(labels.size())); 

        for (size_t i = 0; i < labels.size(); ++i) {
            PyList_SetItem(labelslist.get(), i, PyUnicode_FromString(labels[i].c_str()));
        }
        
        PyObject_CallMethod(ax_.get(), "bar_label", "OO", barsarray.get(), labelslist.get());
        
    }

    void stem(const std::vector<double>& x, const std::vector<double>& y, const std::string&
 fmt = "b") {
        
        PyPtr xarray(toNumpy(x));
        PyPtr yarray(toNumpy(y));
        
        PyObject_CallMethod(ax_.get(), "stem", "OOs", xarray.get(), yarray.get(), fmt.c_str());
        
    }

    void eventplot(const std::vector<double>& x, const std::string& fmt = "b") {

        PyPtr xarray(toNumpy(x));
        
        PyObject_CallMethod(ax_.get(), "eventplot", "Os", xarray.get(), fmt.c_str());
        
    }   


    void pie(const std::vector<double>& x, const std::vector<std::string>& labels = {}, const std::vector<std::string>& colors = {}) {
       
        PyPtr xarray(toNumpy(x));
        PyPtr labelslist(PyList_New(labels.size())); 


        for (size_t i = 0; i < labels.size(); ++i) {
            PyList_SetItem(labelslist.get(), i, PyUnicode_FromString(labels[i].c_str()));
        }
        PyObject* colorslist = PyList_New(colors.size());
        for (size_t i = 0; i < colors.size(); ++i) {
            PyList_SetItem(colorslist, i, PyUnicode_FromString(colors[i].c_str()));
        }
        
        PyObject_CallMethod(ax_.get(), "pie", "OOO", xarray.get(), labelslist.get(), colorslist);
    
    }


    Axes twinx() {

        PyPtr args(PyTuple_New(0));

        PyPtr twinx(PyObject_GetAttrString(ax_.get(), "twinx"));
        checkAttr(twinx.get(), "twinx");

        PyPtr res(PyObject_Call(twinx.get(), args.get(), nullptr));
        checkResult(res.get(), "twinx");
        
        return Axes(res.get());

    }


    Axes twiny() {

        PyPtr args(PyTuple_New(0));

        PyPtr twiny(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "twiny"));
        checkAttr(twiny.get(), "twiny");

        PyPtr res(PyObject_Call(twiny.get(), args.get(), nullptr));
        checkResult(res.get(), "twiny");
        
        return Axes(res.get());

    }


    void tick_params(const TickParamsConfig& config) {
        


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
            PyObject_GetAttrString(ax_.get(), "tick_params"), args.get(), kwargs.get()));
        checkResult(res.get(), "tick_params");
       

    }

    

}; 

}
