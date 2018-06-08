#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef std::ifstream::streampos fsize_t;

fsize_t filesize( string const &filename );
int randomInteger( int const min, int const max );

class WordBank
{
public:
    typedef unsigned long long bank_size_t;

    WordBank( bank_size_t const bank_size = 0 );

    bool loadFromFile( string const &filename, unsigned const word_length );
    void addWord( string word );

    string random();

    string normalizeWord( string word );

private:
    std::vector< string > words_;

    unsigned word_length_;
};

class MasterMind
{
public:
    static string const RIGHT_GUESS;
    static string const WRONG_GUESS;

    string checkGuess( string answer, string guess );
};

string getUserInput();
void display( int count, string guessResult );
string toLowerCase( string str );

int main()
{
    int guessCount = 0;
    string userInput;
    string answer;

    MasterMind masterMind;
    WordBank wordBank;
    wordBank.loadFromFile( "4_letter_words.txt", 4 );
    answer = wordBank.random();
    cout << "Computer: I have a 4 letter word in mind. Can you guess it?"
         << endl;

    while( true )
    {
        // cout << "Answer: " << answer << endl;
        cout << "Player: ";
        userInput = getUserInput();
        userInput = toLowerCase( userInput );
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

int randomInteger( int const min, int const max )
{
    int const range = max - min + 1;

    return min + rand() % range;
}

string getUserInput()
{
    string userInputStr;
    getline( cin, userInputStr );
    return userInputStr;
}

void display( int count, string guessResult )
{
    if( guessResult == MasterMind::RIGHT_GUESS )
        cout << "Computer: You got it! " << count << " tries." << endl;
    else if( guessResult == MasterMind::WRONG_GUESS )
        cout << "Computer: You got nothing. Sorry." << endl;
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
    string result{"    "};
    int i = 0;
    char const MATCHED = ' ';

    for( unsigned k = 0; k < answer.length(); ++k )
    {
        if( answer[k] == guess[k] )
        {
            result[i] = '*';
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
                result[i] = '-';
                ++i;
            }
        }
    }

    return result;
}

WordBank::WordBank( bank_size_t bank_size )
    : words_{bank_size}
{
}

bool WordBank::loadFromFile( string const &filename,
                             unsigned const word_length )
{
    std::streampos const file_size = filesize( filename );
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
        string word;

        file >> word;

        this->addWord( word );
    }

    return true;
}

void WordBank::addWord( string word )
{
    if( word.length() != word_length_ )
    {
        return;
    }

    words_.emplace_back( normalizeWord( word ) );
}

string WordBank::random()
{
    if( words_.size() == 0 )
    {
        return "";
    }

    int const index = randomInteger( 0, words_.size() - 1 );

    return words_[index];
}

string WordBank::normalizeWord( string word )
{
    for( char &letter : word )
    {
        letter = tolower( letter );
    }

    return word;
}
