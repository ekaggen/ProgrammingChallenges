/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Reverse and Add (110502)
	
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

// Reverses the int by transforming it to a string backwards
void intToReversedString(unsigned int i, string *s)
{
	if(i == 0)
	{
		s->append(1, '0');
		return;
	}
	while(i != 0)
	{
		char digit = (i % 10) + '0';
		s->append(1, digit);
		i /= 10;
	}
}

// Hide the grossness
unsigned inline int atoui(const char *s)
{
	return (unsigned int)strtoul(s, NULL, 10);
}

// Reverse the int by converting it into a string and then back
unsigned int reverseInt(unsigned int i)
{
	string s;
	intToReversedString(i, &s);
	return atoui(s.data());
}
int main()
{
	char line[255];
	fgets(line, sizeof(line), stdin);

	int n = atoi(line);
	for(int i = 0; i < n; i++)
	{
		fgets(line, sizeof(line), stdin);
		
		// Compute the number and its reverse
		unsigned int num = atoui(line);
		unsigned int reverse = reverseInt(num);
		int count = 0;
		
		// Apply formula
		while(num != reverse)
		{
			num += reverse;
			reverse = reverseInt(num);
			count++;
		}
		cout<<count<<" "<<num<<endl;
	}
}