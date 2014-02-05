#ifndef Cell_h
#define Cell_h
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "Handle.h"

class Cell : public Handle<AbstractCell>
{
public:/**
	 * calls Handle's constructor with p
	 * @param p an AbstractCell pointer
	 */
	Cell(AbstractCell* p) : Handle<AbstractCell> (p) {}
	/**
	 * calls the underlying pointer's isAlive() method
	 * @return the return from the pointer's isAlive() call
	 */
	bool isAlive()
	{
		return get()->isAlive();
	}
	/**
	 * calls the underlying pointer's run() method, passing parameters
	 * @param a an int
	 * @param b an int
	 * @return the return from the pointer's run() call
	 */
	bool run(int a, int b)
	{
		return get()->run(a, b);
	}
	/**
	 * points the underlying pointer to a new ConwayCell object
	 */
	void mutate()
	{
		//create a new temporary handle and swap the contents
		Handle<AbstractCell> temp(new ConwayCell());
		swap(temp);
		setLife(true);
	}
	/**
	 * calls the underlying pointer's setLife() method, passing parameters
	 * @param l a bool
	 */
	void setLife(bool l)
	{
		get()->setLife(l);
	}
	/**
	 * calls the underlying pointer's sign() method
	 * @return the return from the pointer's sign() call
	 */
	char sign() const
	{
		return get()->sign();
	}
};

#endif
