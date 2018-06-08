#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <random>

using namespace std;
namespace utils
{
    namespace files
    {
        typedef std::ifstream::streampos fsize_t;
        
        fsize_t filesize( std::string const &filename );
    } // namespace files
} // namespace utils

namespace utils
{
    namespace files
    {
        fsize_t filesize( std::string const &filename )
        {
            std::ifstream file( filename.c_str(),
                               std::ifstream::ate | std::ifstream::binary );
            return file.tellg();
        }
    } // namespace files
} // namespac

class RandomIntGenerator
{
public:
    RandomIntGenerator( void );
    int operator()( int const min = 0, int const max = 10 );
    
private:
    std::ranlux24 generator_;
};

RandomIntGenerator::RandomIntGenerator( void )
: generator_( std::chrono::system_clock::now().time_since_epoch().count() )
{
}

int RandomIntGenerator::operator()( int const min, int const max )
{
    std::uniform_int_distribution< int > distribution( min, max );
    
    return distribution( generator_ );
}

class WordBank
{
public:
    typedef unsigned long long bank_size_t;
    
    WordBank( bank_size_t const bank_size = 0 );
    
    bool load_from_file( std::string const &filename,
                        unsigned const word_length );
    void add_word( std::string word );
    
    std::string random();
    
    std::string normalizeWord( std::string word );
    
private:
    std::vector< std::string > words_;
    RandomIntGenerator random_;
    unsigned word_length_;
};

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
    
    words_.emplace_back( normalizeWord( word ) );
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

std::string WordBank::normalizeWord( std::string word )
{
    for( char &letter : word )
    {
        letter = tolower( letter );
    }
    
    return word;
}

class MasterMind
{
public:
    static std::string const RIGHT_GUESS;
    static std::string const WRONG_GUESS;
    
    std::string checkGuess( std::string answer, std::string guess );
};
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

string getUserInput() {
    string userInputStr;
    getline(cin, userInputStr);
    return userInputStr;
}

void display(int count, string guessResult) {
    if(guessResult == "****")
        cout << "Computer: You got it! " << count << " tries." << endl;
    else if(guessResult == "    ")
        cout << "Computer: You got nothing. Sorry." << endl;
    else
        cout << guessResult << endl;
}

string toLowerCase(string str) {
    for(int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

int main() {
    int guessCount = 0;
    string userInput;
    string answer;
    string guess;
    
    MasterMind masterMind;
    WordBank wordBank;
    wordBank.load_from_file("4_letter_words.txt", 4);
    answer = wordBank.random();
    cout << "Computer: I have a 4 letter word in mind. Can you guess it?"
    << endl;
    
    while(true) {
        cout << "Answer: " << answer << endl;
        cout << "Player: ";
        userInput = getUserInput();
        userInput = toLowerCase(userInput);
        guess = masterMind.checkGuess(answer, userInput);
        display(guessCount, guess);
        if(guess == "****")
            break;
    }
    
    
    

    
    return 0;
}
