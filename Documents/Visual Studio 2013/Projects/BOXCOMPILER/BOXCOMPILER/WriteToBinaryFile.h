#ifndef READTOBIN_H
#define READTOBIN_H
#include "ReadSrcBox.h"
#include "ReadData.h"
#include "OutputBuffer.h"
#include "ReadPointers.h"
#include "Registry.h"
#include "OperationFormat.h"

enum DATA_TYPES
{
	_CHAR,
	_INT,
	_FLOAT,
	_LONG,
	_DOUBLE,
	_STRING
};

enum OPERATIONS
{
	MOV,
	ADD,
	MUL,
	DIV,
	SUB,
	MOD,
	RAND,
	SCAN,
	PRINT,
	PRINTLN,
	ADI,
	MUC,
	DIC,
	SUC,
	MODC,
	CMPE,
	CMPNE,
	CMPG,
	CMPL,
	CMPGE,
	CMPLE,
	LOOPE,
	LOOPNE,
	LOOPG,
	LOOPL,
	LOOPGE,
	LOOPLE,
	NEW,
	NEWV,
	FREE,
	OPENW,
	OPENR,
	OPENA,
	PUT,
	GET,
	GETLINE,
	REPLOOP,
	RUN,
	START,
	ESTART
};

#define NUM_OF_OPERATIONS (42)

const char OPERATION[NUM_OF_OPERATIONS][16] =
{
	"MOV",
	"ADD",
	"MUL",
	"DIV",
	"SUB",
	"MOD",
	"RAND",
	"SCAN",
	"PRINT",
	"PRINTLN",
	"ADI",
	"MUC",
	"DIC",
	"SUC",
	"MODC",
	"CMPE",
	"CMPNE",
	"CMPG",
	"CMPL",
	"CMPGE",
	"CMPLE",
	"LOOPE",
	"LOOPNE",
	"LOOPG",
	"LOOPL",
	"LOOPGE",
	"LOOPLE",
	"NEW",
	"NEWV",
	"FREE",
	"OPENW",
	"OPENR",
	"OPENA",
	"PUT",
	"GET",
	"GETLINE",
	"REPLOOP",
	"RUN",
	"START",
	"ESTART",
};

/*** REGISTRY MODE FORMAT OPER **
*                              *
*      MOV [rx][rx]            *
*      ADD [rx][rx]            *
*      DIV [rx][rx]            *
*      SUB [rx][rx]            *
*      MUL [rx][rx]            *
*      MOD [rx][rx]            *
*                              *
*      SCAN    [rx]            *
*      PRINT   [rx]            *
*      RAND    [rx]            *
*      PRINTLN [rx]            *
*                              *
*      ADI     [rx][n]         *
*      MUC     [rx][n]         *
*      DIC     [rx][n]         *
*      SUC     [rx][n]         *
*      MODC    [rx][n]         *
*                              *
*      PUSHS   [var][rx]       *
*      PUSH    [ptr][rx]       *
*      LEA     [ptr][rx][rx]   *
*      LEAC    [ptr][n][rx]    *
*      NEW     [ptr][n]        *
*      NEWV    [ptr][rx]       *
*      FNEW    [ptr][n]        *
*      FNEWV   [ptr][rx]       *
*      FREE    [ptr]           *
*                              *
*      PUT*    [path][rx]      *
*      GET*    [path][rx]      *
*      GETLINE [path][rx]      *
*      FEOF    [path][n]       *
*      ISOPEN  [path]          *
*                              *
*      OPEN*   [path]          *
*                              *
*      CMP*    [rx][rx][n]     *
*      LOOP*   [rx][rx][n]     *
*                              *
*******************************/

void IntToStringBinary(int *value, char *str)
{
	char *p = (char *)value;

	*str = *p;
	str++; p++;
	*str = *p;
	str++; p++;
	*str = *p;
	str++; p++;
	*str = *p;
}

void ShortToStringBinary(short *value, char *str)
{
	char *p = (char *)value;

	*str = *p;
	str++; p++;
	*str = *p;
}

void LongToStringBinary(long *value, char *str)
{
	char *p = (char *)value;

	*str = *p; //0
	str++; p++;

	*str = *p; //1
	str++; p++;

	*str = *p; //2
	str++; p++;

	*str = *p; //3
	str++; p++;

	*str = *p; //4
	str++; p++;

	*str = *p; //5
	str++; p++;

	*str = *p; //6
	str++; p++;

	*str = *p; //7
}

void DoubleToStringBinary(double *value, char *str)
{
	char *p = (char *)value;

	*str = *p; //0
	str++; p++;

	*str = *p; //1
	str++; p++;

	*str = *p; //2
	str++; p++;

	*str = *p; //3
	str++; p++;

	*str = *p; //4
	str++; p++;

	*str = *p; //5
	str++; p++;

	*str = *p; //6
	str++; p++;

	*str = *p; //7
}

