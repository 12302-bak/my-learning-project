#include <gtest/gtest.h>
#include "head.h"

/**
 * @args: --gtest_filter=Calc.Add
 */
TEST(Calc, Add)       { EXPECT_EQ(add(2, 3), 5); }
TEST(Calc, Subtract)  { EXPECT_EQ(subtract(20, 12), 8); }
TEST(Calc, Multiply)  { EXPECT_EQ(multiply(3, 4), 12); }
TEST(Calc, Divide)    { EXPECT_DOUBLE_EQ(divide(20, 4), 5.0); }