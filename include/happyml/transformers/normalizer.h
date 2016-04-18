
#ifndef _HAPPY_ML_TRANSFORMERS_NORMALIZER_H_
#define _HAPPY_ML_TRANSFORMERS_NORMALIZER_H_


#include "happyml/types.h"
#include "happyml/transformers/transformer.h"


namespace happyml
{

    /**
     * Normalizes a dataset using feature scaling:
     * x' = x - min(x) / (max(x) - min(x))
     */
    class Normalizer : public transforms::SimpleTransformer
    {
        protected:

            rowvec minx, maxx, rangex;

            rowvec miny, maxy;


            void init(const mat&);


        public:

            /**
             * Creates a normalizer that will use min and max data obtained
             * from the dataset.
             * 
             * @param dataset Dataset from which it will be extracted the min
             *                and max that will be use when apply normalization.
             */
            Normalizer(const DataSet& dataset)
            {
                init(dataset.X.cols(1, dataset.X.n_cols - 1));
            }

            /**
             * Creates a normalizer that will use min and max data obtained
             * from the matrix x.
             * 
             * @param x Matrix from which it will be extracted the min
             *          and max that will be use when apply normalization.
             */
            Normalizer(const mat& x)
            {
                init(x);
            }

            /**
             * Creates a normalizer that will use the given min and max vectors.
             * 
             * @param minvec Vector with the min numbers.
             * @param maxvec Vector with the max numbers.
             */
            Normalizer(const vec& minvec, const vec& maxvec)
            {
                init(join_cols(minvec.t(), maxvec.t()));
            }

            ~Normalizer() {}


            using SimpleTransformer::apply;

            virtual void apply(mat& x) const;
    };

    class NormalizerXY : public Transformer
    {
        friend class DenormalizerXY;
        
        protected:

            Normalizer nx, ny;


        public:

            NormalizerXY(const DataSet& d) : nx(d), ny(d.y) {}


            Normalizer getNormalizerX() const { return nx; }

            Normalizer getNormalizerY() const { return ny; }

            void apply(DataSet& d) const
            {
                nx.apply(d);
                ny.apply(d.y);
            }

            Input apply(const Input& input) const
            {
                nx.apply(input);
            }
    };

    class Denormalizer : public Normalizer
    {
        public:

            /**
             * Creates a denormalizer that will use min and max data obtained
             * from the dataset.
             * 
             * @param dataset Dataset from which it will be extracted the min
             *                and max that will be use when apply denormalization.
             */
            Denormalizer(const DataSet& dataset) : Normalizer(dataset) {};

            /**
             * Creates a denormalizer that will use min and max data obtained
             * from the matrix x.
             * 
             * @param x Matrix from which it will be extracted the min
             *          and max that will be use when apply denormalization.
             */
            Denormalizer(const mat& x) : Normalizer(x) {}

            /**
             * Creates a denormalizer that will use min and max data obtained
             * from the dataset.
             * 
             * @param minvec Vector with the min numbers.
             * @param maxvec Vector with the max numbers.
             */
            Denormalizer(const vec& minvec, const vec& maxvec)
                    : Normalizer(minvec, maxvec) {}

            /**
             * Creates a denormalizer using the given normalizer
             * 
             * @param n Normalizer to reverse.
             */
            Denormalizer(const Normalizer& n) : Normalizer(n) {}

            ~Denormalizer() {}


            using Normalizer::apply;

            virtual void apply(mat& x) const;
    };

    class DenormalizerXY : public Transformer
    {
        protected:

            Denormalizer dx, dy;


        public:

            DenormalizerXY(const NormalizerXY& n) : dx(n.nx), dy(n.ny) {}

            DenormalizerXY(const DataSet& d) : dx(d), dy(d.y) {}


            Denormalizer getDenormalizerX() const { return dx; }

            Denormalizer getDenormalizerY() const { return dy; }

            void apply(DataSet& d) const
            {
                dx.apply(d);
                dy.apply(d.y);
            }

            Input apply(const Input& input) const
            {
                dx.apply(input);
            }

            vec applyOutput(const vec& output) const
            {
                dy.apply(output);
            }
    };

}


#endif  // _HAPPY_ML_TRANSFORMERS_NORMALIZER_H_
