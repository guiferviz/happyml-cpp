

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class SVMTests : public testing::Test
{
    protected:

        happyml::DataSet dataset;

        happyml::SVM svm;


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
            
            dataset.load("fixtures/2points.data");
        }

        virtual void TearDown()
        {
            //linear.saveLine("line.data", -10, 10, 20);
            //system("happyplot -d fixtures/4points.data");
            
            //remove("output.png");
        }
};


TEST_F(SVMTests, TestSVM)
{
    happyml::Transformer t;
    t.normalize();
    t.apply(dataset);
    dataset.save("points.data");
    
    svm.train(dataset, /* C */ 100, /* Iter */ 10, /* Tolerance */ 0.001);
    
    svm.saveSampling("boundary.data", -2, 2, 500, -2, 2, 500);
    
    system("happyplot");
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
