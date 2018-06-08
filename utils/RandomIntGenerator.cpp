#include "RandomIntGenerator.hpp"

#include <chrono>

RandomIntGenerator::RandomIntGenerator( void )
    : generator_( std::chrono::system_clock::now().time_since_epoch().count() )
{
}

int RandomIntGenerator::operator()( int const min, int const max )
{
    std::uniform_int_distribution< int > distribution( min, max );

    return distribution( generator_ );
}
