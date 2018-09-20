/* Hunter Trautz, hctrautz 
Gabe Aponte, gaaponte
PA5, Polymorphism
Board.h */

#ifndef BOARD_H
#define BOARD_H

#include "Organism.h"
#include "PA5.h"

class Board {
	public:
		Organism** *gameBoard; // pointer to the positons of the organisms on the game board
		int size; // size of the game board
 		Organism *getOrganism(int row, int column, int size);
 		void place(Organism *organism, int max);
};
#endif
