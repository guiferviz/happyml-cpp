

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class KNNTests : public testing::Test
{
    protected:

        happyml::DataSet dataset;


        KNNTests()
        {
        }

        virtual ~KNNTests()
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


TEST_F(KNNTests, TestTrain1)
{
    dataset.load("fixtures/4points.data");

    happyml::KNN knn(dataset);
    happyml::Input x(3);
    x[0] = 1;
    x[1] = 1;
    x[2] = 1;
    double y = knn.predict(x);

    ASSERT_NEAR(1, y, 0.01);
    
    x[1] = -1;
    y = knn.predict(x);

    ASSERT_NEAR(-1, y, 0.01);
}

TEST_F(KNNTests, TestTrain2)
{
    /*dataset.load("fixtures/circle.data");

    happyml::Transformer t;
    t.addPower(1, 2);
    t.addPower(2, 2);
    t.remove(1);
    t.remove(2);
    t.apply(dataset);
    //dataset.save("points.data");  // Save transformed data.

    logistic = happyml::LogisticRegression(dataset.d);
    double error = logistic.train(dataset, 50, 0.4);
    
    //logistic.saveSampling("boundary.data", -3, 3, 50, -3, 3, 50, t);
    //system("happyplot");  // Plot transformed boundary and data.

    ASSERT_NEAR(0, error, 0.1);*/
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
