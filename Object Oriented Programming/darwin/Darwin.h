#ifndef Darwin_h
#define Darwin_h

#include <iostream>	// istream, ostream
#include <cassert>	// assert
#include <vector>	// vector
#include <string>	// string
#include <sstream>	// istringstream
#include <stdexcept>	// out_of_range

using namespace std;

enum direction
{
	north,
	east,
	south,
	west
};
enum grid_type
{
	empty,
	creature,
	enemy,
	wall
};


class Species
{
public:
	/**
	 * stores a vector of strings of instructions
	 * @param s a string
	 * @param c a char
	 */
	Species(string, char);
	vector<string> program;
	char letter;
};


class Creature
{
public:
	/**
	 * stores a Species class and direction
	 * @param s a Species
	 * @param d an enum direction
	 */
	Creature(Species, direction);
	/**
	 * sets the species equal to an empty square
	 */
	Creature();
	Species mySpecies;
	direction dir;
	int pc;
};


class Grid
{
private:
	vector< vector<Creature> > grid;
	Creature* current;
	int x, y, currentX, currentY;

	/**
	 * returns the type of square in front of the currently running creature
	 * @return the grid_type of the square
	 */
	grid_type inFront();

	/**
	 * moves the currently running creature forward if able
	 */
	void hop();
	/**
	 * turns the currently running creature counter-clockwise(to the left)
	 */
	void left();
	/**
	 * turns the currently running creature clockwise(to the right)
	 */
	void right();
	/**
	 * copies the species of the currently running creature to the creature in front of it and reset's that creature's program counter
	 */
	void infect();
	/**
	 * executes a creatures instructions up to and including a single action instruction
	 */
	void runLine();
	/**
	 * prints the current state of the grid to stdout
	 */
	void printGrid();

public:
	/**
	 * constructs the underlying grid of creatures
	 * @param a an int
	 * @param b an int
	 */
	Grid(int, int);
	/**
	 * places a creature on the grid(copies by value)
	 * @param c a Creature
	 * @param a an int
	 * @param b an int
	 */
	void place(Creature, int, int);
	/**
	 * executes one action instruction for every creature in a left-right, top-down sequence
	 */
	void runOnce();
	/**
	 * executes moves turns for each creature on the grid and prints that grid every printFrequency times
	 * @param moves an int
	 * @param printFrequency an int
	 */
	void simulate(int, int);
};

#endif // Darwin_h
