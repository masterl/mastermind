#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <string>

class MasterMind
{
public:
    static std::string const RIGHT_GUESS;
    static std::string const WRONG_GUESS;

    std::string checkGuess( std::string answer, std::string guess );
};

#endif
