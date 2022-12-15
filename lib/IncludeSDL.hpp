/* - Como usar esse arquivo:
 
 * Onde quiser adicionar, por exemplo, SDL_image e SDL_mixer em um arquivo, faça o seguinte e
 * ele incluirá elas automaticamente e de forma multiplataforma (se usar o makefile tbm fornecido).
 * #define INCLUDE_SDL_IMAGE
 * #define INCLUDE_SDL_MIXER
 * #include "SDL_include.h"
*/

//#define FOG_MYMACHINE

#ifdef FOG_MYMACHINE
	/************************************************
	*					SDL.h						*
	*************************************************/
	#ifdef SDL_BASE
		#ifdef _WIN32
			#include "../sdl/include/SDL2/SDL.h"
		#elif __APPLE__
			#include "TargetConditionals.h"
			#include <SDL2/SDL.h>
		#elif __linux__
			#include <SDL2/SDL.h>
		#else
			#error "Unknown compiler"
		#endif
		#undef SDL_BASE 
	#endif // INCLUDE_SDL

	/************************************************
	*				 SDL_image.h					*
	*************************************************/
	#ifdef SDL_IMAGE 
		#ifdef _WIN32
			#include "../sdl/include/SDL2/SDL_image.h"
		#elif __APPLE__
			#include "TargetConditionals.h"
			#include <SDL2/SDL_image.h>
		#elif __linux__
			#include <SDL2/SDL_image.h>
		#else
			#error "Unknown compiler"
		#endif
		#undef SDL_IMAGE 
	#endif // SDL_IMAGE

	/************************************************
	*				 SDL_mixer.h					*
	*************************************************/
	#ifdef SDL_MIXER 
		#ifdef _WIN32
			#include "../sdl/include/SDL2/SDL_mixer.h"
		#elif __APPLE__
			#include "TargetConditionals.h"
			#include <SDL2/SDL_mixer.h>
		#elif __linux__
			#include <SDL2/SDL_mixer.h>
		#else
			#error "Unknown compiler"
		#endif
		#undef SDL_MIXER 
	#endif // SDL_MIXER

	/************************************************
	*				  SDL_ttf.h						*
	*************************************************/
	#ifdef SDL_TTF 
		#ifdef _WIN32
			#include "../sdl/include/SDL2/SDL_ttf.h"
		#elif __APPLE__
			#include "TargetConditionals.h"
			#include <SDL2/SDL_ttf.h>
		#elif __linux__
			#include <SDL2/SDL_ttf.h>
		#else
			#error "Unknown compiler"
		#endif
		#undef SDL_TTF 
	#endif // SDL_TTF

	/************************************************
	*				  SDL_net.h						*
	*************************************************/
	#ifdef INCLUDE_SDL_NET 
		#ifdef _WIN32
			#include <SDL2/SDL_net.h>
		#elif __APPLE__
			#include "TargetConditionals.h"
			#include <SDL2/SDL_net.h>
		#elif __linux__
			#include <SDL2/SDL_net.h>
		#else
			#error "Unknown compiler"
		#endif
		#undef INCLUDE_SDL_NET 
	#endif // INCLUDE_SDL_NET

	#undef FOG_MYMACHINE
#else //not my machine

	/************************************************
	*					SDL.h						*
	*************************************************/
	#ifdef SDL_BASE
		#ifdef _WIN32
			#include <SDL2/SDL.h>
		#elif __APPLE__
			#include "TargetConditionals.h"
			#include <SDL2/SDL.h>
		#elif __linux__
			#include <SDL2/SDL.h>
		#else
			#error "Unknown compiler"
		#endif
		#undef SDL_BASE 
	#endif // SDL_BASE

	/************************************************
	*				 SDL_image.h					*
	*************************************************/
	#ifdef SDL_IMAGE 
		#ifdef _WIN32
			#include <SDL2/SDL_image.h>
		#elif __APPLE__
			#include "TargetConditionals.h"
			#include <SDL2/SDL_image.h>
		#elif __linux__
			#include <SDL2/SDL_image.h>
		#else
			#error "Unknown compiler"
		#endif
		#undef SDL_IMAGE 
	#endif // SDL_IMAGE

	/************************************************
	*				 SDL_mixer.h					*
	*************************************************/
	#ifdef SDL_MIXER 
		#ifdef _WIN32
			#include <SDL2/SDL_mixer.h>
		#elif __APPLE__
			#include "TargetConditionals.h"
			#include <SDL2/SDL_mixer.h>
		#elif __linux__
			#include <SDL2/SDL_mixer.h>
		#else
			#error "Unknown compiler"
		#endif
		#undef SDL_MIXER 
	#endif // SDL_MIXER

	/************************************************
	*				  SDL_ttf.h						*
	*************************************************/
	#ifdef SDL_TTF 
		#ifdef _WIN32
			#include <SDL2/SDL_ttf.h>
		#elif __APPLE__
			#include "TargetConditionals.h"
			#include <SDL2/SDL_ttf.h>
		#elif __linux__
			#include <SDL2/SDL_ttf.h>
		#else
			#error "Unknown compiler"
		#endif
		#undef SDL_TTF 
	#endif // SDL_TTF

	/************************************************
	*				  SDL_net.h						*
	*************************************************/
	#ifdef INCLUDE_SDL_NET 
		#ifdef _WIN32
			#include <SDL2/SDL_net.h>
		#elif __APPLE__
			#include "TargetConditionals.h"
			#include <SDL2/SDL_net.h>
		#elif __linux__
			#include <SDL2/SDL_net.h>
		#else
			#error "Unknown compiler"
		#endif
		#undef INCLUDE_SDL_NET 
	#endif // INCLUDE_SDL_NET
	
#endif//MYMACHINE