/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Marbles (110707)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/

#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
        int n, c1, n1, c2, n2, tmp;

        int out1 = 0;
        int out2 = 0;
        while(true)
        {
                scanf("%d", &n);
                if(n == 0)
                        break;
                scanf("%d %d", &c1, &n1);
                scanf("%d %d", &c2, &n2);

                bool swapped = false;

				// Swap the input values in the case that they're out of order. We swap back later for output.
                if((float)(((float)n1/(float)c1)) <= (float)(((float)n2/(float)c2)))
                {
                        tmp = c1;
                        c1 = c2;
                        c2 = tmp;
                        tmp = n1;
                        n1 = n2;
                        n2 = tmp;
                        swapped = true;
                }

				// Fit as many as possible into the cost effective "cheap" boxes
                int maxCheap = n / n1;
                int leftOver = n % n1;

				int nBackoff = 0;
				
				// Fit the rest into the other boxes
				int initialOther = leftOver / n2;
				
				// Now we may have some left over
				int remainder = leftOver % n2;
				if(remainder > 0)
				{
					int backoff = n1 % n2;

					if(n2 > n1)
					{
							backoff = n1;
					}

					
					int extra = n2 - remainder;
					// Now we solve nBackoff*backoff % n2 == extra

					for(nBackoff = 0; nBackoff <= n2; nBackoff++)
					{
							if((nBackoff*backoff % n2) == extra)
									break;
					}
				}
				
				// Reduce cheap boxes by enough so that the remainder not in cheap boxes can fit evenly into the other type
                out1 = maxCheap - nBackoff;
                out2 = (n - (out1*n1))/n2;

				if(out1 < 0) out1 = 0;
				if(out2 < 0) out2 = 0;
                if(out1*n1+out2*n2 != n)
                {
                        cout<<"failed"<<endl;
                }
                else
                {
                        if(swapped)
						{
                                tmp = out1;
                                out1 = out2;
                                out2 = tmp;
                        }
                        cout<<out1<<" "<<out2<<endl;
                }
        }
        return 0;
}