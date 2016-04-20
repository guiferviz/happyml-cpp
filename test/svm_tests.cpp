

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class SVMTests : public testing::Test
{
    protected:

        happyml::DataSet dataset;


        SVMTests()
        {
        }

        virtual ~SVMTests()
        {
        }

        virtual void SetUp()
        {
            //#include <time.h>
            //srand(time(NULL));
            srand(0);

            remove("points.data");
            remove("boundary.data");
            
            dataset.load("fixtures/svm.data");
        }

        virtual void TearDown()
        {
            //linear.saveLine("line.data", -10, 10, 20);
            //system("happyplot -d fixtures/4points.data");
            
            //remove("output.png");
        }
};


TEST_F(SVMTests, TestSVMLinear)
{
    happyml::SVMLinear svm;
    double error = svm.train(dataset,
            /* C         */   100,
            /* Iter      */    10,
            /* Tolerance */ 1e-10);
    
    int nSV = svm.getNumberSupportVectors();
    ASSERT_EQ(3, nSV);
    ASSERT_NEAR(0, error, 1e-5);
    
    vec expectedWeights;
    expectedWeights << 0 << endr << 0.5 << endr << 0.5 << endr;
    vec actualWeights = svm.getWeights();
    ASSERT_TRUE(approx_equal(expectedWeights, actualWeights, "absdiff", 1e-5));
    
    //svm.saveSampling("boundary.data", -2, 2, 500, -2, 2, 500);
    //system("happyplot -d fixtures/svm.data");
}

TEST_F(SVMTests, TestSVMGaussian)
{
    happyml::SVMGaussian svm(2);
    double error = svm.train(dataset,
            /* C         */   100,
            /* Iter      */    10,
            /* Tolerance */ 1e-10);
    
    int nSV = svm.getNumberSupportVectors();
    ASSERT_EQ(4, nSV);
    ASSERT_NEAR(0, error, 0.2);

    //svm.saveSampling("boundary.data", -2, 2, 500, -2, 2, 500);
    //system("happyplot -d fixtures/svm.data");
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
