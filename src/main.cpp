#include <iostream>
#include "../lib/Game.hpp"
#include "../sdl/include/SDL2/SDL.h"
#include "../sdl/include/SDL2/SDL_mixer.h"
#include "../sdl/include/SDL2/SDL_image.h"
#include "../sdl/include/SDL2/SDL_ttf.h"

int main (int argc, char** argv) {
 
    /* Inicializa todas as bibliotecas */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG);
    TTF_Init();
    std::cout << "Successful init.\n";

    /* Fecha todas */
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    std::cout << "Successful quit.\n";
 
    return 0;
}