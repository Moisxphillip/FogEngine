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

#define ROTFRAC (M_PI/4)
#define FOG_BULLETSPD 300.f
#define FOG_ALIENSPD 170.f
#define FOG_BULLETDIST 900.f
#define FOG_BULLETDMG 15
#define FOG_NUMMINIONS 5
#define FOG_PENGACCEL 100
#define FOG_PENGSPDMAX 250.f
#define FOG_DEATHFRAMETIME 0.15


//TODO implement a class that controls the screen info, reading configs
//from a file or creating a file with the default settings.


enum Uses //Bitwise-based flags
{
    None = 0,
    All = 0xFFFF,
    Collision = 1 << 0,
    Render = 1 << 1,
    Start =  1 << 2,
    Update = 1 << 3
};

inline Uses operator|(Uses a, Uses b)
{
    return static_cast<Uses>(static_cast<int>(a) | static_cast<int>(b));
}


typedef enum
{
    N = SDL_FLIP_NONE,
    H = SDL_FLIP_HORIZONTAL,
    V = SDL_FLIP_VERTICAL,
    HV = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL
} Flip;

inline Flip operator|(Flip a, Flip b)
{
    return static_cast<Flip>(static_cast<int>(a) | static_cast<int>(b));
}

#endif//FOG_SETTINGS