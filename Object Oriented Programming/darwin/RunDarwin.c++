#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

     Species food(
        "0: left\n"
        "1: go 0",
        'f'
        );

    Species hopper(
        "0: hop\n"
        "1: go 0",
        'h'
        );

    Species rover(
        "0: if_enemy 9\n"
        "1: if_empty 7\n"
        "2: if_random 5\n"
        "3: left\n"
        "4: go 0\n"
        "5: right\n"
        "6: go 0\n"
        "7: hop\n"
        "8: go 0\n"
        "9: infect\n"
        "10: go 0",
        'r'
        );

     Species trap(
        "0: if_enemy 3\n"
        "1: left\n"
        "2: go 0\n"
        "3: infect\n"
        "4: go 0",
        't'
        );

    Species spinner(
        "0: left\n"
        "1: hop\n"
        "2: go 0",
        's'
        );

    Species best(
        "0: if_wall 6\n"
        "1: if_enemy 4\n"
        "2: hop\n"
        "3: go 0\n"
        "4: infect\n"
        "5: go 0\n"

        "6: right\n"
        "7: if_enemy 19\n"
        "8: right\n"
        "9: if_enemy 21\n"
        "10: right\n"
        "11: if_enemy 23\n"

        "12: left\n"
        "13: if_enemy 25\n"
        "14: left\n"
        "15: if_enemy 27\n"
        "16: left\n"
        "17: if_enemy 29\n"
        "18: go 6\n"

        "19: infect\n"
        "20: go 8\n"
        "21: infect\n"
        "22: go 10\n"
        "23: infect\n"
        "24: go 12\n"
        "25: infect\n"
        "26: go 14\n"
        "27: infect\n"
        "28: go 16\n"
        "29: infect\n"
        "30: go 18\n",
        'b'
        );

