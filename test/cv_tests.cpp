

#include <gtest/gtest.h>

#include <stdio.h>

#include <happyml.h>


using namespace std;
using namespace happyml;


class CrossValidationTests : public testing::Test
{
    protected:

        DataSet dataset;

        LogisticRegression logistic;


        CrossValidationTests()
        {
        }

        virtual ~CrossValidationTests()
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


class TestingProcess : public TrainingProcess
{
    public:

        virtual void run(const DataSet& training, const DataSet& cv)
        {
            cout << "Training" << endl;
            cout << training.X << endl;
            
            cout << "CV" << endl;
            cout << cv.X << endl;
        }
};


TEST_F(CrossValidationTests, Test01)
{
    //dataset.load("fixtures/4points.data");
    dataset = DataSet(2,0);
    vec one(1); one[0] = 1;
    vec x(3, fill::ones);
    for (int i = 0; i < 10; ++i)
    {
        dataset.N++;
        dataset.X = join_vert(dataset.X, x.t());
        dataset.y = join_vert(dataset.y, (i%2==0)?one:-one);
    }
    
    TestingProcess tp;
    KFoldCrossValidation::apply(dataset, 2, tp);
}




int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
