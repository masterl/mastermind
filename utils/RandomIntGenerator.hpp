#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>

class RandomIntGenerator
{
public:
    RandomIntGenerator( void );
    int operator()( int const min = 0, int const max = 10 );

private:
    std::ranlux24 generator_;
};

#endif
