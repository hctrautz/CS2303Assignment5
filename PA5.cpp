/* Hunter Trautz, hctrautz
Gabe Aponte, gaaponte
PA5, Polymorphism
PA5.cpp */

#include <iostream>
#include <cstdlib>
#include <string>
#include <typeinfo>
#include <cmath>
#include <vector>
#include "stdio.h"

#include "PA5.h"
#include "Organism.h"
#include "Organism.cpp"
#include "Ant.h"
#include "Ant.cpp"
#include "Doodlebug.h"
#include "Doodlebug.cpp"
#include "Board.h"
#include "Board.cpp"
#include "Statistics.h"
#include "Statistics.cpp"

using namespace std;

/** Make a 2D array of integers
 *
 * @param rows Number of rows
 * @param columns Number of columns
 * @return Pointer to the array of pointers to the rows.
 * 	  or null pointer if unable to allocate memory.
 * 	  Note: Will not free partially-allocated memory.
 *
 * @author Mike Ciaraldi
 * @author Hunter Trautz
 * @author Gabe Aponte
 */

Organism*** make2DOrganism(int rows, int columns) {
	Organism ***a = (Organism ***) malloc(rows * columns * sizeof(Organism *)); // Array of pointers to rows
	unsigned int i; //Loop counter

	if (!a) { // Unable to allocate the array
		return (Organism ***) NULL;
	}

	// Now allocate array for each row
	for (i = 0; i < rows; i++) {
		// i is the row we are about to allocate
		a[i] = (Organism **) malloc(columns * sizeof (Organism));
		if (!a[i]) {
			return (Organism ***) NULL; // Unable to allocate
		}
	}
	return a;
}

/** Places the organism at a random gameBoard on the board
* @Param size the size of the game board
* @Param *gameBoard the gameBoard of the
* @Return void, prints the current board state
*/
void printGrid(int size, Organism** *gameBoard){
	//loop through every row and column position
	for(int row = 0;row < size;row++){
		for(int column = 0;column < size;column++){
			//if the cell is not empty (NULL)
			if(gameBoard[row][column]){
				//print x if there is a doodlebug in the cell
				if(gameBoard[row][column]->type == Predator){
					printf("x");
				}
				//print o if there is an ant in the cell
				else if(gameBoard[row][column]->type == Prey){
					printf("o");
				}else{
					//otherwise print a space
					printf(" ");
				}
			}else{
				//print a space if the cell is NULL
				printf(" ");
			}
		}
		//new line at the end of the game board
		printf("\n");
	}
}