//food
    try {
        cout << "*** Darwin 1x1 ***" << endl;

        Grid g(1,1);

        g.place(Creature(food, north), 0, 0);

        g.simulate(3, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

//hopper
    try {
        cout << "*** Darwin 1x11 ***" << endl;

        Grid g(1,11);

        g.place(Creature(hopper, east), 0, 0);

        g.simulate(10, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

//spinner
    try {
        cout << "*** Darwin 8x8 ***" << endl;

        Grid g(8,8);

        g.place(Creature(spinner, north), 4, 4);

        g.simulate(10, 2);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

//rovers
    try {
        srand(0);
        cout << "*** Darwin 8x8 ***" << endl;
        Creature c[] = {
		{food, east},
		{rover, north},
		{rover, east},
		{rover, south},
		{rover, west},
		{food, north}
		};
        Grid g(8,8);

        g.place(c[0], 0, 0);
        g.place(c[1], 3, 3);
        g.place(c[2], 3, 4);
        g.place(c[3], 4, 4);
        g.place(c[4], 4, 3);
        g.place(c[5], 7, 7);

        g.simulate(10, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	//intersection
    try {
        srand(0);
        cout << "*** Darwin 8x8 ***" << endl;
        Creature c[] = {
		{hopper, east},
		{rover, north},
		{food, west}
		};
        Grid g(7,9);

        g.place(c[0], 3, 1);
        g.place(c[1], 5, 3);
        g.place(c[2], 3, 5);

        g.simulate(10, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
        Creature c[] = {
		{food, east},
		{hopper, north},
		{hopper, east},
		{hopper, south},
		{hopper, west},
		{food, north}
		};
        Grid g(8,8);

        g.place(c[0], 0, 0);
        g.place(c[1], 3, 3);
        g.place(c[2], 3, 4);
        g.place(c[3], 4, 4);
        g.place(c[4], 4, 3);
        g.place(c[5], 7, 7);

        g.simulate(5, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;
        srand(0);
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Creature c[] = {
		{trap, south},
		{hopper, east},
		{rover, north},
		{trap, west},
		};
        Grid g(7,9);
        g.place(c[0], 0, 0);
        g.place(c[1], 3, 2);
        g.place(c[2], 5, 4);
        g.place(c[3], 6, 8);

        g.simulate(5, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print every 100th grid.
        */
        Grid g(72,72);

    	for(int i=0;i<10;++i)
    	{
    		int position = rand()%5184;
    		int d = rand()%4;
            direction dir;
            switch(d)
            {
            case 0:
                dir = west;
                break;
            case 1:
                dir = north;
                break;
            case 2:
                dir = east;
                break;
            case 3:
                dir = south;
                break;
            }
    		g.place(Creature(food,dir), position/72, position%72);
    	}
    	for(int i=0;i<10;++i)
        {
            int position = rand()%5184;
            int d = rand()%4;
            direction dir;
            switch(d)
            {
            case 0:
                dir = west;
                break;
            case 1:
                dir = north;
                break;
            case 2:
                dir = east;
                break;
            case 3:
                dir = south;
                break;
            }
            g.place(Creature(hopper,dir), position/72, position%72);
        }
        for(int i=0;i<10;++i)
        {
            int position = rand()%5184;
            int d = rand()%4;
            direction dir;
            switch(d)
            {
            case 0:
                dir = west;
                break;
            case 1:
                dir = north;
                break;
            case 2:
                dir = east;
                break;
            case 3:
                dir = south;
                break;
            }
            g.place(Creature(rover,dir), position/72, position%72);
        }
        for(int i=0;i<10;++i)
        {
            int position = rand()%5184;
            int d = rand()%4;
            direction dir;
            switch(d)
            {
            case 0:
                dir = west;
                break;
            case 1:
                dir = north;
                break;
            case 2:
                dir = east;
                break;
            case 3:
                dir = south;
                break;
            }
            g.place(Creature(trap,dir), position/72, position%72);
        }

        g.simulate(1000, 100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: 0:west, 1:north, 2:east, 3:south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
        Grid g(72,72);

        for(int i=0;i<10;++i)
        {
            int position = rand()%5184;
            int d = rand()%4;
            direction dir;
            switch(d)
            {
            case 0:
                dir = west;
                break;
            case 1:
                dir = north;
                break;
            case 2:
                dir = east;
                break;
            case 3:
                dir = south;
                break;
            }
            g.place(Creature(food,dir), position/72, position%72);
        }
        for(int i=0;i<10;++i)
        {
            int position = rand()%5184;
            int d = rand()%4;
            direction dir;
            switch(d)
            {
            case 0:
                dir = west;
                break;
            case 1:
                dir = north;
                break;
            case 2:
                dir = east;
                break;
            case 3:
                dir = south;
                break;
            }
            g.place(Creature(hopper,dir), position/72, position%72);
        }
        for(int i=0;i<10;++i)
        {
            int position = rand()%5184;
            int d = rand()%4;
            direction dir;
            switch(d)
            {
            case 0:
                dir = west;
                break;
            case 1:
                dir = north;
                break;
            case 2:
                dir = east;
                break;
            case 3:
                dir = south;
                break;
            }
            g.place(Creature(rover,dir), position/72, position%72);
        }
        for(int i=0;i<10;++i)
        {
            int position = rand()%5184;
            int d = rand()%4;
            direction dir;
            switch(d)
            {
            case 0:
                dir = west;
                break;
            case 1:
                dir = north;
                break;
            case 2:
                dir = east;
                break;
            case 3:
                dir = south;
                break;
            }
            g.place(Creature(trap,dir), position/72, position%72);
        }
        for(int i=0;i<10;++i)
        {
            int position = rand()%5184;
            int d = rand()%4;
            direction dir;
            switch(d)
            {
            case 0:
                dir = west;
                break;
            case 1:
                dir = north;
                break;
            case 2:
                dir = east;
                break;
            case 3:
                dir = south;
                break;
            }
            g.place(Creature(best,dir), position/72, position%72);
        }

        g.simulate(1000, 100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // --------------------
    // best vs. rover 15x20
    // --------------------

    try {
        cout << "*** Darwin 15x20 ***" << endl;
        srand(0);
        Grid g(15,20);

        for(int i=0;i<10;++i)
        {
            int d = rand()%4;
            direction dir;
            switch(d)
            {
            case 0:
                dir = west;
                break;
            case 1:
                dir = north;
                break;
            case 2:
                dir = east;
                break;
            case 3:
                dir = south;
                break;
            }
            g.place(Creature(rover,dir), rand()%15, rand()%20);
        }
        for(int i=0;i<10;++i)
        {
            int d = rand()%4;
            direction dir;
            switch(d)
            {
            case 0:
                dir = west;
                break;
            case 1:
                dir = north;
                break;
            case 2:
                dir = east;
                break;
            case 3:
                dir = south;
                break;
            }
            g.place(Creature(best,dir), rand()%15, rand()%20);
        }

        g.simulate(100, 10);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
