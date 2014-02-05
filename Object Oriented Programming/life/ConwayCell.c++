#include "ConwayCell.h"

ConwayCell::ConwayCell()
{
	life = false;
}

ConwayCell* ConwayCell::clone() const
{
	return new ConwayCell(*this);
}

bool ConwayCell::run(int sideNeighbors, int cornerNeighbors)
{
	int neighbors = sideNeighbors + cornerNeighbors;

	if(!isAlive() && neighbors == 3)
		life = true;
	else if(isAlive() && neighbors != 2 && neighbors != 3)
		life = false;

	return true;
}

char ConwayCell::sign() const
{
	return (life ? '*' : '.');
}
