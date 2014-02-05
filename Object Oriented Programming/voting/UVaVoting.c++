// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif


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
#include <stdio.h>	//EOF

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
 * @param votes a vector of int arrays
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
 * @param votes a vector of int arrays
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

// ------------
// voting_read
// ------------

bool voting_read(std::istream& in, int& candidateNum, int& ballotNum, struct Candidate candidates[20], int votes[1000][20])
{
	in >> candidateNum;
	assert(candidateNum>0 && candidateNum<=20);

	in.ignore(INT_MAX, '\n');	//flush the input

	for(int i=0;i<candidateNum;++i)
	{
		getline(in, candidates[i].name);
	}

	for(int i=0;;++i)
	{
		for(int j=0;j<candidateNum;++j)
		{
			in >> votes[i][j];
		}

		++ballotNum;

		//check for a blank line or end of file
		in.ignore(INT_MAX,'\n');
		if(in.peek()=='\n' || in.peek() == '\r' || in.peek()==EOF) break;
	}

	return true;
}

// ------------
// voting_eval
// ------------

string voting_eval(int candidateNum, int ballotNum, struct Candidate candidates[20], int votes[1000][20])
{
	//iterate over all votes and reference them in the candidates
	for(int i=0;i<ballotNum;++i)
	{
		candidates[votes[i][0]-1].votes.push_back(votes[i]);
	}

	return voting_determineWinner(candidates, candidateNum, ballotNum);
}

// -------------
// voting_determineWinner
// -------------

string voting_determineWinner(Candidate candidates[20], int candidateNum, int ballotNum)
{
	deque<Candidate*> losers;
	int tieValue;
	bool tie=false;
	string winners="";

	//check for a winner
	for(int i=0;i<candidateNum;++i)
	{
		if((int)candidates[i].votes.size() > ballotNum/2)
			return candidates[i].name+'\n';
	}

	//check for a tie
	for(int i=0;i<candidateNum;++i)
	{
		//set tie value equal to the first candidate with a non-zero vote count
		if(!candidates[i].votes.empty())
		{
			tieValue = candidates[i].votes.size();
			break;
		}
	}
	for(int i=0;i<candidateNum;++i)
	{
		if((int)candidates[i].votes.size()==tieValue)
			tie=true;
		else if(!candidates[i].votes.empty())
		{
			tie=false;
			break;
		}
	}
	if(tie)
	{
		for(int i=0;i<candidateNum;++i)
		{
			if(!candidates[i].votes.empty())
				winners += candidates[i].name+'\n';
		}
		return winners;
	}

	//look for the candidate with the lowest amount of votes so we can redistribute their votes
	int q;
	for(q=0;q<candidateNum;++q)
	{
		//push on the first candidate with a non-zero vote count
		if(!candidates[q].votes.empty())
		{
			losers.push_back(candidates+q);
			break;
		}
	}

	for(int i=q+1;i<candidateNum;++i)
	{
		if(!candidates[i].votes.empty())//if the candidate has no votes, they are out of the race already
		{
			if(candidates[i].votes.size() < losers[0]->votes.size())
			{
				//clear the vector
				losers.clear();

				//and push the new candidate on
				losers.push_back(candidates+i);
			}
			else if(candidates[i].votes.size() == losers[0]->votes.size())
			{
				//push the candidate onto the vector
				losers.push_back(candidates+i);
			}
		}
	}

	//mark all as winners
	for(int i=0;i<candidateNum;++i)
		candidates[i].isLoser = false;

	//now, mark the true losers
	for(int i=0;i<(int)losers.size();++i)
		losers[i]->isLoser = true;

	//reallocate the votes of the losers
        int ballotOffset;
        for(int i=0;i<(int)losers.size();++i)
        	while(!losers[i]->votes.empty())
                {
                        ballotOffset=1;


                        //if the destination is a loser or has 0 votes, skip that vote
			while(candidates[losers[i]->votes.front()[ballotOffset]-1].isLoser ||
				candidates[losers[i]->votes.front()[ballotOffset]-1].votes.empty())
				++ballotOffset;

                        //push the pointer to the second vote of the top ballot onto the list of votes of the candidate it belongs to
                        candidates[losers[i]->votes.front()[ballotOffset]-1].votes.push_back(losers[i]->votes.front()+ballotOffset);

                        //delete that ballot from the list
                        losers[i]->votes.pop_front();
                }

        //recurse
        return voting_determineWinner(candidates, candidateNum, ballotNum);
}

// -------------
// voting_print
// -------------

void voting_print(std::ostream& out, string str)
{
	//print results
	out << str;
}

// -------------
// voting_solve
// -------------

void voting_solve(std::istream& in, std::ostream& out)
{
	int caseNum;
	in >> caseNum;

	//clear blankline
	in.get();

	for(int i=0;i<caseNum;++i)
	{
		int candidateNum, ballotNum=0;
		struct Candidate candidates[20];
		int votes[1000][20];

		voting_read(in, candidateNum, ballotNum, candidates, votes);
		const string rtrn = voting_eval(candidateNum, ballotNum, candidates, votes);
		voting_print(out, rtrn);
		if(i+1 != caseNum) cout << endl;
	}
}


// ----
// main
// ----

int main ()
{
	using namespace std;
//	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
	voting_solve(cin, cout);
	return 0;
}

