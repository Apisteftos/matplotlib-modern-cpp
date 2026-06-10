#pragma once
// =============================================================================
// Configs.h - C++ wrapper for matplotlib.pyplot.configs
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 10/06/2024
// =============================================================================


#include <string>
#include <vector>

namespace matplotlibcpp {

    struct FigureConfig {
        int num = 0;
        std::vector<long> figsize = {10, 10};
        float dpi = 100.0f;
        std::string label = "";

    };


    struct AxesConfig {

        
    };

    struct PlotConfig {
        
        std::vector<double> x; 
        std::vector<double> y; 
        std::string fmt = "b";

    };



}