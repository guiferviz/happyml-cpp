

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;


class TransformerTests : public testing::Test
{
    protected:

        happyml::DataSet dataset;

        happyml::TransformerCollection t;


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
            
            dataset.load("fixtures/2points.data");
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


TEST_F(TransformerTests, TestSquareNewFeatureTransform)
{
    t.add(new happyml::transforms::Pow(1, 2, true));
    t.apply(dataset);

    ASSERT_EQ(3, dataset.d);
    ASSERT_EQ(25, dataset.X(0, 3));
    ASSERT_EQ(25, dataset.X(1, 3));
}

TEST_F(TransformerTests, TestAddTransform)
{
    t.add(new happyml::transforms::Add(1, 2, false));
    t.apply(dataset);

    ASSERT_EQ(2, dataset.d);
    ASSERT_EQ(7, dataset.X(0, 1));
    ASSERT_EQ(-3, dataset.X(1, 1));
}

TEST_F(TransformerTests, TestMultTransform)
{
    t.add(new happyml::transforms::Mul(1, 3, false));
    t.apply(dataset);

    ASSERT_EQ(2, dataset.d);
    ASSERT_EQ(15, dataset.X(0, 1));
    ASSERT_EQ(-15, dataset.X(1, 1));
}

TEST_F(TransformerTests, TestSquareTransform)
{
    t.add(new happyml::transforms::Pow(2, 2, false));
    t.apply(dataset);

    ASSERT_EQ(2, dataset.d);
    ASSERT_EQ(25, dataset.X(0, 2));
    ASSERT_EQ(25, dataset.X(1, 2));
}

TEST_F(TransformerTests, TestAddNewFeatureTransform)
{
    t.add(new happyml::transforms::Add(1, 2, true));
    t.apply(dataset);

    ASSERT_EQ(3, dataset.d);
    ASSERT_EQ(7, dataset.X(0, 3));
    ASSERT_EQ(-3, dataset.X(1, 3));
}

TEST_F(TransformerTests, TestMultNewFeatureTransform)
{
    t.add(new happyml::transforms::Mul(1, 3, true));
    t.apply(dataset);

    ASSERT_EQ(3, dataset.d);
    ASSERT_EQ(15, dataset.X(0, 3));
    ASSERT_EQ(-15, dataset.X(1, 3));
}

TEST_F(TransformerTests, TestRemoveTransform)
{
    t.add(new happyml::transforms::Remove(1));
    t.apply(dataset);

    ASSERT_EQ(1, dataset.d);
    ASSERT_EQ(-5, dataset.X(0, 1));
    ASSERT_EQ(5, dataset.X(1, 1));
}

TEST_F(TransformerTests, TestRemove2Transform)
{
    dataset.load("fixtures/3features.data");

    t.add(new happyml::transforms::Remove(3));
    t.add(new happyml::transforms::Remove(1));
    t.apply(dataset);

    ASSERT_EQ(1, dataset.d);
    ASSERT_EQ(2, dataset.X(0, 1));
    ASSERT_EQ(5, dataset.X(1, 1));
    ASSERT_EQ(8, dataset.X(2, 1));
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
