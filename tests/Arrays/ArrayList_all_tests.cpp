/**
 * @file ArrayList_all_tests.cpp
 * @author YT_Minro (yurilt15312@outlook.com)
 * @brief
 * @version 0.1
 * @date 2025-09-12
 *
 * @copyright Copyright (c) 2025
 *
 */
// #define DOCTEST_CONFIG_COLORS_ANSI
#include <Windows.h>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "ArrayList.hpp"
#include "doctest/doctest.h"
#include <string>


TEST_CASE("Test ArrayList function") {
    using namespace LiyStd;
    using namespace std;
    const int aa = 66;
    int a        = 2;
    int b        = 5;
    CHECK(a + b == 7);
    CHECK(a == 2);
    
}