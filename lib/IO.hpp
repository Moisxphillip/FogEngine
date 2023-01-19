#ifndef FOG_IO
#define FOG_IO

#include "../lib/IncludeAll.hpp"

class IO
{
    public:
        static bool ReadToBuffer(std::string, std::vector<unsigned char>&);
        static GLTexture LoadPNG(std::string);
};

#endif// FOG_IO