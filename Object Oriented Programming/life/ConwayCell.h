#ifndef ConwayCell_h
#define ConwayCell_h
#include "AbstractCell.h"

class ConwayCell : public AbstractCell
{
public:
	/**
	 * initializes life to false
	 */
	ConwayCell();
	/**
	 * creates a copy of this class and returns it
	 * @return a new FredkinCell
	 */
	ConwayCell* clone() const;
	/**
	 * changes life based on the number of neighbors
	 * @param sideNeighbors an int
	 * @param cornerNeighbors an int
	 * @return a bool indicating whether or not to mutate
	 */
	bool run(int, int);
	/**
	 * returns a character represenation of the state of life
	 * @return a char based on life
	 */
	char sign() const;
};

#endif
