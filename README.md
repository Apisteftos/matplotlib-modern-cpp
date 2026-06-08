# matplotlib-modern-cpp

A modern C++23 header-only plotting library wrapping Python's matplotlib, 
featuring RAII-based Axes and Figure classes, fixed API compatibility with 
Python 3.11+ and numpy, and a clean CMake build system.

## Motivation
The original matplotlib-cpp library (lava/matplotlib-cpp) is largely 
unmaintained and has several bugs with modern Python/matplotlib versions. 
This project modernizes the codebase with:

- C++23 support
- RAII memory management (no manual Py_DECREF in user code)
- Object-oriented separated classes
- Modern CMake with compile_commands.json support
- Clean split header architecture

## Credits
Inspired by lava/matplotlib-cpp (MIT License)


