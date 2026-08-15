# pragma once

// =============================================================================
// Artist.h - C++ wrapper for matplotlib.artist
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 16/06/2024
// =============================================================================

#include "Interpreter.h"
#include "PyPtr.h"
#include "NumpyUtils.h"
#include "Configs.h"
#include "Helper.h"

#include <memory>
#include <string>
#include <vector>

namespace matplotlibcpp {

class Artist {

private: 
    PyPtr art_;

public:

    Artist() : art_(nullptr) {}
    explicit Artist(PyObject* art) : art_(art) {}

    PyObject* get_artist() const { return art_.get(); }

    

};

} // namespace matplotlibcpp