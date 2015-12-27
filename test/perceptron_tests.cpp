

#include <gtest/gtest.h>

#include <happyml.h>


using namespace std;


TEST(PerceptronTests, TestTraining)
{
    happyml::DataSet dataset;
    dataset.load("borrame.csv");
    
    happyml::Perceptron perceptron(dataset.d);
    perceptron.train(dataset, 10);
    
    system("happyplot");
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
