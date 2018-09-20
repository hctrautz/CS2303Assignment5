/* Hunter Trautz, hctrautz 
Gabe Aponte, gaaponte
PA5, Polymorphism 
Doodlebug.h */

#ifndef DOODLEBUG_H
#define DOODLEBUG_H

#include "Organism.h"
#include "Ant.h"
#include "Statistics.h"

class Doodlebug : public Organism {
	public:
		int turnsSinceEating; //keeps track of how many turns it's been since the Doodlebug ran the function eat() 

		//Default contructor
		Doodlebug(){
			this->turnCounter = 0;
			this->type = Predator;
			this->row = 0;
			this->column = 0;
			this->turnsSinceEating = 0;
			this->moveFlag = false;
		}

		Doodlebug(int turnCounter, Type type, int row, int column, int turnsSinceEating, bool moveFlag){
			this->turnCounter = turnCounter;
			this->type = type;
			this->row = row;
			this->column = column;
			this->turnsSinceEating = turnsSinceEating;
			this->moveFlag = moveFlag;
		}

		
		void move(Organism ***board, int size, Statistics *stats);
		void eat(Ant *ant, Organism ***board);
		void breed(Organism ***board, int size);
		void starve(Organism ***board);
};
#endif
