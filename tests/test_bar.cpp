#include "../include/Matplotlib.h"
#include "Configs.h"
#include <iostream>
#include <print>


using matplotlibcpp::Vec;
using matplotlibcpp::XY;

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

void test_bar() {
    matplotlibcpp::PyPlot plt;
    std::vector<std::string> categories = {
        "Monday", 
        "Tuesday", 
        "Wednesday", 
        "Thursday", 
        "Friday", 
        "Saturday", 
        "Sunday"
    };
    Vec x  = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
    Vec height = x * 2.0;
    auto [fig, axes] = plt.subplots();
    axes[0].bar({
        .x     = x,
        .height = height,
        .width = 0.8,
        .bottom = 0.1,
        .align = "edge",
        .xerr = 0.1,
        .yerr = 0.1,
        .color = "blue",
        .facecolor = "red",
        .edgecolor = "green",
    });
    plt.close("all");


    auto [fig2, axes2] = plt.subplots();
    axes2[0].bar({
        .x     = x,
        .height = height,
        .linewidth = 2.0,
        .tick_label = categories,
        .label = "Test bar",
        .ecolor = "orange",
        .capsize = 0.2,
        .log = true
    });
    plt.close("all");


    auto [fig3, axes3] = plt.subplots();
    axes3[0].bar({
        .x     = x,
        .height = height,
        .alpha = 0.3,
        .animated = true,
        .antialiased = true,
        .bounds = "boxes",
        .capstyle = "round",
        .clip_on = true,
        .edgegapcolor = "red",
        .fill = true,
        .gid = "bar-1",
        .hatch = "o",
        .in_layout = true
    });
    plt.close("all");


    auto [fig4, axes4] = plt.subplots();
    axes4[0].bar({
        .x     = x,
        .height = height,
        .joinstyle = "miter",
        .linestyle = "--",
        .mouseover = true,
        .rasterized = true,
        .snap = true,
        .url = "www.everythingok.com",
        .visible = true,
        .xy = XY{0.5, 0.5},
        .zorder = 9
    });
    plt.close("all");
}



// ============================================================
// Main
// ============================================================

int main() {
    std::println("Running tests...");

    TEST(interpreter)
    TEST(bar)

    std::println("");
    std::println("Passed: {}", passed);
    std::println("Failed: {}", failed);

    return failed > 0 ? 1 : 0;  
}