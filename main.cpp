#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

typedef ifstream::streampos fsize_t;

static string const COMPUTER_LABEL{"Computer: "};
static string const PLAYER_LABEL{"Player: "};

class WordBank
{
public:
    typedef unsigned long long bank_size_t;

    WordBank( string const filename = "4_letter_words.txt",
              unsigned const word_length = 4 );

    string randomWord();

private:
    string filename;
    unsigned const word_length_;
    unsigned long long words_count_;

    void refreshWordsCount();
    string loadWordFromFile( unsigned const word_index ) const;
};

class MasterMind
{
public:
    static string const RIGHT_GUESS;
    static string const WRONG_GUESS;

    string checkGuess( string answer, string guess );
};

fsize_t filesize( string const &filename );
long long randomInteger( long long const min, long long const max );
string getUserInput();
string getUserGuess();
void display( int count, string guessResult );
string toLowerCase( string str );

int main()
{
    srand( static_cast< unsigned >( time( nullptr ) ) );

    WordBank wordBank;
    MasterMind masterMind;

    // Game begins
    int guessCount = 0;
    string userInput;
    string answer;

    answer = wordBank.randomWord();
    cout << COMPUTER_LABEL
         << "I have a 4 letter word in mind. Can you guess it?" << endl;

    while( true )
    {
        // cout << "Answer: " << answer << endl;
        userInput = toLowerCase( getUserGuess() );
        guessCount++;

        string const guessResult = masterMind.checkGuess( answer, userInput );

        // cout << "Result: [" << guessResult << "]" << endl;
        display( guessCount, guessResult );

        if( guessResult == MasterMind::RIGHT_GUESS )
            break;
    }

    return 0;
}

fsize_t filesize( string const &filename )
{
    std::ifstream file( filename.c_str(),
                        std::ifstream::ate | std::ifstream::binary );
    return file.tellg();
}

long long randomInteger( long long const min, long long const max )
{
    long long const range = max - min + 1;

    return min + rand() % range;
}

string getUserInput()
{
    string userInputStr;
    getline( cin, userInputStr );
    return userInputStr;
}

string getUserGuess()
{
    std::string guess;
    int const valid_guess_length = 4;

    do
    {
        cout << PLAYER_LABEL << "(length: " << valid_guess_length << "): ";
        guess = getUserInput();
    } while( guess.length() != valid_guess_length );

    return guess;
}

void display( int count, string guessResult )
{
    if( guessResult == MasterMind::RIGHT_GUESS )
        cout << COMPUTER_LABEL << "You got it! " << count << " tries." << endl;
    else if( guessResult == MasterMind::WRONG_GUESS )
        cout << COMPUTER_LABEL << "You got nothing. Sorry." << endl;
    else
        cout << guessResult << endl;
}

string toLowerCase( string str )
{
    for( unsigned i = 0; i < str.length(); i++ )
    {
        str[i] = tolower( str[i] );
    }
    return str;
}

string const MasterMind::RIGHT_GUESS{"****"};
string const MasterMind::WRONG_GUESS{"    "};

string MasterMind::checkGuess( string answer, string guess )
{
    char const EXACT_MATCH = '*';
    char const DIFF_POS_MATCH = '-';
    string result{"    "};
    int i = 0;
    char const MATCHED = ' ';

    for( unsigned k = 0; k < answer.length(); ++k )
    {
        if( answer[k] == guess[k] )
        {
            result[i] = EXACT_MATCH;
            ++i;

            answer[k] = MATCHED;
            guess[k] = MATCHED;
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

            if( answer[k] == guess[m] )
            {
                result[i] = DIFF_POS_MATCH;
                ++i;

                answer[k] = MATCHED;
                guess[m] = MATCHED;
                break;
            }
        }
    }

    return result;
}

WordBank::WordBank( string const filename, unsigned const word_length )
    : filename{filename}
    , word_length_{word_length}
    , words_count_{0}
{
    this->refreshWordsCount();
}

void WordBank::refreshWordsCount()
{
    std::streampos const file_size = filesize( filename );

    // +1 for \n
    this->words_count_ = file_size / ( this->word_length_ + 1 );
}

string WordBank::loadWordFromFile( unsigned const word_index ) const
{
    int const line_size = this->word_length_ + 1;
    std::ifstream file{filename};

    file.seekg( word_index * line_size );

    std::string word;

    file >> word;

    return word;
}

string WordBank::randomWord()
{
    int const word_index = randomInteger( 0, words_count_ - 1 );

    return toLowerCase( this->loadWordFromFile( word_index ) );
}
