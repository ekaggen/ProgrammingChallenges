/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: The Archaeologist's Dilemma  (110503)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;
int main()
{
        char line[255];
		
		// For converting between bases
        double baseLog = log2(10);
        while(fgets(line, sizeof(line), stdin) != NULL)
        {
                line[strlen(line) - 1] = '\0';
                unsigned int n = atoi(line);
                double l1 = log2(n);
                double l2 = log2(n+1);

				// Loop through potential exponents
                for(int k = strlen(line) + 1; k < 8000000; k++)
                {
						// Exploit some properties of logarithms to keep numbers manageable
                        double high = k * baseLog + l2;
                        double low = k * baseLog + l1;
						
						// Test when it straddles the power of 2
                        if(floor(high) == ceil(low))
                        {
                                cout <<(int)high<<endl;
                                break;
                        }
                }
        }
        return 0;
}