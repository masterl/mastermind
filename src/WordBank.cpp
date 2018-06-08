#include "WordBank.hpp"

#include "../utils/files.hpp"

#include <cctype>

WordBank::WordBank( bank_size_t bank_size )
    : words_{bank_size}
{
}

bool WordBank::load_from_file( std::string const &filename,
                               unsigned const word_length )
{
    namespace ufiles = utils::files;

    std::streampos const file_size = ufiles::filesize( filename );
    unsigned long long const words_count = file_size / word_length;

    this->word_length_ = word_length;

    words_.clear();
    words_.reserve( words_count );

    std::ifstream file{filename};

    if( !file.is_open() )
    {
        return false;
    }

    for( unsigned long long i = 0; i < words_count; ++i )
    {
        std::string word;

        file >> word;

        this->add_word( word );
    }

    return true;
}

void WordBank::add_word( std::string word )
{
    if( word.length() != word_length_ )
    {
        return;
    }

    words_.emplace_back( normalize_word( word ) );
}

std::string WordBank::random()
{
    if( words_.size() == 0 )
    {
        return "";
    }

    int const index = random_( 0, words_.size() - 1 );

    return words_[index];
}

std::string WordBank::normalize_word( std::string word )
{
    for( auto &letter : word )
    {
        letter = tolower( letter );
    }

    return word;
}
