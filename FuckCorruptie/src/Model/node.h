#ifndef NODE_H
#define NODE_H

#include "maze.h"
#include <climits>

namespace model {
	class node {
			room *current_room;
			room *prev_room; 
			node *prev_node;
			int weight[bottom+1];
		      	bool visited = false;
			bool missing_wall[bottom+1];
		public:		
			void setVisited(void);
			void setCurrentRoom(room *currRoom);
			void setPrevRoom(room *prevRoom);
			void setPrevNode(node *prevNode);
			void setWeightWalls(void);
			void setWeightOpening(int *weight_counter);
			void setWeightBacktracking(sides currentRoomWeight); 
			void setWeightBacktrackingPrevNode(sides currentRoomWeight); 
			int getWeight(sides theSide);
			void setMissingWalls(void);
	};
}

#endif
