

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class PCATests : public testing::Test
{
    protected:

        happyml::DataSet dataset;


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
            
            dataset.load("fixtures/pca.data");
        }

        virtual void TearDown()
        {
            //linear.saveLine("line.data", -10, 10, 20);
            //system("happyplot -d fixtures/4points.data");
            
            //remove("output.png");
        }
        
        void checkDataset()
        {
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
};


TEST_F(PCATests, TestPCAUntilK)
{
    happyml::PCA pca(dataset, 1);
    pca.apply(dataset);
    
    checkDataset();
}

TEST_F(PCATests, TestPCAMinVariance)
{
    happyml::PCA pca(dataset, 0.85);
    pca.apply(dataset);
    
    checkDataset();
}


TEST_F(PCATests, TestPCARetainedVariance)
{
    happyml::PCA pca(dataset, 0.85);
    pca.apply(dataset);
    
    double retainedVar = pca.getRetainedVariance();
    
    ASSERT_TRUE(retainedVar > 0.85);
}



class LDATests : public testing::Test
{
    protected:

        happyml::DataSet dataset;


        LDATests()
        {
        }

        virtual ~LDATests()
        {
        }

        virtual void SetUp()
        {
            //#include <time.h>
            //srand(time(NULL));
            srand(0);

            remove("points.data");
            remove("boundary.data");
            
            dataset.load("fixtures/pca.data");
        }

        virtual void TearDown()
        {
            //linear.saveLine("line.data", -10, 10, 20);
            //system("happyplot -d fixtures/4points.data");
            
            //remove("output.png");
        }
        
        void checkDataset()
        {
            ASSERT_EQ(1, dataset.d);
            ASSERT_EQ(4, dataset.N);
            
            ASSERT_NEAR(1, dataset.X(0, 0), 0.001);
            ASSERT_NEAR(-1, dataset.X(0, 1), 0.001);
            
            ASSERT_NEAR(1, dataset.X(1, 0), 0.001);
            ASSERT_NEAR(0, dataset.X(1, 1), 0.001);
            
            ASSERT_NEAR(1, dataset.X(2, 0), 0.001);
            ASSERT_NEAR(0, dataset.X(2, 1), 0.001);
            
            ASSERT_NEAR(1, dataset.X(3, 0), 0.001);
            ASSERT_NEAR(1, dataset.X(3, 1), 0.001);
        }
};


TEST_F(LDATests, TestLDA)
{
    happyml::LDA lda(dataset, 1);
    lda.apply(dataset);
    
    checkDataset();
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
