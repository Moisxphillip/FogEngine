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
#include <unordered_map>
#include <fstream>
#include <iomanip>

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
#include "../lib/Sound.hpp"
#include "../lib/State.hpp"
#include "../lib/Game.hpp"
#include "../lib/Face.hpp"
#include "../lib/Path.hpp"
#include "../lib/Sprite.hpp"
#include "../lib/Resources.hpp"
#include "../lib/TileSet.hpp"
#include "../lib/TileMap.hpp"
#include "../lib/InputManager.hpp"
#include "../lib/Camera.hpp"
#include "../lib/CameraFollower.hpp"

#endif//FOG_INCLUDEALL