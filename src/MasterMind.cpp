#include "MasterMind.hpp"

std::string const MasterMind::RIGHT_GUESS{"****"};
std::string const MasterMind::WRONG_GUESS{"    "};

std::string MasterMind::checkGuess( std::string answer, std::string guess )
{
    std::string result{"    "};
    int i = 0;
    char const MATCHED = ' ';

    for( unsigned k = 0; k < answer.length(); ++k )
    {
        if( answer[k] == guess[k] )
        {
            result[i] = '*';
            ++i;

            answer[k] = MATCHED;
        }
    }

    for( unsigned k = 0; k < answer.length(); ++k )
    {
        if( answer[k] == MATCHED )
        {
            continue;
        }

        for( unsigned m = 0; m < guess.length(); ++m )
        {
            if( guess[m] == MATCHED )
            {
                continue;
            }

            if( answer[k] == guess[k] )
            {
                result[i] = '-';
                ++i;
            }
        }
    }

    return result;
}
