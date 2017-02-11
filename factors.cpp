#include <iostream>
#include <sys/time.h>
#include <ctype.h>
#include "InfInt.h"
#include <algorithm>


using namespace std;


char* getCmdOption(char ** begin, char ** end, const string & option)
{
	char ** itr = find(begin, end, option);
	if (itr != end && ++itr != end)
	{
		return *itr;
	}
	return 0;
}

bool cmdOptionExists(char** begin, char** end, const string& option)
{
	return find(begin, end, option) != end;
}

void factors(InfInt n) {
	InfInt z = 2;
	while (z * z <= n) {
		if (n % z == 0) {
			cout << z << " ";
			n /= z;
		} else {
			z++;
		}
	}
	if (n > 1) {
		cout << n << endl;
	}
}

int main(int argc, char *argv[])
{
	InfInt a = atoll(argv[1]);
	bool quiet;

	struct timeval tv_before, tv_after;

	if(cmdOptionExists(argv, argv+argc, "-q"))
	{
		quiet = true;
	}
	
	if ( !quiet ) cout << a << ": ";

	gettimeofday(&tv_before, 0);
	factors(a);
	gettimeofday(&tv_after, 0);

	if ( !quiet ) printf("\033[35mTook %ld µs\033[0m\n",
			((tv_after.tv_sec - tv_before.tv_sec)*1000000L
				+tv_after.tv_usec) - tv_before.tv_usec );

	return 0;
}