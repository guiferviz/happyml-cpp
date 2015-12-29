

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class TransformerTests : public testing::Test
{
    protected:

        happyml::DataSet dataset;

        happyml::Transformer t;


        TransformerTests()
        {
        }

        virtual ~TransformerTests()
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


TEST_F(TransformerTests, TestSquareTransform)
{
    dataset.load("fixtures/2points.data");

    t.addPower(1, 2);
    t.apply(dataset);

    ASSERT_EQ(3, dataset.d);
    ASSERT_EQ(25, dataset.X(0, 3));
    ASSERT_EQ(25, dataset.X(1, 3));
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
