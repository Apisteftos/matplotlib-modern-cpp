# Changelog

All notable changes to this project will be documented in this file.

## [Unreleased]

## [0.13.0] - 15/08/2026

### Added
- `LegendConfig` with `LegendLocValue` (`std::variant<std::string, int, Loc>`) covering string keywords, legacy int codes, and exact `(x, y)` coordinates for `loc`
- `Loc` struct `{double x; double y;}` and `locToPython()` converter
- `Axes::legend()` / `PyPlot::legend()` wrappers
- `StackplotConfig` with full kwargs coverage (`baseline`, `labels`, `colors`, plus complete `fill_between`-forwarded properties)
- `Axes::stackplot()` / `PyPlot::stackplot()` wrappers
- `stackplotImpl()` in `Detail.h`
- `toNumpyList<T>()` — templated `vector<vector<T>>` to Python list-of-1D-numpy-arrays converter, needed for `stackplot`'s `(M,N)` `y` shape
- `stackplot_example.cpp` and `stackplot_example.py`
- `test_stackplot.cpp` — full parameter coverage
- `Artist.h` — RAII-based wrapper for matplotlib.artist.Artist


### Fixed
- **`FontSizeValue`** default `std::optional<FontSizeValue> fontsize = "large"` in `SupTitleConfig` — corrected the underlying variant type from `std::vector<std::string>` to `std::string`, fixing construction failure
- **Circular include** — `Configs.h` included `Figure.h` (for `subplot2gridConfig::fig` and `Figure::suptitle()`), which transitively re-included `Configs.h`'s own dependents before its structs were defined
- **`label` kwarg collision in `stackplotImpl`** — `stackplot()` internally forwards its own per-series `labels` iteration into `fill_between()`; the generic `config.label` field (from `kwargsFillBetweenImpl`) collided with it, causing `TypeError: got multiple values for keyword argument 'label'`; now stripped from kwargs before the call
- **`toNumpy()` called directly on `vector<vector<double>>`** — `Detail.h`'s original `stackplotImpl` passed `config.y` straight to `toNumpy()`, which only handles flat `vector<T>`; fixed by introducing `toNumpyList()` and routing the 2D `y` through it instead
- Confirmed (not a library bug) — a dtype-dependent discrepancy in matplotlib's own `weighted_wiggle` baseline algorithm: `int64` vs `float64` input arrays produce numerically different polygon geometry inside matplotlib itself; the C++ wrapper's `float64`-only output is correct, and `stackplot_example.py` was updated to use `dtype=float` explicitly to match


### Changed
- `CMakeLists.txt`: added `stackplot` example executable and `test_stackplot` test executable
- `Vec` to templated `VecT<T>`, with `Vec = VecT<double>` and `StrVec = VecT<std::string>` aliases; comparison operators available for any `T`, arithmetic operators gated to arithmetic `T` via `requires`
- `fix.save` to `fix.savefig` in all cpp examples
- `Figure::suptitle()` — added `kwargsTextImpl()` to forward `t` and `text` kwargs by using the `detail::suptitleImpl()` internals


## [0.12.0] - 11/08/2026

### Added
- `StemConfig` struct with `locs` (optional), `heads`, `linefmt`, `markerfmt`, `basefmt`, `bottom`, `label`, `orientation`
- `Axes::stem()` and `PyPlot::stem()` wrappers using the config-struct pattern
- `stemImpl()` in `Detail.h`
- `BoxConfig` with `on` (`std::optional<bool>` — toggle behavior when `nullopt`) and `PyPlot::box()` wrapper
- `Axes::set_frame_on(bool)` — direct scalar parameter, no config struct needed
- `XLabelConfig`, `YLabelConfig`, `SupTitleConfig` structs covering the full matplotlib Text properties surface
- `Axes::set_xlabel()`, `Axes::set_ylabel()`, `PyPlot::xlabel()`, `PyPlot::ylabel()`, `PyPlot::suptitle()` wrappers
- doctest integration via CMake `FetchContent` for unit tests
- `tests/test_stem.cpp`, `tests/test_box.cpp`, `tests/test_set_frame_on.cpp`, `tests/test_xlabel.cpp`, `tests/test_ylabel.cpp`, `tests/test_suptitle.cpp`
- `stem_example`, `box_example`, `set_frame_on_example`, `xlabel_example`, `ylabel_example` in Python and C++
- `fetchPythonError()` helper in `Helper.h` — captures the live Python exception message via `PyErr_Fetch`/`PyErr_NormalizeException` and folds it into thrown `std::runtime_error` messages

