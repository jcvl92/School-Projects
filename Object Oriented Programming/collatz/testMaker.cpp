#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	srand(4872);
	for(int i=1;i<=1000;i++)
	{
		int num1;
		cout << (num1=rand()%(i*1000));
		cout  << ' ' << (num1+rand()%(i*1000-num1)) << endl;
	}
	return 0;
}
