/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Stack 'em Up (110205)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct shuffle
{
	int ordering[52];
};

// Just so we can easily initialize a deck
struct deck
{
	int cards[52];
	deck()
	{
		for(int i = 0; i < 52; i++)
		{
			this->cards[i] = i+1;
		}
	}
};
int main()
{
	int n;
	int cases;
	char line[30];
	cin>>cases;
	bool firstCase = true;

	string types[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
	string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
	while(cases-- > 0)
	{
		deck currentDeck;

		vector<shuffle> shuffles;
		cin>>n;

		// Read in each shuffle order
		for(int i = 0; i < n; i++)
		{
			shuffle s;
			for(int c = 0; c < 52; c++)
			{
				cin>>s.ordering[c];
			}
			shuffles.push_back(s);
		}
		cin.getline(line, 30); // Next line
		
		// Replay each shuffle observed
		while(true)
		{
			cin.getline(line, 30);

			int a = atoi(line);
			if(a==0)
				break;

			deck newDeck = currentDeck;
			for(int i = 0; i < 52; i++)
			{
				newDeck.cards[i] = currentDeck.cards[shuffles[a-1].ordering[i]-1];
			}
			currentDeck = newDeck;
		}

		if(!firstCase)
			cout<<"\n";
		firstCase = false;
		
		// Print the deck
		for(int i = 0; i < 52; i++)
		{
			cout<<types[(currentDeck.cards[i]-1) % 13]<<" of "<< suits[(currentDeck.cards[i]-1) / 13]<<endl;
		}
	}
	return 0;
}