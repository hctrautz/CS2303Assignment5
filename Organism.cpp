/* Hunter Trautz, hctrautz 
Gabe Aponte, gaaponte
PA5, Polymorphism 
Organism.cpp */

#include "Organism.h"
#include <iostream>

using namespace std;

bool Organism::boardCheck(int size){
	if(this->row - 1 >= 0 && this->column - 1 >= 0 && this->column + 1 < size && this->row + 1 < size){
		cout << "safe move" << endl;
		return true;
	} else {
		cout << "blocked dangerous move" << endl;

		return false;
	}
}
