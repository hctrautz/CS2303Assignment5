/* Hunter Trautz, hctrautz 
Gabe Aponte, gaaponte
PA5, Polymorphism
Ant.h */

#ifndef ANT_H
#define ANT_H
	class Ant : public Organism {
	public:
		//default contructor
		Ant(){
			this->turnCounter = 0;
			this->type = Prey;
			this->row = 0;
			this->column = 0;
			this->moveFlag = false;
		}

		Ant(int turnCounter, Type type, int row, int column, bool moveFlag){
			this->turnCounter = turnCounter;
			this->type = type;
			this->row = row;
			this->column = column;
			this->moveFlag = moveFlag;
		}
		
		void breed(Organism ***board, int size);	
		void move(Organism ***board, int size, Statistics *stats);
	};
	#endif
