/* Hunter Trautz, hctrautz 
Gabe Aponte, gaaponte
PA5, Polymorphism 
Statistics.h */

#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics{
	public:
	int gridSize;			
	int doodleBugs;
	int ants;
	int steps;
	int seed;
	int pause;
	int doodlebugTotal;
	int antTotal;
	int doodlebugRemaining;
	int antRemaining;
	int stepsRun;
	virtual void printResults();

	Statistics(){}
};
#endif
