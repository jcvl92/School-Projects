#ifndef Life_h
#define Life_h

#include "Cell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

template <typename T>
class Life
{
private:
	vector< vector<T> > grid;
	int generation, population;

	/**
	 * moves the grid forward one generation
	 */
	void progress()
	{
		//make a copy of the grid to later replace the grid(so changes don't affect future changes)
		vector< vector<T> > newGrid(grid);
		for(int i=1;i<(int)grid.size()-1;++i)
		{
			for(int j=1;j<(int)grid[0].size()-1;++j)
			{
				//if the cell is alive before taking a turn, take it out of the population count
				if(grid[i][j].isAlive()) --population;
				//count the alive side neighbors
				int asn =
					(int)grid[i+1][j].isAlive() +
					(int)grid[i-1][j].isAlive() +
					(int)grid[i][j+1].isAlive() +
					(int)grid[i][j-1].isAlive();

				//count the alive corner neighbors
				int acn =
					(int)grid[i+1][j+1].isAlive() +
					(int)grid[i+1][j-1].isAlive() +
					(int)grid[i-1][j+1].isAlive() +
					(int)grid[i-1][j-1].isAlive();

				if(newGrid[i][j].run(asn, acn) == false)
					newGrid[i][j].mutate();
				//if the cell is alive after taking a turn, add it to the population count
				if(newGrid[i][j].isAlive()) ++population;
			}
		}
		swap(grid, newGrid);
		++generation;
	}
public:
	/**
	 * builds an x by y vector grid of type T, populated with cellType based on the contents of str
	 * @param x an int
	 * @param y an int
	 * @param str a string
	 * @param cellType a T
	 */
	Life(int x, int y, string str, T cellType)
	{
		generation = population = 0;
		istringstream s(str);

		//use the string to populate the grid, while padding the outside with dead cells
		{
			vector<T> temp;
			for(int i=0;i<x+2;++i)
			{
				temp.push_back(cellType);
			}
			grid.push_back(temp);
		}
		for(int i=1;i<y+1;++i)
		{
			vector<T> temp;
			temp.push_back(cellType);
			for(int j=1;j<x+1;++j)
			{
				if(s.peek() == EOF)
				{
					assert(false);
				}
				else if(s.peek() == '.')
					temp.push_back(cellType);
				else if(s.peek() == '*')
				{
					temp.push_back(cellType);
					temp[j].setLife(true);
					++population;
				}
				else if(s.peek() == '-')
					temp.push_back(cellType);
				else if(s.peek() == '0')
				{
					temp.push_back(cellType);
					temp[j].setLife(true);
					++population;
				}
				else
					--j;
				s.get();
			}
			temp.push_back(cellType);
			grid.push_back(temp);
		}
		{
			vector<T> temp;
			for(int i=0;i<x+2;++i)
			{
				temp.push_back(cellType);
			}
			grid.push_back(temp);
		}

		assert((int)grid[0].size()													== x+2);
		assert((int)grid[grid.size()-1].size()										== x+2);
		assert((int)grid.size()														== y+2);
		assert(grid[0][0].isAlive()													== false);
		assert(grid[grid.size()-1][0].isAlive()										== false);
		assert(grid[0][grid[0].size()-1].isAlive()									== false);
		assert(grid[grid.size()-1][grid[grid.size()-1].size()-1].isAlive()			== false);
	}
	/**
	 * progresses num times and then prints the grid
	 * @param num an int
	 */
	void simulate(int num)
	{
		for(int i=0;i<num;++i)
		{
			progress();
		}
		print();
	}
	/**
	 * progresses once and then prints the grid
	 */
	void simulate()
	{
		progress();
		print();
	}
	/**
	 * prints the contents of the grid(the signs of the cells)
	 */
	void print()
	{
	cout << "Generation = " << generation << ", Population = " << population << '.' << endl;
		for(int i=1;i<(int)grid.size()-1;++i)
		{
			for(int j=1;j<(int)grid[0].size()-1;++j)
			{
				cout << grid[i][j].sign();
			}
			cout << endl;
		}
	cout << endl;
	}
};

#endif
