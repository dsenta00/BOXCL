#ifndef REGISTRY_H
#define REGISTRY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRYNUM 8
const char registry[][3] = { "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7" };

int Registry(char *_reg)
{
	int i = 0;
	do
	{
		if (!strcmpi(_reg, registry[i]))
		{
			break;
		}
	} while (++i < REGISTRYNUM);

	if (i == 8)
	{
		printf("\n\tThis is not registry -> '%s'\n", _reg);
		i = -1;
	}

	return i;
}

#endif