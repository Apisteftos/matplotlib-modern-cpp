#pragma once

// =============================================================================
// PyPlot.h - C++ wrapper for matplotlib.pyplot
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 12/06/2024
// =============================================================================

#include "Interpreter.h"
#include "Axes.h"
#include "AxesGrid.h"
#include "Figure.h"
#include "NumpyUtils.h"
#include "Configs.h"
#include "Helper.h"

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

        checkResult(res.get(), "show");

    }

    //TODO: add more parameters to plot


    /**
    * @brief Plots a line graph.
    * @param config plot configuration
    * @throws std::runtime_error if plot fails
    */
    void plot(const PlotConfig& config) {
        detail::plotImpl(Interpreter::getInstance().getPyplot(), config);
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
        checkAttr(subplot.get(), "subplot");
        
        PyPtr res(PyObject_Call(subplot.get(), args.get(), nullptr));
        checkResult(res.get(), "subplot");
        
    }


    /**
     * @brief Calls subplots() function.
     * @param config subplot config
     * @return pair of Figure and vector of Axes
     */
    std::pair<Figure, AxesGrid> subplots(const SubplotsConfig& config = {}){
        
        
        PyPtr args(PyTuple_New(2));
        PyTuple_SetItem(args.get(), 0, PyLong_FromLong(config.nrows));
        PyTuple_SetItem(args.get(), 1, PyLong_FromLong(config.ncols));

        PyPtr kwargs(PyDict_New());
        PyPtr fs(PyTuple_New(2));
        PyTuple_SetItem(fs.get(), 0, PyLong_FromLong(config.figsize[0]));
        PyTuple_SetItem(fs.get(), 1, PyLong_FromLong(config.figsize[1]));
        PyDict_SetItemString(kwargs.get(), "figsize", fs.get());
        PyDict_SetItemString(kwargs.get(), "squeeze", Py_False);
        
        PyPtr subplots(PyObject_GetAttrString(
        Interpreter::getInstance().getPyplot(), "subplots"));
        checkAttr(subplots.get(), "subplots");

        PyPtr res(PyObject_Call(subplots.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "subplots");
            


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

        return std::make_pair(Figure(fig), AxesGrid(std::move(ax_list), config.nrows, config.ncols));
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
        checkAttr(subplot2grid.get(), "subplot2grid");

        PyPtr res(PyObject_Call(subplot2grid.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "subplot2grid");

        return Axes(res.get());
    }



    /**
     * @brief Calls tight_layout() function.
     */
    void tight_layout() {

        PyPtr args(PyTuple_New(0));

        PyPtr tight_layout(PyObject_GetAttrString(
            Interpreter::getInstance().getPyplot(), "tight_layout"));
        checkAttr(tight_layout.get(), "tight_layout");

        PyPtr res(PyObject_Call(tight_layout.get(), args.get(), nullptr));
        checkResult(res.get(), "tight_layout");
    }



    void clf() {
    
        PyPtr args(PyTuple_New(0));

        PyPtr clf(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "clf"));
        checkAttr(clf.get(), "clf");

        PyPtr res(PyObject_Call(clf.get(), args.get(), nullptr));
        checkResult(res.get(), "clf");
        
        

    }


    void cla() {

        PyPtr args(PyTuple_New(0));

        PyPtr cla(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "cla"));
        if (!cla) throw std::runtime_error("failed to get cla function");

        PyPtr res(PyObject_Call(cla.get(), args.get(), nullptr));
        checkResult(res.get(), "cla");

    }



    /**
     * @brief Closes current figure
     */
    void close() { 

        PyPtr args(PyTuple_New(0));

        PyPtr close(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "close"));
        checkAttr(close.get(), "close");

        PyPtr res(PyObject_Call(close.get(), args.get(), nullptr));
        checkResult(res.get(), "close");

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
        checkResult(res.get(), "close");
       

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
        checkResult(res.get(), "close");
        
    }
        

    
    void gca() {

        PyPtr args(PyTuple_New(0));

        PyPtr gca(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "gca"));
        checkAttr(gca.get(), "gca");

        PyPtr res(PyObject_Call(gca.get(), args.get(), nullptr));
        checkResult(res.get(), "gca");

    }


    void gcf() {

        PyPtr args(PyTuple_New(0));

        PyPtr gcf(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "gcf"));
        checkAttr(gcf.get(), "gcf");

        PyPtr res(PyObject_Call(gcf.get(), args.get(), nullptr));
        checkResult(res.get(), "gcf");

    }




    /**
     * @brief Sets the current axes.
     * @param ax axes object
     */
    void sca(const Axes& ax) {

        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, ax.get_axes());

        PyPtr sca(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "sca"));
        checkAttr(sca.get(), "sca");

        PyPtr res(PyObject_Call(sca.get(), args.get(), nullptr));
        checkResult(res.get(), "sca");

    }

    

    /**
     * @brief Sets the title of the current axes.
     * @param tlt title string
     */
    void title(const std::string& tlt) {


        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(tlt.c_str()));

        PyPtr title(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "title"));
        checkAttr(title.get(), "title");
        
        PyPtr res(PyObject_Call(title.get(), args.get(), nullptr));
        checkResult(res.get(), "title");
        
    }

    /**
     * @brief Sets the grid on or off.
     * @param flag if true, grid is on
     */
    void grid(bool flag = true) {

        PyPtr args(PyTuple_New(0));

        if (flag) {
            PyPtr grid(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "grid"));
            checkAttr(grid.get(), "grid");
            
            PyPtr res(PyObject_Call(grid.get(), args.get(), nullptr));
            checkResult(grid.get(), "grid");
        }
        else {
            PyPtr grid(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "grid"));
            checkAttr(grid.get(), "grid");
            
            PyPtr res(PyObject_Call(grid.get(), args.get(), nullptr));
            checkResult(grid.get(), "grid");
        }

    }

    /**
     * @brief Returns the current axes.
     */
    void axes() {
        
        PyPtr args(PyTuple_New(0));
        
        PyPtr axes(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "axes"));
        checkAttr(axes.get(), "axes");
        
        PyPtr res(PyObject_Call(axes.get(), args.get(), nullptr));
        checkResult(res.get(), "axes");
    }


    /**
     * @brief Sets the current axes.
     * @param ax axes object
     */
    void axes(const Axes& ax) {
        
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, ax.get_axes());
        
        PyPtr axes(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "axes"));
        checkAttr(axes.get(), "axes");
        
        PyPtr res(PyObject_Call(axes.get(), args.get(), nullptr));
        checkResult(res.get(), "axes");
    }

    /**
     * @brief Deletes the current axes.
     * @param ax axes object
     */
    void delaxes(const Axes& ax) {
        
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, ax.get_axes());
        
        PyPtr delaxes(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "delaxes"));
        checkAttr(delaxes.get(), "delaxes");
        
        PyPtr res(PyObject_Call(delaxes.get(), args.get(), nullptr));
        checkResult(res.get(), "delaxes");
    }

    /**
    * @brief Checks if figure exists.
    * @param fig figure number
    */
    void fignum_exists(const std::string& fig) {
        
        PyPtr args(PyTuple_New(1));
        PyTuple_SetItem(args.get(), 0, PyUnicode_FromString(fig.c_str()));
        
        PyPtr fignum_exists(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "fignum_exists"));
        checkAttr(fignum_exists.get(), "fignum_exists");
        
        PyPtr res(PyObject_Call(fignum_exists.get(), args.get(), nullptr));
        checkResult(res.get(), "fignum_exists");
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
        checkAttr(figure.get(), "figure");

        PyPtr res(PyObject_Call(figure.get(), args.get(), kwargs.get()));
        checkResult(res.get(), "figure");

        return Figure(res.get());
    }


    /**
     * @brief Returns the figure labels.
     * @return vector of figure labels
     */
    std::vector<std::string> get_figlabels() {

        PyPtr args(PyTuple_New(0));

        PyPtr get_figlabels(PyObject_GetAttrString(Interpreter::getInstance().getPyplot(), "get_figlabels"));
        checkAttr(get_figlabels.get(), "get_figlabels");

        PyPtr res(PyObject_Call(get_figlabels.get(), args.get(), nullptr));
        checkResult(res.get(), "get_figlabels");
        
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
        checkAttr(get_fignums.get(), "get_fignums");

        PyPtr res(PyObject_Call(get_fignums.get(), args.get(), nullptr));
        checkResult(res.get(), "get_fignums");

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


    /**
    * @brief Plots a step graph.
    * @param config step configuration
    * @throws std::runtime_error if step fails
    */
    void step(const StepConfig& config) {
        detail::stepImpl(Interpreter::getInstance().getPyplot(), config);
    }


    /**
    * @brief Configures the tick parameters.
    * @param config tick parameters configuration
    * @throws std::runtime_error if tick_params fails
    */
    void tick_params(const TickParamsConfig& config) {
        detail::tickParamsImpl(Interpreter::getInstance().getPyplot(), config);
    }



};

} // namespace matplotlibcpp