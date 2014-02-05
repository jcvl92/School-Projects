// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------

#ifndef Collatz_h
#define Collatz_h

// --------
// includes
// --------

#include <iostream> // istream, ostream, endl
#include <cassert>  // assert
#include <map>	// map, student code
#include <stdexcept>	// out_of_range, student code

std::map<int, int> cache;// student code

// ------------
// collatz_read
// ------------

/**
 * reads two ints into i and j
 * @param r a  std::istream
 * @param i an int by reference
 * @param j an int by reference
 * @return true if that succeeds, false otherwise
 */
bool collatz_read (std::istream&, int&, int&);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length in the range [i, j]
 */
int collatz_eval (int, int);

// -------------
// collatz_print
// -------------

/**
 * prints the values of i, j, and v
 * @param w a std::ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print (std::ostream&, int, int, int);

// -------------
// collatz_solve
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void collatz_solve (std::istream&, std::ostream&);

// ---------------
// collatz_compute
// ---------------

/**
 * computes the cycle length of a single value
 * @param num the number to compute the cycle length of
 * @param length the current value of the length being computed
 */
int collatz_compute(int);

#endif // Collatz_h

//end collatz.h

//begin collatz.c++

// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

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

//end collatz.c++

//begin RunCollatz.c++

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

// ----
// main
// ----

int main () {
    using namespace std;
//  ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    collatz_solve(cin, cout);
    return 0;}
