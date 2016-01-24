
#include "happyml/k_fold_cross_validation.h"

#include <iomanip>  // std::setprecision

#include "happyml/utils.h"


namespace happyml
{

    void KFoldCrossValidation::apply(const DataSet& dataset, int n,
            TrainingProcess& process)
    {
        uvec class1 = find(dataset.y ==  1);
        int nClass1 = class1.size();
        uvec class2 = find(dataset.y == -1);
        int nClass2 = class2.size();
        
        class1 = shuffle(class1);
        class2 = shuffle(class2);
        
        int size1 = nClass1 / n;
        int size2 = nClass2 / n;
        for (int i = 0; i < n; ++i)
        {
            int start1 = size1 * i;
            int start2 = size2 * i;
            int end1 = (i + 1) * size1 - 1;
            int end2 = (i + 1) * size2 - 1;
            uvec selectedClass1 = class1.rows(start1, end1);
            uvec selectedClass2 = class2.rows(start2, end2);
            uvec allSelected = sort(join_vert(selectedClass1, selectedClass2),
                    "descend");
            
            // Create training set.
            DataSet trainingset(dataset);
            for (int j = 0; j < allSelected.size(); ++j)
            {
                trainingset.X.shed_row(allSelected[j]);
                trainingset.y.shed_row(allSelected[j]);
            }
            
            // Create CV set.
            DataSet cvset(dataset.d, dataset.N / n);
            cvset.X = join_vert(
                dataset.X.rows(selectedClass1),
                dataset.X.rows(selectedClass2)
            );
            cvset.y = join_vert(
                dataset.y.rows(selectedClass1),
                dataset.y.rows(selectedClass2)
            );
            
            // Run process.
            process.run(trainingset, cvset);
        }
    }

}
