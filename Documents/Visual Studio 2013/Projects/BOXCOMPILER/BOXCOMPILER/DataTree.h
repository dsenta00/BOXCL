#ifndef DATATREE_H
#define DATATREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAXTOKEN
#define MAXTOKEN 128
#endif
#define NUM_DATA_TYPES 7

const char dataTypes[][10] = 
{ 
	"CHAR",
	"INT", 
	"FLOAT", 
	"LONG", 
	"DOUBLE", 
	"STRING" 
};

struct _DataTree;
typedef struct _DataTree * DataTree_p;
typedef struct _DataTree {
	char initvalue[MAXTOKEN];
	char name[MAXTOKEN];
	int type;
	int ID;
	DataTree_p left;
	DataTree_p right;
}DataTree;

DataTree_p dataTree_makeNode(char *_type, char *_name, char *_initvalue, int _ID)
{
	DataTree_p q = (DataTree_p)calloc(1, sizeof(DataTree));
	int i = 0;

	printf("\nCreating data: [%d] %s %s = %s\n", _ID, _type, _name, _initvalue);

	if (q)
	{
		strcpy(q->initvalue, _initvalue);
		strcpy(q->name, _name);
		q->ID = _ID;

		do
		{
			if (!strcmpi(_type, dataTypes[i]))
			{
				q->type = i;
				break;
			}
		}while (++i < NUM_DATA_TYPES);
	}
	else
	{
		printf("\n\tThere was an internal error during compilation.\nPlease, try again.");
	}

	return q;
}

DataTree_p dataTree_insertNode(DataTree_p _curr, DataTree_p _q, int *succ)
{
	if (!_curr)
	{
		*succ = 0;
		return _q;
	}
	else
	{
		if (strcmp(_curr->name, _q->name) > 0)
		{
			_curr->left = dataTree_insertNode(_curr->left, _q, succ);
		}
		else if (strcmp(_curr->name, _q->name) < 0)
		{
			_curr->right = dataTree_insertNode(_curr->right, _q, succ);
		}
		else
		{
			*succ = -1;
			printf("\n\tThere is already a data named \'%s\'.", _q->name);
			free(_q);
		}

		return _curr;
	}
}

int dataTree_getId(DataTree_p _root, char *_name)
{
	if (!_root)
	{
		printf("\n\t'%s' is not declared in this code.\n", _name);
	}
	else
	{
		if (!strcmp(_root->name, _name))
		{
			return _root->ID;
		}
		else if (strcmp(_root->name, _name) > 0)
		{
			return dataTree_getId(_root->left, _name);
		}
		else
		{
			return dataTree_getId(_root->right, _name);
		}
	}

	return -1;
}

DataTree_p dataTree_getNode(DataTree_p _root, int _ID)
{
	DataTree_p searchLeft = NULL;
	DataTree_p searchRight = NULL;

	if (_root && _root->ID != _ID)
	{
		searchLeft = _root->left;
		searchRight = _root->right;

		if (searchLeft == NULL && searchRight == NULL)
		{
			return NULL;
		}
		else
		{
			searchLeft = dataTree_getNode(searchLeft, _ID);
			searchRight = dataTree_getNode(searchRight, _ID);

			if (searchLeft)
			{
				return searchLeft;
			}
			else
			{
				return searchRight;
			}
		}
	}
	else
	{
		return _root;
	}
}

DataTree_p dataTree_destruct(DataTree_p _curr)
{
	if (_curr)
	{
		_curr->left = dataTree_destruct(_curr->left);
		_curr->right = dataTree_destruct(_curr->right);
		free(_curr);
		_curr = NULL;
		return _curr;
	}
}

#endif