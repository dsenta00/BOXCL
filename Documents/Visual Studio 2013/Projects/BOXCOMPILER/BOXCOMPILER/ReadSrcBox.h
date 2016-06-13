#ifndef READSRCBOX_H
#define READSRCBOX_H
#include "InputList.h"

int ReadSrcBox(char *_filename, InputList_p Head)
{
	int stat = 0;
	InputList_p q = NULL;
	InputList_p last = Head;
	char buffer[MAXTOKEN] = { 0 };

	FILE *fp = fopen(_filename, "r");

	if (fp)
	{
		printf("\n\tInvoking file.");

		while (!feof(fp))
		{
			//popravit za string i char
			fscanf(fp, " %s", buffer);
			q = inputList_makeNode(buffer);

			if (q)
			{
				last = inputList_add(last, q);
			}
			else
			{
				stat = -2;
				inputList_destruct(Head);
			}
		}
	}
	else
	{
		stat = -1;
		printf("\n\tFile \'%s\' don't exist at all.",_filename);
	}

	return stat;
}

#endif 