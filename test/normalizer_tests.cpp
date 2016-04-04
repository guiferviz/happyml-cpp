

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class NormalizerTests : public testing::Test
{
    protected:

        happyml::DataSet dataset;


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

TEST_F(NormalizerTests, TestNormalizer0)
{
    dataset.load("fixtures/4points.data");
    
    happyml::Normalizer n(dataset);
    n.apply(dataset);
    
    ASSERT_NEAR(1, dataset.X(0, 0), 0.001);
    ASSERT_NEAR(1, dataset.X(0, 1), 0.001);
    ASSERT_NEAR(1, dataset.X(0, 2), 0.001);
    ASSERT_NEAR(1, dataset.X(1, 0), 0.001);
    ASSERT_NEAR(1, dataset.X(1, 1), 0.001);
    ASSERT_NEAR(0, dataset.X(1, 2), 0.001);
    ASSERT_NEAR(1, dataset.X(2, 0), 0.001);
    ASSERT_NEAR(0, dataset.X(2, 1), 0.001);
    ASSERT_NEAR(1, dataset.X(2, 2), 0.001);
    ASSERT_NEAR(1, dataset.X(3, 0), 0.001);
    ASSERT_NEAR(0, dataset.X(3, 1), 0.001);
    ASSERT_NEAR(0, dataset.X(3, 2), 0.001);
}

TEST_F(NormalizerTests, TestNormalizer1)
{
    dataset.load("fixtures/4points.data");
    
    happyml::Standarizer s(dataset);
    s.apply(dataset);
    
    ASSERT_NEAR(1, dataset.X(0, 0), 0.001);
    ASSERT_NEAR(0.8660, dataset.X(0, 1), 0.001);
    ASSERT_NEAR(0.8660, dataset.X(0, 2), 0.001);
    ASSERT_NEAR(1, dataset.X(1, 0), 0.001);
    ASSERT_NEAR(0.8660, dataset.X(1, 1), 0.001);
    ASSERT_NEAR(-0.8660, dataset.X(1, 2), 0.001);
    ASSERT_NEAR(1, dataset.X(2, 0), 0.001);
    ASSERT_NEAR(-0.8660, dataset.X(2, 1), 0.001);
    ASSERT_NEAR(0.8660, dataset.X(2, 2), 0.001);
    ASSERT_NEAR(1, dataset.X(3, 0), 0.001);
    ASSERT_NEAR(-0.8660, dataset.X(3, 1), 0.001);
    ASSERT_NEAR(-0.8660, dataset.X(3, 2), 0.001);
}

TEST_F(NormalizerTests, TestNormalizerWithTransformations)
{
    dataset.load("fixtures/4points.data");
    
    happyml::TransformerCollection t;
    t.add(new happyml::transforms::Pow(1, 2, true));
    t.add(new happyml::transforms::Remove(1));
    t.apply(dataset);
    
    happyml::Standarizer s(dataset);
    s.apply(dataset);
    
    ASSERT_NEAR(1, dataset.X(0, 0), 0.001);
    ASSERT_NEAR(0.8660, dataset.X(0, 1), 0.001);
    ASSERT_NEAR(0, dataset.X(0, 2), 0.001);
    ASSERT_NEAR(1, dataset.X(1, 0), 0.001);
    ASSERT_NEAR(-0.8660, dataset.X(1, 1), 0.001);
    ASSERT_NEAR(0, dataset.X(1, 2), 0.001);
    ASSERT_NEAR(1, dataset.X(2, 0), 0.001);
    ASSERT_NEAR(0.8660, dataset.X(2, 1), 0.001);
    ASSERT_NEAR(0, dataset.X(2, 2), 0.001);
    ASSERT_NEAR(1, dataset.X(3, 0), 0.001);
    ASSERT_NEAR(-0.8660, dataset.X(3, 1), 0.001);
    ASSERT_NEAR(0, dataset.X(3, 2), 0.001);
}

TEST_F(NormalizerTests, TestNormalizerMinMax)
{
    dataset.load("fixtures/4points.data");
    
    vec minvec(2); minvec(0) = -5; minvec(1) = -5;
    vec maxvec(2); maxvec(0) =  5; maxvec(1) =  5;
    happyml::Normalizer n(minvec, maxvec);
    n.apply(dataset);
    
    ASSERT_NEAR(1, dataset.X(0, 0), 0.001);
    ASSERT_NEAR(1, dataset.X(0, 1), 0.001);
    ASSERT_NEAR(1, dataset.X(0, 2), 0.001);
    ASSERT_NEAR(1, dataset.X(1, 0), 0.001);
    ASSERT_NEAR(1, dataset.X(1, 1), 0.001);
    ASSERT_NEAR(0, dataset.X(1, 2), 0.001);
    ASSERT_NEAR(1, dataset.X(2, 0), 0.001);
    ASSERT_NEAR(0, dataset.X(2, 1), 0.001);
    ASSERT_NEAR(1, dataset.X(2, 2), 0.001);
    ASSERT_NEAR(1, dataset.X(3, 0), 0.001);
    ASSERT_NEAR(0, dataset.X(3, 1), 0.001);
    ASSERT_NEAR(0, dataset.X(3, 2), 0.001);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
