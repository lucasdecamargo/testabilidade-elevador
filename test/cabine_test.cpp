#include <gtest/gtest.h>
#include <cabine.h>
#include <iostream>
#include <exception>
#include <thread>


TEST(CabineTest, Iluminacao)
{
    Iluminacao ilum(true);
    EXPECT_EQ(ilum.soma(2,2), 4);
}

