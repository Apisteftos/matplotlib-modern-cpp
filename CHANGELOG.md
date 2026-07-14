# Changelog

All notable changes to this project will be documented in this file.

## [Unreleased]



## [0.11.1] - 14/07/2026

### Fixed

- `bar()`, `barh()` bounds from string to `Bounds` struct coorindates
- boundsToPython() in the `NumpyUtils.h` header
- Bounds in the `Detail.h` header
- Bounds in the test_bar.cpp for unit tests

## [0.11.0] - 14/07/2026



### Added

- `BarConfig` — full Rectangle kwargs for `bar()`
- `BarhConfig` — full Rectangle kwargs for `barh()`
- `XTicksConfig`, `YTicksConfig` — `set_xticks()`, `set_yticks()` with Text kwargs
- `XTickLabelsConfig`, `YTickLabelsConfig` — `set_xticklabels()`, `set_yticklabels()`
- `kwargsTextImpl<T>()` — shared Text kwargs implementation
- `FontSizeValue` — `variant<double, string>` for font size
- `FontStretchValue` — `variant<int, string>` for font stretch
- `FontWeightValue` — `variant<int, string>` for font weight
- `LineSpacingValue` — `variant<double, string>` for line spacing
- `RotationValue` — `variant<double, string>` for rotation
- `SketchParams` struct — `{scale, length, randomness}`
- `Position` struct — `{x, y}` for text position
- `XY` struct — `{x, y}` for rectangle position
- `tickLabelValueToPython()`, `fontSizeValueToPython()`, `fontStretchValueToPython()`
- `fontWeightValueToPython()`, `lineSpacingValueToPython()`, `rotationValueToPython()`
- `sketchParamsToPython()`, `positionToTuple()`, `xyToTuple()`, `barYValueToPython()`
- bar and barh C++ and Python examples
- text example in Python
- test_bar.cpp CI/CD and unit test for bar



### Changed

- updated the CmakeLists.txt file for bar and CI/CD and unit test for bar
- separated gereric conversion functions int the `NumpyUtils.h` header


### Removed

- unused `Subplot2Grid.h` header
- `fillBetweenValueToPython()` in the `NumpyUtils.h` header
- `FillBetweenValue`struct in the `Configs.h` header


### Fixed

- typo `kwargsPolygonImpl<T>()` — kwargs for Polygon 
- typo `kwargsFillBetweenImpl<T>()` — kwargs for FillBetween
- animated in the `FillBetweenConfig` and  `FillBetweenxConfig` struct data type from `FillBetweenValue`to bool




## [0.10.0] - 08/07/2026

### Added
- `Clim` general reusable struct — `{vmin, vmax}` for colormap limits
- `climToTuple()` — Clim to Python tuple converter
- `pairToTuple<T1,T2>()` — generic pair to Python tuple
- `kwardsFillBetweenImpl` — shared kwargs for fill_between/fill_betweenx
- `test_basic.cpp` — unit tests for core functionality
- `test_fill.cpp` — comprehensive fill_between/fill_betweenx unit tests
- `fillBetweenValueToPython()` — converts FillBetweenValue to Python bool or numpy array
- `linewidthValueToPython()` — converts LinewidthValue to Python float or numpy array
- Full PolyCollection kwargs in `FillBetweenConfig` and `FillBetweenxConfig`
- CI `CI` workflow with AddressSanitizer and ci.yml configuration file
- test executable function in `CMakeLists.txt` with test_basic and test_fill

### Fixed
- fill_between/fill_betweenx examples — removed conflicting color+array+cmap
- Missing `plt.close("all")` in fill examples
- Duplicate `cmake -B build` in CI workflow


## [0.9.0] - 05/07/2026

### Added
- `subplot_mosaic()` — `SubplotMosaicConfig` with string and 2D list mosaic layout
- `MosaicValue` — `std::variant<std::string, std::vector<std::vector<std::string>>>`
- `mosaicValueToPython()` — converts MosaicValue to Python string or list of lists
- `bar()` — `BarConfig` with `BarXValue` (float/Vec/categorical strings),
  `BarValue` (float/Vec), `BarAlign` enum
