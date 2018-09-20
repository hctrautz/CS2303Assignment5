/* Hunter Trautz, hctrautz 
Gabe Aponte, gaaponte
PA5, Polymorphism 
Board.cpp */

#include "Board.h"
#include "Organism.h"
#include <cstddef>
#include <cstdlib>

		/** Places the organism at a random gameBoard on the board
		 * @Param *organism pointer to Organism 
		 * @Param max the maximum integer to be used to randomly generate the gameBoard the organism will be placed
		 * @Return void, places the organism at a random gameBoard on the board
		*/
		void Board::place(Organism *organism, int max){

			int randRow = rand()%(max);
			int randColumn = rand()%(max);

			if(this->gameBoard[randRow][randColumn] != NULL){
				return place(organism, max);
			}

			this->gameBoard[randRow][randColumn] = organism;
				organism->row = randRow;
				organism->column = randColumn;
		}

		/** Returns the organism at the given location
		 * @Param row the row number of the organism you want to return
		 * @Param column he column number of the organism you want to return
		 * @Param size the size of the game board to make sure you aren't asking for an organism that isn't on the board
		 * @Return the organism at the given location
		*/
		Organism *Board::getOrganism(int row, int column, int size){
			if(row < 0 || row >= size || column < 0 || column >= size){
				return NULL;
			}
			return this->gameBoard[row][column];
		}
