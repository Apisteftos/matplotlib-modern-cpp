# Changelog

All notable changes to this project will be documented in this file.

## [Unreleased]



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