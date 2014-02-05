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
#include <map>		// unordered_map, student code
#include <stdexcept>	// out_of_range, student code

#include "Collatz.h"

std::map<int, int> cache;// student code

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
	int maxLength = 0, lengthHolder, upper, lower;

	if(i <= j)
	{
		lower = i;
		upper = j;
	}
	else
	{
		lower = j;
		upper = i;
	}

	//check each value in the range and hold the max value
	for(long k=lower;k<=upper;k++)//iterate of each number starting at i and ending at j
	{
		if(cache.count(k))
			lengthHolder = cache[k];
		else
		{
			lengthHolder = collatz_compute(k);
			cache[k] = lengthHolder;
		}
		(lengthHolder > maxLength) ? maxLength = lengthHolder : true;
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
int collatz_compute(int input)
{
	long num = input;
	int cycleLength = 0;
	while(num > 1)
	{
		if(cache.count(num))
			return (cycleLength += cache[num]);
		else
		{
			if(num%2)
			{
				num = 3*num+1;
				cycleLength++;
			}
			else
			{
				num /= 2;
				cycleLength++;
			}
		}
	}
	return ++cycleLength;
}
