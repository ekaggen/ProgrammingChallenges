/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Selfdescribing Sequence (110607)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/

#include <iostream>
#include <stdio.h>
using namespace std;

int dp[700000];
int main()
{
        dp[0] = 1;
		dp[1] = 2;
		dp[2] = 4;
		
		// Precompute function for potential input range (DP)
		for(int i = 1; dp[dp[i-1]] < 2000000000; i++)
		{
			for(int j = dp[i]; j < dp[i+1]; j++)
			{
				dp[j] = dp[j-1] + i + 1;
			}
		}

		int n;
		while ( scanf ("%d", &n) != EOF )
		{
			if(n == 0)
				break;
			// Now print the first f(n) that surpasses n
			for(int i = 0; i < 700000; i++)
			{
				if(n < dp[i])
				{
					cout<<i<<endl;
					break;
				}
			}
		}
        return 0;
}