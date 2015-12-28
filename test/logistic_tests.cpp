

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class LogisticRegressionTests : public testing::Test
{
    protected:

        happyml::DataSet dataset;

        happyml::LogisticRegression logistic;


        LogisticRegressionTests()
        {
        }

        virtual ~LogisticRegressionTests()
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


TEST_F(LogisticRegressionTests, TestTrain)
{
    dataset.load("fixtures/4points.data");

    logistic = happyml::LogisticRegression(dataset.d);
    double error = logistic.train(dataset, 10, 0.1);

    ASSERT_NEAR(0, error, 0.1);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
