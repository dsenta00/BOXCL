#define _CRT_SECURE_NO_WARNINGS
#include "ReadSrcBox.h"
#include "ReadData.h"
#include "OutputBuffer.h"
#include "ReadPointers.h"
#include "SetCompiler.h"
#include "WriteToBinaryFile.h"

void CompileToBox(char *_filename)
{
	char filename[1024] = { 0 };
	InputList inputlist = { NULL, NULL };
	OBuff_p outputbuffer = NULL;
	DataTree_p staticroot = NULL;
	DataTree_p dynamicroot = NULL;

	strcpy(filename, _filename);

	if (setCompilerData(filename, &inputlist, &outputbuffer, &staticroot, &dynamicroot) == 0)
	{
		if (writeToBinaryFile(&inputlist, &outputbuffer, staticroot, dynamicroot) == 0)
		{
			if (outputBuffer_destruct(outputbuffer) == 0)
			{
				printf("\n\tSuccessfully compiled program!\n\n");
			}
		}
		else
		{
			outputBuffer_delete(outputbuffer);
		}

		staticroot = dataTree_destruct(staticroot);
		dynamicroot = dataTree_destruct(dynamicroot);
		inputList_destruct(&inputlist);
	}
}

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		CompileToBox(argv[1]);
	}
	else
	{
		printf("\n\tPlease, type \'srcbox\' program to compile.\n");
		CompileToBox("D:\\DUJE\\Materijali zavrsni rad\\Programi za testiranje\\Pi\\pi.srcbox");
	}

	getchar();
	return 0;
}