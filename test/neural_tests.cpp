

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
            srand(time(NULL));
            //srand(0);
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

TEST_F(NeuralNetworkTests, TestTrain5)
{
    dataset.load("fixtures/parabolas.data", 2);
    
    happyml::NormalizerXY n(dataset);
    n.apply(dataset);

    nnr = happyml::NNRegression(3, 1, 10, 2);
    double error = nnr.train(dataset, 5000, 0.3);
    
    happyml::Input x(2);  x[0] = 1;  x[1] = 2;
    vec output = nnr.predictVec(n.apply(x));
    
    happyml::DenormalizerXY d(n);
    output = d.applyOutput(output);
    
    ASSERT_NEAR(-1, output[0], 0.25);
    ASSERT_NEAR( 2, output[1], 0.25);
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

TEST_F(NeuralNetworkTests, TestTrain6)
{
    dataset.load("fixtures/4points_2outputs.data", 2);

    happyml::Standarizer n(dataset);
    n.apply(dataset);
    
    nn = happyml::NeuralNetwork(3, 2, 8, 2);
    double error = nn.train(dataset, 1000, 0.1);

    // Test point (5, 5) -> (1, 1)
    happyml::Input x(3);  x[0] = 1;  x[1] = 5;  x[2] = 5;
    vec output = nn.predictVec(n.apply(x));
    ASSERT_TRUE(output[0] > 0);
    ASSERT_TRUE(output[1] > 0);
    
    // Testing point (5, -5) -> (1, -1)
    x[1] = 5;  x[2] = -5;
    output = nn.predictVec(n.apply(x));
    ASSERT_TRUE(output[0] > 0);
    ASSERT_TRUE(output[1] < 0);
    
    // Testing point (-5, -5) -> (-1, -1)
    x[1] = -5;  x[2] = -5;
    output = nn.predictVec(n.apply(x));
    ASSERT_TRUE(output[0] < 0);
    ASSERT_TRUE(output[1] < 0);
    
    // Testing point (-5, 5) -> (-1, 1)
    x[1] = -5;  x[2] = 5;
    output = nn.predictVec(n.apply(x));
    ASSERT_TRUE(output[0] < 0);
    ASSERT_TRUE(output[1] > 0);
}

TEST_F(NeuralNetworkTests, TestSGD)
{
    dataset.load("fixtures/4points.data");

    nn = happyml::NeuralNetwork(2, 2, 1);
    double error = nn.sgdTrain(dataset, 50, 0.1, 0, 4);

    ASSERT_NEAR(0, error, 1e-10);
}
/*
TEST_F(NeuralNetworkTests, TestSGDOverfit)
{
    dataset.load("fixtures/overfitme.data");
    dataset.save("points.data");

    nn = happyml::NeuralNetwork(4, 2, 20, 20, 1);
    double error = nn.sgdTrain(dataset, 300000, 0.1, 0, 3);
    //double error = nn.train(dataset, 3000, 0.1, 0.1);

    nn.saveSampling("boundary.data", -1, 1, 500, -1, 1, 500);
    system("happyplot -o images/output.png");
    
    ASSERT_NEAR(0, error, 1e-10);
}
*/

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
