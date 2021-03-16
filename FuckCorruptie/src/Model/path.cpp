#include "path.h"

void model::path::init(maze *yourMaze) {
	SDL_Point counter = {0, 0};
	room *tmp;
	theMaze = yourMaze;
        int weight_counter = 0;
	printf("Initializing path\n");	
	for (int j = 0; j < SCREEN_HEIGHT/ROOM_SIZE; j++) {
		for (int i = 0; i < SCREEN_WIDTH/ROOM_SIZE; i++) {
			counter.x = i;
			counter.y = j;
			printf("Initializing node %d, %d \n", i, j);
			tmp = theMaze->getRoomByCoords(counter);
			//printf("HUH\n");
			nodes[i][j].setCurrentRoom(tmp);
			printf("Current room was set %p\n", tmp);
			nodes[i][j].setMissingWalls(); //dodelijk
			//(void)theMaze->rooms[i][j];
			printf("Missing walls recorded\n");
			nodes[i][j].setWeightWalls();
			printf("Weight of the walls has been set\n");
			nodes[i][j].setWeightOpening(&weight_counter);
			printf("Weight of the opening has been set\n");
		}
	}
}

void model::path::getNextRoom(SDL_Point *counter) {
	printf("none of my ifs work\n");
	if (nodes[counter->x][counter->y].getWeight(top) < nodes[counter->x][counter->y].getWeight(bottom) &&
	    nodes[counter->x][counter->y].getWeight(top) < nodes[counter->x][counter->y].getWeight(right) &&
	    nodes[counter->x][counter->y].getWeight(top) < nodes[counter->x][counter->y].getWeight(left) && 
	    counter->y > 0) {
		counter->y--;
		printf("top is the best choice: %d, %d\n", counter->x, counter->y);	
	}
	if (nodes[counter->x][counter->y].getWeight(right) < nodes[counter->x][counter->y].getWeight(bottom) &&
	    nodes[counter->x][counter->y].getWeight(right) < nodes[counter->x][counter->y].getWeight(top) &&
	    nodes[counter->x][counter->y].getWeight(right) < nodes[counter->x][counter->y].getWeight(left) &&
	    counter->x < SCREEN_WIDTH/ROOM_SIZE) {
		counter->x++;
		printf("right is the best choice: %d, %d\n", counter->x, counter->y);	
	}
	if (nodes[counter->x][counter->y].getWeight(left) < nodes[counter->x][counter->y].getWeight(bottom) &&
	    nodes[counter->x][counter->y].getWeight(left) < nodes[counter->x][counter->y].getWeight(right) &&
	    nodes[counter->x][counter->y].getWeight(left) < nodes[counter->x][counter->y].getWeight(top) &&
	    counter->x > 0) {
		counter->x--;
		printf("left is the best choice: %d, %d\n", counter->x, counter->y);	
	}
	if (nodes[counter->x][counter->y].getWeight(bottom) < nodes[counter->x][counter->y].getWeight(top) &&
	    nodes[counter->x][counter->y].getWeight(bottom) < nodes[counter->x][counter->y].getWeight(right) &&
	    nodes[counter->x][counter->y].getWeight(bottom) < nodes[counter->x][counter->y].getWeight(left) &&
	    counter->y < SCREEN_WIDTH/ROOM_SIZE) {
		counter->y++;
		printf("bottom is the best choice: %d, %d\n", counter->x, counter->y);	
	}
}

