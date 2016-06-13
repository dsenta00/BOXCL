#ifndef INPUTLIST_H
#define INPUTLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef MAXTOKEN
#define MAXTOKEN 128
#endif
struct _inputlist;
typedef struct _inputlist *InputList_p;
typedef struct _inputlist {
	char *content;
	InputList_p Next;
}InputList;

InputList_p inputList_makeNode(char *_content)
{
	InputList_p q = (InputList_p)calloc(1, sizeof(InputList));

	if (q)
	{
		q->content = (char *)calloc(strlen(_content) + 1, sizeof(char));

		if (q->content)
		{
			strcpy(q->content, _content);
		}
		else
		{
			free(q);
			q = NULL;
			printf("\n\tThere was an internal error during compilation.\nPlease, try again.");
		}
	}
	else
	{
		printf("\n\tThere was an internal error during compilation.\nPlease, try again.");
	}

	return q;
}

InputList_p inputList_add(InputList_p _last, InputList_p _q)
{
	_q->Next = _last->Next;
	_last->Next = _q;
	return _q;
}

void TestPrint(InputList_p _P)
{
	printf("List:\t");
	while (_P)
	{
		printf("%s ", _P->content);
		_P = _P->Next;
	}

	printf("\n\n");
}

char *inputList_pop(InputList_p _head)
{
	char *content = NULL;
	InputList_p del = _head->Next;

	if (del)
	{
		_head->Next = del->Next;
		content = del->content;
		free(del);
	}

	return content;
}

void inputList_destruct(InputList_p _head)
{
	char *content = NULL;

	while (1)
	{
		content = inputList_pop(_head);

		if (content)
		{
			free(content);
		}
		else
		{
			break;
		}
	}
}

#endif