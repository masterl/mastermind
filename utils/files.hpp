#ifndef UTILS_FILE_H
#define UTILS_FILE_H

#include <fstream>
#include <string>

namespace utils
{
    namespace files
    {
        typedef std::ifstream::streampos fsize_t;

        fsize_t filesize( std::string const &filename );
    } // namespace files
} // namespace utils

#endif
