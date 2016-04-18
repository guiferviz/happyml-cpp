
#ifndef _HAPPY_ML_TRANSFORMERS_STANDARIZER_H_
#define _HAPPY_ML_TRANSFORMERS_STANDARIZER_H_


#include "happyml/types.h"
#include "happyml/transformers/transformer.h"


namespace happyml
{

    /**
     * Applies Z-Score transformation:
     * x' = x - mean(x) / stddev(x)
     */
    class Standarizer : public transforms::SimpleTransformer
    {
        protected:

            rowvec meanVec, stdVec;


            void init(const mat&);


        public:

            /**
             * Creates a standarizer that will use mean and stddev data obtained
             * from the dataset.
             * 
             * @param dataset Dataset from which it will be extracted the mean
             *                and stddev that will be used when apply Z-Score.
             * //@param normY If true, it standarizes also the outputs.
             */
            Standarizer(const DataSet& dataset)
            {
                init(dataset.X.cols(1, dataset.X.n_cols - 1));
            }

            /**
             * Creates a standarizer that will use mean and stddev data obtained
             * from the given matrix.
             * 
             * @param x Matrix from which it will be extracted the mean and
             *          stddev vectors that will be used when apply Z-Score.
             */
            Standarizer(const mat& x)
            {
                init(x);
            }

            /**
             * Creates a standarizer that will use mean and stddev vectors.
             * 
             * @param mean Vector with the mean of each column.
             * @param stddev Vector with the stddev of each column.
             */
            Standarizer(vec mean, vec stddev)
            {
                meanVec =   mean;
                stdVec  = stddev;
            }
            
            ~Standarizer() {}


            using SimpleTransformer::apply;

            void apply(mat& x) const;
    };

    class StandarizerXY : public Transformer
    {
        friend class DestandarizerXY;
        
        protected:

            Standarizer nx, ny;


        public:

            StandarizerXY(const DataSet& d) : nx(d), ny(d.y) {}


            Standarizer getStandarizerX() const { return nx; }

            Standarizer getStandarizerY() const { return ny; }

            void apply(DataSet& d) const
            {
                nx.apply(d);
                ny.apply(d.y);
            }

            Input apply(const Input& input) const
            {
                return nx.apply(input);
            }

            vec applyOutput(const vec& output) const
            {
                return ny.apply(output);
            }
    };

    class Destandarizer : public Standarizer
    {
        public:

            /**
             * Creates a denormalizer that will use min and max data obtained
             * from the dataset.
             * 
             * @param dataset Dataset from which it will be extracted the min
             *                and max that will be use when apply denormalization.
             */
            Destandarizer(const DataSet& dataset) : Standarizer(dataset) {};

            /**
             * Creates a denormalizer that will use min and max data obtained
             * from the matrix x.
             * 
             * @param x Matrix from which it will be extracted the min
             *          and max that will be use when apply denormalization.
             */
            Destandarizer(const mat& x) : Standarizer(x) {}

            /**
             * Creates a denormalizer that will use min and max data obtained
             * from the dataset.
             * 
             * @param minvec Vector with the min numbers.
             * @param maxvec Vector with the max numbers.
             */
            Destandarizer(const vec& minvec, const vec& maxvec)
                    : Standarizer(minvec, maxvec) {}

            /**
             * Creates a denormalizer using the given normalizer
             * 
             * @param n Normalizer to reverse.
             */
            Destandarizer(const Standarizer& n) : Standarizer(n) {}

            ~Destandarizer() {}


            using Standarizer::apply;

            virtual void apply(mat& x) const;
    };

    class DestandarizerXY : public Transformer
    {
        protected:

            Destandarizer dx, dy;


        public:

            DestandarizerXY(const StandarizerXY& n) : dx(n.nx), dy(n.ny) {}

            DestandarizerXY(const DataSet& d) : dx(d), dy(d.y) {}


            Destandarizer getDestandarizerX() const { return dx; }

            Destandarizer getDestandarizerY() const { return dy; }

            void apply(DataSet& d) const
            {
                dx.apply(d);
                dy.apply(d.y);
            }

            Input apply(const Input& input) const
            {
                return dx.apply(input);
            }

            vec applyOutput(const vec& output) const
            {
                return dy.apply(output, false);
            }
    };

}


#endif  // _HAPPY_ML_TRANSFORMERS_STANDARIZER_H_
