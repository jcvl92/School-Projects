#include "Darwin.h"


//*****Grid*****//

//initialize the grid with empty grid peices
Grid::Grid(int a, int b) : x(b), y(a)
{
	for(int i=0;i<y;++i)
	{
		vector<Creature> temp;
		for(int j=0;j<x;++j)
		{
			temp.push_back(Creature());
		}
		grid.push_back(temp);
	}
}

void Grid::printGrid()
{
	cout << "  ";
	for(int i=0;i<x;++i)
	{
		cout << i%10;
	}
	cout << endl;
	for(int i=0;i<y;++i)
	{
		cout << i%10 << ' ';
		for(int j=0;j<x;++j)
		{
			cout << grid[i][j].mySpecies.letter;
		}
		cout << endl;
	}
	cout << endl;
}

void Grid::runOnce()
{
	vector<Creature*> creatures;
	vector<int> xC;
	vector<int> yC;

	for(int i=0;i<y;++i)
		for(int j=0;j<x;++j)
			if(grid[i][j].mySpecies.letter != '.')
			{
				creatures.push_back(&grid[i][j]);
				yC.push_back(i);
				xC.push_back(j);
			}

	for(int i=0;i<(int)creatures.size();++i)
	{
		current = creatures[i];
		currentY = yC[i];
		currentX = xC[i];
		runLine();
	}

}

void Grid::simulate(int moves, int printFrequency)
{
	cout << "Turn = 0." << endl;
	printGrid();

	for(int i=1;i<=moves;++i)
	{
		runOnce();
		if(!(i%printFrequency))
		{
			cout << "Turn = " << i << '.' << endl;
			printGrid();
		}
	}
}

//places a Creature onto the grid
void Grid::place(Creature c, int a, int b)
{
	assert(a<y && b<x && a>=0 && b>=0);
	
	grid[a][b] = c;
}

//returns the type of object in front of this object
grid_type Grid::inFront()
{
	switch(current->dir)
	{
	case north:
		if(currentY == 0) return wall;

		if(grid[currentY-1][currentX].mySpecies.letter != '.')
			return (grid[currentY-1][currentX].mySpecies.letter == current->mySpecies.letter) ? creature : enemy;
		break;
	case east:
		if(currentX == x-1) return wall;

		if(grid[currentY][currentX+1].mySpecies.letter != '.')
			return (grid[currentY][currentX+1].mySpecies.letter == current->mySpecies.letter) ? creature : enemy;
		break;
	case south:
		if(currentY == y-1) return wall;

		if(grid[currentY+1][currentX].mySpecies.letter != '.')
			return (grid[currentY+1][currentX].mySpecies.letter == current->mySpecies.letter) ? creature : enemy;
		break;
	case west:
		if(currentX == 0) return wall;

		if(grid[currentY][currentX-1].mySpecies.letter != '.')
			return (grid[currentY][currentX-1].mySpecies.letter == current->mySpecies.letter) ? creature : enemy;
		break;
	}

	return empty;
}

void Grid::runLine()
{
	istringstream in(current->mySpecies.program[current->pc]);
	string instruction, discard;

	in >> discard;
	in >> instruction;

	if(instruction == "hop")
	{
		current->pc++;
		hop();
	}
	else if(instruction == "left")
	{
		current->pc++;
		left();
	}
	else if(instruction == "right")
	{
		current->pc++;
		right();
	}
	else if(instruction == "infect")
	{
		current->pc++;
		infect();
	}
	else if(instruction == "if_empty")
	{
		int line_jump;
		in >> line_jump;
		if(inFront() == empty)
			current->pc = line_jump;
		else
			current->pc++;
		runLine();
	}
	else if(instruction == "if_wall")
	{
		int line_jump;
		in >> line_jump;			
		if(inFront() == wall)
			current->pc = line_jump;
		else
			current->pc++;
		runLine();
	}
	else if(instruction == "if_random")
	{
		int line_jump;
		in >> line_jump;			
		if(rand()%2)
			current->pc = line_jump;
		else
			current->pc++;
		runLine();
	}
	else if(instruction == "if_enemy")
	{
		int line_jump;
		in >> line_jump;			
		if(inFront() == enemy)
			current->pc = line_jump;
		else
			current->pc++;
		runLine();
	}
	else if(instruction == "go")
	{
		int line_jump;
		in >> line_jump;
			
		current->pc = line_jump;
		
		runLine();
	}
	else
		assert(false);
}

void Grid::hop()
{
	if(inFront() == empty)
	{
		//place the creature forward
		switch(current->dir)
		{
		case north:
				grid[currentY-1][currentX] = *current;
			break;
		case east:
				grid[currentY][currentX+1] = *current;
			break;
		case south:
				grid[currentY+1][currentX] = *current;
			break;
		case west:
				grid[currentY][currentX-1] = *current;
			break;
		}
		grid[currentY][currentX] = Creature();
	}
}

void Grid::left()
{
	if(current->dir == north)
		current->dir = west;
	else if(current->dir == east)
		current->dir = north;
	else if(current->dir == south)
		current->dir = east;
	else
		current->dir = south;
}

void Grid::right()
{
	if(current->dir == north)
		current->dir = east;
	else if(current->dir == east)
		current->dir = south;
	else if(current->dir == south)
		current->dir = west;
	else
		current->dir = north;
}

void Grid::infect()
{
	if(inFront() == enemy)
	{
		//place the creature forward(infection when the old one isn't removed)
		switch(current->dir)
		{
		case north:
			grid[currentY-1][currentX].mySpecies = current->mySpecies;
			grid[currentY-1][currentX].pc = 0;
			break;
		case east:
			grid[currentY][currentX+1].mySpecies = current->mySpecies;
			grid[currentY][currentX+1].pc = 0;
			break;
		case south:
			grid[currentY+1][currentX].mySpecies = current->mySpecies;
			grid[currentY+1][currentX].pc = 0;
			break;
		case west:
			grid[currentY][currentX-1].mySpecies = current->mySpecies;
			grid[currentY][currentX-1].pc = 0;
			break;
		}
	}
}


//*****Species*****//

Species::Species(string s, char c) : letter(c)
{
	istringstream in(s);
	string temp;
	char holder[20];
	for(int i=0;!in.eof();++i)
	{
		in.getline(holder, 20);
		temp = holder;
		program.push_back(temp);
	}
}

//*****Creature*****//

Creature::Creature(Species s, direction d) : mySpecies(s), dir(d)
{
	pc = 0;
}

Creature::Creature() : mySpecies(Species("",'.'))
{
}
