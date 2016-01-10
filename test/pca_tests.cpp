

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
    
    //t.normalize();
    t.pca(2);
    t.apply(dataset);
    
    dataset.save("points.data");
    // z = Xm*V(:,1)
    //vec z = Xm * eigVec.col(1);
    // p = z*V(:,1)'
    //mat p = z * eigVec.col(1).t();
    // p = bsxfun(@plus, p, mu)
    //p = p + vec(dataset.N, fill::ones) * meanVec;
    
    vec w1(3); w1(0) = 1; w1(1) = -.85065; w1(2) = -.52573;
    vec w2(3); w2(0) = 1; w2(1) = 0.52573; w2(2) = -.85065;
    happyml::Perceptron p(w1);
    //p.saveSampling("boundary.data", -2, 4, 500, -2, 4, 500);
    
    system("happyplot -t PCA");
    //system("happyplot -d fixtures/pca.data");
    
    ASSERT_EQ(1, dataset.d);
    ASSERT_EQ(4, dataset.N);
    
    ASSERT_NEAR(1, dataset.X(0, 0), 0.001);
    ASSERT_NEAR(-0.10041, dataset.X(0, 1), 0.001);
    
    ASSERT_NEAR(1, dataset.X(1, 0), 0.001);
    ASSERT_NEAR(-0.42533, dataset.X(1, 1), 0.001);
    
    ASSERT_NEAR(1, dataset.X(2, 0), 0.001);
    ASSERT_NEAR(0.42533, dataset.X(2, 1), 0.001);
    
    ASSERT_NEAR(1, dataset.X(3, 0), 0.001);
    ASSERT_NEAR(0.10041, dataset.X(3, 1), 0.001);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
