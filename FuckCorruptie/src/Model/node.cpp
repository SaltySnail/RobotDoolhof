#include "node.h"

void model::node::setVisited(void) { 
	visited = true;
}
void model::node::setCurrentRoom(room *currRoom) {
	current_room = currRoom;
}
void model::node::setPrevRoom(room *prevRoom) { 
	prev_room = prevRoom;
}
void model::node::setPrevNode(node *prevNode) { 
	prev_node = prevNode;
}
void model::node::setWeightWalls() { 
	if (missing_wall[top] == false)
		weight[top] = INT_MAX;
	if (missing_wall[bottom] == false)
		weight[bottom] = INT_MAX;
	if (missing_wall[right] == false)
		weight[right] = INT_MAX;
	if (missing_wall[left] == false)
		weight[left] = INT_MAX;
}
void model::node::setWeightOpening(int *weight_counter) { 
	if (missing_wall[top] == true) {
		weight[top] = *weight_counter;
		weight_counter++;
	}
	else if (missing_wall[bottom] == true) {
		weight[bottom] = *weight_counter;
		weight_counter++;
		}
	else if (missing_wall[right] == true) {
		weight[right] = *weight_counter;
		weight_counter++;
	}
	else if (missing_wall[left] == true) {
		weight[left] = *weight_counter;
		weight_counter++;
	}
}

void model::node::setWeightBacktracking(sides currentRoomWeight) {
	switch (currentRoomWeight) {
		case top:
			weight[top] = INT_MAX;
			setWeightBacktrackingPrevNode(bottom);
		case bottom:
			weight[bottom] = INT_MAX;
			setWeightBacktrackingPrevNode(top);
		case left:
			weight[left] = INT_MAX;
			setWeightBacktrackingPrevNode(right);
		case right:
			weight[right] = INT_MAX;
			setWeightBacktrackingPrevNode(left);
		default:
			break;
	}	
}
void model::node::setWeightBacktrackingPrevNode(sides currentRoomWeight) { 
	switch (currentRoomWeight) {
		case top:
			weight[top] = INT_MAX;
		case bottom:
			weight[bottom] = INT_MAX;
		case left:
			weight[left] = INT_MAX;
		case right:
			weight[right] = INT_MAX;
		default:
			break;
	}
}

int model::node::getWeight(sides theSide) {
	switch (theSide) {
		case top:
			return weight[top];
		case bottom:
			return weight[bottom];
		case left:
			return weight[left];
		case right:
			return weight[right];
		default:
			break;
	}
	return INT_MAX; //zou nooit moeten gebeuren
}

void model::node::setMissingWalls() {
	printf("locating segfault\n");
	missing_wall[top] = current_room->isWallMissing(top);
	missing_wall[bottom] = current_room->isWallMissing(bottom);
	missing_wall[right] = current_room->isWallMissing(right);
	missing_wall[left] = current_room->isWallMissing(left);
	printf("Missing walls: \t top: %d \t bottom: %d \t right: %d \t left: %d \n", missing_wall[top], missing_wall[bottom], missing_wall[right], missing_wall[left]);
}
