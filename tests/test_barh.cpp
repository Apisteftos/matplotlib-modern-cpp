#include "../include/Matplotlib.h"
#include "Configs.h"
#include <iostream>
#include <print>

using matplotlibcpp::Vec;
using matplotlibcpp::XY;
using matplotlibcpp::Bounds;

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

void test_barh() {
    matplotlibcpp::PyPlot plt;
    std::vector<std::string> categories = {
        "one", 
        "two", 
        "three", 
        "four", 
        "five", 
        "six",
        "seven",
    };
    
    Vec x  = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Vec height = x * 2.0;
    auto [fig, axes] = plt.subplots();
    axes[0].barh({
        .y     = x,
        .width = 0.8,
        .height = height,
        .left = 0.1,
        .align = "edge",
        .xerr = 0.1,
        .yerr = 0.1,
        .color = "blue",
        .facecolor = "red",
        .edgecolor = "green",
    });
    plt.close("all");


    auto [fig2, axes2] = plt.subplots();
    axes2[0].barh({
        .y     = x,
        .width = 0.8,
        .height = height,
        .linewidth = 2.0,
        .tick_label = categories,
        .label = "Test barh",
        .ecolor = "orange",
        .capsize = 0.2,
        .log = true
    });
    plt.close("all");


    auto [fig3, axes3] = plt.subplots();
    axes3[0].barh({
        .y     = x,
        .width = 0.8,
        .height = height,
        .alpha = 0.3,
        .animated = true,
        .antialiased = true,
        .bounds = Bounds{1.1, 1.1, 0.0, 0.0},
        .capstyle = "round",
        .clip_on = true,
        .edgegapcolor = "red",
        .fill = true,
        .gid = "barh-1",
        .hatch = "o",
        .in_layout = true
    });
    plt.close("all");


    auto [fig4, axes4] = plt.subplots();
    axes4[0].barh({
        .y     = x,
        .width = 0.8,
        .height = height,
        .joinstyle = "miter",
        .linestyle = "--",
        .mouseover = true,
        .rasterized = true,
        .snap = true,
        .url = "www.goodeveryday.com",
        .visible = true,
        .xy = XY{0.2, 0.2},
        .zorder = 7
    });
    plt.close("all");
}


// ============================================================
// Main
// ============================================================

int main() {
    std::println("Running tests...");

    TEST(interpreter)
    TEST(barh)

    std::println("");
    std::println("Passed: {}", passed);
    std::println("Failed: {}", failed);

    return failed > 0 ? 1 : 0;  
}