### Fixed
- **`FontSizeValue`** variant corrected from `std::variant<double, std::vector<std::string>>` to `std::variant<double, std::string>` — fixes construction failures for string defaults like `"large"`
- **`clip_on`** type corrected from `std::optional<double>` to `std::optional<bool>` across all Text-based configs
- **`parse_math`** type corrected from `std::optional<std::string>` to `std::optional<bool>` across all Text-based configs
- **`loc`** made `std::optional<std::string>` (was a hardcoded `std::string loc = "center"`) in `XLabelConfig`/`YLabelConfig` — was being sent unconditionally on every call, causing `TypeError: Specifying 'loc' is disallowed when any of its corresponding low level keyword arguments (['x'/'y', 'horizontalalignment', 'ha']) are also supplied` whenever low-level positioning kwargs were also set
- **`labelpad`** made `std::optional<double>` (was a hardcoded `double labelpad = 4.0`) — was silently overriding any previously-set labelpad value on every call instead of respecting matplotlib's "if None, previous value is left as is" behavior
- **`label` kwarg collision** — the generic Text `label` property collided with the positional `xlabel`/`ylabel`/`t` argument in `set_xlabel()`/`set_ylabel()`/`suptitle()`, causing `TypeError: got multiple values for argument 'label'`; now stripped from kwargs before the call when redundant
- **`text` kwarg collision** — same issue as `label`, between `SupTitleConfig::text` and the positional `t` argument in `suptitle()`; now stripped from kwargs before the call
- **`checkResult()` / `checkAttr()`** in `Helper.h` — previously only called `PyErr_Print()` (stderr only, not captured); now use `fetchPythonError()` to fold the actual Python exception message into the thrown `std::runtime_error`, making failures debuggable from the exception text alone
- **Field naming convention** — renamed `fontFamily`, `fontSize`, `fontStretch`, `fontStyle`, `fontVariant`, `fontWeight` (camelCase) to `fontfamily`, `fontsize`, `fontstretch`, `fontstyle`, `fontvariant`, `fontweight` (snake_case) across all Text-kwargs config structs, matching matplotlib's actual Python kwarg names exactly — prevents silent kwarg mismatches when building the `kwargs` dict
- Diagnosed and fixed a CI-only build failure caused by a system-wide `doctest-dev` apt package masking a missing `doctest::doctest` link locally; CI's clean container correctly exposed the bug
- Diagnosed and fixed a local Python/matplotlib version mismatch: CMake was resolving `/usr/bin/python3` (system, matplotlib 3.10.9) instead of `.venv`'s Python (3.12.3, matplotlib 3.11.0), causing spurious `AttributeError: 'Text' object has no property 'language'`; fixed via explicit `-DPython3_EXECUTABLE`/`-DPython3_ROOT_DIR` when configuring with `.venv` activated

### Changed
- `CMakeLists.txt`: added `doctest` FetchContent block (moved above the Tests section so `doctest::doctest` target exists before test executables reference it) and `test_stem`, `test_box`, `test_set_frame_on`, `test_xlabel`, `test_ylabel`, `test_suptitle` executables
- `add_test_executable()` CMake function: added `doctest::doctest` to `target_link_libraries` (previously missing, causing `doctest/doctest.h: No such file or directory` in clean CI containers while masked locally by a system-installed `doctest-dev` package)



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