#ifndef MAZE_H
#define MAZE_H

#include "room.h"
#include "init.h"

#define ROOM_SIZE 20

namespace model {
	class maze {
			room rooms[(SCREEN_WIDTH/ROOM_SIZE)][(SCREEN_HEIGHT/ROOM_SIZE)];
		public:
			void initRooms(void);
			void draw(SDL_Renderer *renderer);
			void generate(SDL_Point *counter, bool *end);
	};
}

#endif
