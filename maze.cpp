#include "maze.h"


void model::maze::setAllRoomSizes(void) {
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
	int x, y;
	for (int i = 0; i <= SCREEN_WIDTH/ROOM_SIZE; i++) {
		for (int j = 0; j <= SCREEN_HEIGHT/ROOM_SIZE; j++) {
			srand(i*j);
			rooms[i][j].setVisited();
			for (int tmp = 0; tmp < 4; tmp++) {
			switch (tmp) {
				case 0:
					if (x < SCREEN_WIDTH/ROOM_SIZE) {
						x = i + 1;
						y = j;
						if (rooms[x][y].isVisited() == 0) {
							rooms[x][y].setMissingWall(0);
				      			rooms[i][j].setMissingWall(2);
							rooms[x][y].setVisited();
							rooms[x][y].setPrev(i, j);
							i = x;
							j = y;
						}
						else {
							SDL_Point prev = rooms[x][y].getPrev();
							i = prev.x;
							j = prev.y;
						}
					}
					break;
				case 1:
					if (y > 0) {
						x = i;
						y = j - 1;
						if (rooms[x][y].isVisited() == 0) {
							rooms[x][y].setMissingWall(1);
					      		rooms[i][j].setMissingWall(3);
							rooms[x][y].setVisited();
							rooms[x][y].setPrev(i, j);
							i = x;
							j = y;
						}
						else {
							SDL_Point prev = rooms[x][y].getPrev();
							i = prev.x;
							j = prev.y;
						}
					}
					break;
				case 2:
					if (x > 0) {
						x = i - 1;
						y = j;
						if (rooms[x][y].isVisited() == 0) {
							rooms[x][y].setMissingWall(2);
					      		rooms[i][j].setMissingWall(0);	
							rooms[x][y].setVisited();
							rooms[x][y].setPrev(i, j);
							i = x;
							j = y;
						}
						else {
							SDL_Point prev = rooms[x][y].getPrev();
							i = prev.x;
							j = prev.y;
						}
					}
					break;	
				case 3:
					if (y < SCREEN_HEIGHT/ROOM_SIZE) {
						x = i;
						y = j + 1;
						if (rooms[x][y].isVisited() == 0) {
							rooms[x][y].setMissingWall(3);
					     	 	rooms[i][j].setMissingWall(1);	
							rooms[x][y].setVisited();
							rooms[x][y].setPrev(i, j);
							i = x;
							j = y;
						}
						else {
							SDL_Point prev = rooms[x][y].getPrev();
							i = prev.x;
							j = prev.y;
						}
					}
					break;
				default:
				break;
				}
			}
		}
	}
}
