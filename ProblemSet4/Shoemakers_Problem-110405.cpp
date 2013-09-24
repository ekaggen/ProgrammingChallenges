/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Shoemaker's problem  (110405)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

struct job
{
	int time;
	int penalty;
	int jobNum;
	job(int jobNum, int time, int penalty)
	{
		this->time = time;
		this->penalty = penalty;
		this->jobNum = jobNum;
	}
};

bool compareJobs(job a, job b)
{
	long long leftRatio = b.time*a.penalty;
	long long rightRatio = b.penalty*a.time;

	if(leftRatio == rightRatio)
	{
		return a.jobNum < b.jobNum;
	}
	return leftRatio > rightRatio;
}
int main()
{
	int n;
	int t,p;
	int cases;
	char line[30];
	cin>>cases;
	bool firstCase = true;

	while(cases-- > 0)
	{
		if(!firstCase)
			cout<<"\n";
		firstCase = false;
		cin>>n;

		// Read in the jobs
		vector<job> jobs;
		for(int i = 0; i < n; i++)
		{
			cin>>t;
			cin>>p;
			jobs.push_back(job(i+1, t,p));
		}

		// Sort by time penalty ratio
		sort(jobs.begin(), jobs.end(), compareJobs);

		for(int i = 0; i < jobs.size(); i++)
		{
			cout<<jobs[i].jobNum;
			if(i != jobs.size() - 1)
				cout<<" ";
		}
		cout<<"\n";

	}
	return 0;
}