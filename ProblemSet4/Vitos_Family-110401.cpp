/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Vito's Family (110401)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/
#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;

int main()
{
		int cases, nRelatives, house;

		cin>>cases;
		while(cases-- > 0)
		{
			vector<int> relatives;
			cin>>nRelatives;
			
			// Read in the relatives
			for(int i = 0; i < nRelatives; i++)
			{
				cin>>house;
				relatives.push_back(house);
			}

			sort(relatives.begin(), relatives.end());

			// Much larger than the input range
			int bestDist = (1<<30);
			
			int bestStreetNum = 0;
			
			// Find the minimal distance
			for(int s = relatives.front(); s <= relatives.back(); s++)
			{
				int distance = 0;
				for(int i = 0; i < relatives.size(); i++)
				{
					distance += abs(s - relatives[i]);
					if(distance > bestDist)
						break;
				}
				if(distance < bestDist)
				{
					bestStreetNum = s;
					bestDist = distance;
				}
				else if(distance > bestDist)
				{
					break;
				}
			}
			cout<<bestDist<<endl;
		}
        return 0;
}