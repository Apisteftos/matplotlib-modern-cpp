#pragma once 

// =============================================================================
// AxesGrid.h - C++ wrapper for matplotlib.pyplot.AxesGrid
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 16/06/2024
// =============================================================================

#include "Axes.h"

#include <string>
#include <vector>

namespace matplotlibcpp {

    class AxesGrid {

        public:
            AxesGrid(std::vector<Axes>&& axes, long nrows, long ncols)
                : axes_(std::move(axes)), nrows_(nrows), ncols_(ncols) {}

            Axes& operator[](long row, long col) {
                return axes_[row * ncols_ + col];
            }
                

            Axes& operator[](long i) {
                return axes_[i];
            }

            size_t size() const { return axes_.size(); }

        private:
            std::vector<Axes> axes_;
            long nrows_, ncols_;
    };


} // namespace matplotlibcpp

    