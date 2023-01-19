#ifndef FOG_INCLUDEALL
#define FOG_INCLUDEALL

//Joined defines for avoiding conflict on compilation order
//STD
#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <stack>
#include <memory>
#include <vector>
#include <stdint.h>
#include <climits>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <queue>
#include <cstddef>

//SDL
#define SDL_BASE
#define SDL_IMAGE
#define SDL_MIXER
#define SDL_TTF
#include "../lib/IncludeSDL.hpp"
#include "../glew/include/GL/glew.h"

#include "../lib/xrand.hpp"

#include "../lib/Timer.hpp"
#include "../lib/Vec2.hpp"
#include "../lib/Rect.hpp"
#include "../lib/Color.hpp"
#include "../lib/Vertex.hpp"
#include "../lib/GLTexture.hpp"
#include "../lib/IO.hpp"
#include "../lib/GLSL.hpp"
#include "../lib/PicoPNG.hpp"
#include "../lib/GameStats.hpp"
#include "../lib/Settings.hpp"
#include "../lib/Tools.hpp"
#include "../lib/GameObject.hpp"
#include "../lib/Component.hpp"
#include "../lib/Music.hpp"
#include "../lib/Sound.hpp"
#include "../lib/Camera.hpp"
#include "../lib/State.hpp"
#include "../lib/StageState.hpp"
#include "../lib/EndState.hpp"
#include "../lib/TitleState.hpp"
#include "../lib/Game.hpp"
#include "../lib/Path.hpp"
#include "../lib/Sprite.hpp"
#include "../lib/SpriteGL.hpp"
#include "../lib/Resources.hpp"
#include "../lib/TileSet.hpp"
#include "../lib/TileMap.hpp"
#include "../lib/InputManager.hpp"
#include "../lib/CameraFollower.hpp"
#include "../lib/Bullet.hpp"
#include "../lib/Generic.hpp"
#include "../lib/Alien.hpp"
#include "../lib/Minion.hpp"
#include "../lib/PenguinCannon.hpp"
#include "../lib/PenguinBody.hpp"
#include "../lib/Collider.hpp"
#include "../lib/Collision.hpp"
#include "../lib/Text.hpp"
#include "../lib/ScreenFilter.hpp"
#include "../lib/ScreenFade.hpp"

#endif//FOG_INCLUDEALL