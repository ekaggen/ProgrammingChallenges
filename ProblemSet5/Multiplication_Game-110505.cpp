/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: A Multiplication Game (110505)
	
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
                bool stan = true;

                while(n != 1)
                {
                        if(stan)
                                n = ceil((double)n / 9.0);
                        else
                                n = ceil((double)n / 2.0);

						stan = !stan;
                }
                if(stan)
                        cout<<"Stan wins."<<endl;
                else
                        cout<<"Ollie wins."<<endl;
        }
        return 0;
}