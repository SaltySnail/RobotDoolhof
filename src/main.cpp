#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>
#include "Model/maze.h"
#include "Model/init.h"
#include "Model/robot.h"
#include "Model/input.h"

int main(void) {
	srand(time(NULL));
	SDL_bool quit;
	model::init init;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Point counter = {0, 0};
	SDL_Point startMaze = {0, 0}, endMaze = {SCREEN_WIDTH/ROOM_SIZE+1, SCREEN_HEIGHT/ROOM_SIZE+1};
	bool endGenerating = 0;
	init.sdl(&window, &renderer);
	model::maze maze;
	model::robot robot;
	model::input input;	
	maze.initRooms();
	maze.setStartEnd(startMaze, endMaze);
	robot.init(renderer, startMaze, &maze);
	//void *ptr;
	//SDL_Thread *threadID = SDL_CreateThread(model::maze::draw, "drawingThread", (void *)ptr);
	
	while (!quit) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		quit = input.update();
		if (!endGenerating) { 	
			maze.generate(&counter, &endGenerating);
		}
		else {
			robot.update();
		}
		maze.stupidlyCorrectBorders(renderer);
		robot.draw(renderer);
		maze.draw(renderer);	
		SDL_RenderPresent(renderer);
		if (endGenerating) {
			SDL_Delay(7);
		}
		else {
			//SDL_Delay(1); //1440p & 120 pixels/room
			SDL_Delay(3); //1440p & 20 pixels/room
			//SDL_Delay(5); //4k & 20 pixels/room
		}
	}
	SDL_Quit();
	//SDL_WaitThread( threadID, NULL );
	return 0;	
}
