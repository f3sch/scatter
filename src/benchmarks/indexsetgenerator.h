//
// Created by anton on 1/23/22.
//

#ifndef INDEXSETGENERATOR_H
#define INDEXSETGENERATOR_H

#include <random>
#include <iostream>
#include <algorithm>
#include <cmath>


namespace detail {


class DataGenerator
{
public:
    explicit DataGenerator(unsigned seed)
        : seed_{seed}, rd_{}, engine_{seed_}
    {}

    /*!
     * \brief Generate uniform random numbers
     * \param begin Iterator to start of the container to fill
     * \param end Iterator to end of the container to fill
     * \param rangeMin Minimum of random number range
     * \param rangeMax Maximum of random number range
     */
    template<typename Iterator>
    void generateUniformRandom(Iterator begin, Iterator end, typename Iterator::value_type rangeMin, typename Iterator::value_type rangeMax);

    /// Overload to specifie the seed
    template<typename Iterator>
    void generateUniformRandom(Iterator begin, Iterator end, typename Iterator::value_type rangeMin, typename Iterator::value_type rangeMax, unsigned seed);

    template<typename Iterator>
    /*!
     * \brief Generate uniform int distribution
     * \param begin Iterator to start of the container to fill
     * \param end Iterator to end of the container to fill
     * \param rangeMin Minimum of random number range
     * \param rangeMax Maximum of random number range
     */
    void generateUniformRandomInt(Iterator begin, Iterator end, typename Iterator::value_type rangeMin, typename Iterator::value_type rangeMax);


    /*!
     * \brief Generate random indices in given intervall
     * \param begin Iterator to the start of the container to fill
     * \param end Iterator to the end of the container to fill
     * \param rangeMin Lover bound of intervall
     * \param rangeMax Uppter bound of intervall
     */
    template<typename Iterator>
    void genRandomIndices(Iterator begin, Iterator end, typename Iterator::value_type rangeMin, typename Iterator::value_type rangeMax);

    /// Overload to specify the seed
    template<typename Iterator>
    void genRandomIndices(Iterator begin, Iterator end, typename Iterator::value_type rangeMin, typename Iterator::value_type rangeMax, unsigned seed);

    /*!
     * \brief genLinIndicesRandFactor  Generate linear indices with random part depending on delta
     * \param begin Iterator to the start of the container to fill
     * \param end Iterator to the end of the container to fill
     * \param sizeValues Size of the value container
     * \param delta Random factor
     */
    template<typename InputIterator1, typename InputIterator2>
    void genLinIndicesRandFactor(InputIterator1 begin, InputIterator2 end, size_t sizeValues, int delta);

    // Overload to specify the seed
    template<typename InputIterator1, typename InputIterator2>
    void genLinIndicesRandFactor(InputIterator1 begin, InputIterator2 end, size_t sizeValues, int delta, unsigned seed);

private:
    unsigned seed_;
    std::random_device rd_;
    std::minstd_rand engine_;
};


template<typename Iterator>
void DataGenerator::generateUniformRandom(Iterator begin, Iterator end, typename Iterator::value_type rangeMin, typename Iterator::value_type rangeMax)
{
   std::uniform_real_distribution<typename Iterator::value_type> dist(rangeMin, rangeMax);

   std::generate(begin, end, [&](){ return dist(engine_); });

}

template<typename Iterator>
void DataGenerator::generateUniformRandom(Iterator begin, Iterator end, typename Iterator::value_type rangeMin, typename Iterator::value_type rangeMax, unsigned seed)
{
    engine_.seed(seed);

    std::uniform_real_distribution<typename Iterator::value_type> dist(rangeMin, rangeMax);

    std::generate(begin, end, [&](){ return dist(engine_); });

}

template<typename Iterator>
void DataGenerator::generateUniformRandomInt(Iterator begin, Iterator end, typename Iterator::value_type rangeMin, typename Iterator::value_type rangeMax)
{
   std::uniform_int_distribution<typename Iterator::value_type> dist(rangeMin, rangeMax);

   std::generate(begin, end, [&](){ return dist(engine_); });

}

template<typename Iterator>
void DataGenerator::genRandomIndices(Iterator begin, Iterator end, typename Iterator::value_type rangeMin, typename Iterator::value_type rangeMax)
{
    std::uniform_int_distribution<std::minstd_rand::result_type> dist(rangeMin, rangeMax);

    std::generate(begin, end, [&](){ return dist(engine_); });
}

template<typename Iterator>
void DataGenerator::genRandomIndices(Iterator begin, Iterator end, typename Iterator::value_type rangeMin, typename Iterator::value_type rangeMax, unsigned seed)
{
    engine_.seed(seed);

    std::uniform_int_distribution<std::minstd_rand::result_type> dist(rangeMin, rangeMax);

    std::generate(begin, end, [&](){ return dist(engine_); });
}

template<typename InputIterator1, typename InputIterator2>
void DataGenerator::genLinIndicesRandFactor(InputIterator1 begin, InputIterator2 end, size_t sizeValues, int delta)
{
    std::size_t numIndices = end - begin;

    std::uniform_int_distribution<int> dist(-delta, delta);

    float i = 0;
    std::generate(begin, end, [&]()
        {
            auto index =  static_cast<unsigned>(std::floor(i * sizeValues / numIndices) + dist(engine_));
            i++;

            return (index + sizeValues) % sizeValues;
        });
}

template<typename InputIterator1, typename InputIterator2>
void DataGenerator::genLinIndicesRandFactor(InputIterator1 begin, InputIterator2 end, size_t sizeValues, int delta, unsigned seed)
{
    std::size_t numIndices = end - begin;

    engine_.seed(seed);
    std::uniform_int_distribution<int> dist(-delta, delta);

    float i = 0;
    std::generate(begin, end, [&]()
        {
            auto index = static_cast<unsigned>(std::floor(i * sizeValues / numIndices) + dist(engine_));
            i++;

            return (index + sizeValues) % sizeValues;
        });
}


} // end namespace detail



#endif //INDEXSETGENERATOR_H
