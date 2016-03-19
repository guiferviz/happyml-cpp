

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


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
