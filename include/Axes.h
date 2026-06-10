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

    void plot(const std::vector<double>& x, 
              const std::vector<double>& y, 
              const std::string& fmt = "b")
    {
        PyPtr xarray(toNumpy(x));
        PyPtr yarray(toNumpy(y));
        
        PyObject_CallMethod(ax_.get(), "plot",      "OOs", xarray.get(), yarray.get(), fmt.c_str());

    }

    void grid(bool flag = true){
        PyObject_CallMethod(ax_.get(), "grid", "O", flag ? Py_True : Py_False);
    }

    void set_title(const std::string& title) {
        PyObject_CallMethod(ax_.get(), "set_title", "s", title.c_str());
    }

    void set_xlabel(const std::string& label) {
        PyObject_CallMethod(ax_.get(), "set_xlabel", "s", label.c_str());
    }

    void set_ylabel(const std::string& label) {
        PyObject_CallMethod(ax_.get(), "set_ylabel", "s", label.c_str());
    }

    void set_xlim(double left, double right) {
        PyObject_CallMethod(ax_.get(), "set_xlim", "dd", left, right);
    }

    void set_ylim(double bottom, double top) {
        PyObject_CallMethod(ax_.get(), "set_ylim", "dd", bottom, top);
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

    void stem(const std::vector<double>& x, const std::vector<double>& y, const std::string& fmt = "b") {
        
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




}; 

}
