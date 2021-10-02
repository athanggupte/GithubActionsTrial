#include <gtest/gtest.h>

TEST(FailingTest, OneNotEqualToZero)
{
    EXPECT_EQ(1, 0);
}