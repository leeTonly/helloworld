#include <stdio.h>
#include <fcntl.h>
#include <string.h>

/**************Stucture**************/
typedef struct _paramStruct
{
	char *sfile1;
	char *sfile2;
	char *sOpt;
	char iNumOfOpt;
}t_paramStruct;


/**************Global Value**************/
t_paramStruct g_paramStruct;

/**********Function declaration**********/

/****************************
* Function: checkParam 		*
* Param: 					*
* 1. argc(number of Param)	*
* 2. argv(Param)			*
* Return:					*
*	0:	OK,  				*
*  -1:	param not enough	*
*  -2:	param too much		*
*  -3:	fail,				*
*  -4:	fail,				*
***************************/
int checkParam(int argc, char const **pargv)
{
	int i;
	int iIfHaveParam = 0;
	char **argv = NULL;

	argv = pargv;

	memset(&g_paramStruct, 0x0, sizeof(t_paramStruct));
	g_paramStruct.sfile1 = NULL;
	g_paramStruct.sfile2 = NULL;
	g_paramStruct.sOpt = NULL;

	if(argc < 3)
	{
		printf("USAGE: diff <option> <file1> <file2>\n");
		return -1;
	}

	for(i=1; i<argc; i++)
	{
		if((argv[i][0] == '-') && (iIfHaveParam == 0))
		{
			if(argc < 4)
			{
				printf("USAGE: diff <option> <file1> <file2>\n");
				return -1;
			}
			iIfHaveParam = 1;	
			g_paramStruct.sOpt = &argv[i][1];
			continue;
		}	
		else if((argv[i][0] == '-') && (iIfHaveParam == 1))
		{
			printf("[diff]option more than one\n");
			return -2;
		}

		if(g_paramStruct.sfile1 == 0)
		{
			g_paramStruct.sfile1 = argv[i];
		}
		else if(g_paramStruct.sfile2 == 0)
		{
			g_paramStruct.sfile2 = argv[i];
		}
	}

	if(iIfHaveParam)
	{
		g_paramStruct.iNumOfOpt = strlen(g_paramStruct.sOpt);
		printf("option=[%s][%d],file1[%s],fil2[%s]\n", \
				g_paramStruct.sOpt, g_paramStruct.iNumOfOpt, g_paramStruct.sfile1, g_paramStruct.sfile2);	
	}
	else
	{
		printf("file1[%s],fil2[%s]\n", g_paramStruct.sfile1, g_paramStruct.sfile2);			
	}


	//Here set bool value of paramStruct depent on opt char.

	return 0;
}




/*************main function***************/
int main(int argc, char const *argv[])
{
	int i4Ret=0;
	FILE *fp1;
	FILE *fp2;

	/*Check the param user enter*/
	i4Ret = checkParam(argc, argv);
	if(0 != i4Ret)
	{
		printf("[diff]Param error, errcode[%d]\n", i4Ret);
		return -1;
	}

	/*Open the file need compare*/
	fp1 = fopen(g_paramStruct.sfile1, "r");
	if(NULL == fp1)
	{
		printf("[diff]Cannot open %s\n", g_paramStruct.sfile1);
		return -1;
	}

	fp2 = fopen(g_paramStruct.sfile2, "r");
	if(NULL == fp2)
	{
		printf("[diff]Cannot open %s\n", g_paramStruct.sfile2);
		return -1;
	}







	/*free file point and set null*/
	if(fp1 != NULL)
	{
		fclose(fp1);
		fp1 = NULL;
	}

	if(fp2 != NULL)
	{
		fclose(fp2);
		fp2 = NULL;
	}


	return 0;
}