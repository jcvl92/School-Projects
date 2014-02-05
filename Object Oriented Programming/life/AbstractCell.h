#ifndef AbstractCell_h
#define AbstractCell_h

class AbstractCell
{
protected:
	bool life;
public:
	virtual AbstractCell* clone() const = 0;
	/**
	 * returns the state of life(dead or alive)
	 * @return a bool based on the state of life
	 */
	bool isAlive();
	/**
	 * sets the value of life based on l
	 * @param l a bool
	 */
	void setLife(bool);
	virtual bool run(int, int) = 0;
	/**
	 * an empty API-compliant function
	 */
	void mutate() const;
	virtual char sign() const = 0;
};

#endif
