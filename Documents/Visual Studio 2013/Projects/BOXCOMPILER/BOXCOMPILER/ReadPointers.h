#ifndef READPOINTERS_H
#define READPOINTERS_H
#include "DataTree.h"
#include "InputList.h"

DataTree_p ReadPointerTreeFromInputList(DataTree_p _tree, InputList_p _head, int *stat)
{
	char *content = NULL;
	char dataname[MAXTOKEN] = { 0 };
	char type[MAXTOKEN] = { 0 };
	char initvalue[MAXTOKEN] = { 0 };
	DataTree_p q = NULL;
	int ID = 0;

	while (1)
	{
		content = inputList_pop(_head);

		if (!strcmpi(content, "@CODE"))
		{
			free(content);
			break;
		}
		else
		{
			strcpy(type, content);
			free(content);

			content = inputList_pop(_head);
			strcpy(dataname, content);
			free(content);

			q = dataTree_makeNode(type, dataname, initvalue, ++ID);

			if (q)
			{
				_tree = dataTree_insertNode(_tree, q, stat);

				if (*stat)
				{
					_tree = dataTree_destruct(_tree);
					break;
				}
			}
		}
	}

	return _tree;
}

#endif