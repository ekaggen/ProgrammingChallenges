/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Where's Waldorf? (110302)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/

#include <stdio.h>
#include <string.h>
#include <list>
#include <iostream>

#define MAX_GRID_ROWS 50
#define MAX_GRID_COLS 50
using namespace std;

// Finds a word in the supplied grid. Grid positions stored in buckets by their letter.
char* findWord(char *word, list<char*> alphaBuckets[26])
{
	char *position;
	int cols = MAX_GRID_COLS + 2;
	
	// Shortcut to allow looping over neighboring 8 squares
	int modifiers[] = {-cols, -cols + 1, 1, cols + 1, cols, cols - 1, -1, -cols - 1};

	int firstLetter = tolower(word[0]) - 'a';
	
	// Save some time by only looking at positions in the grid that are equal to the first letter
	for(list<char*>::iterator it = alphaBuckets[firstLetter].begin(); it != alphaBuckets[firstLetter].end(); it++)
	{
		// Search around this character
		for(int i = 0; i < 8; i++)
		{
			char *position = *it; // Go through board
			char *ptr = word; // Go through search term
			
			while(tolower(*position) == tolower(*ptr))
			{
				ptr++;
				if(*ptr == '\0')
				{
					return *it;
				}
				
				position += modifiers[i]; // Move in current direction to next letter
			}
		}
	}
	return NULL;
}
int main()
{
	int cases;
	int n, m, k;
	char line[100];
	char wordList[20][100];
	char grid[MAX_GRID_ROWS + 2][MAX_GRID_COLS + 2];

	list<char*> alphaBuckets[26];

	cin >> cases;

	while(cases-- > 0)
	{
		cin >> m;
		cin >> n;

		cin.getline(line, sizeof(line));

		// Fill sentinel
		memset(grid[0], '\0', n + 2);
		memset(grid[m + 1], '\0', n + 2);
		
		// Pre-processing to bucket grid positions by their letter
		for(int i = 1; i <= m; i++)
		{
			grid[i][0] = '\0'; // Set first char of line
			grid[i][n + 1] = '\0'; // Not really needed

			cin.getline(&grid[i][1], n + 1);

			for(int j = 1; j <= n; j++)
			{
				int pos = tolower(grid[i][j]) - 'a';
				alphaBuckets[pos].push_back(&grid[i][j]);
			}
		}

		cin >> k;
		cin.getline(line, sizeof(line));

		// Now just search for each word given
		for(int i = 0; i < k; i++)
		{
			cin.getline(line, sizeof(line));
			char* position = findWord(line, alphaBuckets);
			if(position != NULL)
			{
				// Found it
				size_t offset = (size_t)position - (size_t)grid;
				size_t i = offset / (MAX_GRID_COLS + 2);
				size_t j = offset - i * (MAX_GRID_COLS + 2);
				cout << i << " " << j<<endl;
			}
		}

		if(cases > 0)
		{
			cout<<"\n";
		}
	}
	return 0;
}