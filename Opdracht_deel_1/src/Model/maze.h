#ifndef MAZE_H
#define MAZE_H

#include "room.h"
#include "init.h"

#define ROOM_SIZE 160


namespace model {
	class maze {
			//SDL_Point start, finish;
		public:
			room rooms[(SCREEN_WIDTH/ROOM_SIZE)+1][(SCREEN_HEIGHT/ROOM_SIZE)+1];
			void initRooms(void);
			void draw(SDL_Renderer *renderer);
			void generate(SDL_Point *counter, bool *end);
			//void setStartEnd(SDL_Point setStart, SDL_Point setEnd);
			//SDL_Point getStart(void);
			//SDL_Point getEnd(void);
			model::room *getRoomByCoords(SDL_Point coords);
			void stupidlyCorrectBorders(SDL_Renderer *renderer);
	};
}

#endif