void FloatToStringBinary(float *value, char *str)
{
	char *p = (char *)value;

	*str = *p; //0
	str++; p++;

	*str = *p; //1
	str++; p++;

	*str = *p; //2
	str++; p++;

	*str = *p; //3
}

int DynamicDataHeaderToBinary(OBuff_p *_outputbuff, DataTree_p _dynamicRoot)
{
	int stat = 0;
	char buffer[MAXTOKEN] = { 0 };
	DataTree_p tmp = NULL;
	int count = 0;

	while (1)
	{
		tmp = dataTree_getNode(_dynamicRoot, ++count);

		if (tmp)
		{
			memset(&buffer, 0, MAXTOKEN);
			IntToStringBinary(&tmp->type, buffer);
			outputBuffer_write(_outputbuff, buffer, sizeof(char));

			if (!*_outputbuff)
			{
				stat = -1;
				break;
			}
		}
		else
		{
			break;
		}
	}

	return stat;
}

int StaticDataHeaderToBinary(OBuff_p *_outputbuff, DataTree_p _staticRoot)
{
	int stat = 0;
	char buffer[MAXTOKEN] = { 0 };
	DataTree_p tmp = NULL;
	short sh = 0;
	int i = 0;
	int count = 0;
	char c = 0;
	long l = 0;
	double d = 0;
	float f = 0;

	while (1)
	{
		tmp = dataTree_getNode(_staticRoot, ++count);

		if (tmp)
		{
			memset(&buffer, 0, MAXTOKEN);
			IntToStringBinary(&tmp->type, buffer);
			outputBuffer_write(_outputbuff, buffer, sizeof(char));

			memset(&buffer, 0, MAXTOKEN);

			switch (tmp->type)
			{
			case _CHAR:
				sscanf(tmp->initvalue, " %d", &c);
				outputBuffer_write(_outputbuff, &c, sizeof(char));
				break;
			case _INT:
				sscanf(tmp->initvalue, " %d", &i);
				IntToStringBinary(&i, buffer);
				outputBuffer_write(_outputbuff, buffer, sizeof(int));
				break;
			case _FLOAT:
				sscanf(tmp->initvalue, " %f", &f);
				FloatToStringBinary(&f, buffer);
				outputBuffer_write(_outputbuff, buffer, sizeof(float));
				break;
			case _LONG:
				sscanf(tmp->initvalue, " %ld", &l);
				LongToStringBinary(&l, buffer);
				outputBuffer_write(_outputbuff, buffer, sizeof(long));
				break;
			case _DOUBLE:
				sscanf(tmp->initvalue, " %lf", &d);
				DoubleToStringBinary(&d, buffer);
				outputBuffer_write(_outputbuff, buffer, sizeof(double));
				break;
			case _STRING:
				outputBuffer_write(_outputbuff, tmp->initvalue, strlen(tmp->initvalue) + 1);
				break;
			}

			if (!*_outputbuff)
			{
				stat = -1;
				break;
			}
		}
		else
		{
			break;
		}
	}

	return stat;
}

int RegistryToBinary(char *reg, InputList_p _input)
{
	int stat = 0;
	char *tmp = NULL;

	tmp = inputList_pop(_input);
	*reg = Registry(tmp);
	free(tmp);

	if (*reg == -1)
		stat = *reg;

	printf(" R%d", *reg);

	return stat;
}

int DataIndexToBinary(char *dataOrPtr, InputList_p _input, DataTree_p _anyTypeData)
{
	char *tmp = NULL;
	int stat = 0;
	int ID = 0;

	tmp = inputList_pop(_input);
	ID = dataTree_getId(_anyTypeData, tmp);
	printf(" %s", tmp);
	free(tmp);

	if (ID != -1)
	{
		*dataOrPtr = ID;
	}
	else
	{
		stat = ID;
	}

	return stat;
}

void insertToConstant(short *constant, InputList_p _input)
{
	char *tmp = NULL;

	tmp = inputList_pop(_input);

	if (*tmp == 'R' || *tmp == 'r')
	{
		tmp++;
		sscanf(tmp, " %hd", constant);
		printf(" R%d", *constant);
		return;
	}

	sscanf(tmp, " %hd", constant);
	printf(" %d", *constant);
}

int OpCodeToBinary(OperationFormat *opFormat, InputList_p _input)
{
	char *tmp = NULL;
	char buffer[MAXTOKEN] = { 0 };
	int i = 0;

	i = 0;
	tmp = inputList_pop(_input);

	do
	{
		if (!strcmpi(tmp, OPERATION[i]))
		{
			printf("\n%s", tmp);
			break;
		}
	} while (++i < NUM_OF_OPERATIONS);

	if (i < NUM_OF_OPERATIONS)
	{
		opFormat->opCode = i;
	}
	else if (!strcmpi(tmp, "@CODE"))
	{
		i = START;
	}
	else if (strcmpi(tmp, "@ENDCODE"))
	{
		printf("\n\tUnkown operation \'%s\'.", tmp);
		i = -1;
	}

	return i;
}

