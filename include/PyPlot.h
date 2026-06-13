#pragma once

// =============================================================================
// PyPlot.h - C++ wrapper for matplotlib.pyplot
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 12/06/2024
// =============================================================================

#include "Interpreter.h"
#include "Axes.h"
#include "Figure.h"
#include "numpy_utils.h"
#include "configs.h"


#include <map>



namespace matplotlibcpp {

class PyPlot {

public:

    PyPlot( ) {
        Interpreter::getInstance();
    }



    // ============================================================
    // functions - pyplot wrappers
    // ============================================================

    /**
     * @brief Shows the plots.
     * @param block if true, waits for user input.
     */
    void show( bool block = true){

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
    void plot(const std::vector<double>& x, 
              const std::vector<double>& y, 
              const std::string& fmt = "b") {


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
     * @brief Calls subplot() function.
     * @param nrows number of rows
     * @param ncols number of columns
     * @param plot_number subplot number
     */
    void subplot(long nrows, long ncols, long plot_number) {


        PyPtr args(PyTuple_New(3));
        PyTuple_SetItem(args.get(), 0, PyLong_FromLong(nrows));
        PyTuple_SetItem(args.get(), 1, PyLong_FromLong(ncols));
        PyTuple_SetItem(args.get(), 2, PyLong_FromLong(plot_number));

        PyPtr subplot(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "subplot"));
        if (!subplot) throw std::runtime_error("failed to get subplot function");
        
        PyPtr res(PyObject_Call(subplot.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to subplot() failed.");
        
    }


    /**
     * @brief Calls subplots() function.
     * @param nrows number of rows
     * @param ncols number of columns
     * @param figsize size of each subplot
     * @return pair of Figure and vector of Axes
     */
    std::pair<Figure, std::vector<Axes>> subplots(
        long nrows, 
        long ncols, 
        std::vector<long> &figsize){
        
        
        PyPtr args(PyTuple_New(2));
        PyTuple_SetItem(args.get(), 0, PyLong_FromLong(nrows));
        PyTuple_SetItem(args.get(), 1, PyLong_FromLong(ncols));

        PyPtr kwargs(PyDict_New());
        PyPtr fs(PyTuple_New(2));
        PyTuple_SetItem(fs.get(), 0, PyLong_FromLong(figsize[0]));
        PyTuple_SetItem(fs.get(), 1, PyLong_FromLong(figsize[1]));
        PyDict_SetItemString(kwargs.get(), "figsize", fs.get());
        PyDict_SetItemString(kwargs.get(), "squeeze", Py_False);
        
        PyPtr subplots(PyObject_GetAttrString(
        Interpreter::getInstance().getPyplot(), "subplots"));
        if (!subplots) throw std::runtime_error("Failed to get subplots function");

        PyPtr res(PyObject_Call(subplots.get(), args.get(), kwargs.get()));
        if(!res) throw std::runtime_error("Call to subplots() failed.");


        PyObject* fig  = PyTuple_GetItem(res.get(), 0);
        PyObject* axes = PyTuple_GetItem(res.get(), 1);

        Py_INCREF(fig); 

        std::vector<Axes> ax_list;
        // 2D numpy array
        if (PyArray_Check(axes)) {
            PyArrayObject* arr = reinterpret_cast<PyArrayObject*>(axes);
            npy_intp total = PyArray_SIZE(arr);
            PyObject* flat = PyArray_Flatten(arr, NPY_CORDER);
            PyArrayObject* flat_arr = reinterpret_cast<PyArrayObject*>(flat);
            for (npy_intp i = 0; i < total; ++i) {
                PyObject* ax = *reinterpret_cast<PyObject**>(PyArray_GETPTR1(flat_arr, i));
                Py_INCREF(ax);
                ax_list.emplace_back(ax);
            }
            Py_DECREF(flat);
        } else {
            Py_INCREF(axes);
            ax_list.emplace_back(axes);
        }

        return std::make_pair(Figure(fig), std::move(ax_list));
    }


    /**
     * @brief Calls subplot2grid() function.
     * @param config subplot2gridConfig struct
     */
    Axes subplot2grid(const subplot2gridConfig& config) {


        PyPtr shape(PyTuple_New(2));    
        PyTuple_SetItem(shape.get(), 0, PyLong_FromLong(config.shape[0]));
        PyTuple_SetItem(shape.get(), 1, PyLong_FromLong(config.shape[1]));

        PyPtr loc(PyTuple_New(2));    
        PyTuple_SetItem(loc.get(), 0, PyLong_FromLong(config.loc[0]));
        PyTuple_SetItem(loc.get(), 1, PyLong_FromLong(config.loc[1]));

        PyPtr args(PyTuple_New(2));
        PyTuple_SetItem(args.get(), 0, shape.get());
        PyTuple_SetItem(args.get(), 1, loc.get());

        PyPtr kwargs(PyDict_New());
        PyDict_SetItemString(kwargs.get(), "rowspan", PyLong_FromLong(config.rowspan));
        PyDict_SetItemString(kwargs.get(), "colspan", PyLong_FromLong(config.colspan));

        if (config.fig != nullptr) {
            PyDict_SetItemString(kwargs.get(), "fig", config.fig->get_figure());
        }


        PyPtr subplot2grid(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "subplot2grid"));
        if (!subplot2grid) throw std::runtime_error("Failed to get subplot2grid function");

        PyPtr res(PyObject_Call(subplot2grid.get(), args.get(), kwargs.get()));
        if (!res) throw std::runtime_error("Call to subplot2grid() failed.");

        return Axes(res.get());
    }




    /**
     * @brief Calls tight_layout() function.
     */
    void tight_layout() {

        PyPtr args(PyTuple_New(0));

        PyPtr tight_layout(PyObject_GetAttrString(
            Interpreter::getInstance().getPyplot(), "tight_layout"));
        if (!tight_layout) throw std::runtime_error("Failed to get tight_layout function"); 

        PyPtr res(PyObject_Call(tight_layout.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("Call to tight_layout() failed.");
    }



    void clf() {
    
        PyPtr args(PyTuple_New(0));

        PyPtr clf(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "clf"));
        if (!clf) throw std::runtime_error("Failed to get clf function");

        PyPtr res(PyObject_Call(clf.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("Call to clf() failed.");

    }


    void cla() {

        PyPtr args(PyTuple_New(0));

        PyPtr cla(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "cla"));
        if (!cla) throw std::runtime_error("failed to get cla function");

        PyPtr res(PyObject_Call(cla.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to cla() failed.");

    }



    /**
     * @brief Closes current figure
     */
    void close() { 

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
    void close(const std::string& fig) { 


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
    void close(const int fig) { 

        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyLong_FromLong(fig));

        PyPtr close(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "close"));
        if (!close) throw std::runtime_error("failed to get close function");

        PyPtr res(PyObject_Call(close.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to close() failed.");
    }
        

    
    void gca() {

        PyPtr args(PyTuple_New(0));

        PyPtr gca(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "gca"));
        if (!gca) throw std::runtime_error("failed to get gca function");

        PyPtr res(PyObject_Call(gca.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to gca() failed.");

    }


    void gcf() {

        PyPtr args(PyTuple_New(0));

        PyPtr gcf(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "gcf"));
        if (!gcf) throw std::runtime_error("failed to get gcf function");

        PyPtr res(PyObject_Call(gcf.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to gcf() failed.");

    }





    void sca(const Axes& ax) {

        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, ax.get_axes());

        PyPtr sca(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "sca"));
        if (!sca) throw std::runtime_error("failed to get sca function");

        PyPtr res(PyObject_Call(sca.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to sca() failed.");

    }

    

    /**
     * @brief Sets the title of the current axes.
     * @param tlt title string
     */
    void title(const std::string& tlt) {


        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(tlt.c_str()));

        PyPtr title(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "title"));
        if (!title) throw std::runtime_error("failed to get title function");
        
        PyPtr res(PyObject_Call(title.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to title() failed.");
        
    }

    /**
     * @brief Sets the grid on or off.
     * @param flag if true, grid is on
     */
    void grid(bool flag = true) {

        PyPtr args(PyTuple_New(0));

        if (flag) {
            PyPtr grid(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "grid"));
            if (!grid) throw std::runtime_error("failed to get grid function");
            
            PyPtr res(PyObject_Call(grid.get(), args.get(), nullptr));
            if (!res) throw std::runtime_error("call to grid() failed.");
        }
        else {
            PyPtr grid(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "grid"));
            if (!grid) throw std::runtime_error("failed to get grid function");
            
            PyPtr res(PyObject_Call(grid.get(), args.get(), nullptr));
            if (!res) throw std::runtime_error("call to grid() failed.");
        }

    }

    /**
     * @brief Returns the current axes.
     */
    void axes() {
        
        PyPtr args(PyTuple_New(0));
        
        PyPtr axes(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "axes"));
        if (!axes) throw std::runtime_error("Failed to get axes function");
        
        PyPtr res(PyObject_Call(axes.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to axes() failed.");
    }


    /**
     * @brief Sets the current axes.
     * @param ax axes object
     */
    void axes(const Axes& ax) {
        
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, ax.get_axes());
        
        PyPtr axes(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "axes"));
        if (!axes) throw std::runtime_error("Failed to get axes function");
        
        PyPtr res(PyObject_Call(axes.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to axes() failed.");
    }

    /**
     * @brief Deletes the current axes.
     * @param ax axes object
     */
    void delaxes(const Axes& ax) {
        
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, ax.get_axes());
        
        PyPtr delaxes(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "delaxes"));
        if (!delaxes) throw std::runtime_error("Failed to get delaxes function");
        
        PyPtr res(PyObject_Call(delaxes.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to delaxes() failed.");
    }

    /**
    * @brief Checks if figure exists.
    * @param fig figure number
    */
    void fignum_exists(const std::string& fig) {
        
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(fig.c_str()));
        
        PyPtr fignum_exists(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "fignum_exists"));
        if (!fignum_exists) throw std::runtime_error("Failed to get fignum_exists function");
        
        PyPtr res(PyObject_Call(fignum_exists.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to fignum_exists() failed.");
    }


    /**
     * @brief Creates a new figure.
     * @param config figure configuration
     * @return Figure
     */
    Figure figure(const FigureConfig& config){

        PyPtr args(PyTuple_New(1));  
        PyTuple_SetItem(args.get(), 0, PyLong_FromLong(config.num));

        PyPtr fs(PyTuple_New(2));
        PyTuple_SetItem(fs.get(), 0, PyLong_FromLong(config.figsize[0]));
        PyTuple_SetItem(fs.get(), 1, PyLong_FromLong(config.figsize[1]));

        PyPtr kwargs(PyDict_New());
        PyDict_SetItemString(kwargs.get(), "figsize", fs.get());
        PyDict_SetItemString(kwargs.get(), "dpi", PyFloat_FromDouble(config.dpi));
        PyDict_SetItemString(kwargs.get(), "label", PyUnicode_FromString(config.label.c_str()));

        PyPtr figure(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "figure"));
        if (!figure) throw std::runtime_error("Failed to get figure function");

        PyPtr res(PyObject_Call(figure.get(), args.get(), kwargs.get()));
        if (!res) throw std::runtime_error("Call to figure() failed");

        return Figure(res.get());
    }


    /**
     * @brief Returns the figure labels.
     * @return vector of figure labels
     */
    std::vector<std::string> get_figlabels() {

        PyPtr args(PyTuple_New(0));

        PyPtr get_figlabels(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "get_figlabels"));
        if (!get_figlabels) throw std::runtime_error("failed to get get_figlabels function");

        PyPtr res(PyObject_Call(get_figlabels.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to get_figlabels() failed.");
        
        std::vector<std::string> labels;

        Py_ssize_t size = PyList_Size(res.get());
        labels.reserve(size);

        for (Py_ssize_t i = 0; i < size; ++i) {
            PyObject* label = PyList_GetItem(res.get(), i); 
            if (label && PyUnicode_Check(label)) {
                labels.emplace_back(PyUnicode_AsUTF8(label));
            }
        }
        
        return labels;
    }

    /**
     * @brief Returns the figure numbers.
     * @return vector of figure numbers
     */
    std::vector<int> get_fignums() {

        PyPtr args(PyTuple_New(0));

        PyPtr get_fignums(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "get_fignums"));
        if (!get_fignums) throw std::runtime_error("failed to get get_fignums function");

        PyPtr res(PyObject_Call(get_fignums.get(), args.get(), nullptr));
        if (!res) throw std::runtime_error("call to get_fignums() failed.");

        std::vector<int> nums;
        
        Py_ssize_t size = PyList_Size(res.get());
        nums.reserve(size);

        for (Py_ssize_t i = 0; i < size; ++i) {
            PyObject* num = PyList_GetItem(res.get(), i); 
            if (num && PyLong_Check(num)) {
                nums.emplace_back(PyLong_AsLong(num));
            }
        }
        
        
        return nums;
    }



};

} // namespace matplotlibcpp