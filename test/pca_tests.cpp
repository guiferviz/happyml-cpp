

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class PCATests : public testing::Test
{
    protected:

        happyml::DataSet dataset;

        happyml::Transformer t;


        PCATests()
        {
        }

        virtual ~PCATests()
        {
        }

        virtual void SetUp()
        {
            //#include <time.h>
            //srand(time(NULL));
            srand(0);

            remove("points.data");
            remove("boundary.data");
        }

        virtual void TearDown()
        {
            //linear.saveLine("line.data", -10, 10, 20);
            //system("happyplot -d fixtures/4points.data");
            
            //remove("output.png");
        }
};


TEST_F(PCATests, TestSquareNewFeatureTransform)
{
    dataset.load("fixtures/pca.data");
    
    t.pca(1);
    t.apply(dataset);
    
    dataset.save("points.data");
    
    vec w1(3); w1(0) = 0; w1(1) = -.85065; w1(2) = -.52573;
    vec w2(3); w2(0) = 0; w2(1) = 0.525731; w2(2) = -0.850651;
    happyml::Perceptron p(w2);
    p.saveSampling("boundary.data", -2, 2, 500, -2, 2, 500);
    
    system("happyplot -t PCA");
    //system("happyplot -d fixtures/pca.data");
    
    ASSERT_EQ(1, dataset.d);
    ASSERT_EQ(4, dataset.N);
    
    ASSERT_NEAR(1, dataset.X(0, 0), 0.001);
    ASSERT_NEAR(1.11352, dataset.X(0, 1), 0.001);
    
    ASSERT_NEAR(1, dataset.X(1, 0), 0.001);
    ASSERT_NEAR(-0.26287, dataset.X(1, 1), 0.001);
    
    ASSERT_NEAR(1, dataset.X(2, 0), 0.001);
    ASSERT_NEAR(0.26287, dataset.X(2, 1), 0.001);
    
    ASSERT_NEAR(1, dataset.X(3, 0), 0.001);
    ASSERT_NEAR(-1.11352, dataset.X(3, 1), 0.001);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
