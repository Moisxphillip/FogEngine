#ifndef FOG_INCLUDEALL
#define FOG_INCLUDEALL

//Joined defines for avoiding conflict on compilation order
//STD
#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <memory>
#include <vector>
#include <stdint.h>
#include <climits>
#include <algorithm>

//SDL
#define SDL_BASE
#define SDL_IMAGE
#define SDL_MIXER
#define SDL_TTF
#include "../lib/IncludeSDL.hpp"

#include "../lib/xrand.hpp"

#include "../lib/Vec2.hpp"
#include "../lib/Rect.hpp"
#include "../lib/Settings.hpp"
#include "../lib/Tools.hpp"

#include "../lib/GameObject.hpp"
#include "../lib/Component.hpp"
#include "../lib/Music.hpp"
#include "../lib/State.hpp"
#include "../lib/Game.hpp"
#include "../lib/Face.hpp"
#include "../lib/Path.hpp"
#include "../lib/Sound.hpp"
#include "../lib/Sprite.hpp"

#endif//FOG_INCLUDEALL