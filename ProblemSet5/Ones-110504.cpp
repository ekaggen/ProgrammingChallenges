/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Ones (110504)
	
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
        while(fgets(line, sizeof(line), stdin) != NULL)
        {
                line[strlen(line) - 1] = '\0';
                unsigned int n = atoi(line);
                int r = 0;
                int div = 0;
                int digits = 0;
                do
                {
                        div = r * 10 + 1;
                        r = div % n;
                        digits++;
                }
                while(r != 0);
                cout<<digits<<endl;
        }
        return 0;
}