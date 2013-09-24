/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Factovisors (110704)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

struct factor
{
        int prime;
        int count;
};

// OK since max is small
bool isPrime(int n)
{
        for(int i = 2; i < n; i++)
        {
                if(n % i == 0)
                        return false;
        }
        return true;
}

// Simple prime number generation
void generatePrimes(vector<int>* target, int max)
{
        for(int n = 2; n <= max; n++)
        {
                if(isPrime(n))
                        target->push_back(n);
        }
}

// Prime factorization
void getFactors(vector<int>* primes, vector<factor>* factors, int n)
{
        for(int i = 0; i < primes->size(); i++)
        {
                factor f;
                f.prime = primes->at(i);
                f.count = 0;

				// Cannot possibly divide evenly into n
                if(f.prime > n)
                        break;
				// Count up how many times this current prime goes into n
                while(n % f.prime == 0)
                {
                        n /= f.prime;
                        f.count++;
                }
				
				// Non-zero count factor is a part of the prime factorization
                if(f.count != 0)
                        factors->push_back(f);
        }
        if(n > 1)
        {
                factor f;
                f.prime = n;
                f.count = 1;
                factors->push_back(f);
        }
}
int multiplicity(int n, int prime)
{
        int sum = 0;
        int curMult = prime;
        while(curMult <= n)
        {
                sum += n / curMult;
                curMult *= prime;
        }
        return sum;
}
bool dividesFactorial(int n, int factorial, vector<int>* primes)
{
        if(factorial == 0 || n == 0)
        {
                if(n==1)
					return true;
                else
					return false;
        }
        vector<factor> factors;
        getFactors(primes, &factors, n);
        for(int i = 0; i < factors.size(); i++)
        {
                factor f = factors.at(i);
                if(f.count > multiplicity(factorial, f.prime))
                        return false;
        }
        return true;
}

int main()
{
        int n, f;

        vector<int> primes;
        generatePrimes(&primes, 60000);

        while ( scanf ("%d %d", &f, &n) != EOF )
        {
                if(dividesFactorial(n, f, &primes))
                        cout<<n<<" divides "<<f<<"!"<<endl;
                else
                        cout<<n<<" does not divide "<<f<<"!"<<endl;

        }
        return 0;
}