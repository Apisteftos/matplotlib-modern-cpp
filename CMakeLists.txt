cmake_minimum_required(VERSION 3.16)
project(MatplotlibCpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)

# Find NumPy include path
execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "import numpy; print(numpy.get_include())"
    OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)


set(COMMON_INCLUDES
    ${CMAKE_SOURCE_DIR}/include
    ${Python3_INCLUDE_DIRS}
    ${NUMPY_INCLUDE_DIR}
)


function(add_plot_executable target source)
    add_executable(${target} examples/${source})
    target_include_directories(${target} PRIVATE ${COMMON_INCLUDES})
    target_link_libraries(${target} PRIVATE ${Python3_LIBRARIES})
endfunction()


add_plot_executable(plot plot_example.cpp)
add_plot_executable(subplot subplot_example.cpp)
add_plot_executable(subplots subplots_example.cpp)
add_plot_executable(sca sca_example.cpp)
add_plot_executable(get_fignums get_fignums_example.cpp)
add_plot_executable(subplot2grid subplot2grid_example.cpp)
add_plot_executable(twinx twinx_example.cpp)
add_plot_executable(twiny twiny_example.cpp)
add_plot_executable(step step_example.cpp)
add_plot_executable(loglog loglog_example.cpp)
add_plot_executable(semilogx semilogx_example.cpp)
add_plot_executable(semilogy semilogy_example.cpp)

