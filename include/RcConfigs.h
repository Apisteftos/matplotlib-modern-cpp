#pragma once

// =============================================================================
// RcConfigs.h - C++ wrapper for matplotlib.rcParams
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 16/08/2024
// =============================================================================

#include "Configs.h"


#include <iostream>
#include <map>
#include <string>
#include <numeric>

namespace matplotlibcpp {


    // =============================================================================
    // Structs for rcParams
    // =============================================================================

     struct RcConfig {
        std::string group; 

        // rc kwargs parameters
        std::map<std::string, RcValue> kwargs;
    };  



    struct GridRcConfig {
        std::string group; 

        // rc kwargs parameters for major and minor grid lines as well. 
        std::optional<std::string> color            = std::nullopt;
        std::optional<std::string> linestyle        = std::nullopt;
        std::optional<double> linewidth             = std::nullopt;
        std::optional<double> alpha                 = std::nullopt;
     
    };


    struct LegendRcConfig {
        std::string group; 

        // rc kwargs parameters for legend
        std::optional<LegendLocValue> loc                = std::nullopt;
        std::optional<bool> frameon                      = std::nullopt;
        std::optional<double> framealpha                 = std::nullopt;
        std::optional<std::string> facecolor             = std::nullopt;
        std::optional<std::string> edgecolor             = std::nullopt;  
        std::optional<double> linewidth                  = std::nullopt;
        std::optional<bool> fancybox                     = std::nullopt;
        // TODO: shadow
        std::optional<int> numpoints                     = std::nullopt;
        std::optional<int> scatterpoints                 = std::nullopt;
        std::optional<FontSizeValue> fontsize            = std::nullopt;
        std::optional<LabelcolorValue> labelcolor        = std::nullopt;
        std::optional<TitleFontSizeValue> title_fontsize = std::nullopt;
        std::optional<double> borderpad                  = std::nullopt;
        std::optional<double> labelspacing               = std::nullopt;
        std::optional<double> handlelength               = std::nullopt;
        std::optional<double> handleheight               = std::nullopt;
        std::optional<double> handletextpad              = std::nullopt;
        std::optional<double> borderaxespad              = std::nullopt;
        std::optional<double> columnspacing              = std::nullopt;


    };




    struct TicksRcConfig {
        std::string group; 

        // rc kwargs parameters for x - y ticks
        std::optional<bool> top                         = std::nullopt;
        std::optional<bool> bottom                      = std::nullopt;
        std::optional<bool> labeltop                    = std::nullopt;
        std::optional<bool> labelbottom                 = std::nullopt;
        std::optional<double> size                      = std::nullopt;
        std::optional<double> width                     = std::nullopt;
        std::optional<double> pad                       = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> labelcolor           = std::nullopt;
        std::optional<LabelsizeValue> labelsize         = std::nullopt;
        std::optional<std::string> direction            = std::nullopt;
        std::optional<bool> visible                     = std::nullopt;
        std::optional<TickNdivsValue> ndivs             = std::nullopt;
        std::optional<std::string> alignment            = std::nullopt;
        std::optional<bool> left                        = std::nullopt;
        std::optional<bool> right                       = std::nullopt;
        std::optional<bool> labelleft                   = std::nullopt;
        std::optional<bool> labelright                  = std::nullopt;

        
    };


    struct BoxplotRcConfig {
        std::string group;

        // rc kwargs parameters for boxplot
        std::optional<bool> notch                       = std::nullopt;
        std::optional<bool> vertical                    = std::nullopt;
        std::optional<WhisValue> whisker                = std::nullopt;
        std::optional<int> bootstrap                    = std::nullopt;
        std::optional<bool> patchartist                 = std::nullopt;
        std::optional<bool> showmeans                   = std::nullopt;
        std::optional<bool> showcaps                    = std::nullopt;
        std::optional<bool> showbox                     = std::nullopt;
        std::optional<bool> showfliers                  = std::nullopt;
        std::optional<bool> meanline                    = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> marker               = std::nullopt;
        std::optional<std::string> markerfacecolor      = std::nullopt;
        std::optional<std::string> markeredgecolor      = std::nullopt;
        std::optional<double> markeredgewidth           = std::nullopt;
        std::optional<double> markersize                = std::nullopt;
        std::optional<std::string> linestyle            = std::nullopt;
        std::optional<double> linewidth                 = std::nullopt;


    };



    struct FontRcConfig {
        std::string group; 

