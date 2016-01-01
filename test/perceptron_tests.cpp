

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class PerceptronTests : public testing::Test
{
    protected:
    
        happyml::DataSet dataset;
        
        happyml::Perceptron perceptron;
        

        PerceptronTests()
        {
        }

        virtual ~PerceptronTests()
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
            //perceptron.saveSampling("boundary.data", -10, 10, 500, -10, 10, 500);
            //system("happyplot -d fixtures/2points.data");
            
            //remove("points.data");
            //remove("boundary.data");
            //remove("output.png");
        }

};


TEST_F(PerceptronTests, TestError1)
{
    dataset.load("fixtures/2points.data");

    vec w(3); w[0] = 0; w[1] = 1; w[2] = -1;
    perceptron = happyml::Perceptron(w);
    double error = perceptron.error(dataset);

    ASSERT_EQ(0, error);
}

TEST_F(PerceptronTests, TestError2)
{
    dataset.load("fixtures/2points.data");

    vec w(3); w[0] = 0; w[1] = -1; w[2] = 1;
    perceptron = happyml::Perceptron(w);
    double error = perceptron.error(dataset);

    ASSERT_EQ(1, error);
}

TEST_F(PerceptronTests, TestError3)
{
    dataset.load("fixtures/4points.data");

    vec w(3); w[0] = 0; w[1] = 0; w[2] = 1;
    perceptron = happyml::Perceptron(w);
    double error = perceptron.error(dataset);

    ASSERT_EQ(0.5, error);
}

TEST_F(PerceptronTests, TestTrain1)
{
    dataset.load("fixtures/4points.data");

    vec w(3); w[0] = 0; w[1] = 0; w[2] = 1;
    perceptron = happyml::Perceptron(w);
    double error = perceptron.train(dataset, 1);

    ASSERT_EQ(0, error);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
