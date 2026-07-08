#include "../include/Matplotlib.h"
#include "Configs.h"
#include <iostream>
#include <print>


using matplotlibcpp::Vec;
using matplotlibcpp::Clim;

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
        .alpha = 0.3,
        .animated = true,
        .array = y1,
        .clim = Clim{-1.0, 1.0},
        .clip_on = true,
        .color = "blue"
        
    });
    plt.close("all");

    auto [fig2, axes2] = plt.subplots();
    axes2[0].fill_between({
        .x     = x,
        .y1    = y1,
        .y2    = y2,
        .interpolate = true,
        .where = y1 > y2,
        .cmap = "viridis",
        .edgecolor = "green",
        .facecolor = "red",
        .gid = "fill-between-1",
        .hatch = "+",
        .in_layout = true,
        .label = "y1 > y2"
        
    });
    plt.close("all");

    auto [fig3, axes3] = plt.subplots();
    axes3[0].fill_between({
        .x     = x,
        .y1    = y1,
        .y2    = y2,
        .interpolate = true,
        .where = y1 > y2,
        .linestyle = "--",
        .linewidth = 2.0,
        .mouseover = true,
        .pickradius = 0.5,
        .rasterized = true,
        .snap = true,
        .url = "https://matplotlib.org",
        .visible = true,
        .zorder = 7
        
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
        .step = "mid",
        .alpha = 0.8,
        .animated = true,
        .array = x1,
        .clim = Clim{-0.9, 0.9},
        .clip_on = true,
    });
    plt.close("all");


    auto [fig2, axes2] = plt.subplots();
    axes2[0].fill_betweenx({
        .y     = y,
        .x1    = x1,
        .x2    = x2,
        .interpolate = true,
        .where = x1 > x2,
        .cmap = "magma",
        .edgecolor = "black",
        .facecolor = "yellow",
        .gid = "fill-betweenx-2",
        .hatch = "+",
        .in_layout = true,
        .label = "x1 > x2"
        
    });
    plt.close("all");

    auto [fig3, axes3] = plt.subplots();
    axes3[0].fill_betweenx({
        .y     = y,
        .x1    = x1,
        .x2    = x2,
        .interpolate = true,
        .where = x1 > x2,
        .linestyle = "-.",
        .linewidth = 2.4,
        .mouseover = true,
        .pickradius = 0.6,
        .rasterized = true,
        .snap = true,
        .url = "https://whatever.com",
        .visible = true,
        .zorder = 8
        
    });
    plt.close("all");

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