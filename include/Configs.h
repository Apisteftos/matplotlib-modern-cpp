#pragma once
// =============================================================================
// Configs.h - C++ wrapper for matplotlib.pyplot.configs
// Modern C++23 matplotlib wrapper build on top of Python C API
// Author: Konstantinos Angeloulis
// Date: 10/06/2024
// =============================================================================


#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <algorithm>
#include <map>



namespace matplotlibcpp {

    class Figure;

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
    enum class Location {
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
     * @brief Converts Location enum to string
     * @param l default is Location::BOTTOM
     */
    inline const char* toString(Location l) {
        switch (l) {
            case Location::BOTTOM: return "bottom";
            case Location::TOP:    return "top";
            case Location::CENTER: return "center";
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

    template<typename T>
    struct VecT : std::vector<T> {
        using std::vector<T>::vector;

        // ============================================================
        // Element-wise comparison operators — return bool mask
        // ============================================================
        std::vector<bool> operator>(const VecT<T>& other) const {
            std::vector<bool> result(this->size());
            std::transform(this->begin(), this->end(), other.begin(), result.begin(),
                [](const T& a, const T& b) { return a > b; });
            return result;
        }

        std::vector<bool> operator<(const VecT<T>& other) const {
            std::vector<bool> result(this->size());
            std::transform(this->begin(), this->end(), other.begin(), result.begin(),
                [](const T& a, const T& b) { return a < b; });
            return result;
        }

        std::vector<bool> operator>=(const VecT<T>& other) const {
            std::vector<bool> result(this->size());
            std::transform(this->begin(), this->end(), other.begin(), result.begin(),
                [](const T& a, const T& b) { return a >= b; });
            return result;
        }

        std::vector<bool> operator<=(const VecT<T>& other) const {
            std::vector<bool> result(this->size());
            std::transform(this->begin(), this->end(), other.begin(), result.begin(),
                [](const T& a, const T& b) { return a <= b; });
            return result;
        }

        std::vector<bool> operator==(const VecT<T>& other) const {
            std::vector<bool> result(this->size());
            std::transform(this->begin(), this->end(), other.begin(), result.begin(),
                [](const T& a, const T& b) { return a == b; });
            return result;
        }

        // ============================================================
        // Element-wise arithmetic operators — like numpy
        // ============================================================
        VecT<T> operator+(const VecT<T>& other) const {
            VecT<T> result(this->size());
            std::transform(this->begin(), this->end(), other.begin(), result.begin(),
                std::plus<T>());
            return result;
        }

        VecT<T> operator-(const VecT<T>& other) const {
            VecT<T> result(this->size());
            std::transform(this->begin(), this->end(), other.begin(), result.begin(),
                std::minus<T>());
            return result;
        }

        VecT<T> operator*(const VecT<T>& other) const {
            VecT<T> result(this->size());
            std::transform(this->begin(), this->end(), other.begin(), result.begin(),
                std::multiplies<T>());
            return result;
        }

        VecT<T> operator/(const VecT<T>& other) const {
            VecT<T> result(this->size());
            std::transform(this->begin(), this->end(), other.begin(), result.begin(),
                std::divides<T>());
            return result;
        }

        // scalar versions
        VecT<T> operator*(T scalar) const {
            VecT<T> result(this->size());
            std::transform(this->begin(), this->end(), result.begin(),
                [scalar](T v) { return v * scalar; });
            return result;
        }

        VecT<T> operator/(T scalar) const {
            VecT<T> result(this->size());
            std::transform(this->begin(), this->end(), result.begin(),
                [scalar](T v) { return v / scalar; });
            return result;
        }

        VecT<T> operator+(T scalar) const {
            VecT<T> result(this->size());
            std::transform(this->begin(), this->end(), result.begin(),
                [scalar](T v) { return v + scalar; });
            return result;
        }

        VecT<T> operator-(T scalar) const {
            VecT<T> result(this->size());
            std::transform(this->begin(), this->end(), result.begin(),
                [scalar](T v) { return v - scalar; });
            return result;
        }
    };

    using Vec = VecT<double>;        
    using StrVec = VecT<std::string>;  
    using IntVec = VecT<int>;
    
    
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

    /**
    * @brief Struct for location with coordinates
    */
    struct Loc {
        double x;
        double y;
    }; 

    /**
     * @brief Struct for figsize with width and height
     */
    struct Fgs {
        double width;
        double height;
    };

    /**
     * @brief Struct for whisker with low and high
     */
    struct Whisker {
        double lower;
        double upper;
    };


    // =============================================================================
    // Multiple data types
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

    // rc parameters
    using LabelcolorValue = std::variant<
        std::string,
        std::vector<std::string>
    >;


    // boxplot parameters
    using WhisValue = std::variant<
        double,
        std::vector<double>
    >;


    
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
        std::string
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

    // legend parameters
    using LegendLocValue = std::variant<
        std::string,                    
        int,                             
        Loc   
    >;

    // legend parameters
    using TitleFontSizeValue = std::variant<
        int,
        std::string
    >;  

    // rc parameters
    using RcValue = std::variant<
        std::string, 
        double, 
        bool, 
        int, 
        std::vector<std::string>,
        Fgs
    >;

    // tick_params and rc parameters
    using TickNdivsValue = std::variant<
        int,
        std::string
    >;



    // =============================================================================
    // Structs for matplotlib.pyplot.plot() 
    // =============================================================================



    struct FigureConfig {
        std::optional<int> num                     = std::nullopt;
        std::vector<long> figsize                  = {};
        std::optional<double> dpi                  = std::nullopt;
        std::optional<std::string> label           = std::nullopt;

    };


    struct AxesConfig {

        
    };

    struct PlotConfig {
        
        std::optional<DataValue> x                 = std::nullopt;
        DataValue y; 
        bool scalex                                = true;
        bool scaley                                = true;

        // optional
        std::optional<std::string> fmt             = std::nullopt;
        
        // kwargs
        std::optional<std::string> color           = std::nullopt;
        std::optional<std::string> label           = std::nullopt;
        std::optional<double> alpha                = std::nullopt;
        std::optional<double> linewidth            = std::nullopt;
        std::optional<std::string> linestyle       = std::nullopt;
        std::optional<std::string> marker          = std::nullopt;
        std::optional<double> markersize           = std::nullopt;
        std::optional<std::string> markerfacecolor = std::nullopt;
        std::optional<std::string> markeredgecolor = std::nullopt;
        std::optional<double> markeredgewidth      = std::nullopt;
        std::optional<std::string> drawstyle       = std::nullopt;
        std::optional<std::string> fillstyle       = std::nullopt;

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
        std::optional<std::string> color           = std::nullopt;
        std::optional<std::string> label           = std::nullopt;
        std::optional<double> alpha                = std::nullopt;
        std::optional<double> linewidth            = std::nullopt;
        std::optional<std::string> linestyle       = std::nullopt;
        std::optional<std::string> marker          = std::nullopt;
        std::optional<double> markersize           = std::nullopt;
        std::optional<std::string> markerfacecolor = std::nullopt;
        std::optional<std::string> markeredgecolor = std::nullopt;
        std::optional<double> markeredgewidth      = std::nullopt;
        std::optional<std::string> drawstyle       = std::nullopt;
        std::optional<std::string> fillstyle       = std::nullopt;
        

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
        std::string xlabel; 
        std::optional<double> labelpad                  = std::nullopt;
        std::optional<std::string> loc                  = std::nullopt;


        // kwargs Text
        std::optional<double> alpha                     = std::nullopt;
        std::optional<bool> animated                    = std::nullopt;
        std::optional<bool> antialiased                 = std::nullopt;
        std::optional<bool> clip_on                     = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> fontfamily           = std::nullopt;
        std::optional<FontSizeValue> fontsize           = std::nullopt;
        std::optional<FontStretchValue> fontstretch     = std::nullopt;
        std::optional<std::string> fontstyle            = std::nullopt;
        std::optional<std::string> fontvariant          = std::nullopt;
        std::optional<FontWeightValue> fontweight       = std::nullopt;
        std::optional<std::string> gid                  = std::nullopt;
        std::optional<std::string> horizontalalignment  = std::nullopt;
        std::optional<bool> in_layout                   = std::nullopt;
        std::optional<std::string> label                = std::nullopt;
        std::optional<std::string> language             = std::nullopt;
        std::optional<LineSpacingValue> linespacing     = std::nullopt; 
        std::optional<std::string> math_fontfamily      = std::nullopt;
        std::optional<bool> mouseover                   = std::nullopt;
        std::optional<std::string> multialignment       = std::nullopt;
        std::optional<bool> parse_math                  = std::nullopt;
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


    struct YLabelConfig {
        std::string ylabel;
        std::optional<double> labelpad                  = std::nullopt;
        std::optional<std::string> loc                  = std::nullopt;


        // kwargs Text
        std::optional<double> alpha                     = std::nullopt;
        std::optional<bool> animated                    = std::nullopt;
        std::optional<bool> antialiased                 = std::nullopt;
        std::optional<bool> clip_on                     = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> fontfamily           = std::nullopt;
        std::optional<FontSizeValue> fontsize           = std::nullopt;
        std::optional<FontStretchValue> fontstretch     = std::nullopt;
        std::optional<std::string> fontstyle            = std::nullopt;
        std::optional<std::string> fontvariant          = std::nullopt;
        std::optional<FontWeightValue> fontweight       = std::nullopt;
        std::optional<std::string> gid                  = std::nullopt;
        std::optional<std::string> horizontalalignment  = std::nullopt;
        std::optional<bool> in_layout                   = std::nullopt;
        std::optional<std::string> label                = std::nullopt;
        std::optional<std::string> language             = std::nullopt;
        std::optional<LineSpacingValue> linespacing     = std::nullopt; 
        std::optional<std::string> math_fontfamily      = std::nullopt;
        std::optional<bool> mouseover                   = std::nullopt;
        std::optional<std::string> multialignment       = std::nullopt;
        std::optional<bool> parse_math                  = std::nullopt;
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

    
  
    struct SubplotsConfig {
        long nrows                = 1;
        long ncols                = 1;
        std::vector<long> figsize = {};
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
        std::optional<std::vector<std::string>> labels   = std::nullopt;
        std::optional<int> ncol                          = 1;
        std::optional<bool> reverse                      = false;
        // TODO: handles
        std::optional<LegendLocValue> loc                = "best";
        // TODO: bbox_to_anchor
        // TODO: prop
        std::optional<FontSizeValue> fontsize            = "medium";
        std::optional<LabelcolorValue> labelcolor        = std::nullopt;
        std::optional<int> numpoints                     = 1;
        std::optional<int> scatterpoints                 = 1;
        // TODO: scatteryoffsets
        std::optional<double> markerscale                = 1.0;
        std::optional<bool> markerfirst                  = true;
        std::optional<bool> frameon                      = true;
        std::optional<bool> fancybox                     = true;
        // TODO: shadow
        std::optional<double> framealpha                 = 0.8;
        std::optional<TitleFontSizeValue> title_fontsize = std::nullopt;
        std::optional<std::string> facecolor             = "inherit";
        std::optional<std::string> edgecolor             = "0.8";   
        std::optional<double> linewidth                  = 1.0;
        std::optional<double> borderpad                  = 0.4;
        std::optional<double> labelspacing               = 0.5;
        std::optional<double> handlelength               = 2.0;
        std::optional<double> handleheight               = 0.7;
        std::optional<double> handletextpad              = 0.8;
        std::optional<double> borderaxespad              = 0.5;
        std::optional<double> columnspacing              = 2.0;

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

        
        // fig_kwargs
        std::optional<double> alpha                         = std::nullopt;
        std::optional<bool> animated                        = std::nullopt;
        std::optional<bool> clip_on                         = std::nullopt;
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
        std::optional<bool> clip_on                 = std::nullopt;
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
        std::optional<bool> clip_on                 = std::nullopt;
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
        std::optional<bool> clip_on                     = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> fontfamily           = std::nullopt;
        std::optional<FontSizeValue> fontsize           = std::nullopt;
        std::optional<FontStretchValue> fontstretch     = std::nullopt;
        std::optional<std::string> fontstyle            = std::nullopt;
        std::optional<std::string> fontvariant          = std::nullopt;
        std::optional<FontWeightValue> fontweight       = std::nullopt;
        std::optional<std::string> gid                  = std::nullopt;
        std::optional<std::string> horizontalalignment  = std::nullopt;
        std::optional<bool> in_layout                   = std::nullopt;
        std::optional<std::string> label                = std::nullopt;
        std::optional<std::string> language             = std::nullopt;
        std::optional<LineSpacingValue> linespacing     = std::nullopt; 
        std::optional<std::string> math_fontfamily      = std::nullopt;
        std::optional<bool> mouseover                   = std::nullopt;
        std::optional<std::string> multialignment       = std::nullopt;
        std::optional<bool> parse_math                  = std::nullopt;
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

        // kwargs TickParams
        std::optional<std::string> axis                 = std::nullopt;
        std::optional<std::string> which                = std::nullopt;
        std::optional<bool> reset                       = std::nullopt;
        std::optional<std::string> direction            = std::nullopt;
        std::optional<double> length                    = std::nullopt;
        std::optional<double> width                     = std::nullopt;
        //std::optional<std::string> color                = std::nullopt;
        std::optional<double> pad                       = std::nullopt;
        std::optional<LabelsizeValue> labelsize         = std::nullopt;
        std::optional<std::string> labelcolor           = std::nullopt;
        std::optional<std::string> labelfontfamily      = std::nullopt;
        std::optional<std::string> colors               = std::nullopt;
        //std::optional<double> zorder                    = std::nullopt;
        std::optional<bool> bottom                      = std::nullopt;
        std::optional<bool> top                         = std::nullopt;
        std::optional<bool> left                        = std::nullopt;
        std::optional<bool> right                       = std::nullopt;
        std::optional<bool> labelbottom                 = std::nullopt;
        std::optional<bool> labeltop                    = std::nullopt;
        std::optional<bool> labelleft                   = std::nullopt;
        std::optional<bool> labelright                  = std::nullopt;
        std::optional<double> labelrotation             = std::nullopt;
        std::optional<std::string> labelrotation_mode   = std::nullopt;
        std::optional<std::string> grid_color           = std::nullopt;
        std::optional<double> grid_alpha                = std::nullopt;
        std::optional<double> grid_linewidth            = std::nullopt;
        std::optional<std::string> grid_linestyle       = std::nullopt;

    };

    struct YTicksConfig {
        std::vector<double> ticks;
        std::optional<bool> minor                       = std::nullopt;

        // kwargs Text
        std::optional<double> alpha                     = std::nullopt;
        std::optional<bool> animated                    = std::nullopt;
        std::optional<bool> antialiased                 = std::nullopt;
        std::optional<bool> clip_on                     = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> fontfamily           = std::nullopt;
        std::optional<FontSizeValue> fontsize           = std::nullopt;
        std::optional<FontStretchValue> fontstretch     = std::nullopt;
        std::optional<std::string> fontstyle            = std::nullopt;
        std::optional<std::string> fontvariant          = std::nullopt;
        std::optional<FontWeightValue> fontweight       = std::nullopt;
        std::optional<std::string> gid                  = std::nullopt;
        std::optional<std::string> horizontalalignment  = std::nullopt;
        std::optional<bool> in_layout                   = std::nullopt;
        std::optional<std::string> label                = std::nullopt;
        std::optional<std::string> language             = std::nullopt;
        std::optional<LineSpacingValue> linespacing     = std::nullopt; 
        std::optional<std::string> math_fontfamily      = std::nullopt;
        std::optional<bool> mouseover                   = std::nullopt;
        std::optional<std::string> multialignment       = std::nullopt;
        std::optional<bool> parse_math                  = std::nullopt;
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

        // kwargs TickParams
        std::optional<std::string> axis                 = std::nullopt;
        std::optional<std::string> which                = std::nullopt;
        std::optional<bool> reset                       = std::nullopt;
        std::optional<std::string> direction            = std::nullopt;
        std::optional<double> length                    = std::nullopt;
        std::optional<double> width                     = std::nullopt;
        //std::optional<std::string> color                = std::nullopt;
        std::optional<double> pad                       = std::nullopt;
        std::optional<LabelsizeValue> labelsize         = std::nullopt;
        std::optional<std::string> labelcolor           = std::nullopt;
        std::optional<std::string> labelfontfamily      = std::nullopt;
        std::optional<std::string> colors               = std::nullopt;
        //std::optional<double> zorder                    = std::nullopt;
        std::optional<bool> bottom                      = std::nullopt;
        std::optional<bool> top                         = std::nullopt;
        std::optional<bool> left                        = std::nullopt;
        std::optional<bool> right                       = std::nullopt;
        std::optional<bool> labelbottom                 = std::nullopt;
        std::optional<bool> labeltop                    = std::nullopt;
        std::optional<bool> labelleft                   = std::nullopt;
        std::optional<bool> labelright                  = std::nullopt;
        std::optional<double> labelrotation             = std::nullopt;
        std::optional<std::string> labelrotation_mode   = std::nullopt;
        std::optional<std::string> grid_color           = std::nullopt;
        std::optional<double> grid_alpha                = std::nullopt;
        std::optional<double> grid_linewidth            = std::nullopt;
        std::optional<std::string> grid_linestyle       = std::nullopt;
    };


    struct XTickLabelsConfig {
        std::vector<std::string> labels;
        std::optional<bool> minor                       = std::nullopt;

        // kwargs Text
        std::optional<double> alpha                     = std::nullopt;
        std::optional<bool> animated                    = std::nullopt;
        std::optional<bool> antialiased                 = std::nullopt;
        std::optional<bool> clip_on                     = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> fontfamily           = std::nullopt;
        std::optional<FontSizeValue> fontsize           = std::nullopt;
        std::optional<FontStretchValue> fontstretch     = std::nullopt;
        std::optional<std::string> fontstyle            = std::nullopt;
        std::optional<std::string> fontvariant          = std::nullopt;
        std::optional<FontWeightValue> fontweight       = std::nullopt;
        std::optional<std::string> gid                  = std::nullopt;
        std::optional<std::string> horizontalalignment  = std::nullopt;
        std::optional<bool> in_layout                   = std::nullopt;
        std::optional<std::string> label                = std::nullopt;
        std::optional<std::string> language             = std::nullopt;
        std::optional<LineSpacingValue> linespacing     = std::nullopt; 
        std::optional<std::string> math_fontfamily      = std::nullopt;
        std::optional<bool> mouseover                   = std::nullopt;
        std::optional<std::string> multialignment       = std::nullopt;
        std::optional<bool> parse_math                  = std::nullopt;
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

    struct YTickLabelsConfig {
        std::vector<std::string> labels;
        std::optional<bool> minor                       = std::nullopt;


        // kwargs Text
        std::optional<double> alpha                     = std::nullopt;
        std::optional<bool> animated                    = std::nullopt;
        std::optional<bool> antialiased                 = std::nullopt;
        std::optional<bool> clip_on                     = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> fontfamily           = std::nullopt;
        std::optional<FontSizeValue> fontsize           = std::nullopt;
        std::optional<FontStretchValue> fontstretch     = std::nullopt;
        std::optional<std::string> fontstyle            = std::nullopt;
        std::optional<std::string> fontvariant          = std::nullopt;
        std::optional<FontWeightValue> fontweight       = std::nullopt;
        std::optional<std::string> gid                  = std::nullopt;
        std::optional<std::string> horizontalalignment  = std::nullopt;
        std::optional<bool> in_layout                   = std::nullopt;
        std::optional<std::string> label                = std::nullopt;
        std::optional<std::string> language             = std::nullopt;
        std::optional<LineSpacingValue> linespacing     = std::nullopt; 
        std::optional<std::string> math_fontfamily      = std::nullopt;
        std::optional<bool> mouseover                   = std::nullopt;
        std::optional<std::string> multialignment       = std::nullopt;
        std::optional<bool> parse_math                  = std::nullopt;
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



    struct StemConfig {

        std::optional<std::vector<double>> locs     = std::nullopt;
        std::vector<double> heads; 

        // optional
        std::optional<std::string> linefmt          = std::nullopt;
        std::optional<std::string> markerfmt        = std::nullopt;
        std::optional<std::string> basefmt          = std::nullopt;
        std::optional<std::string> orientation      = std::nullopt;
        double bottom                               = 0.0;   
        std::optional<std::string> label            = std::nullopt;
        
    };


    struct BoxConfig {
        std::optional<bool> on = std::nullopt;
    };


    struct SetFrameOnConfig {
        std::optional<bool> b = std::nullopt;
    };

    struct SupTitleConfig {
        std::string t; 

        // kwargs Text
        std::optional<double> alpha                     = std::nullopt;
        std::optional<bool> animated                    = std::nullopt;
        std::optional<bool> antialiased                 = std::nullopt;
        std::optional<bool> clip_on                     = std::nullopt;
        std::optional<std::string> color                = std::nullopt;
        std::optional<std::string> fontfamily           = std::nullopt;
        std::optional<FontSizeValue> fontsize           = std::nullopt;
        std::optional<FontStretchValue> fontstretch     = std::nullopt;
        std::optional<std::string> fontstyle            = std::nullopt;
        std::optional<std::string> fontvariant          = std::nullopt;
        std::optional<FontWeightValue> fontweight       = std::nullopt;
        std::optional<std::string> gid                  = std::nullopt;
        std::optional<std::string> horizontalalignment  = std::nullopt;
        std::optional<bool> in_layout                   = std::nullopt;
        std::optional<std::string> label                = std::nullopt;
        std::optional<std::string> language             = std::nullopt;
        std::optional<LineSpacingValue> linespacing     = std::nullopt; 
        std::optional<std::string> math_fontfamily      = std::nullopt;
        std::optional<bool> mouseover                   = std::nullopt;
        std::optional<std::string> multialignment       = std::nullopt;
        std::optional<bool> parse_math                  = std::nullopt;
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


    struct StackplotConfig {
        std::vector<double> x;                        
        std::vector<std::vector<double>> y;
        std::string baseline                            = "zero";
        std::optional<StrVec> labels                    = std::nullopt;
        std::optional<StrVec> colors                    = std::nullopt;
        


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


    

}