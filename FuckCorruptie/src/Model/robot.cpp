#include "robot.h"

void model::robot::init(SDL_Renderer *renderer, SDL_Point start, maze *yourMaze) {
	txtr = IMG_LoadTexture(renderer, TXTR_ROBOT);
	location.x = start.x*ROOM_SIZE;
	location.y = start.y*ROOM_SIZE;
	angle += 90;
	myMaze = yourMaze;
}

void model::robot::draw(SDL_Renderer *renderer) {	
	SDL_Rect dest;
	dest.x = location.x;
	dest.y = location.y;
	SDL_QueryTexture(txtr, NULL, NULL, &dest.w, &dest.h);
	dest.w /= -ROBOT_ZOOM; //zoom out
	dest.h /= -ROBOT_ZOOM;
	dest.x -= dest.w / 2; //center of robot
	dest.y -= dest.h / 2;
	dest.x += ROOM_SIZE / 2;
	dest.y += ROOM_SIZE / 2;
	SDL_RenderCopyEx(renderer, txtr, NULL, &dest, angle, NULL,
		SDL_FLIP_NONE);
}

void model::robot::turn(double degrees) {
	if (desired_angle) {
		if (desired_angle > angle)
			direction = turning_right;
		else 
			direction = turning_left;	
		if ((int)angle == (int)desired_angle) {
			(void)desired_angle;
			angle = (int)angle;
			turning = false;
		}
		else {	
			if (direction == turning_left) {	
				angle--;
			}
			else {
				angle++;
			}
		}
	}
	else {
		turning = true;
		desired_angle = angle + degrees;
	}
}

void model::robot::setDesiredDegrees() { //deze eerst
	SDL_Point tmp;
	tmp.x = counter.x;
	tmp.y = counter.y;
	thePath.getNextRoom(&counter);
	printf("Got the next room boss: %d, %d\n", counter.x, counter.y);
	if (counter.x > tmp.x) { 
		desired_angle = degreesRight; 
		printf("I chose right, with angle %.2f\n", desired_angle);
	}
	if (counter.y > tmp.y) {
		desired_angle = degreesBottom;
		printf("I chose bottom, with angle %.2f\n", desired_angle);
	}
	if (counter.x < tmp.x) {
		desired_angle = degreesLeft;
		printf("I chose left, with angle %.2f\n", desired_angle);
	}
	if (counter.y < tmp.y){
		desired_angle = degreesTop;
		printf("I chose top, with angle %.2f\n", desired_angle);
	}
	turning = true;
} 

void model::robot::drive(double speed) { //dan deze
	if ((int)desired_angle == (int)angle) { //&& (location.x != counter->x*ROOM_SIZE || location.y != counter->y*ROOM_SIZE)) {
		location.x += speed*cos(angle - 90);
		location.y += speed*-sin(angle);
		driving = true;
		printf("Komt dit in beeld?\n");
	}
	else {
		driving = false;
	}
}

bool model::robot::isTurning() {
	return turning;
}

void model::robot::setCurrentRoom(maze *theMaze) {
	current_room = theMaze->getRoomByCoords(location);
}

void model::robot::update(void) {
	if (!path_init) {
		thePath.init(myMaze);
		path_init = true;
	}
	setDesiredDegrees();
	if (turning) {
		turn(0);
		printf("turning\n");
	}
	if (turning == false) {
		drive(2);
		printf("driving\n");
	}	
}
