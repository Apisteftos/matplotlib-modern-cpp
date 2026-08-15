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


# =============================================================================
# EXECUTABLE EXAMPLES
# =============================================================================

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
add_plot_executable(fill fill_example.cpp)
add_plot_executable(errorbar errorbar_example.cpp)
add_plot_executable(scatter scatter_example.cpp)
add_plot_executable(subplot_mosaic subplot_mosaic_example.cpp)
add_plot_executable(bar bar_example.cpp)
add_plot_executable(stem stem_example.cpp)
add_plot_executable(box box_example.cpp)
add_plot_executable(xlabel xlabel_example.cpp)
add_plot_executable(ylabel ylabel_example.cpp)
add_plot_executable(stackplot stackplot_example.cpp)



# =============================================================================
# doctest 
# =============================================================================
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.5.3
)
FetchContent_MakeAvailable(doctest)


# =============================================================================
# Tests
# =============================================================================
function(add_test_executable target source)
    add_executable(${target} tests/${source})
    target_include_directories(${target} PRIVATE ${COMMON_INCLUDES})
    target_link_libraries(${target} PRIVATE ${Python3_LIBRARIES} doctest::doctest)
    add_test(NAME ${target} COMMAND ${target})
endfunction()

enable_testing()
add_test_executable(test_basic test_basic.cpp)
add_test_executable(test_fill test_fill.cpp)
add_test_executable(test_bar test_bar.cpp)
add_test_executable(test_barh test_barh.cpp)
add_test_executable(test_stem test_stem.cpp)
add_test_executable(test_box test_box.cpp)
add_test_executable(test_set_frame_on test_set_frame_on.cpp)
add_test_executable(test_xlabel test_xlabel.cpp)
add_test_executable(test_ylabel test_ylabel.cpp)
add_test_executable(test_suptitle test_suptitle.cpp)
add_test_executable(test_stackplot test_stackplot.cpp)


