#include <iostream>
using namespace std;


int main()
{
	srand(time(0));
	long total;
	double totalnine = 0;

	long ceiling = 1000000000;
	long minrand = 1;
	long maxrand = 10;
	// 1B 1-10 converges to 99%

	double times = 100000;

	for (int i = 0; i < times; ++i)
	{
		total = rand()%(maxrand-minrand) + minrand;
		while (total < ceiling)
		{
			total *= rand()%(maxrand-minrand) + minrand;
		}
		if (total % 9 == 0) ++totalnine;
	}
	cout<<totalnine<<endl;
	cout<<times<<endl;

	cout<<"Percentage: "<<100*totalnine/times<<"%"<<endl;


	return 0;
}