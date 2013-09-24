/* 
	Solution to Programming Challenges Problem
	http://www.programming-challenges.com
	
	Author: Eric Kaggen
	Problem: Interpreter (110106)
	
	This solution favors readability over elegance. The
	assumption is made that program input follows supplied
	specifications. Handling of boundary cases outside of the
	specifications is omitted. This is meant for fun rather than
	practical use. Code style reflects the purpose of the code.
*/
#include <stdlib.h>
#include <stdio.h>
int main()
{
	int runs, curInstruction, n, i, j, r, instruction[3], reg[10], ram[1000];
	char line[5];
	fgets(line, 5, stdin);
	runs = atoi(line);
	fgets(line, 5, stdin);
	
	/* For each input set */
	for(r = 0; r < runs; r++)
	{
		/* Zero out all registers and memory */
		memset(reg, 0, 10*sizeof(int));
		memset(ram, 0, 1000*sizeof(int));

		i = 0;
		
		/* Load instructions into memory */
		while( fgets(line, 5, stdin) != NULL)
		{
			if(line[0] != '\n')
			{
				ram[i++] = atoi(line);;
			}
			else
			{
				break;
			}
		}
		i = 0;
		n = 0;
		
		/* Execute the program until halt */
		while(1)
		{
			n++;
			curInstruction = ram[i];
			if(curInstruction == 100)
			{
				printf("%d\n", n);
				if(r < runs - 1)
					printf("\n");
				break;
			}
			
			/* Decode instruction */
			instruction[2] = curInstruction % 10;
			instruction[1] = (curInstruction / 10) % 10;
			instruction[0] = curInstruction / 100;

			switch(instruction[0])
			{
				case 2:
					reg[instruction[1]] = instruction[2];
					break;
				case 3:
					reg[instruction[1]] += instruction[2];
					reg[instruction[1]] = reg[instruction[1]] % 1000;
					break;
				case 4:
					reg[instruction[1]] *= instruction[2];
					reg[instruction[1]] = reg[instruction[1]] % 1000;
					break;
				case 5:
					reg[instruction[1]] = reg[instruction[2]];
					reg[instruction[1]] = reg[instruction[1]] % 1000;
					break;
				case 6:
					reg[instruction[1]] += reg[instruction[2]];
					reg[instruction[1]] = reg[instruction[1]] % 1000;
					break;
				case 7:
					reg[instruction[1]] *= reg[instruction[2]];
					reg[instruction[1]] = reg[instruction[1]] % 1000;
					break;
				case 8:
					reg[instruction[1]] = ram[reg[instruction[2]]];
					break;
				case 9:
					ram[reg[instruction[2]]] = reg[instruction[1]];
					break;
				case 0:
					if(reg[instruction[2]] != 0)
						i = reg[instruction[1]];
					else
						i++;
					continue;
				default:
					break;
			}
			i++;
		}
	}
}