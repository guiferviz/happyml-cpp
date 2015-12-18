
#include <iostream>

#include <gtest/gtest.h>


using namespace std;


TEST(TestingTests, Test01)
{
    cout << "hooooola" << endl;
    ASSERT_EQ(-1, -1);
}

TEST(TestingTests, Test02)
{ 
    ASSERT_EQ(0.0, 0.0);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
