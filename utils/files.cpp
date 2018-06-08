#include "files.hpp"

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
} // namespace utils
