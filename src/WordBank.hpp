#ifndef WORD_BANK_H
#define WORD_BANK_H

#include "../utils/RandomIntGenerator.hpp"

#include <string>
#include <vector>

class WordBank
{
public:
    typedef unsigned long long bank_size_t;

    WordBank( bank_size_t const bank_size = 0 );

    bool load_from_file( std::string const &filename,
                         unsigned const word_length );
    void add_word( std::string word );

    std::string random();

private:
    std::vector< std::string > words_;
    RandomIntGenerator random_;
    unsigned word_length_;

    std::string normalize_word( std::string word );
};

#endif
