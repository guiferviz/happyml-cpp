

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class NormalizerTests : public testing::Test
{
    protected:

        happyml::DataSet dataset;

        happyml::Transformer t;


        NormalizerTests()
        {
        }

        virtual ~NormalizerTests()
        {
        }

        virtual void SetUp()
        {
            //#include <time.h>
            //srand(time(NULL));
            srand(0);
            
            dataset.load("fixtures/4points.data");
        }

        virtual void TearDown()
        {
            //linear.saveLine("line.data", -10, 10, 20);
            //system("happyplot -d fixtures/4points.data");
            
            //remove("points.data");
            //remove("boundary.data");
            //remove("output.png");
        }
};


TEST_F(NormalizerTests, TestNormalizer1)
{
    t.normalize();
    t.apply(dataset);

    ASSERT_EQ(1, dataset.X(0, 1));
    ASSERT_EQ(1, dataset.X(0, 2));
    ASSERT_EQ(1, dataset.X(1, 1));
    ASSERT_EQ(-1, dataset.X(1, 1));
    ASSERT_EQ(-1, dataset.X(2, 1));
    ASSERT_EQ(1, dataset.X(2, 2));
    ASSERT_EQ(-1, dataset.X(3, 1));
    ASSERT_EQ(-1, dataset.X(3, 1));
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
