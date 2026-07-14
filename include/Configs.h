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
    // Enums
    // =============================================================================

    // TickParamsConfig
    enum class Axis {
        X,
        Y,
        Both
    };

    // TickParamsConfig, GridConfig
    enum class Which {
        Major,
        Minor,
        Both
    };

    // TickParamsConfig
    enum class Direction {
        In,
        Out,
        InOut
    };


    // XLabelConfig - YLabelConfig
    enum class Loc {
        BOTTOM,
        TOP,
        CENTER
    };

    // StepConfig
    enum class Where{
        PRE,
        POST,
        MID
    };

    // LogLogConfig
    enum class NonPositive {
        Mask,
        Clip
    };

    // FillBetweenConfig
    enum class Step {
        Pre,
        Post,
        Mid
    };

    // align enum
    enum class BarAlign {
        Center,
        Edge
    };

    
    // =============================================================================
    // Free functions converting enums to strings
    // =============================================================================

    /**
    * @brief Converts Axis enum to string
    * @param a default is Axis::Both
    */
    inline const char* toString(Axis a) {
        switch (a) {
            case Axis::X:    return "x";
            case Axis::Y:    return "y";
            case Axis::Both: return "both";
        }
        return "both";
    }

    /**
    * @brief Converts Which enum to string
    * @param w default is Which::Major
    */
    inline const char* toString(Which w) {
        switch (w) {
            case Which::Major: return "major";
            case Which::Minor: return "minor";
            case Which::Both:  return "both";
        }
        return "major";
    }

    /**
     * @brief Converts Direction enum to string
     * @param d default is Direction::In
     */
    inline const char* toString(Direction d) {
        switch (d) {
            case Direction::In:     return "in";
            case Direction::Out:    return "out";
            case Direction::InOut:  return "inout";
        }

        return "in";
    }

    /**
     * @brief Converts Loc enum to string
     * @param l default is Loc::BOTTOM
     */
    inline const char* toString(Loc l) {
        switch (l) {
            case Loc::BOTTOM: return "bottom";
            case Loc::TOP:    return "top";
            case Loc::CENTER: return "center";
        }
        return "center";
    }


    /**
     * @brief Converts Where enum to string
     * @param w default is Where::PRE
     */
    inline const char* toString(Where w) {
        switch (w) {
            case Where::PRE: return "pre";
            case Where::POST: return "post";
            case Where::MID: return "mid";
        }
        return "pre";
    }


    /**
     * @brief Converts NonPositive enum to string
     * @param w default is NonPositive::Mask
     */
    inline const char* toString(NonPositive w) {
        switch (w) {
            case NonPositive::Mask: return "mask";
            case NonPositive::Clip: return "clip";
        }
        return "clip";
    }


    /**
     * @brief Converts Step enum to string
     * @param w default is Step::Mid    
     */
    inline const char* toString(Step w) {
        switch (w) {
            case Step::Pre: return "pre";
            case Step::Post: return "post";
            case Step::Mid: return "mid";
        }
        return "mid";
    }

    /**
     * @brief Converts BarAlign enum to string
     * @param a default is BarAlign::Center
     */
    inline const char* toString(BarAlign a) {
        switch (a) {
            case BarAlign::Center: return "center";
            case BarAlign::Edge:   return "edge";
        }
        return "center";
    }




    // ============================================================
    // Vec - a vector of doubles with element-wise operators
    // ============================================================

    struct Vec : std::vector<double> {
        using std::vector<double>::vector;  

        // ============================================================
        // Element-wise comparison operators — return bool mask
        // ============================================================
        std::vector<bool> operator>(const Vec& other) const {
            std::vector<bool> result(size());
            std::transform(begin(), end(), other.begin(), result.begin(),
                [](double a, double b) { return a > b; });
            return result;
        }

        std::vector<bool> operator<(const Vec& other) const {
            std::vector<bool> result(size());
            std::transform(begin(), end(), other.begin(), result.begin(),
                [](double a, double b) { return a < b; });
            return result;
        }

        std::vector<bool> operator>=(const Vec& other) const {
            std::vector<bool> result(size());
            std::transform(begin(), end(), other.begin(), result.begin(),
                [](double a, double b) { return a >= b; });
            return result;
        }

        std::vector<bool> operator<=(const Vec& other) const {
            std::vector<bool> result(size());
            std::transform(begin(), end(), other.begin(), result.begin(),
                [](double a, double b) { return a <= b; });
            return result;
        }

        std::vector<bool> operator==(const Vec& other) const {
            std::vector<bool> result(size());
            std::transform(begin(), end(), other.begin(), result.begin(),
                [](double a, double b) { return a == b; });
            return result;
        }

        // ============================================================
        // Element-wise arithmetic operators — like numpy
        // ============================================================
        Vec operator+(const Vec& other) const {
            Vec result(size());
            std::transform(begin(), end(), other.begin(), result.begin(),
                std::plus<double>());
            return result;
        }

        Vec operator-(const Vec& other) const {
            Vec result(size());
            std::transform(begin(), end(), other.begin(), result.begin(),
                std::minus<double>());
            return result;
        }

        Vec operator*(const Vec& other) const {
            Vec result(size());
            std::transform(begin(), end(), other.begin(), result.begin(),
                std::multiplies<double>());
            return result;
        }

        Vec operator/(const Vec& other) const {
            Vec result(size());
            std::transform(begin(), end(), other.begin(), result.begin(),
                std::divides<double>());
            return result;
        }

        // scalar versions
        Vec operator*(double scalar) const {
            Vec result(size());
            std::transform(begin(), end(), result.begin(),
                [scalar](double v) { return v * scalar; });
            return result;
        }

        Vec operator/(double scalar) const {
            Vec result(size());
            std::transform(begin(), end(), result.begin(),
                [scalar](double v) { return v / scalar; });
            return result;
        }

        Vec operator+(double scalar) const {
            Vec result(size());
            std::transform(begin(), end(), result.begin(),
                [scalar](double v) { return v + scalar; });
            return result;
        }

        Vec operator-(double scalar) const {
            Vec result(size());
            std::transform(begin(), end(), result.begin(),
                [scalar](double v) { return v - scalar; });
            return result;
        }
    };



    // =============================================================================
    // Optional types
    // =============================================================================

    // errorbar parameters
    using ErrorValue = std::variant<
        double,
        std::vector<double>, 
        std::vector<std::vector<double>>
    >; 

    // tick_params parameters
    using LabelsizeValue = std::variant<
        double,
        std::string
    >;


    // =============================================================================
    // Multiple data types
    // =============================================================================

    // Errorbar parameters
    using DataValue = std::variant<
        double,
        std::vector<double>
    >;


    // errorbar parameters
    using LimValue = std::variant<
        bool,
        std::vector<bool>
    >;

    // errorbar parameters
    using ErrorEveryValue = std::variant<
        int,
        std::pair<int, int>
    >;

    // scatter parameters
    using SizeValue = std::variant<
        double,
        Vec
    >;

    // scatter parameters
    using LinewidthsValue = std::variant<
        double, 
        Vec
    >;

    // scatter parameters
    using ColorValue = std::variant<
        std::string, 
        Vec
    >;


    // mosaic parameters
    using MosaicValue = std::variant<
        std::string,                             
        std::vector<std::vector<std::string>>     
    >;

    // fig_kw parameters
    using SizeInchesValue = std::variant<
        std::pair<double, double>,
        double
    >;


    // bar parameters
    using BarXValue = std::variant<
        double,
        Vec, 
        std::vector<std::string> 
    >;

    // barh parameters
    using BarYValue = std::variant<
        double,
        Vec,
        std::vector<std::string>
    >;

    // bar parameters
    using BarValue = std::variant<
        double,
        Vec
    >;


    // fill_between parameters
    using LinewidthValue = std::variant<
        double,
        std::vector<double>
    >;


    // bar parameters
    using TickLabelValue = std::variant<
        std::string,
        std::vector<std::string>
    >;


    // text parameters
    using FontSizeValue = std::variant<
        double,
        std::vector<std::string>
    >;

    // text parameters
    using FontStretchValue = std::variant<
        int,           
        std::string    
    >;

    // text parameters
    using FontWeightValue = std::variant<
        int,           
        std::string    
    >;

    // text parameters
    using LineSpacingValue = std::variant<
        double,         
        std::string   
    >;


    // text parameters
    using RotationValue = std::variant<
        double,         
        std::string   
    >;


    // =============================================================================
    // General reusable structs
    // =============================================================================

    /**
    * @brief Color limits for colormap normalization
    * @note: .clim = {vmin, vmax}
    */
    struct Clim {
        double vmin;
        double vmax;
    };

    /**
     * @brief Struct for x, y coordinates 
     */ 
    struct XY {
        double x;
        double y;
    };

    /**
     * @brief Struct for x, y coordinates for the text position
     */
    struct Position {
        double x;
        double y;
    };


    /**
    * @brief Struct for sketch parameters
    */
    struct SketchParams {
        double scale       = 1.0;    
        double length      = 128.0;  
        double randomness  = 16.0;  
    };

    /**
    * @brief Struct for bounds with coordinates
    */
    struct Bounds {
        double left   = 0.0;
        double bottom = 0.0;
        double width  = 0.0;
        double height = 0.0;
    };
    


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
        
        std::optional<DataValue> x = std::nullopt;
        DataValue y; 
        bool scalex = true;
        bool scaley = true;

        // optional
        std::optional<std::string> fmt = std::nullopt;
        
        // kwargs
        std::optional<std::string> color          = std::nullopt;
        std::optional<std::string> label          = std::nullopt;
        std::optional<double> alpha               = std::nullopt;
        std::optional<double> linewidth           = std::nullopt;
        std::optional<std::string> linestyle      = std::nullopt;
        std::optional<std::string> marker         = std::nullopt;
        std::optional<double> markersize          = std::nullopt;
        std::optional<std::string> markerfacecolor = std::nullopt;
        std::optional<std::string> markeredgecolor = std::nullopt;
        std::optional<double> markeredgewidth     = std::nullopt;
        std::optional<std::string> drawstyle      = std::nullopt;
        std::optional<std::string> fillstyle      = std::nullopt;

    };


    struct ErrorbarConfig {
        DataValue x;
        DataValue y;
        
        // optional
        std::optional<ErrorValue> yerr            = std::nullopt;
        std::optional<ErrorValue> xerr            = std::nullopt;
        std::optional<std::string> fmt            = std::nullopt;
        std::optional<std::string> ecolor         = std::nullopt;
        std::optional<double> elinewidth          = std::nullopt;
        std::optional<double> capsize             = 0.0;
        std::optional<double> capthick            = std::nullopt;
        std::optional<bool> barsabove             = false;

        // limit arrows
        std::optional<LimValue> lolims            = false;
        std::optional<LimValue> uplims            = false;
        std::optional<LimValue> xlolims           = false;
        std::optional<LimValue> xuplims           = false;

        // errorevery — int or (start, N) e.g. .errorevery={4, 2} 
        std::optional<ErrorEveryValue> errorevery = 1;

        // kwargs
        std::optional<std::string> color          = std::nullopt;
        std::optional<std::string> label          = std::nullopt;
        std::optional<double> alpha               = std::nullopt;
        std::optional<double> linewidth           = std::nullopt;
        std::optional<std::string> linestyle      = std::nullopt;
        std::optional<std::string> marker         = std::nullopt;
        std::optional<double> markersize          = std::nullopt;
        std::optional<std::string> markerfacecolor = std::nullopt;
        std::optional<std::string> markeredgecolor = std::nullopt;
        std::optional<double> markeredgewidth     = std::nullopt;
        std::optional<std::string> drawstyle      = std::nullopt;
        std::optional<std::string> fillstyle      = std::nullopt;
        

    };


    struct ScatterConfig {
        Vec x;
        Vec y;
        
        // optional
        std::optional<std::string> fmt              = std::nullopt;
        std::optional<SizeValue> s                  = std::nullopt;
        std::optional<ColorValue> c                 = std::nullopt;
        std::optional<std::string> cmap             = std::nullopt;
        std::optional<double> vmin                  = std::nullopt;
        std::optional<double> vmax                  = std::nullopt;
        std::optional<LinewidthsValue> linewidths   = 1.5;
        std::optional<bool> plotnonfinite           = false;
        std::optional<std::string> edgecolors =     "face";

        // normalization 
        // valid: "linear" (default), "log", "symlog", "logit",
        std::optional<std::string> norm             = std::nullopt;



        // kwargs
        std::optional<std::string> color            = std::nullopt;
        std::optional<std::string> label            = std::nullopt;
        std::optional<double> alpha                 = std::nullopt;
        std::optional<double> linewidth             = std::nullopt;
        std::optional<std::string> linestyle        = std::nullopt;
        std::optional<std::string> marker           = std::nullopt;
        std::optional<double> markersize            = std::nullopt;
        std::optional<std::string> markerfacecolor  = std::nullopt;
        std::optional<std::string> markeredgecolor  = std::nullopt;
        std::optional<double> markeredgewidth       = std::nullopt;
        std::optional<std::string> drawstyle        = std::nullopt;
        std::optional<std::string> fillstyle        = std::nullopt;
    
    };


    struct StepConfig {
        std::vector<double> x;
        std::vector<double> y;

        // optional
        std::optional<std::string> where          = toString(Where::PRE);
        std::optional<std::string> fmt            = std::nullopt;

        // kwargs
        std::optional<std::string> color          = std::nullopt;
        std::optional<std::string> label          = std::nullopt;
        std::optional<double> alpha               = std::nullopt;
        std::optional<double> linewidth           = std::nullopt;
        std::optional<std::string> linestyle      = std::nullopt;
        std::optional<std::string> marker         = std::nullopt;
        std::optional<double> markersize          = std::nullopt;
        std::optional<std::string> markerfacecolor = std::nullopt;
        std::optional<std::string> markeredgecolor = std::nullopt;
        std::optional<double> markeredgewidth     = std::nullopt;
        std::optional<std::string> drawstyle      = std::nullopt;
        std::optional<std::string> fillstyle      = std::nullopt;

    };


    struct subplot2gridConfig {

        std::vector<int> shape;
        std::vector<int> loc;
        int rowspan              = 1;
        int colspan              = 1;
        Figure* fig              = nullptr;
        
    };


    struct XLabelConfig {
        std::string xlabel       = toString(Loc::CENTER);
        double labelpad          = 4.0;
        std::string color;
    };


    struct YLabelConfig {
        std::string ylabel       = toString(Loc::CENTER);
        double labelpad          = 4.0;
        std::string color;
    };

    
  
    struct SubplotsConfig {
        long nrows                = 1;
        long ncols                = 1;
        std::vector<long> figsize = {10, 10};
    };


    struct TickParamsConfig {
        std::string axis           = toString(Axis::Both);
        std::string which          = toString(Which::Both);
        bool reset                 = false;

        //optional
        std::optional<std::string> direction = toString(Direction::In);
        std::optional<double> length; 
        std::optional<double> width;
        std::optional<std::string> color;
        std::optional<double> pad;
        std::optional<LabelsizeValue> labelsize;
        std::optional<std::string> labelcolor;
        std::optional<std::string> labelfontfamily;
        std::optional<std::string> colors;
        std::optional<double> zorder; 
        std::optional<bool> bottom;
        std::optional<bool> top;
        std::optional<bool> left;
        std::optional<bool> right;
        std::optional<bool> labelbottom;
        std::optional<bool> labeltop;
        std::optional<bool> labelleft;
        std::optional<bool> labelright;
        std::optional<double> labelrotation; 
        std::optional<std::string> grid_color; 
        std::optional<double> grid_alpha;
        std::optional<double> grid_linewidth;
        std::optional<std::string> grid_linestyle;
    
    };


    struct SetXlimConfig {
        std::optional<double> left      = std::nullopt;
        std::optional<double> right     = std::nullopt;
        bool emit = true;
        std::optional<bool> auto_       = false;
        std::optional<double> xmin      = std::nullopt;
        std::optional<double> xmax      = std::nullopt;
    };

    struct SetYlimConfig {
        std::optional<double> bottom    = std::nullopt;
        std::optional<double> top       = std::nullopt;
        bool emit = true;
        std::optional<bool> auto_       = false;
        std::optional<double> ymin      = std::nullopt;
        std::optional<double> ymax      = std::nullopt;
    };


    struct LegendConfig {
        
        // optional
        std::optional<std::vector<std::string>> labels = std::nullopt;
        std::optional<int> ncol = 1;
        std::optional<bool> reverse = false;
        // TODO: handles
        // TODO: loc
        // TODO: bbox_to_anchor
        // TODO: prop
        // TODO: fontsize
        // TODO: labelcolorarray-like or float
        // TODO: numpoints
        // TODO: scatterpoints
        // TODO: scatteryoffsets
        // TODO: markerscale
        // TODO: markerfirst
        // TODO: frameon
        // TODO: fancybox
        // TODO: shadow
        // TODO: framealpha
        // TODO: facecolor
        // TODO: edgecolor
        // TODO: linewidth

    };


    struct GridConfig {

        // optional
        std::optional<bool> visible = std::nullopt;
        std::optional<std::string> which = toString(Which::Both);
        std::optional<std::string> axis = toString(Axis::Both);


        // kwargs
        std::optional<std::string> color          = std::nullopt;
        std::optional<std::string> label          = std::nullopt;
        std::optional<double> alpha               = std::nullopt;
        std::optional<double> linewidth           = std::nullopt;
        std::optional<std::string> linestyle      = std::nullopt;
        std::optional<std::string> marker         = std::nullopt;
        std::optional<double> markersize          = std::nullopt;
        std::optional<std::string> markerfacecolor = std::nullopt;
        std::optional<std::string> markeredgecolor = std::nullopt;
        std::optional<double> markeredgewidth     = std::nullopt;
        std::optional<std::string> drawstyle      = std::nullopt;
        std::optional<std::string> fillstyle      = std::nullopt;

    };



    struct LogLogConfig {
        std::vector<double> x;
        std::vector<double> y;
        double base = 10.0;
        std::string nonpositive = toString(NonPositive::Clip);
        
        // optional
        std::optional<std::string> fmt = std::nullopt;
        std::optional<std::vector<double>> subs = std::nullopt;

        // kwargs
        std::optional<std::string> color          = std::nullopt;
        std::optional<std::string> label          = std::nullopt;
        std::optional<double> alpha               = std::nullopt;
        std::optional<double> linewidth           = std::nullopt;
        std::optional<std::string> linestyle      = std::nullopt;
        std::optional<std::string> marker         = std::nullopt;
        std::optional<double> markersize          = std::nullopt;
        std::optional<std::string> markerfacecolor = std::nullopt;
        std::optional<std::string> markeredgecolor = std::nullopt;
        std::optional<double> markeredgewidth     = std::nullopt;
        std::optional<std::string> drawstyle      = std::nullopt;
        std::optional<std::string> fillstyle      = std::nullopt;
        
    };


    struct SemiLogxConfig {
        std::vector<double> x;
        std::vector<double> y;
        double base = 10.0;
        std::string nonpositive = toString(NonPositive::Clip);
        
        // optional
        std::optional<std::string> fmt = std::nullopt;
        std::optional<std::vector<double>> subs = std::nullopt;

        // kwargs
        std::optional<std::string> color          = std::nullopt;
        std::optional<std::string> label          = std::nullopt;
        std::optional<double> alpha               = std::nullopt;
        std::optional<double> linewidth           = std::nullopt;
        std::optional<std::string> linestyle      = std::nullopt;
        std::optional<std::string> marker         = std::nullopt;
        std::optional<double> markersize          = std::nullopt;
        std::optional<std::string> markerfacecolor = std::nullopt;
        std::optional<std::string> markeredgecolor = std::nullopt;
        std::optional<double> markeredgewidth     = std::nullopt;
        std::optional<std::string> drawstyle      = std::nullopt;
        std::optional<std::string> fillstyle      = std::nullopt;
        
    };


    struct SemiLogyConfig {
        std::vector<double> x;
        std::vector<double> y;
        double base = 10.0;
        std::string nonpositive = toString(NonPositive::Clip);
        
        // optional
        std::optional<std::string> fmt = std::nullopt;
        std::optional<std::vector<double>> subs = std::nullopt;

        // kwargs
        std::optional<std::string> color          = std::nullopt;
        std::optional<std::string> label          = std::nullopt;
        std::optional<double> alpha               = std::nullopt;
        std::optional<double> linewidth           = std::nullopt;
        std::optional<std::string> linestyle      = std::nullopt;
        std::optional<std::string> marker         = std::nullopt;
        std::optional<double> markersize          = std::nullopt;
        std::optional<std::string> markerfacecolor = std::nullopt;
        std::optional<std::string> markeredgecolor = std::nullopt;
        std::optional<double> markeredgewidth     = std::nullopt;
        std::optional<std::string> drawstyle      = std::nullopt;
        std::optional<std::string> fillstyle      = std::nullopt;
    };


    struct FillConfig {
        std::vector<double> x;
        std::vector<double> y;
        
    

        // **kwargs polygon properties 
        std::optional<std::string> color            = std::nullopt;
        std::optional<std::string> facecolor        = std::nullopt;
        std::optional<std::string> edgecolor        = std::nullopt;
        std::optional<std::string> label            = std::nullopt;
        std::optional<double> alpha                 = std::nullopt;
        std::optional<double> linewidth             = std::nullopt;
        std::optional<std::string> linestyle        = std::nullopt;
        std::optional<std::string> hatch            = std::nullopt;
        std::optional<bool> fill                    = std::nullopt;
        std::optional<double> zorder                = std::nullopt;
    };



    struct FillBetweenConfig {
        std::vector<double> x;
        DataValue y1;
        DataValue y2                                     = 0.0;
        bool interpolate                                 = false;   

        
        // optional
        std::optional<std::vector<bool>> where          = std::nullopt;
        std::optional<std::string> step                 = toString(Step::Mid);

        // **kwargs between properties
        std::optional<double> alpha                     = std::nullopt;
        std::optional<bool> animated                    = std::nullopt;
        std::optional<Vec> array                        = std::nullopt;
        std::optional<Clim> clim                        = std::nullopt;
        std::optional<bool> clip_on                     = std::nullopt;
        std::optional<std::string> cmap                 = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> edgecolor            = std::nullopt;
        std::optional<std::string> facecolor            = std::nullopt;
        std::optional<std::string> gid                  = std::nullopt;
        std::optional<std::string> hatch                = std::nullopt;
        std::optional<bool> in_layout                   = std::nullopt;
        std::optional<std::string> label                = std::nullopt;
        std::optional<std::string> linestyle            = std::nullopt;
        std::optional<LinewidthValue> linewidth         = std::nullopt;
        std::optional<bool> mouseover                   = std::nullopt;
        std::optional<double> pickradius                = std::nullopt;
        std::optional<bool> rasterized                  = std::nullopt;
        std::optional<bool> snap                        = std::nullopt;
        std::optional<std::string> url                  = std::nullopt;
        std::optional<bool> visible                     = std::nullopt;
        std::optional<double> zorder                    = std::nullopt;
        
    };


    struct FillBetweenxConfig {
        std::vector<double> y;
        DataValue x1;
        DataValue x2 = 0.0;
        bool interpolate = false;

        // optional
        std::optional<std::vector<bool>> where    = std::nullopt;
        std::optional<std::string> step = toString(Step::Mid);


        // **kwargs between properties
        std::optional<double> alpha                     = std::nullopt;
        std::optional<bool> animated                    = std::nullopt;
        std::optional<Vec> array                        = std::nullopt;
        std::optional<Clim> clim                        = std::nullopt;
        std::optional<bool> clip_on                     = std::nullopt;
        std::optional<std::string> cmap                 = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> edgecolor            = std::nullopt;
        std::optional<std::string> facecolor            = std::nullopt;
        std::optional<std::string> gid                  = std::nullopt;
        std::optional<std::string> hatch                = std::nullopt;
        std::optional<bool> in_layout                   = std::nullopt;
        std::optional<std::string> label                = std::nullopt;
        std::optional<std::string> linestyle            = std::nullopt;
        std::optional<LinewidthValue> linewidth         = std::nullopt;
        std::optional<bool> mouseover                   = std::nullopt;
        std::optional<double> pickradius                = std::nullopt;
        std::optional<bool> rasterized                  = std::nullopt;
        std::optional<bool> snap                        = std::nullopt;
        std::optional<std::string> url                  = std::nullopt;
        std::optional<bool> visible                     = std::nullopt;
        std::optional<double> zorder                    = std::nullopt;

    };



    struct SubplotMosaicConfig {
        
        MosaicValue mosaic;
        std::vector<long> figsize                           = {10, 10};
        

        // optional
        std::optional<bool> sharex                          = false; 
        std::optional<bool> sharey                          = false;
        std::optional<std::vector<double>> width_ratios     = std::nullopt;
        std::optional<std::vector<double>> height_ratios    = std::nullopt;
        std::optional<std::string> empty_sentinel           = "empty";

        
        // fig_kw
        std::optional<double> alpha                         = std::nullopt;
        std::optional<bool> animated                        = std::nullopt;
        std::optional<std::string> clip_on                  = std::nullopt;
        std::optional<double> dpi                           = std::nullopt;
        std::optional<std::string> edgecolor                = std::nullopt;
        std::optional<std::string> facecolor                = std::nullopt;
        std::optional<double> figheight                     = std::nullopt;
        std::optional<double> figwidth                      = std::nullopt;
        std::optional<bool> frameon                         = std::nullopt;
        std::optional<std::string> gid                      = std::nullopt;
        std::optional<bool> mouseover                       = std::nullopt;
        std::optional<bool> rasterized                      = std::nullopt;
        std::optional<std::string> url                      = std::nullopt; 
        std::optional<bool> visible                         = std::nullopt;
        std::optional<double> zorder                        = std::nullopt;


    };


    struct BarConfig {

        BarXValue x;
        BarValue height;
        std::optional<BarValue> width               = 0.8;
        std::optional<BarValue> bottom              = 0.0;
        std::optional<std::string> align            = toString(BarAlign::Center);
        std::optional<ErrorValue> xerr              = std::nullopt;
        std::optional<ErrorValue> yerr              = std::nullopt;
        

        // optional
        std::optional<std::string> color            = std::nullopt;
        std::optional<std::string> facecolor        = std::nullopt;
        std::optional<std::string> edgecolor        = std::nullopt;
        std::optional<LinewidthValue> linewidth     = std::nullopt;
        std::optional<TickLabelValue> tick_label    = std::nullopt;
        std::optional<std::string> label            = std::nullopt;
        std::optional<std::string> ecolor           = std::nullopt;
        std::optional<double> capsize               = 0.0;
        std::optional<bool> log                     = false;
        
        // kwargs Rectangle
        std::optional<double> alpha                 = std::nullopt;
        std::optional<bool> animated                = std::nullopt;
        std::optional<bool> antialiased             = std::nullopt;
        std::optional<Bounds> bounds                = std::nullopt;
        std::optional<std::string> capstyle         = std::nullopt;
        std::optional<double> clip_on               = std::nullopt;
        std::optional<std::string> edgegapcolor     = std::nullopt;
        std::optional<bool> fill                    = std::nullopt;
        std::optional<std::string> gid              = std::nullopt;
        std::optional<std::string> hatch            = std::nullopt;
        std::optional<bool> in_layout               = std::nullopt;
        std::optional<std::string> joinstyle        = std::nullopt;
        std::optional<std::string> linestyle        = std::nullopt;
        std::optional<bool> mouseover               = std::nullopt;
        std::optional<bool> rasterized              = std::nullopt;
        std::optional<bool> snap                    = std::nullopt;
        std::optional<std::string> url              = std::nullopt;
        std::optional<bool> visible                 = std::nullopt;
        std::optional<XY> xy                        = std::nullopt;
        std::optional<double> zorder                = std::nullopt;

    };


    struct BarhConfig {
        BarYValue y;
        BarValue width;
        std::optional<BarValue> height            = 0.8;
        std::optional<BarValue> left              = 0.0;
        std::optional<std::string> align          = toString(BarAlign::Center);
        std::optional<ErrorValue> xerr            = std::nullopt;
        std::optional<ErrorValue> yerr            = std::nullopt;


        // optional
        std::optional<std::string> color            = std::nullopt;
        std::optional<std::string> facecolor        = std::nullopt;
        std::optional<std::string> edgecolor        = std::nullopt;
        std::optional<LinewidthValue> linewidth     = std::nullopt;
        std::optional<TickLabelValue> tick_label    = std::nullopt;
        std::optional<std::string> label            = std::nullopt;
        std::optional<std::string> ecolor           = std::nullopt;
        std::optional<double> capsize               = 0.0;
        std::optional<bool> log                     = false;
        
        // kwargs Rectangle
        std::optional<double> alpha                 = std::nullopt;
        std::optional<bool> animated                = std::nullopt;
        std::optional<bool> antialiased             = std::nullopt;
        std::optional<Bounds> bounds                = std::nullopt;
        std::optional<std::string> capstyle         = std::nullopt;
        std::optional<double> clip_on               = std::nullopt;
        std::optional<std::string> edgegapcolor     = std::nullopt;
        std::optional<bool> fill                    = std::nullopt;
        std::optional<std::string> gid              = std::nullopt;
        std::optional<std::string> hatch            = std::nullopt;
        std::optional<bool> in_layout               = std::nullopt;
        std::optional<std::string> joinstyle        = std::nullopt;
        std::optional<std::string> linestyle        = std::nullopt;
        std::optional<bool> mouseover               = std::nullopt;
        std::optional<bool> rasterized              = std::nullopt;
        std::optional<bool> snap                    = std::nullopt;
        std::optional<std::string> url              = std::nullopt;
        std::optional<bool> visible                 = std::nullopt;
        std::optional<XY> xy                        = std::nullopt;
        std::optional<double> zorder                = std::nullopt;

    };


    struct XTicksConfig {
        std::vector<double> ticks;
        std::optional<bool> minor                       = std::nullopt;

        // kwargs Text
        std::optional<double> alpha                     = std::nullopt;
        std::optional<bool> animated                    = std::nullopt;
        std::optional<bool> antialiased                 = std::nullopt;
        std::optional<double> clip_on                   = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> fontFamily           = std::nullopt;
        std::optional<FontSizeValue> fontSize           = std::nullopt;
        std::optional<FontStretchValue> fontStretch     = std::nullopt;
        std::optional<std::string> fontStyle            = std::nullopt;
        std::optional<std::string> fontVariant          = std::nullopt;
        std::optional<FontWeightValue> fontWeight       = std::nullopt;
        std::optional<bool> in_layout                   = std::nullopt;
        std::optional<std::string> label                = std::nullopt;
        std::optional<std::string> language             = std::nullopt;
        std::optional<LineSpacingValue> linespacing     = std::nullopt; 
        std::optional<std::string> math_fontfamily      = std::nullopt;
        std::optional<bool> mouseover                   = std::nullopt;
        std::optional<std::string> multialignment       = std::nullopt;
        std::optional<std::string> parse_math           = std::nullopt;
        std::optional<Position> position                = std::nullopt;
        std::optional<bool> rasterized                  = std::nullopt;
        std::optional<RotationValue> rotation           = std::nullopt;
        std::optional<std::string> rotation_mode        = std::nullopt;
        std::optional<SketchParams> sketch_params       = std::nullopt;
        std::optional<bool> snap                        = std::nullopt;
        std::optional<std::string> text                 = std::nullopt;
        std::optional<bool> transform_rotates_text      = std::nullopt;
        std::optional<std::string> url                  = std::nullopt;
        std::optional<std::string> verticalalignment    = std::nullopt;
        std::optional<bool> visible                     = std::nullopt;
        std::optional<bool> wrap                        = std::nullopt;
        std::optional<double> x                         = std::nullopt;
        std::optional<double> y                         = std::nullopt;
        std::optional<double> zorder                    = std::nullopt;

    };

    struct YTicksConfig {
        std::vector<double> ticks;
        std::optional<bool> minor                       = std::nullopt;

        // kwargs Text
        std::optional<double> alpha                     = std::nullopt;
        std::optional<bool> animated                    = std::nullopt;
        std::optional<bool> antialiased                 = std::nullopt;
        std::optional<double> clip_on                   = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> fontFamily           = std::nullopt;
        std::optional<FontSizeValue> fontSize           = std::nullopt;
        std::optional<FontStretchValue> fontStretch     = std::nullopt;
        std::optional<std::string> fontStyle            = std::nullopt;
        std::optional<std::string> fontVariant          = std::nullopt;
        std::optional<FontWeightValue> fontWeight       = std::nullopt;
        std::optional<bool> in_layout                   = std::nullopt;
        std::optional<std::string> label                = std::nullopt;
        std::optional<std::string> language             = std::nullopt;
        std::optional<LineSpacingValue> linespacing     = std::nullopt; 
        std::optional<std::string> math_fontfamily      = std::nullopt;
        std::optional<bool> mouseover                   = std::nullopt;
        std::optional<std::string> multialignment       = std::nullopt;
        std::optional<std::string> parse_math           = std::nullopt;
        std::optional<Position> position                = std::nullopt;
        std::optional<bool> rasterized                  = std::nullopt;
        std::optional<RotationValue> rotation           = std::nullopt;
        std::optional<std::string> rotation_mode        = std::nullopt;
        std::optional<SketchParams> sketch_params       = std::nullopt;
        std::optional<bool> snap                        = std::nullopt;
        std::optional<std::string> text                 = std::nullopt;
        std::optional<bool> transform_rotates_text      = std::nullopt;
        std::optional<std::string> url                  = std::nullopt;
        std::optional<std::string> verticalalignment    = std::nullopt;
        std::optional<bool> visible                     = std::nullopt;
        std::optional<bool> wrap                        = std::nullopt;
        std::optional<double> x                         = std::nullopt;
        std::optional<double> y                         = std::nullopt;
        std::optional<double> zorder                    = std::nullopt;



    };


    struct XTickLabelsConfig {
        std::vector<std::string> labels;
        std::optional<bool> minor                       = std::nullopt;
    };

    struct YTickLabelsConfig {
        std::vector<std::string> labels;
        std::optional<bool> minor                       = std::nullopt;
    };



}