/** Places the organism at a random gameBoard on the board
* @Param size the size of the game board
* @Param doodlebugs the number of doodlebugs in the simulation
* @Param ants the number of ants in the simulation
* @Param steps the total number of steps that the simulation will run for
* @Param pause 1 if the simulation should stop after each step, or 0 if it should not
* @Param stepsRun
* @Param
* @Return void, prints the current board state
*/
void runSimulation(int size, int doodlebugs, int ants, int steps, int seed, int pause, int stepsRun){

	int totalSteps = 0;
	int remainingDoodlebugTotal = doodlebugs;
	int remainingAntTotal = ants;

	//initialize a 2D array of the size that the user specified
	Organism ***theArray = make2DOrganism(size, size);
	//initliaze a statistic
	Statistics *stats = new Statistics();

	//initialize the board and the size of the board with the user's input
	Board *theBoard = new Board();
	theBoard->size = size;

	//set the 2D array, which holds the positions of the organisims on the game board, as the location field of the game board
	theBoard->gameBoard = theArray;

	// initialize the statistics object for the simulation
	stats->gridSize = size;
	stats->doodleBugs = doodlebugs;
	stats->doodlebugTotal = doodlebugs;
	stats->ants = ants;
	stats->antTotal = ants;
	stats->steps = steps;
	stats->seed = seed;
	stats->pause = pause;

	for(int i = 0;i < doodlebugs;i++){
		Doodlebug *aBug = new Doodlebug();
		//initializes the type of every DoodleBug as a predator
		aBug->type = Predator;
		//initializes all DoodleBugs on a random place on the board
		theBoard->place(aBug, size);
	}

	for(int i = 0;i < ants;i++){
		Ant *aBug = new Ant();
		//initializes the type of every ant as prey
		aBug->type = Prey;
		//initializes all ants on a random place on the board
		theBoard->place(aBug, size);
	}

	printf("Starting Board:\n\n");
	printGrid(size, theBoard->gameBoard);
	printf("\n\n");

	//checks after each step if pause is == 1, and if it is it will ask for a character
	for(int i = 0;i < steps;i++){
		if(i%pause == 0){
			cout << "Step Number: " << totalSteps + 1 << endl;
			printGrid(size, theBoard->gameBoard);
			cout << endl << "Press any key to continue." << endl;
			getchar();
		}


		//Loops through the entire board and runs the actions of the doodlebugs
		for(int row=0;row<size;row++){
			for(int column=0;column<size;column++){
				//if a cell is empty skip over it
				if(theBoard->gameBoard[row][column] == NULL){
					continue;
				}

				//cast the organism to a doodlebug
				Doodlebug *organism = (Doodlebug*)theBoard->gameBoard[row][column];

				//if the organism isn't NULL, a doodlebug (type predator), and hasn't moved this turn, run the actions for the round
				if(organism != NULL && organism->type == Predator && organism->moveFlag == false){
					organism->move(theBoard->gameBoard, size, stats);
				}
			}
		}

		//Loops through the entire board and runs the actions of the ants
		for(int row=0;row<size;row++){
			for(int column=0;column<size;column++){
				//if a cell is empty skip over it
				if(!theBoard->gameBoard[row][column]){
					continue;
				}

				//cast the organism to an ant
				Ant *organism = (Ant *)theBoard->gameBoard[row][column];

				//if the organism isn't NULL, an ant (type prey), and hasn't moved this turn, run the actions for the round
				if(organism != NULL && organism->type == Prey && organism->moveFlag == false){
					organism->move(theBoard->gameBoard, size, stats);
				}
			}
		}

		//after all the actions for every organism on the board have been completed increment the step counter
		totalSteps++;

		int currentAntTotal = 0;
		//Loop through every Ant on the board and set the move flag of everything back to false
		//and counts the current number of Ants on the board after the turn
		for(int row=0;row<size;row++){
			for(int column=0;column<size;column++){
				//if a cell is empty skip over it
				if(!theBoard->gameBoard[row][column]){
					continue;
				}
				//cast the organism to an ant
				Organism *organism = (Ant *)theBoard->gameBoard[row][column];
				//rest the move flag
				organism->moveFlag = false;

				//increment the currentAntTotal
				if(organism->type == Prey){
					currentAntTotal++;
				}
			}
			remainingAntTotal = currentAntTotal;
		}

		int currentBugTotal = 0;
		//Loop through every Doodlebug on the board and set the move flag of everything back to false
		//and counts the current number of Doodlebug on the board after the turn
		for(int row=0;row<size;row++){
			for(int column=0;column<size;column++){
				//if a cell is empty skip over it
				if(!theBoard->gameBoard[row][column]){
					continue;
				}
				//cast the organism to a Doodlebug
				Organism *organism = (Doodlebug *)theBoard->gameBoard[row][column];
				//reset the move flag
				organism->moveFlag = false;

				//increment the currentBugTotal
				if(organism->type == Predator){
					currentBugTotal++;
				}
			}
			remainingDoodlebugTotal = currentBugTotal;
		}

		//if there are either no ants or no doodlebugs left on the board terminate the simulation and print the final board and stats
		if(currentAntTotal == 0 || currentBugTotal == 0){
			break;
		}
	}

	// set values for endgame statistics
	stats->stepsRun = totalSteps;
	stats->doodlebugRemaining = remainingDoodlebugTotal;
	stats->antRemaining = remainingAntTotal;
	stats->printResults(); // prints out simulation statistics
	printGrid(size, theBoard->gameBoard);

	stepsRun++; // increments the step counter
}

int main(int argc, char **argv){
	//sets the default pararmters for the simulation
	int gridSize = 20;
	int steps = 100;
	int seed = 1;
	int pause = 1;
	int doodleBugs = 5;
	int doodlebugTotal = 5;
	int ants = 100;
	int antTotal = 100;
	int stepsRun = 0;

	if(argc > 1){
		gridSize = atoi(argv[1]);
	}

	if(argc > 2){
		doodleBugs = atoi(argv[2]);
		doodlebugTotal = atoi(argv[2]);
	}

	if(argc > 3){
		ants = atoi(argv[3]);
		antTotal = atoi(argv[3]);
	}

	if(argc > 4){
		steps = atoi(argv[4]);
	}

	if(argc > 5 && argv[5]){
		seed = atoi(argv[5]);
		srand(seed);
	}else{
		srand(seed);
	}

	if(argc > 6 && atoi(argv[6]) > 0){
		pause = atoi(argv[6]);
	}

	runSimulation(gridSize, doodleBugs, ants, steps, seed, pause, stepsRun);

	return 0;
}
