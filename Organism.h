/* Hunter Trautz, hctrautz 
Gabe Aponte, gaaponte
PA5, Polymorphism 
Organism.h */

#ifndef ORGANISM_H
#define ORGANISM_H

#include "PA5.h"
#include "Statistics.h"

//Abstract base class that models Doodlebug and Ant
class Organism {
	public:
		int turnCounter; //counts the total number of steps the organism has been alive
		Type type; //type of the organism, either Predator (Doodlebug), Prey (Ant), or Empty (if a cell is NULL)
		int row; //row number on the board of the organism
		int column; //column number on the board of the organism
		bool moveFlag; //keeps track of if the organism has moved this turn, if it has moved (true), if it hasn't (false)
		void virtual move(Organism ***board, int size, Statistics *stats) = 0;
		void virtual breed(Organism ***board, int size) = 0;
		bool virtual boardCheck(int size);
};
#endif
