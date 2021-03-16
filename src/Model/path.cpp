#include "path.h"

void model::path::init(maze *yourMaze) {
	SDL_Point counter = {0, 0};
	room *tmp;
	theMaze = yourMaze;
	printf("Initializing path\n");	
	for (int j = 0; j < SCREEN_HEIGHT/ROOM_SIZE; j++) {
		for (int i = 0; i < SCREEN_WIDTH/ROOM_SIZE; i++) {
			counter.x = i * ROOM_SIZE;
			counter.y = j * ROOM_SIZE;
			printf("Initializing node %d, %d \n", i, j);
			tmp = theMaze->getRoomByCoords(counter);
			nodes[i][j].setCurrentRoom(tmp);
			printf("Current room was set %p\n", tmp);
			nodes[i][j].setMissingWalls(); 
			//(void)theMaze->rooms[i][j];
			printf("Missing walls recorded\n");
			nodes[i][j].setWeightWalls();
			printf("Weight of the walls has been set\n");
			/*nodes[i][j].setWeightOpening(&weight_counter, top); //minst gewild
			nodes[i][j].setWeightOpening(&weight_counter, left);
			nodes[i][j].setWeightOpening(&weight_counter, right);
			nodes[i][j].setWeightOpening(&weight_counter, bottom); //liefst dit zo laag mogelijk
			weight_counter++;
			printf("Weight of the opening has been set\n");*/
		}
	}
}

void model::path::getNextRoom(SDL_Point *counter, int *weight_counter) {
	int weight[4], prev_weight[4] = {0,0,0,0}, min_weight = INT_MAX;//, second_min_weight;
	nodes[counter->x][counter->y].setWeightOpening(weight_counter, top); 
	nodes[counter->x][counter->y].setWeightOpening(weight_counter, left);
	nodes[counter->x][counter->y].setWeightOpening(weight_counter, right);
	nodes[counter->x][counter->y].setWeightOpening(weight_counter, bottom); 
			//weight_counter++;
	if (counter->x != 0 || counter->y != 0) { // && counter->x <= SCREEN_WIDTH/ROOM_SIZE && counter->y <= SCREEN_WIDTH/ROOM_SIZE) {
		node *prev_node = nodes[counter->x][counter->y].getPrevNode();
		if (prev_node) {
			prev_weight[top] = prev_node->getWeight(bottom);
			prev_weight[bottom] = prev_node->getWeight(top);
			prev_weight[right] = prev_node->getWeight(left);
			prev_weight[left] = prev_node->getWeight(right);
			printf("\tprev Weight top: %d\n", prev_weight[top]);
			printf("\tprev Weight bottom: %d\n", prev_weight[bottom]);
			printf("\tprev Weight right: %d\n", prev_weight[right]);
			printf("\tprev Weight left: %d\n", prev_weight[left]);
		}
	}	
	weight[top] = nodes[counter->x][counter->y].getWeight(top);
	weight[bottom] = nodes[counter->x][counter->y].getWeight(bottom);
	weight[right] = nodes[counter->x][counter->y].getWeight(right);
	weight[left] = nodes[counter->x][counter->y].getWeight(left);
	printf("\tWeight top: %d\n", weight[top]);
	printf("\tWeight bottom: %d\n", weight[bottom]);
	printf("\tWeight right: %d\n", weight[right]);
	printf("\tWeight left: %d\n", weight[left]);
	//}
	

	for (int i = 0; i < 4; i++) {
		if (weight[i] <= INT_MAX/2 /*&& prev_weight[i] <= INT_MAX/2 */&& weight[i] /*+prev_weight[i]*/ < min_weight) {
			printf("Weight is: %d, with i %d\n", weight[i], i);
			printf("Previous weight is: %d, with i %d\n", prev_weight[i], i);
			//second_min_weight = min_weight;
			min_weight = weight[i];//+prev_weight[i];
			printf("Min weight is: %d, with i %d\n", min_weight, i);
		}
	}
	if (weight[top] != INT_MAX && weight[top] == min_weight && //|| weight[top] == second_min_weight) && //top
	    counter->y > 0) {
		counter->y--;
		nodes[counter->x][counter->y].setPrevNode(&nodes[counter->x][counter->y+1]);
		printf("top is the best choice: %d, %d\n", counter->x, counter->y);
		*weight_counter += 2;
		nodes[counter->x][counter->y].setWeightOpening(weight_counter, bottom);	
		*weight_counter -= 1;
		//nodes[counter->x][counter->y].setWeightBacktracking(bottom);	
	}
	else if (weight[right] != INT_MAX && weight[right] == min_weight && //|| weight[right] == second_min_weight) && //right
    		counter->x < SCREEN_WIDTH/ROOM_SIZE) {
		counter->x++;
		nodes[counter->x][counter->y].setPrevNode(&nodes[counter->x-1][counter->y]);
		printf("right is the best choice: %d, %d\n", counter->x, counter->y);
		*weight_counter += 2;
		nodes[counter->x][counter->y].setWeightOpening(weight_counter, left);	
		*weight_counter -= 1;
		//nodes[counter->x][counter->y].setWeightBacktracking(left);	
	}
	else if (weight[left] != INT_MAX && weight[left] == min_weight && //|| weight[left] == second_min_weight) && //left
	    counter->x > 0) {
		counter->x--;
		nodes[counter->x][counter->y].setPrevNode(&nodes[counter->x+1][counter->y]);
		printf("left is the best choice: %d, %d\n", counter->x, counter->y);
		*weight_counter += 2;
		nodes[counter->x][counter->y].setWeightOpening(weight_counter, right);	
		*weight_counter -= 1;
		//nodes[counter->x][counter->y].setWeightBacktracking(right);	
	}
	else if (weight[bottom] != INT_MAX && weight[bottom] == min_weight && //|| weight[bottom] == second_min_weight) && //bottom
	    counter->y < SCREEN_WIDTH/ROOM_SIZE) {
		counter->y++;
		nodes[counter->x][counter->y].setPrevNode(&nodes[counter->x][counter->y-1]);
		printf("bottom is the best choice: %d, %d\n", counter->x, counter->y);
		*weight_counter += 2;
		nodes[counter->x][counter->y].setWeightOpening(weight_counter, top);	
		*weight_counter -= 1;
		//nodes[counter->x][counter->y].setWeightBacktracking(top);	
	}
}

/*void model::path::setWeightFinish(SDL_Point finish) {
	int tmp = INT_MAX/2;	
	nodes[finish.x][finish.y].setWeightOpening(&tmp, top); 
	nodes[finish.x][finish.y].setWeightOpening(&tmp, left);
	nodes[finish.x][finish.y].setWeightOpening(&tmp, right);
	tmp = 0;
	nodes[finish.x][finish.y].setWeightOpening(&tmp, bottom); 
}*/
