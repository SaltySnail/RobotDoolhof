#include "maze.h"


void model::maze::initRooms(void) {
	SDL_Point tmp;
	for (int i = 0; i <= SCREEN_WIDTH/ROOM_SIZE; i++) {
		for (int j = 0; j <= SCREEN_HEIGHT/ROOM_SIZE; j++) {
			rooms[i][j].setSize(ROOM_SIZE);
			tmp.x = i*ROOM_SIZE; 
			tmp.y = j*ROOM_SIZE; 
			rooms[i][j].setCoords(tmp);
		}
	}
}

void model::maze::draw(SDL_Renderer *renderer) {	
	for (int i = 0; i <= SCREEN_WIDTH/ROOM_SIZE; i++) {
		for (int j = 0; j <= SCREEN_HEIGHT/ROOM_SIZE; j++) {
			rooms[i][j].draw(renderer);
		}
	}
}

void model::maze::generate() { 
	int chosen_neighbour;
	for (int j = 0; j <= SCREEN_HEIGHT/ROOM_SIZE; j++) {
		for (int i = 0; i <= SCREEN_WIDTH/ROOM_SIZE; i++) {
			chosen_neighbour = rand() % 4;
			rooms[i][j].setVisited();
			//rooms[i][j].setMissingWall(top);
			//rooms[i][j].setMissingWall(bottom);
				if ((rooms[i+1][j  ].isVisited() == 1 && 
				    rooms[i  ][j-1].isVisited() == 1 &&
				    rooms[i-1][j  ].isVisited() == 1 &&
				    rooms[i  ][j+1].isVisited() == 1 ) && 
				    (i > 0 && j > 0 && i+1 < SCREEN_WIDTH/ROOM_SIZE && j+1 < SCREEN_HEIGHT/ROOM_SIZE)) {
					SDL_Point prev = rooms[i][j].getPrev();
					i = prev.x;
					j = prev.y;
					printf("Backtracking... \n");	
				}
				/*if ((rooms[i  ][j-1].isVisited() == 1 && rooms[i-1][j  ].isVisited() == 1 && j > 0 && i > 0) ||
				  (rooms[i  ][j+1].isVisited() == 1 && rooms[i+1][j  ].isVisited() == 1 && j+1 < SCREEN_HEIGHT/ROOM_SIZE && i+1 < SCREEN_WIDTH/ROOM_SIZE))
				{
					SDL_Point prev = rooms[i][j].getPrev();
					i = prev.x;
					j = prev.y;
					printf("Backtracking from edgecase... \n");	
					
				}*/
				if (i+1 <= SCREEN_WIDTH/ROOM_SIZE && rooms[i+1][j].isVisited() == 0 && chosen_neighbour == right) { //right side
				      	rooms[i][j].setMissingWall(right);
					rooms[i+1][j].setMissingWall(left);
					rooms[i+1][j].setPrev(i, j);
					printf("right\n");
				}
				if (j > 0 && rooms[i][j-1].isVisited() == 0 && chosen_neighbour == top) { //top side
				      	rooms[i][j].setMissingWall(top);
					rooms[i][j-1].setMissingWall(bottom);
					rooms[i][j-1].setPrev(i, j);
					printf("top\n");
				}
				if (i > 0 && rooms[i-1][j].isVisited() == 0 && chosen_neighbour == left) { //left side
				      	rooms[i][j].setMissingWall(left);
					rooms[i-1][j].setMissingWall(right);
					rooms[i-1][j].setPrev(i, j);
					printf("left\n");
				}
				if (j+1 <= SCREEN_HEIGHT/ROOM_SIZE && rooms[i][j+1].isVisited() == 0 && chosen_neighbour == bottom) { //bottom side
					rooms[i][j+1].setMissingWall(top);
				      	rooms[i][j].setMissingWall(bottom);
					rooms[i][j+1].setPrev(i, j);
					printf("bottom\n");
				}
		}
	}
}
