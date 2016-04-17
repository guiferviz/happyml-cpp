

#include <gtest/gtest.h>

#include <happyml.h>


using namespace std;


TEST(DataSetTests, TestDefaultConstructor)
{
    happyml::DataSet dataset;
    
    ASSERT_EQ(0, dataset.d);
    ASSERT_EQ(0, dataset.N);
    ASSERT_EQ(0, dataset.X.n_rows);
    ASSERT_EQ(0, dataset.y.n_rows);
}

TEST(DataSetTests, TestConstructor)
{
    happyml::DataSet dataset(2, 2);
    
    ASSERT_EQ(2, dataset.d);
    ASSERT_EQ(2, dataset.N);
    ASSERT_EQ(2, dataset.X.n_rows);
    ASSERT_EQ(3, dataset.X.n_cols);
    ASSERT_EQ(2, dataset.y.n_rows);
    ASSERT_EQ(1, dataset.y.n_cols);
}

TEST(DataSetTests, TestSave)
{
    happyml::DataSet dataset(2, 2);
    dataset.X(0, 1) = 2;
    dataset.X(0, 2) = 4;
    dataset.X(1, 1) = 3;
    dataset.X(1, 2) = 6;
    dataset.save("borrame.csv");
}

TEST(DataSetTests, TestLoad)
{
    happyml::DataSet dataset;
    dataset.load("borrame.csv");
    ASSERT_EQ(1, dataset.X(0, 0));
    ASSERT_EQ(2, dataset.X(0, 1));
    ASSERT_EQ(4, dataset.X(0, 2));
    ASSERT_EQ(1, dataset.X(1, 0));
    ASSERT_EQ(3, dataset.X(1, 1));
    ASSERT_EQ(6, dataset.X(1, 2));
    ASSERT_EQ(0, dataset.y(0));
    ASSERT_EQ(0, dataset.y(1));
    
    ASSERT_EQ(2, dataset.d);
    ASSERT_EQ(2, dataset.N);
    ASSERT_EQ(2, dataset.X.n_rows);
    ASSERT_EQ(3, dataset.X.n_cols);
    ASSERT_EQ(2, dataset.y.n_rows);
    ASSERT_EQ(1, dataset.y.n_cols);
}

TEST(DataSetTests, TestMultipleOutputs)
{
    happyml::DataSet dataset;
    dataset.load("fixtures/parabolas.data", 2);
    
    ASSERT_EQ(1, dataset.d);
    ASSERT_EQ(6, dataset.N);
    ASSERT_EQ(2, dataset.k);
    ASSERT_EQ(6, dataset.X.n_rows);
    ASSERT_EQ(2, dataset.X.n_cols);
    ASSERT_EQ(6, dataset.y.n_rows);
    ASSERT_EQ(2, dataset.y.n_cols);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
