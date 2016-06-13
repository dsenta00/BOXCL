#ifndef setCompilerData_H
#define setCompilerData_H
#include "ReadSrcBox.h"
#include "ReadData.h"
#include "OutputBuffer.h"
#include "ReadPointers.h"

int setCompilerData(char *_filename, InputList_p _input, OBuff_p *_outputbuff, DataTree_p *_staticRoot, DataTree_p *_dynamicRoot)
{
	int stat = 0;

	stat = ReadSrcBox(_filename, _input);

	if (!stat)
	{
		*_staticRoot = ReadDataTreeFromInputList(*_staticRoot, _input);

		if (*_staticRoot)
		{
			*_dynamicRoot = ReadPointerTreeFromInputList(*_dynamicRoot, _input, &stat);

			if (!stat)
			{
				*_outputbuff = outputBuffer_construct(_filename);

				if (!*_outputbuff)
				{
					inputList_destruct(_input);
					*_staticRoot = dataTree_destruct(*_staticRoot);
					*_dynamicRoot = dataTree_destruct(*_dynamicRoot);
					stat = -3;
				}
			}
		}
		else
		{
			stat = -1;
		}
	}

	return stat;
}


#endif