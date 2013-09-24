/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: File Fragmentation (110306)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <cstring>
using namespace std;

class Backtracker
{

public:
	vector<string> fragments;
	unsigned int fileLength;
	string partialSolution;
	bool done;
	int bitCountsZero[300];
	int bitCountsOne[300];

	Backtracker(unsigned int fileLen, vector<string> fragments)
	{
		this->fragments = fragments;
		this->fileLength = fileLen;
		this->done = false;

		for(int i = 0; i < fileLength; i++)
		{
			bitCountsZero[i] = 0;
			bitCountsOne[i] = 0;
		}

		// Count 1's and 0's at each position of each fragment
		for(int i = 0; i < fragments.size(); i++)
		{
			for(int j = 0; j < fragments[i].length(); j++)
			{
				// Count with the fragment left aligned with the full file string
				// For when this fragment might be the left side of the file
				if(fragments[i][j] == '1')
					bitCountsOne[j]++;
				if(fragments[i][j] == '0')
					bitCountsZero[j]++;
				
				// Count with the fragment right aligned with the full file string
				// For when this fragment might be the right side of the file
				if(fragments[i][fragments[i].length() - j - 1] == '1')				
					bitCountsOne[fileLength - j - 1]++;
					
				if(fragments[i][fragments[i].length() - j - 1] == '0')
					bitCountsZero[fileLength - j - 1]++;
			}
		}
	}
	
	void backtrack()
	{	
		vector<char> candidates;
		
		if(isSolution())
		{
			this->processSolution();
			return;
		}
		constructCandidates(&candidates);
		for(int i = 0; i < candidates.size(); i++)
		{
			partialSolution.push_back(candidates.at(i)); // Try this candidate
			backtrack();
			partialSolution = partialSolution.substr(0, partialSolution.length() - 1); // Revert candidate choice
			if(done)
				return;
		}
	}

	bool isSolution()
	{
		// If the partial solution is now a full candidate ...
		if(partialSolution.size() == fileLength)
		{
			int agreements[300];
			for(int i = 0; i < fileLength; i++)
			{
				agreements[i] = 0;
			}

			// Count how many times each bit in the candidate solution is aligned with each fragment
			for(int i = 0; i < fragments.size(); i++)
			{
				for(int j = 0; j < fragments[i].length(); j++)
				{
					// Left align the fragment against the partial solution
					if(fragments[i][j] == partialSolution[j])
						agreements[j]++;
						
					// Right align the fragment against the partial solution
					if(fragments[i][fragments[i].length() - j - 1] == partialSolution[fileLength - j - 1])
						agreements[fileLength - j - 1]++;
				}
			}
			
			int votes = 0;
			for(int i = 0; i < fragments.size(); i++)
			{
				bool validSolution = false;
				// Fragment matches left side of the candidate solution?
				if(partialSolution.substr(0, fragments[i].length()) == fragments[i])
				{
					// Attempt to find a matching right side fragment
					for(int j = 0; j < fragments.size(); j++)
					{
						if(j==i)
							continue;
						string matcher = fragments[i];
						matcher.append(fragments[j]);
						if(matcher == partialSolution) // Found two fragments which match partial solution, they vote for the solution
						{
							validSolution = true;
							votes++;
						}
					}
				}

				// Fragment matches right side of the candidate solution?
				if(partialSolution.substr(partialSolution.length() - fragments[i].length(), fragments[i].length()) == fragments[i])
				{
					// Attempt to find a matching left side fragment
					for(int j = 0; j < fragments.size(); j++)
					{
						if(j==i)
							continue;
						string matcher = fragments[j];
						matcher.append(fragments[i]);
						if(matcher == partialSolution) // Found two fragments which match partial solution, they vote for the solution
						{
							validSolution = true;
							votes++;
						}
					}
				}
				if(!validSolution)
				{
					return false;
				}
			}
			// Enough matches were found so this is a winner
			return votes >= fragments.size();
		}
		return false;
	}

	void processSolution()
	{
		done = true;
		cout<<partialSolution<<endl;
	}

	void constructCandidates(vector<char>* candidates)
	{
		if(partialSolution.size() == fileLength)
			return;
		// Some good pruning eliminates a huge amount of the search space
		if(bitCountsOne[partialSolution.size()]  > bitCountsZero[partialSolution.size()])
		{
			candidates->push_back('1');
		}
		else if(bitCountsOne[partialSolution.size()]  < bitCountsZero[partialSolution.size()])
		{
			candidates->push_back('0');
		}
		else
		{
			candidates->push_back('1');
			candidates->push_back('0');
		}
	}
};

int main()
{
	int cases;
	char line[300];
	cin>>cases;
	cin.getline(line, 300);
	cin.getline(line, 300);

	bool firstCase = true;
	while(cases-- > 0)
	{
		vector<string> fragments;
		string file;
		int fragLen = 0;
		int lowest = 300;
		int highest = 0;
		if(!firstCase)
			cout<<"\n";
			
		// Read in the fragments
		while(!cin.eof())
		{
			firstCase = false;
			cin.getline(line, 300);
			if(strlen(line) > 0)
			{
				string s;
				for(int i = 0; line[i] != 0; i++)
				{
					if(line[i] == '1' || line[i] == '0')
						s.push_back(line[i]);
				}
				fragments.push_back(s);
				
				// For computing solution length
				if(fragments.back().length() < lowest)
					lowest = fragments.back().length();
				if(fragments.back().length() > highest)
					highest = fragments.back().length();

				fragLen += fragments.back().length();
			}
			else
			{
				break;
			}
		}
		int fileLength = highest+lowest;
		Backtracker bt(fileLength, fragments);
		bt.backtrack();
	}


	return 0;
}