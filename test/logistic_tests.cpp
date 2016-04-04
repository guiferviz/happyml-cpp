

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
            //remove("points.data");
            //remove("boundary.data");
            //remove("output.png");
        }
};


TEST_F(LogisticRegressionTests, TestTrain1)
{
    dataset.load("fixtures/4points.data");

    logistic = happyml::LogisticRegression(dataset.d);
    double error = logistic.train(dataset, 10, 0.1);

    ASSERT_NEAR(0, error, 0.1);
}

TEST_F(LogisticRegressionTests, TestTrain2)
{
    dataset.load("fixtures/circle.data");

    happyml::TransformerCollection t;
    t.add(new happyml::transforms::Pow(1, 2, true));
    t.add(new happyml::transforms::Pow(2, 2, true));
    t.add(new happyml::transforms::Remove(2));
    t.add(new happyml::transforms::Remove(1));
    t.apply(dataset);
    //dataset.save("points.data");  // Save transformed data.

    logistic = happyml::LogisticRegression(dataset.d);
    double error = logistic.train(dataset, 50, 0.4);
    
    //logistic.saveSampling("boundary.data", -3, 3, 50, -3, 3, 50, t);
    //system("happyplot");  // Plot transformed boundary and data.

    ASSERT_NEAR(0, error, 0.1);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
