

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class HappyToolsTests : public testing::Test
{
    protected:

        happyml::DataSet dataset;

        happyml::LogisticRegression logistic;


        HappyToolsTests()
        {
        }

        virtual ~HappyToolsTests()
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


TEST_F(HappyToolsTests, TestStringSubstitution)
{
    happyml::tools::dictionary dic;
    dic["mood"] = "happy";

    string actual = happyml::tools::substitute("Be {{mood}}", dic);
    
    ASSERT_EQ("Be happy", actual);
}


TEST_F(HappyToolsTests, TestSaveDot)
{
    dataset.load("fixtures/4points.data");

    logistic = happyml::LogisticRegression(dataset.d);
    double error = logistic.train(dataset, 1000, 2);
    

    happyml::tools::modelToDot(logistic, "model.dot");
    
    cout << logistic.getWeights() << endl;
    
    system("dot -Tpng -omodel.png -Gsize=9,15\\! -Gdpi=100 model.dot");
    //logistic.saveSampling("boundary.data", -10, 10, 50, -10, 10, 50);
    //system("happyplot -d fixtures/4points.data");
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
