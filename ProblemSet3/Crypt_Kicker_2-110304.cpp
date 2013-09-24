/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Crypt Kicker II (110304)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;


int main()
{
	int cases;
	int nLines;
	char *line;
	
	// Sorted form of "the quick brown fox jumps over the lazy dog"
	char refHashCode[] = "abc defgh ijklm nko peqrs ktcj abc uvwx ykz";
	char lines[200][200];
	char alphabet[26];
	cin >> cases;

	cin.ignore();
	cin.ignore();
	while(cases-- > 0)
	{
		nLines = 0;
		bool foundAlphabet = false;
		
		// Attempt to find the alphabet by finding a string which matches our ref string
		// in spacing and has all unique letters.
		while(1)
		{
			line = lines[nLines];
			cin.getline(line, sizeof(lines[nLines]));
			if(line[0] == '\0') // For empty string
			{
				break;
			}
			if(!foundAlphabet)
			{
				memset(alphabet, '\0', sizeof(alphabet));
				char nextChar = 'a';
				int i = 0;
				bool viable = true;
				while(*line != '\0')
				{
					// Space misalignment?
					if(*line == ' ')
					{
						if(refHashCode[i] != ' ')
						{
							viable = false;
							break;
						}
					}
					else if(*line == '\n' || *line == '\r') // Try the next line
					{
						line++;
						continue;
					}
					else
					{
						if(alphabet[*line - 'a'] == '\0')
						{
							alphabet[*line - 'a'] = nextChar++;
						}
						if(alphabet[*line - 'a'] != refHashCode[i])
						{
							viable = false;
							break;
						}
					}
					i++;
					line++;
				}
				if(i < strlen(refHashCode))
				{
					viable = false;
				}

				// Map the found string to the known reference string to generate a lookup table
				if(viable)
				{
					int mappings[] = {36,10,7,40,2,16,42,1,6,20,8,35,22,14,17,23,4,11,24,0,21,27,13,18,38,37};
					line = lines[nLines];

					for(int x = 0; x < 26; x++)	alphabet[line[mappings[x]] - 'a'] = 'a' + x;
					foundAlphabet = true;
				}
			}
			nLines++;
		}

		// If found then decrypt all
		if(foundAlphabet)
		{
			for(int i = 0; i < nLines; i++)
			{
				for(int j = 0; j < strlen(lines[i]); j++)
				{
					if(isalpha(lines[i][j]))
					{
						cout<<alphabet[tolower(lines[i][j]) - 'a'];
					}
					else
					{
						cout<<lines[i][j];
					}
				}
				cout<<"\n";
			}
		}
		else
		{
			cout<<"No solution."<<endl;
		}
		if(cases > 0)
		{
			cout<<"\n";
		}
	}
	return 0;
}