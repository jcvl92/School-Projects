#ifndef FredkinCell_h
#define FredkinCell_h
#include "AbstractCell.h"

class FredkinCell : public AbstractCell
{
private:
	int age;
public:
	/**
	 * initializes the age to 0 and life to false
	 */
	FredkinCell();
	/**
	 * creates a copy of this class and returns it
	 * @return a new FredkinCell
	 */
	FredkinCell* clone() const;
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
