#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Model/maze.h"
#include "Model/init.h"

int main(void) {
	model::init init;
	SDL_Window *window;
	SDL_Renderer *renderer;
	init.sdl(&window, &renderer);
	model::maze maze;	
	maze.setAllRoomSizes();
	maze.generate();
	while (1) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		maze.draw(renderer);	
		SDL_RenderPresent(renderer);
	}
	return 0;	
}
