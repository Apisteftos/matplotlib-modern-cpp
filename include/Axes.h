#pragma once

// =============================================================================
// Axes.h - C++ wrapper for matplotlib.axes.Axes
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 07/06/2024
// =============================================================================

#include "Interpreter.h"
#include "PyPtr.h"
#include "NumpyUtils.h"
#include "Configs.h"
#include "Helper.h"
#include "pythonrun.h"
#include "Detail.h"

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


    /**
    * @brief Plots a line graph.
    * @param config plot configuration
    * @throws std::runtime_error if plot fails
    */
    void plot(const PlotConfig& config) {
        detail::plotImpl(ax_.get(), config);
    }

    /**
     * @brief Sets the grid on or off.
     * @param config grid configuration
     * @throws std::runtime_error if grid fails
     */
    void grid(const GridConfig& config) {
        detail::gridImpl(ax_.get(), config);
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


    /**
     * @brief Plots a line graph.
     * @param config plot configuration
     * @throws std::runtime_error if plot fails
     */
    void errorbar(const ErrorbarConfig& config) {
        detail::errorbarImpl(ax_.get(), config);
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

    /**
     * @brief Plots a step graph.
     * @param config step configuration
     * @throws std::runtime_error if step fails
     */
    void loglog(const LogLogConfig& config) {
        detail::loglogImpl(ax_.get(), config);
    }

    /**
     * @brief Plots a step graph.
     * @param config step configuration
     * @throws std::runtime_error if step fails 
     */
    void semilogx(const SemiLogxConfig& config) {
        detail::semilogxImpl(ax_.get(), config);
    }

    /**
     * @brief Plots a step graph.
     * @param config step configuration
     * @throws std::runtime_error if step fails 
     */
    void semilogy(const SemiLogyConfig& config) {
        detail::semilogyImpl(ax_.get(), config);
    }


    /**
     * @brief Fills a polygon.
     * @param config fill configuration
     * @throws std::runtime_error if fill fails
     */
    void fill(const FillConfig& config) {
        detail::fillImpl(ax_.get(), config);
    }

    /**
     * @brief Fills a polygon.
     * @param config fill configuration
     * @throws std::runtime_error if fill fails
     */
    void fill_between(const FillBetweenConfig& config) {
        detail::fillBetweenImpl(ax_.get(), config);
    }

    /**
     * @brief Fills a polygon.
     * @param config fill configuration
     * @throws std::runtime_error if fill fails 
     */
    void fill_betweenx(const FillBetweenxConfig& config) {
        detail::fillBetweenxImpl(ax_.get(), config);
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

    void stem(const std::vector<double>& x, const std::vector<double>& y, const std::string&fmt = "b") {
        
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


    /**
    * @brief Configures the tick parameters.
    * @param config tick parameters configuration
    * @throws std::runtime_error if tick_params fails
    */
    void tick_params(const TickParamsConfig& config) {
        detail::tickParamsImpl(ax_.get(), config);
    }



    /**
    * @brief Plots a step graph.
    * @param config step configuration
    * @throws std::runtime_error if step fails
    */
    void step(const StepConfig& config) {
        detail::stepImpl(ax_.get(), config);
    }

    /**
    * @brief Plots a step graph.
    * @param config step configuration
    * @throws std::runtime_error if step fails
    */
    void legend(const LegendConfig& config = {}) {
        detail::legendImpl(ax_.get(), config);
    }


    

    

}; 

}
