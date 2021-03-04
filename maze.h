#ifndef MAZE_H
#define MAZE_H

#include "room.h"
#include "init.h"

#define ROOM_SIZE 20

namespace model {
	class maze {
			room rooms[(SCREEN_WIDTH/ROOM_SIZE)+1][(SCREEN_HEIGHT/ROOM_SIZE)+1];
		public:
			void setAllRoomSizes(void);
			void draw(SDL_Renderer *renderer);
			void generate(void);
	};
}

#endif
