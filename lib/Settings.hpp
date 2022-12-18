#ifndef FOG_SETTINGS
#define FOG_SETTINGS

//Definitions for quick changes across all project files

#define FOG_SCRTITLE "Moises Felipe Jaco Andrade de Lima - 190018364 | Fog"
#define FOG_SCRWIDTH 1024
#define FOG_SCRHEIGHT 600
#define FOG_SOUNDCHANNELS 32
#define FOG_TILEWIDTH 64
#define FOG_TILEHEIGHT 64
#define FOG_KEYARR 416
#define FOG_BUTTONARR 6


//TODO implement a class that controls the screen info, reading configs
//from a file or creating a file with the default settings.


enum USEDFN //Bitwise checks
{
    NONE = 0,
    UPDATE = 1 << 0,
    RENDER = 1 << 1
};

inline USEDFN operator|(USEDFN a, USEDFN b)
{
    return static_cast<USEDFN>(static_cast<int>(a) | static_cast<int>(b));
}

#endif//FOG_SETTINGS