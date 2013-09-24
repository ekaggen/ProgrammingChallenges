/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Jolly Jumpers (110201)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/
#include <stdlib.h>
#include <stdio.h>

// Simple routine to tokenize and then convert to int
int nextInt(char **buf)
{
	int i;
	char theInt[12];
	for(i = 0; i < sizeof(theInt); i++)
	{
		if(((*buf)[i] < 48 || (*buf)[i] > 57) && (*buf)[i] != '-')
		{
			theInt[i] = '\0';
			*buf += (i + 1);
			break;
		}
		theInt[i] = (*buf)[i];
	}
	return atoi(theInt);
}
int main()
{
	int diff;
	int i;
	char line[75000];
	char *cursor;
	int jollyTrack[3000];
	while(1)
	{
		if(fgets(line, sizeof(line), stdin) == NULL)
		{
			break;
		}
		cursor = line;
		int count = nextInt(&cursor);
		
		// Always jolly
		if(count < 1)
		{
			printf("Jolly\n");
			continue;
		}
		int jollyCount = 0;
		
		// Zero out the jolly tracking array
		for(i = 0; i < count - 1; i++)
		{
			jollyTrack[i] = 0;
		}
		
		// Track the last seen number
		int last = nextInt(&cursor);
		for(i = 1; i < count; i++)
		{
			int num = nextInt(&cursor);
			diff = abs(num - last);
			if(diff >= count)
			{
				break;
			}
			
			// Checking if we've seen this abs value before
			if(jollyTrack[diff - 1] == 0)
			{
				jollyTrack[diff - 1] = 1;
				jollyCount++;
			}
			else
			{
				break; // Duplicates aren't jolly
			}			
			last = num;
		}

		if(jollyCount == count - 1)
		{
			printf("Jolly\n");
		}
		else
		{
			printf("Not jolly\n");
		}
	}
	return 0;
}