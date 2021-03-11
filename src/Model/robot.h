#ifndef ROBOT
#define ROBOT

#include "maze.h"
#include "path.h"

#define ROBOT_ZOOM -10

namespace model {
	enum directions {
			turning_right,
			turning_left
	};
	enum sideDegrees {
		degreesTop = 0,	
		degreesLeft = 90,
		degreesBottom = 180,
		degreesRight = 270	
	};
	class robot {
			int width, height;
			SDL_Point location;
			SDL_Texture *txtr;
			double angle, desired_angle;
			bool turning, driving, path_init;
			room *current_room;
			path thePath;
			directions direction;
			SDL_Point counter;
			maze *myMaze;
		public:
			void draw(SDL_Renderer *renderer);
			void init(SDL_Renderer *renderer, SDL_Point start, maze *yourMaze);
			void turn(double degrees);
			void drive(double speed);
			bool isTurning(void);
			void setCurrentRoom(maze *theMaze);
			void getRoom(void);
			void setDesiredDegrees(void);
			void update(void);
	};	
}

#endif