- `barXValueToPython()`, `barValueToPython()` converters
- subplot_mosaic C++ and Python examples
- subplot_mosaic example in the CMakeLists.txt

### Fixed
- `Axes` default constructor added — required for `std::map<std::string, Axes>`
  (`operator[]` needs default-constructible value type)


## [0.8.0] - 04/07/2026

### Added
- `errorbar()` — full `ErrorbarConfig` with yerr, xerr, lolims, uplims, 
  xlolims, xuplims, errorevery, capsize, capthick, barsabove. etc
- `LimValue` — `std::variant<bool, std::vector<bool>>` for limit arrows
- `ErrorEveryValue` — `std::variant<int, std::pair<int,int>>`
- `limValueToPython()`, `errorEveryValueToPython()` converters
- `toBoolArray()` — `std::vector<bool>` → numpy bool array
- errorbar and scatter, fill C++ and Python examples
- `scatter()` — full `ScatterConfig` with s, c, cmap, norm, vmin, vmax,
  alpha, linewidths, edgecolors, plotnonfinite
- `SizeValue` — `std::variant<double, Vec>` for marker size
- `ColorValue` — `std::variant<std::string, Vec>` for marker color
- `LinewidthsValue` — `std::variant<double, Vec>` for linewidths
- `sizeInPointsValueToPython()`, `colorValueToPython()`, `linewidthsToPython()`


### Changed
- updated the README.md file
- separated the API reference from the README.md file into the docs/API.md file


### Fixed
- `errorbar()` fmt must be kwarg not positional — 3rd positional arg is yerr
- `toNumpy()` — `PyArray_SimpleNewFromData` borrows pointer causing
  dangling reference switched to `PyArray_SimpleNew` + `memcpy` so numpy owns its own buffer
- comments in Axes.h and PyPlot.h




## [0.7.0] - 02/07/2026

### Added
- `fill()` — `FillConfig` with Polygon kwargs (color, facecolor, edgecolor, hatch, zorder)
- `fill_between()` — `FillBetweenConfig` with `where` boolean mask support
- `fill_betweenx()` — `FillBetweenxConfig`
- `Vec` struct — element-wise operators (+, -, *, /, >, <, >=, <=, ==) mirroring numpy
- `toBoolArray()` — `std::vector<bool>` numpy bool array
- `toStringList()` — `std::vector<std::string>`  Python list
- `toSubs()` — `std::vector<double>`  Python tuple
- `kwargsPolygonImpl<T>()` — shared Polygon kwargs implementation
- examples for `fill()`, `fill_between()`, `fill_betweenx()` in c++ and python
- fill example in CmakeLists.txt





## [0.6.0] - 16/06/2026

### Added

- `detail.h` — implementation of `plotImpl()`, `stepImpl()`, `tickParamsImpl()`, `loglogImpl()`, `semilogxImpl()`, `semilogyImpl()`
-  step, loglog, semilogx, semilogy examples in c++ and python
- AxesGrid class — flat operator[](long i) for 1D indexing of subplots and 2D indexing of subplots with operator[](long row, long col)
- LogLogConfig, GridConfig, LegendConfig, SemiLogxConfig, SemiLogyConfig structs
- toSubs() — converts std::vector<double> to Python tuple for subs parameter
- toStringList() — converts a vector of strings to a Python list of strings
- Enum NonPositive — NonPositive enum for LogLogConfig


### Changed

- duplicated  `plot()`, `step()`, `tickParams()`, `grid()` moved to `detail.h`
- StepConfig struct updated with full optional kwargs
- src directory renamed to examples
- `configs.h`, `helper.h`, `numpy_utils.h`, `detail.h`, `matplotlib.h` renamed to PascalCase style with capital first letter
- all cpp examples contain the new configuration structs {}

### Fixed

