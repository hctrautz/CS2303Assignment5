/* Hunter Trautz, hctrautz 
Gabe Aponte, gaaponte
PA5, Polymorphism
Statistics.cpp */

#include <iostream>
#include "Statistics.h"

using namespace std;


/** Prints the results of the simulation
 * @Return Prints out the results of the simulation
*/
void Statistics::printResults(){

	// printing the original command line input
	cout << "******************************************" << endl;
	cout << "STATISTICS FOR SIMULATION:" << endl << endl;
	cout << "The original command line was: gridSize – " << gridSize;
	cout << " #doodlebugs – " << doodleBugs;
	cout << " ants – " << ants;
	cout << " time_steps – " << steps;
	cout << " seed – " << seed;
	cout << " pause - " << pause << endl;
	cout << "Steps Run: " << stepsRun << endl;
	cout << "Ant Total: " << antTotal << endl;
	cout << "Ants Remaining: " << antRemaining << endl;
	cout << "Doodlebug Total: " << doodlebugTotal << endl;
	cout << "Doodlebugs Remaining: " << doodlebugRemaining << endl;
	cout << "*******************************************" << endl;
	cout << "FINAL BOARD LAYOUT:" << endl << endl;
}
