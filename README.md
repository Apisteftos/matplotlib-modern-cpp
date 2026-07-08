# matplotlib-modern-cpp

A modern C++23 header-only plotting library wrapping Python's matplotlib,
featuring RAII-based Axes and Figure classes, fixed API compatibility with
Python 3.12+ and numpy, and a clean CMake build system.

![Version](https://img.shields.io/github/v/tag/Apisteftos/matplotlib-modern-cpp?label=version)
![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey)
![Last commit](https://img.shields.io/github/last-commit/Apisteftos/matplotlib-modern-cpp)
![CI](https://github.com/Apisteftos/matplotlib-modern-cpp/actions/workflows/ci.yml/badge.svg)

---

## Motivation

The original matplotlib-cpp library (lava/matplotlib-cpp) is largely
unmaintained and has several bugs with modern Python/matplotlib versions.
This project modernizes the codebase with:

- C++23 support
- RAII memory management — no manual `Py_DECREF` in user code
- Object-oriented separated classes (`Axes`, `Figure`, `Pyplot`, `Subplot2Grid`)
- Fixed API compatibility with Python 3.12+ and numpy
- Modern CMake with `compile_commands.json` support
- Clean split header architecture
- `Vec` struct with numpy-like element-wise operators

---

## Requirements

### Compiler
| Tool  | Version |
|-------|---------|
| GCC   | 14.1.0+ |
| C++   | 23      |
| CMake | 3.16+   |

### Python
| Package    | Version |
|------------|---------|
| Python     | 3.12.3  |
| matplotlib | 3.10.9  |
| numpy      | 2.4.4   |

### Install Python dependencies
```bash
pip install matplotlib numpy --break-system-packages
```

### Include paths
```bash
# Python headers
/usr/include/python3.12

# Numpy headers
python3 -c "import numpy; print(numpy.get_include())"
```

---

## Installation

```bash
git clone https://github.com/Apisteftos/matplotlib-modern-cpp
cd matplotlib-modern-cpp
mkdir build && cd build
cmake ..
make
```

---

## Quick Start

```cpp
#include "Matplotlib.h"
#include <cmath>
#include <vector>

int main() {
    matplotlibcpp::PyPlot plt;

    const int n = 100;
    matplotlibcpp::Vec x(n), y(n);
    for (int i = 0; i < n; ++i) {
        x[i] = i * 2 * M_PI / (n - 1);
        y[i] = std::sin(x[i]);
    }

    auto [fig, axes] = plt.subplots({.figsize = {10, 5}});
    axes[0].plot({.x = x, .y = y, .color = "b", .label = "sin(x)"});
    axes[0].set_title("Sine Wave");
    axes[0].legend();
    axes[0].grid({.visible = true});

    fig.tight_layout();
    plt.show();

    return 0;
}
```

---

## Examples

| Example | Description |
|---------|-------------|
| `plot_example` | Basic line plots |
| `subplots_example` | Multiple subplots |
| `subplot2grid_example` | Custom grid layout |
| `step_example` | Step plots with where parameter |
| `loglog_example` | Log-log scale |
| `semilogx_example` | Semi-log x scale |
| `semilogy_example` | Semi-log y scale |
| `errorbar_example` | Error bars with asymmetric errors |
| `scatter_example` | Scatter plots with colormap |
| `fill_example` | Fill polygons and between curves |
| `twinx_example` | Dual y-axis |
| `twiny_example` | Dual x-axis |

---

## Vec — numpy-like vector

`Vec` is a `std::vector<double>` subclass with element-wise operators:

```cpp
using matplotlibcpp::Vec;

Vec x = matplotlibcpp::linspace(0, 10, 100);
Vec y1 = x * 2.0;          // element-wise scalar multiply
Vec y2 = x + 1.0;          // element-wise scalar add
Vec y3 = y1 - y2;          // element-wise vector subtract
Vec y4 = y1 * y2;          // element-wise vector multiply

// boolean masks for fill_between where=
auto mask = y1 > y2;       // returns std::vector<bool>

axes[0].fill_between({
    .x     = x,
    .y1    = y1,
    .y2    = y2,
    .where = y1 > y2,
    .alpha = 0.3
});
```

---

## API Reference

See [docs/API.md](docs/API.md) for the full list of methods, config structs,
type aliases, enums, and helper functions.

---

## Credits

Inspired by [lava/matplotlib-cpp](https://github.com/lava/matplotlib-cpp) (MIT License)

---

## License

MIT License — see [LICENSE](LICENSE) for details.