// C helper library 

#ifndef UTILS_H
#define UTILS_H


#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>

#define CALL1(a,b) (a(b))
#define CALL2(a,b,c) (a(b,c))

static char randbuf[4];

uint32_t getrand() {

	getrandom(randbuf, 4, 0);

	uint32_t rand = randbuf[0] + (randbuf[1] << 8) + (randbuf[2] << 16) + (randbuf[3] << 24);

	return rand;
}

int string_IndexOf(char stack[], char find[]) // start => end
{
	int find_size = strlen(find);
	int stack_size = strlen(stack);



	for (size_t i = 0; i < stack_size; i += find_size) // do jumps with sizeof find
	{
		for (size_t fold = 0; fold < find_size; fold++) // iter over find
		{
			int fidx = i - fold; // start from the find beginning

			if (find[fold] == stack[i] && fidx >= 0 && fidx + find_size <= stack_size)
			{

				if (stack[fidx] == find[0])
				{

					int ifind = 0;
					for (size_t istack = fidx; istack < fidx + find_size; istack++)
					{

						if (stack[istack] == find[ifind])
						{
							if (ifind == find_size - 1) // checks count == find size?
								return fidx; // found
						}
						else
						{
							break; // break if char at stack istack pos != chat at find ifind pos
						}
						ifind++;
					}
				}
			}
		}
	}

	return -1;
}

char* string_Substring(char* string, int pos, int length)
{
	char* buf = (char*)malloc(length);
	//strset(buf, 0);

	if (buf == NULL)
		printf("ERR_NULL_MALLOC\n");

	int stral = pos + length;
	size_t bufpos = 0;

	for (size_t i = pos; i < stral; i++)
	{
		buf[bufpos++] = string[i];
	}
	buf[bufpos] = '\0';

	return buf;
}

char* file_ReadAllText(char const* _FileName)
{

	FILE* f = fopen(_FileName, "r");
	int fchar = 0;
	size_t buf_size = 0;
	char* buf = (char*)malloc(1);

	buf[0] = '0';

	while ((fchar = fgetc(f)) != -1)
	{
		char c = fchar;
		buf_size++;

		buf = (char*)realloc(buf, buf_size);

		buf[buf_size - 1] = c;
	}

	buf[buf_size] = 0;

	fclose(f);

	return buf;
}

#endif // !UTILS_H