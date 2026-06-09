#pragma once

// =============================================================================
// functions.h - C++ wrapper for matplotlib.pyplot.functions
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 09/06/2024
// =============================================================================

#include "Interpreter.h"
#include "Axes.h"
#include "Figure.h"




namespace matplotlibcpp {



    // ============================================================
    // Free functions - pyplot wrappers
    // ============================================================

    /**
     * @brief Shows the plots.
     * @param block if true, waits for user input.
     */
    inline void show( bool block = true)
    {
        Interpreter::getInstance(); 

        PyPtr args(PyTuple_New(0));

        PyObject* show = PyObject_GetAttrString(
            Interpreter::getInstance().getPyplot(), "show");
        if (!show) throw std::runtime_error("Failed to get show function");

        PyPtr res;
        if(block)
        {
            res.reset(PyObject_Call(show, args.get(), nullptr));
        }
        else
        {
            PyPtr kwargs(PyDict_New());
            PyDict_SetItemString(kwargs.get(), "block", Py_False);
            res.reset(PyObject_Call(show, args.get(), kwargs.get()));
        
        }

        Py_XDECREF(show); 

        if (!res) throw std::runtime_error("Call to show() failed.");

    }

    //TODO: add more parameters to plot


    /**
     * @brief Plots a line graph.
     * @param x x coordinates
     * @param y y coordinates
     * @param format format string
     */
    inline void plot(const std::vector<double>& x, 
                    const std::vector<double>& y, 
                    const std::string& fmt = "b") 
    {
        Interpreter::getInstance(); 

        PyPtr args(PyTuple_New(3));
        PyPtr kwargs(PyDict_New());

        PyTuple_SetItem(args.get(), 0, toNumpy(x));
        PyTuple_SetItem(args.get(), 1, toNumpy(y));
        PyTuple_SetItem(args.get(), 2, PyUnicode_FromString(fmt.c_str()));
        
        PyDict_SetItemString(kwargs.get(), "format", PyUnicode_FromString(fmt.c_str()));
        

        PyPtr plot(PyObject_GetAttrString(
            Interpreter::getInstance().getPyplot(), "plot"));
        if (!plot) throw std::runtime_error("Failed to get plot function");

        PyPtr res(PyObject_Call(plot.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("Call to plot() failed.");
    }



    /**
     * @brief Calls tight_layout() function.
     */
    inline void tight_layout() {
        Interpreter::getInstance();

        PyPtr args(PyTuple_New(0));

        PyPtr tight_layout(PyObject_GetAttrString(
            Interpreter::getInstance().getPyplot(), "tight_layout"));
        if (!tight_layout) throw std::runtime_error("Failed to get tight_layout function"); 

        PyPtr res(PyObject_Call(tight_layout.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("Call to tight_layout() failed.");
    }



    inline void clf() {
        Interpreter::getInstance();

        PyPtr args(PyTuple_New(0));

        PyPtr clf(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "clf"));
        if (!clf) throw std::runtime_error("Failed to get clf function");

        PyPtr res(PyObject_Call(clf.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("Call to clf() failed.");

    }


    inline void cla() {
        Interpreter::getInstance();

        PyPtr args(PyTuple_New(0));

        PyPtr cla(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "cla"));
        if (!cla) throw std::runtime_error("failed to get cla function");

        PyPtr res(PyObject_Call(cla.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to cla() failed.");

    }



    /**
     * @brief Closes current figure
     */
    inline void close() { 

        Interpreter::getInstance();

        PyPtr args(PyTuple_New(0));

        PyPtr close(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "close"));
        if (!close) throw std::runtime_error("failed to get close function");

        PyPtr res(PyObject_Call(close.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to close() failed.");

    }


    /**
     * @brief Closes by string 
     * @param fig figure name
     */
    inline void close(const std::string& fig) { 

        Interpreter::getInstance();

        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(fig.c_str()));

        PyPtr close(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "close"));
        if (!close) throw std::runtime_error("failed to get close function");

        PyPtr res(PyObject_Call(close.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to close() failed.");

    }

    /**
     * @brief Closes by int 
     * @param fig figure number
     */
    inline void close(const int fig) { 
        
        Interpreter::getInstance();

        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyLong_FromLong(fig));

        PyPtr close(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "close"));
        if (!close) throw std::runtime_error("failed to get close function");

        PyPtr res(PyObject_Call(close.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to close() failed.");
    }
        


    inline void gca() {
        Interpreter::getInstance();

        PyPtr args(PyTuple_New(0));

        PyPtr gca(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "gca"));
        if (!gca) throw std::runtime_error("failed to get gca function");

        PyPtr res(PyObject_Call(gca.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to gca() failed.");

    }


    inline void gcf() {
        Interpreter::getInstance();

        PyPtr args(PyTuple_New(0));

        PyPtr gcf(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "gcf"));
        if (!gcf) throw std::runtime_error("failed to get gcf function");

        PyPtr res(PyObject_Call(gcf.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to gcf() failed.");

    }



    inline void get_figlabels() {
        Interpreter::getInstance();

        PyPtr args(PyTuple_New(0));

        PyPtr get_figlabels(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "get_figlabels"));
        if (!get_figlabels) throw std::runtime_error("failed to get get_figlabels function");

        PyPtr res(PyObject_Call(get_figlabels.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to get_figlabels() failed.");

    }



    inline void get_fignums() {
        Interpreter::getInstance();

        PyPtr args(PyTuple_New(0));

        PyPtr get_fignums(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "get_fignums"));
        if (!get_fignums) throw std::runtime_error("failed to get get_fignums function");

        PyPtr res(PyObject_Call(get_fignums.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to get_fignums() failed.");

    }



    inline void sca(const Axes& ax) {

        Interpreter::getInstance();

        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, ax.get_axes());

        PyPtr sca(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "sca"));
        if (!sca) throw std::runtime_error("failed to get sca function");

        PyPtr res(PyObject_Call(sca.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to sca() failed.");

    }

}
