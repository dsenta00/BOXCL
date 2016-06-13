#ifndef OUTPUTBUFF_H
#define OUTPUTBUFF_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STARTCAPACITY 100

typedef struct {
	char *filename;
	char *buffer;
	int capacity;
	int size;
}OBuff, *OBuff_p;

void outputBuffer_delete(OBuff_p _outputbuffer)
{
	if (_outputbuffer)
	{
		if (_outputbuffer->filename)
		{
			free(_outputbuffer->filename);
		}

		if (_outputbuffer->buffer)
		{
			free(_outputbuffer->buffer);
		}

		free(_outputbuffer);
	}
}

OBuff_p outputBuffer_construct(const char *_filename)
{
	OBuff_p q = (OBuff_p)calloc(1, sizeof(OBuff));
	char *tmp = NULL;

	if (q)
	{
		q->filename = (char *)calloc(strlen(_filename) + 1, sizeof(char));

		if (q->filename)
		{
			strcpy(q->filename, _filename);
			tmp = strstr(q->filename, ".srcbox");

			if (tmp)
			{
				strcpy(tmp, ".box");
				q->size = 0;
				q->capacity = STARTCAPACITY;

				q->buffer = (char *)calloc(STARTCAPACITY, sizeof(char));

				if (!q->buffer)
				{
					outputBuffer_delete(q);
					q = NULL;
					printf("\n\tThere was an internal error during compilation.\nPlease, try again.");
				}
			}
			else
			{
				outputBuffer_delete(q);
				q = NULL;
				printf("\n\tInvalid file extension! File must be \'.srcbox\' type.");
			}
		}
		else
		{
			outputBuffer_delete(q);
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

void outputBuffer_dump(char *data, int n)
{
	int i = 0;

	printf("\n");

	for (i; i < n; i++)
	{
		printf("[%d]", data[i]);
	}

	printf("\n");
}

void outputBuffer_write(OBuff_p *_outputbuff, char *_data, int _n)
{
	OBuff_p obuff = *_outputbuff;
	char *tmp = NULL;

	if (obuff->capacity < obuff->size + _n)
	{
		obuff->capacity *= 2;
		tmp = (char *)realloc(obuff->buffer, obuff->capacity);

		if (tmp)
		{
			obuff->buffer = tmp;
		}
		else
		{
			printf("\n\tThere was an internal error during compilation.\nPlease, try again.");
			outputBuffer_delete(obuff);
			obuff = NULL;
		}
	}

	if (obuff)
	{
		memcpy(&obuff->buffer[obuff->size], _data, _n);
		
		outputBuffer_dump(_data, _n);

		obuff->size += _n;
	}

	*_outputbuff = obuff;
}

int outputBuffer_destruct(OBuff_p _outputbuff)
{
	FILE *fp = fopen(_outputbuff->filename, "wb+");
	int written = 0;
	int stat = 0;

	if (fp)
	{
		written = fwrite(_outputbuff->buffer, sizeof(char), _outputbuff->size, fp);

		if (written != _outputbuff->size)
		{
			printf("\n\tThere was an internal error during compilation.\n\tPlease, try again.");
			stat = -1;
		}
		else
		{
			printf("\n\tGenerated execute file -> \'%s\'.", _outputbuff->filename);
		}

		fclose(fp);
	}
	else
	{
		printf("\n\tThere was an internal error during compilation.\nPlease, try again.");
		stat = -2;
	}

	outputBuffer_delete(_outputbuff);
	return stat;
}

#endif