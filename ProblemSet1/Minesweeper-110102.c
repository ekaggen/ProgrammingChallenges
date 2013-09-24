/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Minesweeper (110102)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/
#include <stdlib.h>
#include <stdio.h>
#define increase(i, j) if(field[(i)][(j)] != -1) field[(i)][(j)]++
int main()
{
        int i, j, m, n, counter;
		
		/* Allocate extra 1 element border to act as a "sentinel" */
        int field[102][102];
        char line[100];
        counter = 1;

		int printNewline = 0;
        
        while(1)
        {
				/* Read header or terminate on EOF */
				if(scanf ("%d %d", &n, &m) == EOF)
					break;
					
				/* Input termination condition */
                if(n == 0 && m == 0)
                    break;
				
				/* Printing newline between lines */
				if(printNewline)
					printf("\n");
				else
					printNewline = 1;
					
				/* Read board into array */
                for(i = 1; i <= n; i++)
                {
                        scanf("%s", line);
                        for(j = 1; j <= m; j++)
                        {
                                field[i][j] = (line[j-1] == '.' ? 0 : -1);
                        }
                }
				
				/* For all fields, if its a mine increase all neighbor values by 1 */
                for(i = 1; i <= n; i++)
                {
                        for(j = 1; j <= m; j++)
                        {
                                if(field[i][j] == -1)
                                {
                                        increase(i-1, j-1);
                                        increase(i, j-1);
                                        increase(i-1, j);
                                        increase(i+1, j-1);
                                        increase(i-1, j+1);
                                        increase(i+1, j+1);
                                        increase(i+1, j);
                                        increase(i, j+1);
                                }
                        }
                }

				/* Print out the board, omitting the sentinel border */
                printf("Field #%i:\n", counter++);
                for(i = 1; i <= n; i++)
                {
                        for(j = 1; j <= m; j++)
                        {
                                if(field[i][j] == -1)
                                        printf("*");
                                else
                                        printf("%i", field[i][j]);
                        }
                        printf("\n");
                }
        }
}