# matplotlib-modern-cpp

A modern C++23 header-only plotting library wrapping Python's matplotlib,
featuring RAII-based Axes and Figure classes, fixed API compatibility with
Python 3.11+ and numpy, and a clean CMake build system.

![Version](https://img.shields.io/badge/version-0.4.0-blue)
![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey)

---

## Motivation

The original matplotlib-cpp library (lava/matplotlib-cpp) is largely
unmaintained and has several bugs with modern Python/matplotlib versions.
This project modernizes the codebase with:

- C++23 support
- RAII memory management — no manual `Py_DECREF` in user code
- Object-oriented separated classes (`Axes`, `Figure`, `Pyplot`)
- Fixed API compatibility with Python 3.11+ and numpy
- Modern CMake with `compile_commands.json` support
- Clean split header architecture

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
| matplotlib | 3.10.8  |
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
#include "matplotlib.h"

int main() {
    matplotlibcpp::Pyplot plt;

    const int n = 100;
    std::vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        x[i] = i * 2 * M_PI / (n - 1);
        y[i] = std::sin(x[i]);
    }

    plt.plot(x, y, "b");
    plt.title("Sine Wave");
    plt.grid();
    plt.show();

    return 0;
}
```

---

## Subplots

```cpp
#include "matplotlib.h"

int main() {
    matplotlibcpp::Pyplot plt;

    std::vector<double> x = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> sinY = {0.84, 0.91, 0.14, -0.76};
    std::vector<double> cosY = {0.54, -0.42, -0.99, -0.65};

    std::vector<long> figsize = {10, 5};
    auto [fig, axes] = plt.subplots(1, 2, figsize);

    axes[0].plot(x, sinY, "b");
    axes[0].set_title("Sine");
    axes[0].grid();

    axes[1].plot(x, cosY, "r");
    axes[1].set_title("Cosine");
    axes[1].grid();

    fig.suptitle("Trig Functions");
    fig.tight_layout();
    plt.show();

    return 0;
}
```

---

## Axes Methods

| Method | Description |
|--------|-------------|
| `plot(x, y, fmt)` | Line plot |
| `scatter(x, y, fmt)` | Scatter plot |
| `bar(x, height, fmt)` | Bar chart |
| `barh(y, width, fmt)` | Horizontal bar chart |
| `errorbar(config)` | Error bar plot |
| `fill_between(x, y1, y2)` | Fill between two lines |
| `step(x, y, fmt)` | Step plot |
| `stem(x, y, fmt)` | Stem plot |
| `loglog(x, y, fmt)` | Log-log plot |
| `semilogx(x, y, fmt)` | Semi-log x plot |
| `semilogy(x, y, fmt)` | Semi-log y plot |
| `pie(x, labels, colors)` | Pie chart |
| `set_title(title)` | Set axes title |
| `set_xlabel(label)` | Set x label |
| `set_ylabel(label)` | Set y label |
| `set_xlim(left, right)` | Set x limits |
| `set_ylim(bottom, top)` | Set y limits |
| `set_aspect(aspect)` | Set aspect ratio |
| `grid(flag)` | Toggle grid |

---

## Figure Methods

| Method | Description |
|--------|-------------|
| `suptitle(title)` | Set figure title |
| `save(filename, dpi)` | Save figure to file |
| `tight_layout()` | Adjust subplot spacing |
| `clf()` | Clear figure |

---

## Pyplot Methods

| Method | Description |
|--------|-------------|
| `show(block)` | Display plots |
| `plot(x, y, fmt)` | Plot on current axes |
| `figure(config)` | Create new figure |
| `subplots(nrows, ncols, figsize)` | Create subplots |
| `subplot2grid(config)` | Create subplot at grid location |
| `subplot(nrows, ncols, num)` | Select subplot |
| `tight_layout()` | Adjust layout |
| `clf()` | Clear figure |
| `cla()` | Clear axes |
| `close()` | Close figure |
| `close(fig)` | Close specific figure |
| `title(t)` | Set title |
| `grid(flag)` | Toggle grid |
| `sca(ax)` | Set current axes |
| `get_fignums()` | Get open figure numbers |
| `get_figlabels()` | Get open figure labels |
| `fignum_exists(num)` | Check if figure exists |

---

## Configuration Structs

```cpp
// Figure configuration
plt.figure({
    .num     = 1,
    .figsize = {10, 8},
    .dpi     = 100.0f,
    .label   = "my_figure"
});

// Errorbar configuration
axes[0].errorbar({
    .x       = x,
    .y       = y,
    .yerr    = errors,
    .fmt     = "bo",
    .ecolor  = "red",
    .capsize = 5.0
});

// subplot2grid configuration
auto ax = plt.subplot2grid({
    .shape   = {3, 3},
    .loc     = {0, 0},
    .colspan = 3
});
```

---

## Credits

Inspired by [lava/matplotlib-cpp](https://github.com/lava/matplotlib-cpp) (MIT License)

---

## License

MIT License — see [LICENSE](LICENSE) for details.