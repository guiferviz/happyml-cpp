

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
            remove("borrame.nn");
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
    
    //dataset.save("borrame.data");

    nnr = happyml::NNRegression(4, 1, 10, 10, 1);
    double error = nnr.train(dataset, 500, 0.1);
    
    //nnr.saveSampling("line.data", 0, 1, 500);
    //system("happyplot -d borrame.data");

    ASSERT_NEAR(0, error, 0.03);
}

TEST_F(NeuralNetworkTests, TestConstructorVectorLayers)
{
    dataset.load("fixtures/4points.data");

    vector<unsigned> layers;
    layers.push_back(2);
    layers.push_back(1);
    nn = happyml::NeuralNetwork(layers);
    double error = nn.train(dataset, 100, 0.1);

    ASSERT_NEAR(0, error, 0.1);
}

TEST_F(NeuralNetworkTests, TestSaveLoad)
{
    dataset.load("fixtures/4points.data");

    nn = happyml::NeuralNetwork(2, 2, 1);
    double error = nn.train(dataset, 100, 0.1);
    nn.save("borrame.nn");
    
    happyml::NeuralNetwork nn2;
    nn2.load("borrame.nn");
    
    error = nn2.error(dataset);

    ASSERT_NEAR(0, error, 0.1);
}

TEST_F(NeuralNetworkTests, TestConstructorWeights)
{
    dataset.load("fixtures/4points.data");

    vector<mat> weights;
    vec w(3); w(0) = 1.1550; w(1) = 0.6802; w(2) = 0.0167;
    weights.push_back(w);

    nn = happyml::NeuralNetwork(weights);
    double error = nn.error(dataset);

    ASSERT_NEAR(0, error, 0.1);
}

TEST_F(NeuralNetworkTests, TestDeltaStop)
{
    dataset.load("fixtures/4points.data");

    nn = happyml::NeuralNetwork(2, 2, 1);
    double error = nn.train(dataset, 1000000, 0.1, 0, 1e-7);
    unsigned iterations = nn.getLastIterations();

    ASSERT_NEAR(0, error, 0.001);
    ASSERT_EQ(495, iterations);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
