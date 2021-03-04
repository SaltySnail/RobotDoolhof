#ifndef INIT
#define INIT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
//#define TXTR_ROBOT (char *)"textures/robot.png"

namespace model {
	class init
	{
		public:
			void sdl(SDL_Window **window, SDL_Renderer **renderer);
	};
}

#endif
