#include <iostream>
using namespace std;



int main()
{
	try 
	{
		int age_mother = 40;
		int age_son = 5;

		int age_old_chap = 100/0;

		if (age_son > age_mother)
		{
			throw 99;
		}


	}catch (int errornum)
	{
		cout << "Err " << errornum << endl;

		if (errornum == 99) cout << "ERR 99: Mother can not be younger than her son" << endl;
	}
}
