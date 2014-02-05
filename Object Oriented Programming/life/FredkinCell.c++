#include "FredkinCell.h"

FredkinCell::FredkinCell()
{
	life = false;
	age = 0;
}

FredkinCell* FredkinCell::clone() const
{
	return new FredkinCell(*this);
}

bool FredkinCell::run(int sideNeighbors, int cornerNeighbors)
{
	//FredkinCell only cares about the side neighbors
	bool ager = isAlive();
	
	if(!isAlive() && (sideNeighbors == 1 || sideNeighbors == 3))
		life = true;
	else if(isAlive() && sideNeighbors != 1 && sideNeighbors != 3)
		life = false;


	//age the cell if it was alive and is still alive
	if(ager && isAlive()) ++age;

	//if the cell is still alive and just turned 2(or more than 2 for safety), mutate it
	if(age >= 2 && isAlive())
		return false;	
	return true;
}

char FredkinCell::sign() const
{
	//return the age as a character or a '+' or '-'
	return (life ? (age<10 ? '0'+age : '+') : '-');
}
