#include "AbstractCell.h"

bool AbstractCell::isAlive()
{
	return life;
}

void AbstractCell::setLife(bool l)
{
	life = l;
}

void AbstractCell::mutate() const
{
}