

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
    
    ASSERT_NEAR(0, dataset.X(0, 0), 0.001);
    ASSERT_NEAR(0.8660, dataset.X(0, 1), 0.001);
    ASSERT_NEAR(0.8660, dataset.X(0, 2), 0.001);
    ASSERT_NEAR(0.8660, dataset.X(1, 1), 0.001);
    ASSERT_NEAR(-0.8660, dataset.X(1, 2), 0.001);
    ASSERT_NEAR(-0.8660, dataset.X(2, 1), 0.001);
    ASSERT_NEAR(0.8660, dataset.X(2, 2), 0.001);
    ASSERT_NEAR(-0.8660, dataset.X(3, 1), 0.001);
    ASSERT_NEAR(-0.8660, dataset.X(3, 2), 0.001);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
