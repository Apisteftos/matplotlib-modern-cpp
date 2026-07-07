#include "../include/Matplotlib.h"
#include <iostream>
#include <print>


using matplotlibcpp::Vec;

// ============================================================
// Test helpers
// ============================================================
int passed = 0;
int failed = 0;

#define TEST(name) \
    try { \
        test_##name(); \
        std::println("Passed: {}", #name ); \
        ++passed; \
    } catch (const std::exception& e) { \
        std::println("Failed: {} : {}", #name,  e.what()); \
        ++failed; \
    }


// ============================================================
// Tests
// ============================================================
void test_interpreter() {
    matplotlibcpp::Interpreter::getInstance();
}


void test_fill() {
    matplotlibcpp::PyPlot plt;
    Vec x  = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    Vec y1 = x * 2.0;
    auto [fig, axes] = plt.subplots();
    axes[0].fill({
        .x     = x,
        .y     = y1, 
        .color = "orange",
        .facecolor = "red",
        .edgecolor = "green",
        .label = "Test fill",
        .alpha = 0.3,
        .linewidth = 2.0,
        .linestyle = "--",
        .hatch = "/",
        .fill = true,
        .zorder = 10
    });
    plt.close("all");
}

void test_fill_between() {
    matplotlibcpp::PyPlot plt;
    Vec x  = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    Vec y1 = x * 2.0;
    Vec y2 = x * 0.5;
    auto [fig, axes] = plt.subplots();
    axes[0].fill_between({
        .x     = x,
        .y1    = y1,
        .y2    = y2,
        .interpolate = true,
        .where = y1 > y2,
        .step = "post",
        .label = "Test between",
        .alpha = 0.3,
        .linewidth = 2.0,
        .linestyle = "--",
        .marker = "x",
        .markersize = 10.0,
        .markerfacecolor = "red",
        .markeredgecolor = "green",
        .markeredgewidth = 2.0,
        .drawstyle = "steps-post",
        .fillstyle = "full"
        
    });
    plt.close("all");
}


void test_fill_betweenx() {
    matplotlibcpp::PyPlot plt;
    Vec y  = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    Vec x1 = y * 2.0;
    Vec x2 = y * 0.5;
    auto [fig, axes] = plt.subplots();
    axes[0].fill_betweenx({
        .y     = y,
        .x1    = x1,
        .x2    = x2,
        .interpolate = true,
        .where = x1 > x2,
        .step = "post",
        .color = "blue",
        .label = "Test betweenx",
        .alpha = 0.3,
        .linewidth = 2.0,
        .linestyle = "--",
        .marker = "x",
        .markersize = 10.0,
        .markerfacecolor = "red",
        .markeredgecolor = "green",
        .markeredgewidth = 2.0,
        .drawstyle = "steps-post",
        .fillstyle = "full"
    });

}

// ============================================================
// Main
// ============================================================
int main() {
    std::println("Running tests...");

    TEST(interpreter)
    TEST(fill)
    TEST(fill_between)
    TEST(fill_betweenx)

    std::println("");
    std::println("Passed: {}", passed);
    std::println("Failed: {}", failed);

    return failed > 0 ? 1 : 0;  
}