- toNumpy() — switched from PyArray_SimpleNewFromData (borrowed pointer, dangling after vector goes out of scope) to PyArray_SimpleNew + memcpy (copies data into numpy's own buffer)
- PyPtr + PyTuple_SetItem double-free bug — numpy arrays must be passed directly to PyTuple_SetItem, never wrapped in PyPtr first (tuple steals the reference)


## [0.5.0] - 15/06/2026

### Added

- `twinx()`, `ticks_params()`, `get_xlim()`, `get_ylim()` functions
- `twinx`, `twiny` cpp and python examples
- `helper.h` — helper functions for checking PyObject* results, valid objects and printing Python errors
- Enum `Axis`, `Which`, `Direction`, `Loc`  used by TickParamsConfig, XLabelConfig, YLabelConfig
- toString() overloads for converting enums to strings
- TickParamsConfig, XLabelConfig, YLabelConfig, SubplotsConfig, SetXlimConfig, SetYlimConfig structs



### Changed

- `set_xlim()`, `set_ylim()`, in Axes.h
- Parameters in `PyPlot.h` for `plot`, `subplots`
- Parameters in `Axes.h` for `set_xlabel`, `set_ylabel`



## [0.4.0] - 12/06/2026


### Changed

- free functions from `functions.h` — moved to `PyPlot.h`


## [0.3.0] - 10/06/2026

### Added
- `subplot2grid()` function
- `Subplot2Grid` class
- `Subplot2GridConfig`, `FigureConfig`, `ErrorbarConfig`, `ScatterConfig`, `StepConfig` structs
- examples for `subplot2grid()` in c++ and python
- errorValueToNumpy() and dataValueToNumpy() functions
- get_figure() function in Figure class
- optional types and multiple data types in configs



## [0.2.1] - 10/06/2026

### Fixed

- missing inline keyword for `get_figlabels()` and `subplot()`
- typo in the include dir name
- all inlcude paths in the src files




## [0.2.0] - 09/06/2026

### Added

- Free functions: `show()`, `plot()`, `tight_layout()`, `clf()`, `cla()`, `close()`, `sca()`, `grid()`, `title()`, `subplot()`, `axes()`, `delaxes()`, `gca()`, `gcf()`, 
- `Axes.h` a get_axes() function 
- `CHANGELOG.md` unreleased version
- `configs.h` structs configurations for the free functions
- `subplot_example.cpp` example subplot
- `get_fignums_example.cpp` example get_fignums


### Fixed

- Free functions `get_figlabels()`, `get_fignums()`


### Changed

- `matplotlibcpp.h` is now `Interpreter.h`
- Moved free functions to functions.h
- Moved numpy utils from Interpreter.h to numpy_utils.h
- Moved `subplots()` to functions.h




## [0.1.0] - 08/06/2026


### Added
- `Axes` class - RAII-based wrapper for matplotlib axes object with multiple plotting functions
- `Figure` class - RAII-based wrapper for matplotlib figure object
- `PyPtr` - RAII smart pointer for `PyObject*` using `std::unique_ptr`
- `matplotlibcpp.h` - Meyers' singleton managing Python lifecycle
- `NumpyType` - type trait mapping C++ types to numpy type constants
- `toNumpy()` - template function converting `std::vector<T>` to numpy array
- `subplots()` returns `std::pair<Figure, std::vector<Axes>>`
- `CmakeLists.txt` with Python3 and numpy auto-detection
- CMake build system with Python3 and numpy auto-detection
- C++23 support 
- License


### Fixed
- `subplot()` — was passing floats instead of integers (Python 3.12+ compatibility)
- `tick_params()` — numeric parameters now passed as correct Python types
- `subplots()` — now correctly returns axes for any layout (1x2, 2x2, NxM)
- Removed deprecated `Py_SetProgramName` and `PySys_SetArgv` calls


### Changed
- Complete rewrite from scratch — no copy of lava/matplotlib-cpp
- Modern C++23 throughout
- RAII memory management — no manual `Py_DECREF` in user code
- Split into separate headers for clean OOP architecture