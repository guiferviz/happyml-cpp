
#include <iostream>

#include <gtest/gtest.h>

#include <happyml.h>


using namespace std;


TEST(BasicTests, TestVersion)
{
    ASSERT_EQ(HAPPY_ML_VERSION, happyml::version);
}

TEST(BasicTests, TestGreeting)
{
    happyml::greet();
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
