

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class NeuralNetworkTests : public testing::Test
{
    protected:

        happyml::DataSet dataset;

        happyml::NeuralNetwork nn;

        happyml::NNRegression nnr;


        NeuralNetworkTests() : nn(2, 2, 1), nnr(2, 1, 1)
        {
        }

        virtual ~NeuralNetworkTests()
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


TEST_F(NeuralNetworkTests, TestTrain1)
{
    dataset.load("fixtures/4points.data");

    nn = happyml::NeuralNetwork(2, 2, 1);
    double error = nn.train(dataset, 100, 0.1);

    ASSERT_NEAR(0, error, 0.1);
}

TEST_F(NeuralNetworkTests, TestTrain2)
{
    dataset.load("fixtures/circle.data");

    nn = happyml::NeuralNetwork(5, 2, 10, 10, 10, 1);
    double error = nn.train(dataset, 500, 0.1);
    
    //nn.saveSampling("boundary.data", -10, 10, 50, -10, 10, 50);
    //system("happyplot -d fixtures/circle.data");

    ASSERT_NEAR(0, error, 0.1);
}

TEST_F(NeuralNetworkTests, TestTrain3)
{
    dataset.load("fixtures/parabola.data");
    
    happyml::Normalizer nx(dataset);
    nx.apply(dataset);
    // It's important to normalize que outputs too.
    happyml::Normalizer ny(dataset.y);
    ny.apply(dataset.y);
    
    dataset.save("borrame.data");

    nnr = happyml::NNRegression(3, 1, 10, 1);
    double error = nnr.train(dataset, 500, 0.1);
    
    //nnr.saveSampling("line.data", -1, 2, 500);
    //system("happyplot -d borrame.data");

    ASSERT_NEAR(0, error, 0.01);
}

TEST_F(NeuralNetworkTests, TestTrain4)
{
    dataset.load("fixtures/parabola.data");
    
    happyml::Normalizer nx(dataset);
    nx.apply(dataset);
    // It's important to normalize que outputs too.
    happyml::Normalizer ny(dataset.y);
    ny.apply(dataset.y);
    
    dataset.save("borrame.data");

    nnr = happyml::NNRegression(4, 1, 10, 10, 1);
    double error = nnr.train(dataset, 1000000, 0.1);
    
    nnr.saveSampling("line.data", 0, 1, 500);
    system("happyplot -d borrame.data");

    ASSERT_NEAR(0, error, 0.01);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
