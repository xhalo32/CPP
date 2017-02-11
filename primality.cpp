#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <math.h>


using namespace std;



bool IsPrimeByBruteForce(int number)
{
	if(number<2)
		return false;
	for(int i=2; i<number; i++)
	{
		//A number "number" is divisible by another number "i"
		//if the rest of the division of number divided i equals to zero
		if(number%i==0)
			return false;
	}
	//If no exist a number between 2 and number-1 that divides number
	return true;
}

bool IsPrimeOptimizationOne(int number)
{
	if(number<2)
		return false;
	if(number==2)
		return true;
	for(int i=2;i<=number/2;i++)
	{
		if(number%i==0)
			return false;
	}
	//If no exist a number between 2 and number/2 that divides number
	return true;
}

bool IsPrimeOptimizationTwo(int number)
{
	if(number<2)
		return false;
	if(number==2)
		return true;
	//sqrt() function is defined in cmath library (#include&ltcmath&gt)
	for(int i=2;i<=sqrt(number);i++)
	{
		if(number%i==0)
			return false;
	}
	//If no exist a number between 2 and number/2 that divides number
	return true;
}

bool IsPrimeOptimizationThree(long number)
{
	if(number<2)
		return false;
	if(number==2)
		return true;
	if(number%2==0)
		return false;
	for(int i=3;i<=sqrt(number);i += 2)
	{
		if(number%i==0)
			return false;
	}
	return true;
}

bool * SieveOfEratosthenes(int number)
{
	bool * prime = new bool[number+1];
	for(int i=0;i<=number;i++)
		prime[i] = true;
	//0 and 1 are not prime, and we mark because we do not check in the algorithm
	//(because will cause bad results, if we divide by 0, we go to hell, and if we divide one by one, we will mark all numbers a nonprime.
	prime[0] = false;
	prime[1] = false;
	int squareRoot = sqrt(number);
	for(int i=2;i<=squareRoot;i++)
	{
		//If is gray (Is prime)
		if(prime[i])
		{
			//We start j by the next multiple of i (that is: 2*i), and we increase it by i each time until j is less than or equal to sqrt(number)
			for(int j=2*i;j<=number; j += i)
				prime[j] = false;
		}
	}
	return prime;
}




int main( int argc, char *argv[] )
{
	struct timeval tv_before, tv_after;

	unsigned long long a = atoll( argv[ 1 ] );
	bool prime_a;

	cout << a;
	cout << ": ";

	gettimeofday(&tv_before, 0);
	prime_a = IsPrimeOptimizationThree( a );
	gettimeofday(&tv_after, 0);
	
	cout << prime_a << "\n";


	printf("\033[35mTook %ld µs\033[0m\n",
			((tv_after.tv_sec - tv_before.tv_sec)*1000000L
					+tv_after.tv_usec) - tv_before.tv_usec
	);

	return 0;
}