        // rc kwargs parameters for font
        std::optional<std::string> family              = std::nullopt;
        std::optional<std::string> style               = std::nullopt;
        std::optional<std::string> variant             = std::nullopt;
        std::optional<FontWeightValue> weight          = std::nullopt;
        std::optional<FontStretchValue> stretch        = std::nullopt;
        std::optional<double> size                     = std::nullopt;
        StrVec serif                                   = {};
        StrVec sansserif                               = {};
        StrVec cursive                                 = {};
        StrVec fantasy                                 = {};
        StrVec monospace                               = {};
        std::optional<bool> enable_last_resort         = std::nullopt;


    };


    struct LinesRcConfig {
        std::string group; 
        
        // rc kwargs parameters for lines
        std::optional<double> linewidth               = std::nullopt;
        std::optional<std::string> linestyle          = std::nullopt;
        std::optional<std::string> color              = std::nullopt;
        std::optional<std::string> marker             = std::nullopt;
        std::optional<std::string> markerfacecolor    = std::nullopt;
        std::optional<std::string> markeredgecolor    = std::nullopt;
        std::optional<double> markeredgewidth         = std::nullopt;
        std::optional<double> markersize              = std::nullopt;
        std::optional<std::string> dash_joinstyle     = std::nullopt;
        std::optional<std::string> dash_capstyle      = std::nullopt;
        std::optional<std::string> solid_joinstyle    = std::nullopt;
        std::optional<std::string> solid_capstyle     = std::nullopt;
        std::optional<bool> antialiased               = std::nullopt;
        Vec dashed_pattern                            = {};            
        Vec dashdot_pattern                           = {};   
        Vec dotted_pattern                            = {};            
        std::optional<bool> scale_dashes              = std::nullopt;

    };


    struct AxesRcConfig {
        std::string group; 
        
        // rc kwargs parameters for axes
        std::optional<std::string> facecolor         = std::nullopt;
        std::optional<std::string> edgecolor         = std::nullopt;
        std::optional<double> linewidth              = std::nullopt;
        std::optional<bool> grid                     = std::nullopt;
        std::optional<std::string> axis              = std::nullopt;
        std::optional<std::string> which             = std::nullopt;
        std::optional<std::string> titlelocation     = std::nullopt;
        std::optional<std::string> titlesize         = std::nullopt; 
        std::optional<std::string> titleweight       = std::nullopt;
        std::optional<std::string> titlecolor        = std::nullopt;
        std::optional<std::string> titley            = std::nullopt;
        std::optional<double> titlepad               = std::nullopt;
        std::optional<std::string> labelsize         = std::nullopt;
        std::optional<double> labelpad               = std::nullopt;
        std::optional<std::string> labelweight       = std::nullopt;
        std::optional<std::string> labelcolor        = std::nullopt;
        std::optional<std::string> axisbelow         = std::nullopt;
        Vec limits                                   = {};
        std::optional<bool> use_locale               = std::nullopt;
        std::optional<bool> use_mathtext             = std::nullopt;
        std::optional<int> min_exponent              = std::nullopt;
        std::optional<bool> useoffset                = std::nullopt;
        std::optional<int> offset_threshold          = std::nullopt;
        std::optional<bool> left                     = std::nullopt;
        std::optional<bool> bottom                   = std::nullopt;
        std::optional<bool> top                      = std::nullopt;
        std::optional<bool> right                    = std::nullopt;
        // TODO: prop_cycle
        std::optional<double> xmargin                = std::nullopt;
        std::optional<double> ymargin                = std::nullopt;
        std::optional<double> zmargin                = std::nullopt;
        std::optional<std::string> autolimit_mode    = std::nullopt;

    };


    struct FigureRcConfig {
        std::string group; 
        
        // rc kwargs parameters for figure
        std::optional<std::string> titlesize         = std::nullopt; 
        std::optional<std::string> titleweight       = std::nullopt;
        std::optional<std::string> labelsize         = std::nullopt;
        std::optional<std::string> labelweight       = std::nullopt;
        Vec figsize                                  = {};
        std::optional<double> dpi                    = std::nullopt;
        std::optional<std::string> facecolor         = std::nullopt;
        std::optional<std::string> edgecolor         = std::nullopt;
        std::optional<bool> frameon                  = std::nullopt;
        std::optional<int> max_open_warning          = std::nullopt;
        std::optional<bool> raise_window             = std::nullopt;
        std::optional<double> left                   = std::nullopt;
        std::optional<double> right                  = std::nullopt;
        std::optional<double> top                    = std::nullopt;
        std::optional<double> bottom                 = std::nullopt;
        std::optional<double> wspace                 = std::nullopt;
        std::optional<double> hspace                 = std::nullopt;
        std::optional<bool> autolayout               = std::nullopt;
        std::optional<bool> use                      = std::nullopt;
        std::optional<double> h_pad                  = std::nullopt;
        std::optional<double> w_pad                  = std::nullopt;
    };



} // namespace matplotlibcpp