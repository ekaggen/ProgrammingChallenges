/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: The 3n + 1 problem (110101)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/
#include <stdlib.h>
#include <stdio.h>

/* Calculate number of operations to reach n=1 using 3n+1 operation */
int calcCycles(int n)
{
	/* Invariant for this given problem */
	if(n > 1000000 || n < 0)
		return -1;
	
	int cycles = 1;
	
	/* For given invariant will never loop infinite */
	while(n > 1)
	{
		if(n % 2 == 0)
		{
			n /= 2;
		}
		else
		{
			n = 3 * n + 1;
		}
		cycles++;
	}
	return cycles;
}
int main()
{
	int i, j, n, start, end, max, cycles;
	while ( scanf ("%d %d", &i, &j) != EOF )
	{
		/* Handle case for out of order numbers */
		start = i;
		end = j;
		if(j < i)
		{
			start = j;
			end = i;
		}
		max = 0;
		
		/* Find max cycles for given input */
		for(n = start; n <= end; n++)
		{
			cycles = calcCycles(n);
			if(cycles > max)
			{
				max = cycles;
			}
		}
		printf("%i %i %i\n", i, j, max);
	}
}