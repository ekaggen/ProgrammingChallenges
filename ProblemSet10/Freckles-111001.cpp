/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Freckles (111001)
	
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
#include <iomanip>
#include <math.h>
using namespace std;

struct freckle
{
	double x;
	double y;
	bool used;

	freckle()
	{
	}
	freckle(double x, double y)
	{
		this->x = x;
		this->y = y;
		this->used = false;
	}
};

int main()
{
	double x,y;
	int cases;
	int nFreckles;
	char line[5];
	freckle freckles[100];
	cin>>cases;
	cin.getline(line, 5);
	cin.getline(line, 5);

	cout.setf(ios::fixed, ios::floatfield);
	cout.setf(ios::showpoint);

	bool firstCase = true;
	while(cases-- > 0)
	{
		if(!firstCase)
			cout<<"\n";
		firstCase = false;
		cin>>nFreckles;


		for(int i = 0; i < nFreckles; i++)
		{
			cin>>x;
			cin>>y;
			freckles[i] = freckle(x,y);
		}
		double sum = 0;
		
		vector<freckle*> mst;
		mst.push_back(&freckles[0]);
		freckles[0].used = true;

		// Simply build a minimum spanning tree
		while(mst.size() < nFreckles)
		{
			double nextBestLength = 0;
			freckle* nextBest = NULL;
			for(int i = 0; i < mst.size(); i++)
			{
				for(int j = 0; j < nFreckles; j++)
				{
					if(freckles[j].used)
						continue;

					// How much ink to connect these two?
					double length = sqrt((mst[i]->x - freckles[j].x)*(mst[i]->x - freckles[j].x)+(mst[i]->y - freckles[j].y)*(mst[i]->y - freckles[j].y));
					if(nextBest == NULL || length < nextBestLength)
					{
						nextBest = &freckles[j];
						nextBestLength = length;
					}
				}
			}
			sum += nextBestLength;
			mst.push_back(nextBest);
			nextBest->used = true;
		}
		cout<<setprecision(2)<<sum<<endl;
	}


	return 0;
}