int CodeToBinary(OBuff_p *_outputbuff, InputList_p _input, DataTree_p _staticRoot, DataTree_p _dynamicRoot)
{
	int stat = 0;
	char *tmp = NULL;
	char buffer[MAXTOKEN] = { 0 };
	DataTree_p data = NULL;
	int i = 0;
	OperationFormat opFormat;

	do
	{
		operationFormat_reset(&opFormat);
		i = OpCodeToBinary(&opFormat, _input);

		if (i < NUM_OF_OPERATIONS)
		{
			switch (i)
			{
			case MOV: case ADD: case SUB: case MUL: case DIV: case MOD:
				stat = DataIndexToBinary(&opFormat.data1, _input, _staticRoot);

				if (!stat)
					stat = DataIndexToBinary(&opFormat.data2, _input, _staticRoot);
				break;
			case SCAN: case PRINT: case RAND: case PRINTLN:
				stat = DataIndexToBinary(&opFormat.data1, _input, _staticRoot);
				break;
			case OPENW: case OPENA: case OPENR:
				stat = DataIndexToBinary(&opFormat.data1, _input, _staticRoot);
				opFormat.constant = opFormat.data1;
				break;
			case ADI: case MUC: case DIC: case SUC: case MODC:
				stat = DataIndexToBinary(&opFormat.data1, _input, _staticRoot);

				if (!stat)
					insertToConstant(&opFormat.constant, _input);
				break;
			case CMPE: case CMPG: case CMPGE: case CMPL: case CMPLE: case CMPNE:
			case LOOPE: case LOOPG: case LOOPGE: case LOOPL: case LOOPLE: case LOOPNE:
				stat = DataIndexToBinary(&opFormat.data1, _input, _staticRoot);

				if (!stat)
				{
					stat = DataIndexToBinary(&opFormat.data2, _input, _staticRoot);

					if (!stat)
						insertToConstant(&opFormat.constant, _input);
				}
				break;
			case PUT: case GET: case GETLINE:
				stat = DataIndexToBinary(&opFormat.constant, _input, _staticRoot);

				if (!stat)
				{
					stat = DataIndexToBinary(&opFormat.data1, _input, _staticRoot);
				}
				break;
			case NEWV:
				stat = DataIndexToBinary(&opFormat.ptr, _input, _dynamicRoot);

				if (!stat)
					stat = RegistryToBinary(&opFormat.data1, _input);
				break;
			case NEW:
				stat = DataIndexToBinary(&opFormat.ptr, _input, _dynamicRoot);

				if (!stat)
					insertToConstant(&opFormat.constant, _input);
				break;
			case FREE:
				stat = DataIndexToBinary(&opFormat.ptr, _input, _dynamicRoot);
				break;
			case RUN:
				stat = DataIndexToBinary(&opFormat.data1, _input, _staticRoot);
				break;
			case START: case ESTART: case REPLOOP:
				break;
			default:
				printf("Unkown operation!\n");
				stat = -1;
				break;
			}
		}

		printf("\n\n\topCode: %d (%s)\n", opFormat.opCode, OPERATION[opFormat.opCode]);
		printf("\tptr:    %d\n", opFormat.ptr);
		printf("\tdata1:   %d\n", opFormat.data1);
		printf("\tdata2:   %d\n", opFormat.data2);
		printf("\tconst:   %d\n", opFormat.constant);

		outputBuffer_write(_outputbuff, (char *)&opFormat, sizeof(opFormat));
	} while (i < NUM_OF_OPERATIONS && i != ESTART && stat == 0);

	return stat;
}

int writeToBinaryFile(InputList_p _input, OBuff_p *_outputbuff, DataTree_p _staticRoot, DataTree_p _dynamicRoot)
{
	int stat = 0;
	char buffer[MAXTOKEN] = { 0 };
	char borderStatDyn = '@';
	DataTree_p tmp = NULL;
	char *str = NULL;

	printf("\n\tMaking bin header.");

	stat = StaticDataHeaderToBinary(_outputbuff, _staticRoot);

	if (!stat)
	{
		outputBuffer_write(_outputbuff, &borderStatDyn, sizeof(char));

		if (*_outputbuff)
		{
			stat = DynamicDataHeaderToBinary(_outputbuff, _dynamicRoot);

			if (!stat)
			{
				printf("\n\tGenerating code.");
				stat = CodeToBinary(_outputbuff, _input, _staticRoot, _dynamicRoot);
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