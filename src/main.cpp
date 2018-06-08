#include <iostream>

#include "WordBank.hpp"

int main()
{
    std::cin.sync_with_stdio( false );

    WordBank word_bank;

    word_bank.load_from_file( "4_letter_words.txt", 4 );

    for( int i = 0; i < 20; ++i )
    {
        std::cout << word_bank.random() << "\n";
    }

    return 0;
}
