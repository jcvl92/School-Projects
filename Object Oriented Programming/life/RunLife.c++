// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2013
// Glenn P. Downing
// -------------------------

/*
To run the program:
    % make RunLife
    % make run

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <fstream>   // ifstream
#include "Life.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ------------------
    // Conway Cell 109x69
    // ------------------

    try {
        cout << "*** Life<ConwayCell> 109x69 ***\n" << endl;
        /*
        read RunLifeConway.in // assume all Conway cells
        Simulate 283 moves.
        Print the first 10 grids (i.e. 0, 1, 2...9).
        Print the 283rd grid.
        Simulate 40 moves.
        Print the 323rd grid.
        Simulate 2177 moves.
        Print the 2500th grid.
        */

        ifstream in("RunLifeConway.in");
        int x, y;
        string s = "";
        //read in y value
        in >> y;
        //read in x value
        in >> x;
        //pass the remainder of the stream as a string
	while(in.peek()!= EOF)
	{
		s += in.get();
	}
	in.close();

	Life<ConwayCell> l(x, y, s, ConwayCell());

	l.print();
	for(int i=0;i<10;++i)
		l.simulate();
	l.simulate(273);
	l.simulate(40);
	l.simulate(2177);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {
        cout << "*** Life<FredkinCell> 20x20 ***\n" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Simulate 5 moves.
        Print every grid (i.e. 0, 1, 2...5)
        */

        ifstream in("RunLifeFredkin.in");
        int x, y;
        string s = "";
        //read in y value
        in >> y;
        //read in x value
        in >> x;
        //pass the remainder of the stream as a string
	while(in.peek()!= EOF)
	{
		s += in.get();
	}
	in.close();

	Life<FredkinCell> l(x, y, s, FredkinCell());

	l.print();
	for(int i=0;i<5;++i)
		l.simulate();

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 20x20
    // ----------

    try {
        cout << "*** Life<Cell> 20x20 ***\n" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Simulate 5 moves.
        Print every grid (i.e. 0, 1, 2...5)
        */

        ifstream in("RunLifeCell.in");
        int x, y;
        string s = "";
        //read in y value
        in >> y;
        //read in x value
        in >> x;
        //pass the remainder of the stream as a string
	while(in.peek()!= EOF)
	{
		s += in.get();
	}
	in.close();

	Life<Cell> l(x, y, s, new FredkinCell());

	l.print();
	for(int i=0;i<5;++i)
		l.simulate();

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    //ConwayCell 4x4
    try{
        Life<ConwayCell> l(4, 4, 
            "*...*\n"
            ".*.*.\n"
            "..*..\n"
            ".*.*.\n"
            "*...*",
            ConwayCell());

        l.print();
        for(int i=0;i<10;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

    //ConwayCell 1x1
    try{
        Life<ConwayCell> l(1, 1, 
            "*",
            ConwayCell());

        l.print();
        for(int i=0;i<5;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

//ConwayCell 5x5
    try{
        Life<ConwayCell> l(5, 5, 
            "......\n"
            ".*..*.\n"
            ".*..*.\n"
            ".*..*.\n"
            "......",
            ConwayCell());

        l.print();
        for(int i=0;i<10;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

//ConwayCell 3x3
    try{
        Life<ConwayCell> l(3, 3, 
            "***\n"
            "*.*\n"
            "***",
            ConwayCell());

        l.print();
        for(int i=0;i<5;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

//ConwayCell 3x10
    try{
        Life<ConwayCell> l(10, 3,
            ".*.*.*.*.*\n"
            "*.*.*.*.*.\n"
            ".*.*.*.*.*",
            ConwayCell());

        l.print();
        for(int i=0;i<10;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

//FredkinCell 1x10
    try{
        Life<FredkinCell> l(10, 1,
            "-00--00-0-",
            FredkinCell());

        l.print();
        for(int i=0;i<10;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

//FredkinCell 5x5
    try{
        Life<FredkinCell> l(5, 5,
            "0---0\n"
            "-0-0-\n"
            "--0--\n"
            "-0-0-\n"
            "0---0",
            FredkinCell());

        l.print();
        for(int i=0;i<10;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

    //FredkinCell 3x7
    try{
        Life<FredkinCell> l(7, 3,
            "000-000\n"
            "---0---\n"
            "00---00",
            FredkinCell());

        l.print();
        for(int i=0;i<10;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

    //FredkinCell 7x3
    try{
        Life<FredkinCell> l(3, 7,
            "0-0\n"
            "0-0\n"
            "0--\n"
            "-0-\n"
            "0--\n"
            "0-0\n"
            "0-0",
            FredkinCell());

        l.print();
        for(int i=0;i<10;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

    //FredkinCell 0x0
    try{
        Life<FredkinCell> l(0, 0,
            "",
            FredkinCell());

        l.print();
        for(int i=0;i<3;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

    //Cell 2x2
    try{
        Life<Cell> l(2, 2,
            "0-\n"
            "-0",
            new FredkinCell());

        l.print();
        for(int i=0;i<5;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

    //Cell 3x4
    try{
        Life<Cell> l(4, 3,
            "..**"
            "*..*"
            "**..",
            new ConwayCell());

        l.print();
        for(int i=0;i<10;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }
    //Cell 10x10
    try{
        Life<Cell> l(10, 10,
            "-0---0-00-\n"
            "-00-0--0-0\n"
            "0000000000\n"
            "----------\n"
            "0------00-\n"
            "00--00-00-\n"
            "----00----\n"
            "00--00----\n"
            "00---00--0\n"
            "0-0-0-0-0-",
            new FredkinCell());

        l.print();
        for(int i=0;i<10;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

    //Cell 2x10
    try{
        Life<Cell> l(10, 2,
            "-0-0-0-0-0\n"
            "0-0-0-0-0-",
            new FredkinCell());

        l.print();
        for(int i=0;i<5;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

    //Cell 1x20
    try{
        Life<Cell> l(20, 1,
            "000--00--00-0-0-0--0",
            new FredkinCell());

        l.print();
        for(int i=0;i<5;++i)
            l.simulate();
    }
    catch(const invalid_argument&)
    {
        assert(false);
    }
    catch(const out_of_range&)
    {
        assert(false);
    }

    return 0;}
