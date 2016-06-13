#ifndef READDATA_H
#define READDATA_H
#include "DataTree.h"
#include "InputList.h"

int isEndOfString(char *initvalue)
{
	int n = strlen(initvalue);

	if (initvalue[n - 1] == '\"')
	{
		return 1;
	}

	return 0;
}

void ClearFromBackSlashes(char *initvalue)
{
	char buffer[128] = { 0 };
	char *p = buffer;
	char *q = initvalue;

	while (*q)
	{
		if (*q == '\\')
		{
			q++;

			switch (*q)
			{
			case 'n':
				*p = '\n';
				break;
			case 't':
				*p = '\t';
				break;
			case 'r':
				*p = '\r';
				break;
			case '\\':
				*p = '/';
				break;
			}
			q++;
			p++;
		}
		else
		{
			*p = *q;
			q++;
			p++;
		}
	}

	*p = '\0';

	strcpy(initvalue, buffer);
}

int ReadInitString(char *initvalue, InputList_p _head)
{
	char *tmp = NULL;
	int i = 0;
	int n = 0;

	memset(initvalue, 0, MAXTOKEN);
	tmp = inputList_pop(_head);

	if (tmp[0] == '\"')
	{
		while (1)
		{
			if (!strcmp(initvalue, ""))
			{
				strcat(initvalue, &tmp[1]); // avoid first (")
			}
			else
			{
				strcat(initvalue, tmp); 
			}

			free(tmp);
			ClearFromBackSlashes(initvalue);

			if (!isEndOfString(initvalue))
			{
				strcat(initvalue, " ");
				tmp = inputList_pop(_head);
			}
			else
			{
				initvalue[strlen(initvalue) - 1] = 0; //avoid last (")
				break;
			}
		}
	}
	else
	{
		printf("\n\tString must start with [\"\] (\'%s\')", tmp);
		free(tmp);
		return -1;
	}

	return 0;
}

DataTree_p ReadDataTreeFromInputList(DataTree_p _tree, InputList_p _head)
{
	char *content = NULL;
	char dataname[MAXTOKEN] = { 0 };
	char type[MAXTOKEN] = { 0 };
	char initvalue[MAXTOKEN] = { 0 };
	DataTree_p q = NULL;
	int stat = 0;
	int ID = 0;

	while (1)
	{
		content = inputList_pop(_head);

		if (!strcmpi(content, "@HEAP"))
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

			if (!strcmpi(type, "STRING"))
			{
				stat = ReadInitString(initvalue, _head);
			}
			else
			{
				content = inputList_pop(_head);
				strcpy(initvalue, content);
				free(content);
			}

			q = dataTree_makeNode(type, dataname, initvalue, ++ID);

			if (q)
			{
				_tree = dataTree_insertNode(_tree, q, &stat);

				if (stat)
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