// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

#include "Collatz.h"

// ------------
// collatz_read
// ------------

bool collatz_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);
    // ********** student code begin **********
	long maxLength = 0, lengthHolder;

	//check each value in the range and hold the max value
	for(long k=i;k<=j;k++)//iterate of each number starting at i and ending at j
	{
		lengthHolder = collatz_compute(k);
		if(lengthHolder > maxLength)
			maxLength = lengthHolder;
	}
	int v = maxLength;
    // ********** student code end **********
    //int v = 1;
    assert(v > 0);
    return v;}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

// ---------------
// collatz_compute
// ---------------
// ********** student coded function **********
long collatz_compute(long num)
{
	if(num == 1)
		return 1;
	if(num%2)	//if n is odd
		return collatz_compute(3*num+1) + 1;
	else		//if n is even
		return collatz_compute(num/2) + 1;
}
