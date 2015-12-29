

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class LinearRegressionTests : public testing::Test
{
    protected:

        happyml::DataSet dataset;

        happyml::LinearRegression linear;


        LinearRegressionTests()
        {
        }

        virtual ~LinearRegressionTests()
        {
        }

        virtual void SetUp()
        {
            //#include <time.h>
            //srand(time(NULL));
            srand(0);
        }

        virtual void TearDown()
        {
            //logistic.saveBoundary("boundary.data", 500, -10, 10, -10, 10);
            //system("happyplot -d fixtures/4points.data");
            
            //remove("points.data");
            //remove("boundary.data");
            //remove("output.png");
        }
};


TEST_F(LinearRegressionTests, TestError)
{
    dataset.load("fixtures/4points_reg.data");

    vec w(2); w[0] = 1; w[1] = 1;
    linear = happyml::LinearRegression(w);
    double error = linear.error(dataset);

    ASSERT_EQ(0, error);
}

TEST_F(LinearRegressionTests, TestTrain)
{
    dataset.load("fixtures/4points_reg.data");

    linear = happyml::LinearRegression(dataset.d);
    double error = linear.train(dataset);

    ASSERT_NEAR(0, error, 0.001);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
