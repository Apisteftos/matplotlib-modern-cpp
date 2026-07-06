#include "../include/Matplotlib.h"
#include <cassert>
#include <iostream>
#include <cmath>

using matplotlibcpp::Vec;

// ============================================================
// Test helpers
// ============================================================
int passed = 0;
int failed = 0;

#define TEST(name) \
    try { \
        test_##name(); \
        std::cout << "Passed " << #name << "\n"; \
        ++passed; \
    } catch (const std::exception& e) { \
        std::cout << "Failed " << #name << ": " << e.what() << "\n"; \
        ++failed; \
    }

// ============================================================
// Tests
// ============================================================
void test_interpreter() {
    matplotlibcpp::Interpreter::getInstance();
}


void test_vec_operators() {
    Vec a = {1.0, 2.0, 3.0};
    Vec b = {4.0, 5.0, 6.0};

    auto sum = a + b;
    assert(sum[0] == 5.0);
    assert(sum[1] == 7.0);

    auto diff = b - a;
    assert(diff[0] == 3.0);

    auto scaled = a * 2.0;
    assert(scaled[0] == 2.0);
    assert(scaled[2] == 6.0);

    auto mask = a < b;
    assert(mask[0] == true);
    assert(mask[1] == true);
}

void test_plot() {
    matplotlibcpp::PyPlot plt;
    Vec x = {1.0, 2.0, 3.0};
    Vec y = {1.0, 4.0, 9.0};
    auto [fig, axes] = plt.subplots();
    axes[0].plot({.x = x, .y = y, .color = "b"});
    plt.close("all");
}

void test_scatter() {
    matplotlibcpp::PyPlot plt;
    Vec x = {1.0, 2.0, 3.0};
    Vec y = {1.0, 4.0, 9.0};
    auto [fig, axes] = plt.subplots();
    axes[0].scatter({.x = x, .y = y, .color = "r"});
    plt.close("all");
}

void test_bar() {
    matplotlibcpp::PyPlot plt;
    Vec x = {1.0, 2.0, 3.0};
    Vec h = {4.0, 2.0, 5.0};
    auto [fig, axes] = plt.subplots();
    axes[0].bar({.x = x, .height = h, .color = "orange"});
    plt.close("all");
}

void test_subplots() {
    matplotlibcpp::PyPlot plt;
    auto [fig, axes] = plt.subplots({.nrows = 2, .ncols = 2});
    assert(axes.size() == 4);
    plt.close("all");
}

void test_subplot_mosaic() {
    matplotlibcpp::PyPlot plt;
    auto [fig, axs] = plt.subplot_mosaic({.mosaic = "AB\nCC"});
    assert(axs.count("A") == 1);
    assert(axs.count("B") == 1);
    assert(axs.count("C") == 1);
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
        .where = y1 > y2,
        .alpha = 0.3
    });
    plt.close("all");
}

// ============================================================
// Main
// ============================================================
int main() {
    std::cout << "Running tests...\n\n";

    TEST(interpreter)
    TEST(vec_operators)
    TEST(plot)
    TEST(scatter)
    TEST(bar)
    TEST(subplots)
    TEST(subplot_mosaic)
    TEST(fill_between)

    std::cout << "\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed > 0 ? 1 : 0;  
}