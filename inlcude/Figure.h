#pragma once

// =============================================================================
// Figure.h - C++ wrapper for matplotlib.figure.Figure
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 07/06/2024
// =============================================================================

#include "Axes.h"
#include "matplotlibcpp.h"
#include "PyPtr.h"

#include <vector>

namespace matplotlibcpp {

    class Figure
    {
    private:
        PyPtr fig_;
    public:
        explicit Figure(PyObject* fig) : fig_(fig) {}

        void suptitle(const std::string& title) {
            PyObject_CallMethod(fig_.get(), "suptitle", "s", title.c_str());
        }

        void save(const std::string& filename, const int dpi=0) {
            if(dpi > 0)
                PyObject_CallMethod(fig_.get(), "savefig", "si", filename.c_str(), dpi);
            else
                PyObject_CallMethod(fig_.get(), "savefig", "s", filename.c_str());
        }


        void tight_layout() {
            PyObject_CallMethod(fig_.get(), "tight_layout", nullptr);
        }

        void clf() {
            PyObject_CallMethod(fig_.get(), "clf", nullptr);
        }
        
    };


    std::pair<Figure, std::vector<Axes>> subplots(long nrows, long ncols, std::vector<long> &figsize)
    {
        // needs init because runs before any Python call
        Interpreter::getInstance();
        
        PyPtr args(PyTuple_New(2));
        PyTuple_SetItem(args.get(), 0, PyLong_FromLong(nrows));
        PyTuple_SetItem(args.get(), 1, PyLong_FromLong(ncols));

        PyPtr kwargs(PyDict_New());
        PyPtr fs(PyTuple_New(2));
        PyTuple_SetItem(fs.get(), 0, PyLong_FromLong(figsize[0]));
        PyTuple_SetItem(fs.get(), 1, PyLong_FromLong(figsize[1]));
        PyDict_SetItemString(kwargs.get(), "figsize", fs.get());
        PyDict_SetItemString(kwargs.get(), "squeeze", Py_False);
        
        PyObject* subplots = PyObject_GetAttrString(
        Interpreter::getInstance().getPyplot(), "subplots");
        if (!subplots) throw std::runtime_error("Failed to get subplots function");

        PyPtr res(PyObject_Call(subplots, args.get(), kwargs.get()));
        Py_XDECREF(subplots);
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


}


