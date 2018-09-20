/* Hunter Trautz, hctrautz 
Gabe Aponte, gaaponte
PA5, Polymorphism 
Ant.cpp */

#include "Organism.h"
#include "Ant.h"
#include "Statistics.h"

using namespace std;

/** Checks the area surronding the ant, and moves to a random empty space if it can
* Also,if it meet the requirments it will breed at the end of the turn
* @Param **board array of pointers to organisms representing the gameboard
* @Param size the size of the gameboard, used to make sure we don't go off the end of the gameboard
* @Param stats stores the statistics of the simulation so that they can be printed at the end
* @Return void, prints the current board state
*/
void Ant::move(Organism ***board, int size, Statistics *stats){
	//stores the row numbers of cells an ant can move to
	vector<int> emptyRowNumbers;
	//stores the column numbers of cells an ant can move to
	vector<int> emptyColumnNumbers;

	//checks to the left of the ant and if it's empty add the coordinates of the cell to the vector
	if(this->column-1 >= 0 && board[this->row][this->column-1] == NULL){
		emptyRowNumbers.push_back(this->row);
		emptyColumnNumbers.push_back(this->column-1);
	}

	//checks to the right of the ant if it's empty add the coordinates of the cell to the vector
	if(this->column+1 < size && board[this->row][this->column+1] == NULL){
		emptyRowNumbers.push_back(this->row);
		emptyColumnNumbers.push_back(this->column+1);
	}

	//checks above the ant and if it's empty add the coordinates of the cell to the vector
	if(this->row-1 >= 0 && board[this->row-1][this->column] == NULL){
		emptyRowNumbers.push_back(this->row-1);
		emptyColumnNumbers.push_back(this->column);
	}

	//checks below the ant and if it's empty add the coordinates of the cell to the vector
	if(this->row+1 < size && board[this->row+1][this->column] == NULL){
		emptyRowNumbers.push_back(this->row+1);
		emptyColumnNumbers.push_back(this->column);
	}

	if(emptyRowNumbers.size() == 0){
		//if there are no possible cells that an Ant can move to terminate
		return;
	}

	//generate a random position to move to 
	int randomIndex = rand()%emptyRowNumbers.size();
	int randomRow = emptyRowNumbers[randomIndex];
	int randomColumn = emptyColumnNumbers[randomIndex];

	Ant* newAnt = new Ant(this->turnCounter+1, this->type, randomRow, randomColumn, true);
	//place the updated Ant in its new position
	board[randomRow][randomColumn] = newAnt;
	//remove it from its old position
	board[this->row][this->column] = NULL;

	//Allows the ant to breed if it meets the conditions to do so 
	if(newAnt->turnCounter > 2){
		newAnt->turnCounter = 0;
		newAnt->breed(board, size);
		//increments the ant total in the simulation's statistics object
		stats->antTotal = stats->antTotal+1;
	}
}

/** Checks the area surronding the ant, and if there is an empty cells around the ant, it will create a new ant in a random empty space
* @Param **board array of pointers to organisms representing the gameboard
* @Param size the size of the gameboard, used to make sure we don't go off the end of the gameboard
* @Return adds a new ant to the board around the already exisiting ant
*/
void Ant::breed(Organism ***board, int size){
	vector<int> emptyRowNumbers;
	vector<int> emptyColumnNumbers;

	//checks above the ant and if it's empty add the coordinates of the cell to the vector
	if(this->row-1 >= 0 && board[this->row-1][this->column] == NULL){
		emptyRowNumbers.push_back(this->row-1);
		emptyColumnNumbers.push_back(this->column);
	}

	//checks to the right of the ant and if it's empty add the coordinates of the cell to the vector
	if(this->column+1 < size && board[this->row][this->column+1] == NULL){
		emptyRowNumbers.push_back(this->row);
		emptyColumnNumbers.push_back(this->column+1);
	}

	//checks below the ant and if it's empty add the coordinates of the cell to the vector
	if(this->row+1 < size && board[this->row+1][this->column] == NULL){
		emptyRowNumbers.push_back(this->row+1);
		emptyColumnNumbers.push_back(this->column);
	}

	//checks to the left of the ant and if it's empty add the coordinates of the cell to the vector
	if(this->column-1 >= 0 && board[this->row][this->column-1] == NULL){
		emptyRowNumbers.push_back(this->row);
		emptyColumnNumbers.push_back(this->column-1);
	}

	//if there are no empty spaces around the ant then terminate the function, it can't breed
	if(emptyRowNumbers.size() == 0){
		return;
	}

	//generate a random position to place the new ant from the vectors
	int randomIndex = rand()%emptyRowNumbers.size();
	int randomRow = emptyRowNumbers[randomIndex];
	int randomColumn = emptyColumnNumbers[randomIndex];

	Ant* newAnt = new Ant(0, this->type, randomRow, randomColumn, true);
	//place the new ant on the board
	board[randomRow][randomColumn] = newAnt;
}



