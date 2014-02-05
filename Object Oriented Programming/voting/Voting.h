#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <cassert>	//assert
#include <iostream>	//istream, ostream
#include <deque>	//deque
#include <vector>	//vector
#include <string>	//string
#include <climits>	//INT_MAX

using namespace std;

struct Candidate{
	string name;
	deque<int*> votes;
	bool isLoser;
};

// ------------
// voting_read
// ------------

/**
 * reads candidate and voting data
 * @param in a std::istream
 * @param candidateNum an int
 * @param ballotNum an int
 * @param candidates an array of struct Candidates
 * @param votes an array of arrays of ints
 * @return true if that succeeds, false otherwise
 */
bool voting_read(std::istream&, int&, int&, struct Candidate[20], int[1000][20]);

// ------------
// voting_eval
// ------------

/**
 * evaluates the votes for a winner
 * @param candidateNum an int
 * @param ballotNum an int
 * @param candidates an array of struct Candidates
 * @param votes an array of arrays of ints
 * @return a string of the winner's name
 */
string voting_eval(int, int, struct Candidate[20], int[1000][20]);

// -------------
// voting_print
// -------------

/**
 * prints the winner's name string
 * @param out a std::ostream
 * @param str the name of the winner
 */
void voting_print(std::ostream&, string);

// -------------
// voting_solve
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void voting_solve(std::istream&, std::ostream&);

// -------------
// voting_determineWinner
// -------------

/**
 * determines the winner
 * @param candidates an array of struct Candidates
 * @param candidateNum an int
 * @param ballotNum an int
 */
string voting_determineWinner(Candidate[20], int, int);


#endif // Voting_h
