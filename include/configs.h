#pragma once
// =============================================================================
// Configs.h - C++ wrapper for matplotlib.pyplot.configs
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 10/06/2024
// =============================================================================

#include "Figure.h"

#include <string>
#include <vector>
#include <optional>
#include <variant>



namespace matplotlibcpp {



    // =============================================================================
    // Optional types
    // =============================================================================


    using ErrorValue = std::variant<
        double,
        std::vector<double>, 
        std::vector<std::vector<double>>
    >; 


    // =============================================================================
    // Multiple data types
    // =============================================================================

    using DataValue = std::variant<
        double,
        std::vector<double>
    >;



    // =============================================================================
    // Structs for matplotlib.pyplot.plot() 
    // =============================================================================
    


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


    struct ErrorbarConfig {
        DataValue x;
        DataValue y;
        std::optional<ErrorValue> yerr = std::nullopt;
        std::optional<ErrorValue> xerr = std::nullopt;
        std::string fmt = "";
        std::string ecolor = "";
        std::string label = "";
        double capsize = 0.0;
        double alpha = 1.0;
        double linewidth = 1.0;
        double elinewidth; 
    };


    struct ScatterConfig {
        std::vector<double> x;
        std::vector<double> y;
        std::string label = "";
    
    };


    struct StepConfig {
        std::vector<double> x;
        std::vector<double> y;
        std::string label = "";
    };


    struct subplot2gridConfig {

        std::vector<int> shape;
        std::vector<int> loc;
        int rowspan = 1;
        int colspan = 1;
        Figure* fig = nullptr;
        ;
    };



}