	/* Hunter Trautz, hctrautz 
	Gabe Aponte, gaaponte
	PA5, Polymorphism 
	Doodlebug.cpp */

	#include "Organism.h"
	#include "Doodlebug.h"
	#include <cstddef>
	#include <iostream>
	using namespace std;

/** Checks the area surronding the doodlebug, and if there is an Ant near eat it (if there is more than one eat a random one),
* otherwise move normally to a random empty position 
* @Param **board array of pointers to organisms representing the gameboard
* @Param size the size of the gameboard, used to make sure we don't go off the end of the gameboard
* @Param stats stores the statistics of the simulation so that they can be printed at the end
* @Return void, moves the doodlebug
*/
void Doodlebug::move(Organism ***board, int size, Statistics *stats){
	vector<int> canEatRow;
	vector<int> canEatColumn;

	//checks above the doodlebug and if there is an Ant add the coordinates of the cell to the vectors
	if(this->row-1 >= 0 && board[this->row-1][this->column] != NULL && board[this->row-1][this->column]->type == Prey){
		canEatRow.push_back(this->row-1);
		canEatColumn.push_back(this->column);
	}

	//checks to the right of the doodlebug and if there is an Ant add the coordinates of the cell to the vectors
	if(this->column+1 < size && board[this->row][this->column+1] != NULL && board[this->row][this->column+1]->type == Prey){
		canEatRow.push_back(this->row);
		canEatColumn.push_back(this->column+1);
	}

	//checks to the left of the doodlebug and if there is an Ant add the coordinates of the cell to the vectors
	if(this->column-1 >= 0 && board[this->row][this->column-1] != NULL && board[this->row][this->column-1]->type == Prey){
		canEatRow.push_back(this->row);
		canEatColumn.push_back(this->column-1);
	}

	//checks below the doodlebug and if there is an Ant add the coordinates of the cell to the vectors
	if(this->row+1 < size && board[this->row+1][this->column] != NULL && board[this->row+1][this->column]->type == Prey){
		canEatRow.push_back(this->row+1);
		canEatColumn.push_back(this->column);
	}

	//if there is an Ant that the doodlebug can eat, eat it 
	if(canEatRow.size() > 0){
		//generate a random Ant to eat from the vectors
		int randomEatIndex = rand()%canEatRow.size();
		int randomEatRow = canEatRow[randomEatIndex];
		int randomEatColumn = canEatColumn[randomEatIndex];

		//cast board variable of type Organism to Ant
		Ant *antEat = (Ant*)board[randomEatRow][randomEatColumn];
		this->eat(antEat, board);

	} else /* otherwise move normally */ { 
		vector<int> emptyRowNumbers;
		vector<int> emptyColumnNumbers;

		//checks above the doodlebug and if it's empty add the coordinates of the cell to the vectors
		if(this->row-1 >= 0 && board[this->row-1][this->column] == NULL){
			emptyRowNumbers.push_back(this->row-1);
			emptyColumnNumbers.push_back(this->column);
		}

		//checks to the right of the doodlebug and if it's empty add the coordinates of the cell to the vectors
		if(this->column+1 < size && board[this->row][this->column+1] == NULL){
			emptyRowNumbers.push_back(this->row);
			emptyColumnNumbers.push_back(this->column+1);
		}

		//checks below the doodlebug and if it's empty add the coordinates of the cell to the vectors
		if(this->row+1 < size && board[this->row+1][this->column] == NULL){
			emptyRowNumbers.push_back(this->row+1);
			emptyColumnNumbers.push_back(this->column);
		}

		//checks to the left the doodlebug and if it's empty add the coordinates of the cell to the vectors
		if(this->column-1 >= 0 && board[this->row][this->column-1] == NULL){
			emptyRowNumbers.push_back(this->row);
			emptyColumnNumbers.push_back(this->column-1);
		}

		//if the doodlebug can't move terminate the function
		if(emptyRowNumbers.size() == 0){
			return;
		}

		//generate a random position to move to from the vectors
		int randomMoveIndex = rand()%emptyRowNumbers.size();
		int randomMoveRow = emptyRowNumbers[randomMoveIndex];
		int randomMoveColumn = emptyColumnNumbers[randomMoveIndex];

		Doodlebug* newBug = new Doodlebug(this->turnCounter+1, this->type, randomMoveRow, randomMoveColumn, this->turnsSinceEating+1, true);
		//place the new doodlebug on the board
		board[randomMoveRow][randomMoveColumn] = newBug;
		//remove it from its old position
		board[this->row][this->column] = NULL;

		//if the doodlebug meets the condition for starving run starve() on it and update the stats
		if(newBug->turnsSinceEating > 2){
			newBug->starve(board);
		}

		//if the doodlebug meets the condition for breeding run breed() on it and update the stats
		if(newBug->turnCounter > 7){
			newBug->breed(board, size);
			newBug->turnCounter = 0;
			stats->doodlebugTotal = stats->doodlebugTotal+1;
		}
	}
}

/** Replaces the cell containg an Ant with a Doodlebug
* @Param stats stores the statistics of the simulation so that they can be printed at the end
* @Param **board array of pointers to organisms representing the gameboard
* @Return void, Replaces the cell containg an Ant with a Doodlebug
*/
void Doodlebug::eat(Ant *ant, Organism ***board){
	int antRow = ant->row;
	int antColumn = ant->column;
	//new doodlebug containg the same fields as the ant the function was called on
	Doodlebug *temp = new Doodlebug(this->turnCounter+1, this->type, antRow, antColumn, 0, true);
	//replaces the cell containg the ant with the new doodlebug
	board[antRow][antColumn] = temp;
	//removes the doodlebug from its old location
	board[this->row][this->column] = NULL;
} 

/** Checks the area surronding the doodlebug, and if there is an empty cell around the doodlebug, it will create a new doodlebug in a random empty space
* @Param **board array of pointers to organisms representing the gameboard
* @Param size the size of the gameboard, used to make sure we don't go off the end of the gameboard
* @Return adds a new Doodlebug to the board around the already exisiting doodlebug
*/
void Doodlebug::breed(Organism ***board, int size){
	vector<int> emptyRowNumbers;
	vector<int> emptyColumnNumbers;

	//checks above the doodlebug and if it's empty add the coordinates of the cell to the vectors
	if(this->row-1 >= 0 && board[this->row-1][this->column] == NULL){
		emptyRowNumbers.push_back(this->row-1);
		emptyColumnNumbers.push_back(this->column);
	}

	//checks to the right the doodlebug and if it's empty add the coordinates of the cell to the vectors
	if(this->column+1 < size && board[this->row][this->column+1] == NULL){
		emptyRowNumbers.push_back(this->row);
		emptyColumnNumbers.push_back(this->column+1);
	}

	//checks below the doodlebug and if it's empty add the coordinates of the cell to the vectors
	if(this->row+1 < size && board[this->row+1][this->column] == NULL){
		emptyRowNumbers.push_back(this->row+1);
		emptyColumnNumbers.push_back(this->column);
	}

	//checks to the left the doodlebug and if it's empty add the coordinates of the cell to the vectors
	if(this->column-1 >= 0 && board[this->row][this->column-1] == NULL){
		emptyRowNumbers.push_back(this->row);
		emptyColumnNumbers.push_back(this->column-1);
	}

	//if the doodlebug can't move terminate
	if(emptyRowNumbers.size() == 0){
		return;
	}
	
	//generate a random position to place the new doodlebug from the vectors
	int randomIndex = rand()%emptyRowNumbers.size();
	int randomRow = emptyRowNumbers[randomIndex];
	int randomColumn = emptyColumnNumbers[randomIndex];

	Doodlebug* newBug = new Doodlebug(0, this->type, randomRow, randomColumn, 0, true);
	//place the new doodlebug in the randomly generated cell
	board[randomRow][randomColumn] = newBug;
}

/** Removes the doodlebug from the board
* @Param **board array of pointers to organisms representing the gameboard	
* @Return void, Removes the doodlebug from the board
*/
void Doodlebug::starve(Organism ***board){
	board[this->row][this->column] = NULL;
}
