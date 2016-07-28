/*---------------------------------------- Include files ------------------------------------------*/
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
/*----------------------------------------- Macro define ------------------------------------------*/
#define END 1
#define DEBUG 0

/*----------------------------------------- Type define -------------------------------------------*/
typedef struct _paramStruct
{
	char *sfile1;		/*第一个文件的路*/
	char *sfile2;		/*第二个文件的路*/
	char *sOpt;			/*可选参数*/
	char bNumOfOpt;		/*输入参数的个数*/
}t_paramStruct;

typedef struct _FileStruct
{
	FILE *fp;
	char sCurLine[1024];
	int iCurLineNo;
	char bisEnd;
	long iFilePointBk;
}t_FileStruct;

typedef struct _FileAdd
{
	char sAddLines[1024][1024];

	// int iFilePointBk;
	// int iFilePointCur;

	int bAddStartLine;
	int bAddEndLine;
}t_FileAdd;

typedef struct _FileDel
{
	char sDelLines[1024][1024];

	// int iFilePointBk;
	// int iFilePointCur;

	int bDelStartLine;
	int bDelEndLine;
}t_FileDel;

typedef struct _FileChange
{
	char sChangeLines1[1024][1024];
	char sChangeLines2[1024][1024];

	int bChangeStartLine1;
	int bChangeEndLine1;

	int bChangeStartLine2;
	int bChangeEndLine2;

	// int iFilePointBk1;
	// int iFilePointCur1;

	// int iFilePointBk2;
	// int iFilePointCur2;
}t_FileChange;

/*--------------------------------- Local function declaration ------------------------------------*/
int fgLineAddHandle(char *bRunStt);
int fgLineDelHandle(char *bRunStt);
int fgLineChangeHandle(char *bRunStt);
int fgLineNormalHandle(char *bRunStt);
long fgGetCurFilePlace(FILE *fp);
int fgSetCurFilePlace(FILE *fp, long fileplace);

/*--------------------------------------- Global variable -----------------------------------------*/
t_paramStruct 	g_paramStruct;
t_FileStruct	g_file1;
t_FileStruct	g_file2;
t_FileAdd		g_fileadd;
t_FileDel		g_filedel;
t_FileChange	g_filechange;
char 			bIsDiff;
char 			bLineStt;
int 			bSameLineNo;
/*--------------------------------------- Global functions ----------------------------------------*/


/*---------------------------------------
Function : 		checkParam
Describtion: 	
Param:			argc, argv
Return:
		Normal  0
		Error	-1
*/
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

	if(argc < 3){
		printf("USAGE: diff <option> <file1> <file2>\n");
		return -1;
	}

	for(i=1; i<argc; i++){
		if((argv[i][0] == '-') && (iIfHaveParam == 0)){
			if(argc < 4){
				printf("USAGE: diff <option> <file1> <file2>\n");
				return -1;
			}
			iIfHaveParam = 1;	
			g_paramStruct.sOpt = &argv[i][1];
			continue;
		}else if((argv[i][0] == '-') && (iIfHaveParam == 1)){
			printf("[diff]option more than one\n");
			return -2;
		}

		if(g_paramStruct.sfile1 == 0){
			g_paramStruct.sfile1 = argv[i];
		}else if(g_paramStruct.sfile2 == 0){
			g_paramStruct.sfile2 = argv[i];
		}
	}

	// if(iIfHaveParam){
	// 	g_paramStruct.bNumOfOpt = strlen(g_paramStruct.sOpt);
	// 	printf("option=[%s][%d],file1[%s],fil2[%s]\n", \
	// 			g_paramStruct.sOpt, g_paramStruct.bNumOfOpt, g_paramStruct.sfile1, g_paramStruct.sfile2);	
	// }
	// else
	// {
	// 	printf("file1[%s],fil2[%s]\n", g_paramStruct.sfile1, g_paramStruct.sfile2);			
	// }


	//Here set bool value of paramStruct depent on opt char.

	return 0;
}


/*---------------------------------------
Function : 		fgGetCurFilePlace
Describtion: 	
Param:			tfile
Return:
		Normal  fileplace
		Error	-1
*/
long fgGetCurFilePlace(FILE *fp)
{
	if(fp == NULL){
		fprintf(stderr, "fgGetCurFilePlace, param is null\n");
		return -1;
	}
	return ftell(fp);
}


/*---------------------------------------
Function : 		fgSetCurFilePlace
Describtion: 	
Param:			tfile, fileplace
Return:
		Normal  0
		Error	-1
*/
int fgSetCurFilePlace(FILE *fp, long fileplace)
{
	if(fp == NULL){
		fprintf(stderr, "fgSetCurFilePlace, param is null\n");
		return -1;
	}
	
	return fseek(fp, fileplace, SEEK_SET);

}


/*---------------------------------------
Function : 		fgLineAddHandle
Describtion: 	
Param:			bRunStt
Return:
		Normal  0
		Error	-1
*/
int fgLineAddHandle(char *bRunStt)
{
	int i;
	int bstart;
	int bend;

	bstart = g_fileadd.bAddStartLine;
	bend = g_fileadd.bAddEndLine;

	if(*bRunStt != 'a'){
		return -1;
	}

	if((bend - bstart) == 0) {
		//printf("%da%d\n",bSameLineNo,bstart);
		printf("%da%d\n",g_file1.iCurLineNo-1,bstart);
		printf("> %s", g_fileadd.sAddLines[0]);

	}else if((bend - bstart) > 0) {
		//printf("%da%d,%d\n",bSameLineNo, bstart, bend);
		printf("%da%d,%d\n",g_file1.iCurLineNo-1, bstart, bend);
		for(i=0; i< bend - bstart + 1; i++)	{
			printf("> %s", g_fileadd.sAddLines[i]);
		}
	}
#if DEBUG
	sleep(1);
#endif
	memset(g_fileadd.sAddLines, 0, 32*1024);
	g_fileadd.bAddStartLine = 1;
	g_fileadd.bAddEndLine = 1;

// #if DEBUG
// 	printf("g_file1.iCurLineNo=%d, g_file2.iCurLineNo=%d\n", g_file1.iCurLineNo, g_file2.iCurLineNo);
// #endif

	bSameLineNo++;

	*bRunStt = 'r';
	bLineStt = 0;

	return 0;
}


/*---------------------------------------
Function : 		fgLineDelHandle
Describtion: 	
Param:			bRunStt
Return:
		Normal  0
		Error	-1
*/
int fgLineDelHandle(char *bRunStt)
{
	int i;
	int bstart;
	int bend;

	bstart = g_filedel.bDelStartLine;
	bend = g_filedel.bDelEndLine;

	if(*bRunStt != 'd'){
		return -1;
	}

	if((bend - bstart) == 0) {
		printf("%dd%d\n",bstart,bSameLineNo);
		printf("< %s", g_filedel.sDelLines[0]);

	}else if((bend - bstart) > 0) {
		printf("%d,%dd%d\n", bstart, bend,bSameLineNo);
		for(i=0; i< bend - bstart + 1; i++)
		{
			printf("< %s", g_filedel.sDelLines[i]);
		}
	}
#if DEBUG
	sleep(1);
#endif
	//memset(g_filedel.sDelLines, 0, sizeof(g_filedel.sDelLines));
	memset(g_filedel.sDelLines, 0, 32*1024);
	g_filedel.bDelStartLine = 1;
	g_filedel.bDelEndLine = 1;

//#if DEBUG
	//printf("g_file1.iCurLineNo=%d, g_file2.iCurLineNo=%d\n", g_file1.iCurLineNo, g_file2.iCurLineNo);
//#endif

	bSameLineNo++;

	*bRunStt = 'r';
	bLineStt = 0;

	return 0;
}


/*---------------------------------------
Function : 		fgLineChangeHandle
Describtion: 	
Param:			bRunStt
Return:
		Normal  0
		Error	-1
*/
int fgLineChangeHandle(char *bRunStt)
{
	if(*bRunStt != 'c'){
		return -1;
	}


	return 0;
}


/*---------------------------------------
Function : 		fgLineNormalHandle
Describtion: 	
Param:			bRunStt
Return:
		Normal  0
		Error	-1
*/
int fgLineNormalHandle(char *bRunStt)
{
	int iCurFilePoint1 = 0;
	int iCurFilePoint2 = 0;

	if(*bRunStt != 'r'){
		return -1;
	}

	if(bLineStt == 'd'){	/*Check if is del mode*/
		memset(g_file1.sCurLine, 0, 1024);

		if(fgets(g_file1.sCurLine, 1024, g_file1.fp) == NULL){
			if(feof(g_file1.fp) && !g_file2.bisEnd){
				/*file1 is end but cannot find a line which same with the line of file2*/
				bLineStt = 'a';
				strcpy(g_file1.sCurLine, g_filedel.sDelLines[0]);
				memset(g_filedel.sDelLines, 0, 32*1024);
				g_file1.iCurLineNo = g_filedel.bDelStartLine;

				g_filedel.bDelStartLine = 1;
				g_filedel.bDelEndLine = 1;	
				g_file1.bisEnd = 0;
				g_file2.bisEnd = 0;	
				fgSetCurFilePlace(g_file1.fp, g_file1.iFilePointBk);
				fgSetCurFilePlace(g_file2.fp, g_file2.iFilePointBk);

				return 0;
			}else if(g_file2.bisEnd){

				*bRunStt = 'd';
				return 0;
			}
		}

		/*If file2 already end, all remain lines of file1 need removed*/
		if(g_file2.bisEnd){

			g_filedel.bDelEndLine++;
			strcpy(g_filedel.sDelLines[g_filedel.bDelEndLine - g_filedel.bDelStartLine], g_file1.sCurLine);			
		}else if(strcmp(g_file1.sCurLine, g_file2.sCurLine) == 0){
#if DEBUG
			printf("@@%s@@%s", g_file1.sCurLine,g_file2.sCurLine);
			printf("####%d,####%d\n", g_file1.iCurLineNo,g_file2.iCurLineNo);
#endif
			/*the lines are same, so the lines between startline and endline need to be removed*/
			*bRunStt = 'd';
		}else{
#if DEBUG
			printf("@@%s@@%s", g_file1.sCurLine,g_file2.sCurLine);
			printf("####%d,####%d\n", g_file1.iCurLineNo,g_file2.iCurLineNo);
#endif
			g_filedel.bDelEndLine++;
			strcpy(g_filedel.sDelLines[g_filedel.bDelEndLine - g_filedel.bDelStartLine], g_file1.sCurLine);
		}

		g_file1.iCurLineNo++;		

	}else if(bLineStt == 'a'){	/*Check if add mode*/
		memset(g_file2.sCurLine, 0 ,1024);

		if(fgets(g_file2.sCurLine, 1024, g_file2.fp) == NULL){
			if(feof(g_file2.fp) && !g_file1.bisEnd){
				/*file2 is end but cannot find a line which same with the line of line1*/
				bLineStt = 'c';

				memset(g_fileadd.sAddLines, 0, 32*1024);
				g_file1.iCurLineNo = g_filechange.bChangeStartLine1;
				g_file2.iCurLineNo = g_filechange.bChangeStartLine2;
				g_fileadd.bAddStartLine = 1;
				g_fileadd.bAddEndLine = 1;
				fgSetCurFilePlace(g_file1.fp, g_file1.iFilePointBk);
				fgSetCurFilePlace(g_file2.fp, g_file2.iFilePointBk);

				return 0;
			}else if(g_file1.bisEnd){
				*bRunStt = 'a';

				return 0;
			}
		}

		/*If file1 already end, all remain lines of file2 need add*/
		if(g_file1.bisEnd)
		{
			g_fileadd.bAddEndLine++;
			strcpy(g_fileadd.sAddLines[g_fileadd.bAddEndLine - g_fileadd.bAddStartLine], g_file2.sCurLine);
		}else if(strcmp(g_file1.sCurLine, g_file2.sCurLine) == 0){
			/*the lines are same, so the lines between startline and endline need to be added*/
			*bRunStt = 'a';
#if DEBUG
			printf("@@%s@@%s", g_file1.sCurLine,g_file2.sCurLine);
			printf("####%d,####%d\n", g_file1.iCurLineNo,g_file2.iCurLineNo);
#endif
		}else{

			g_fileadd.bAddEndLine++;
			strcpy(g_fileadd.sAddLines[g_fileadd.bAddEndLine - g_fileadd.bAddStartLine], g_file2.sCurLine);
		}

		g_file2.iCurLineNo++;

	}else if(bLineStt == 'c'){	/*Check if change mode*/


	}else{

		iCurFilePoint1 = fgGetCurFilePlace(g_file1.fp);
		iCurFilePoint2 = fgGetCurFilePlace(g_file2.fp);

		if(fgets(g_file1.sCurLine, 1024, g_file1.fp) == NULL) {
			if(g_file1.iCurLineNo == 1){
				/*file1 is empty*/
				return -1;
			}else if(feof(g_file1.fp)){
#if DEBUG
				printf("####file1 is end\n");
#endif
				g_file1.bisEnd = 1;
			}
		}
		

		if(fgets(g_file2.sCurLine, 1024, g_file2.fp) == NULL) {
			if(g_file2.iCurLineNo == 1){
				/*file2 is empty*/
				return -1;
			} else if(feof(g_file2.fp)){
#if DEBUG
				printf("####fil2 is end\n");
#endif
				g_file2.bisEnd = 1;
			}
		}

		if(strcmp(g_file1.sCurLine, g_file2.sCurLine) == 0) {
			/*lines are same*/

			bSameLineNo++;

#if DEBUG
			printf("@@%s@@%s", g_file1.sCurLine,g_file2.sCurLine);
			printf("####bSameLineNo = %d\n", bSameLineNo);
#endif

			if(g_file1.bisEnd == 1 && g_file2.bisEnd == 1)
			{
				return END;
			}else if(g_file1.bisEnd == 1){
				bLineStt = 'a';
				g_fileadd.bAddStartLine = g_file2.iCurLineNo;
				g_fileadd.bAddEndLine = g_file2.iCurLineNo;
				memset(g_file2.sCurLine, 0, 1024);
				g_file2.iCurLineNo++;
			}else if(g_file2.bisEnd == 1){
				bLineStt = 'd';
				g_filedel.bDelStartLine = g_file1.iCurLineNo;
				g_filedel.bDelEndLine = g_file1.iCurLineNo;
				memset(g_file1.sCurLine, 0, 1024);
				g_file1.iCurLineNo++;
			}else{
				memset(g_file1.sCurLine, 0, 1024);
				memset(g_file2.sCurLine, 0, 1024);
				g_file1.iCurLineNo++;
				g_file2.iCurLineNo++;
			}

#if DEBUG
			printf("1#####fgLineNormalHandle,r, CurLineNo, %d,%d\n",g_file1.iCurLineNo,g_file2.iCurLineNo);
#endif

		} else {
			// bIsDiff = 1;
			//bLineStt = 'd';
			strcpy(g_filedel.sDelLines[0], g_file1.sCurLine);
			strcpy(g_fileadd.sAddLines[0], g_file2.sCurLine);
			strcpy(g_filechange.sChangeLines1[0], g_file1.sCurLine);
			strcpy(g_filechange.sChangeLines2[0], g_file2.sCurLine);

			if(g_file1.bisEnd == 1){
				bLineStt = 'a';
				g_fileadd.bAddStartLine = g_file2.iCurLineNo;
				g_fileadd.bAddEndLine = g_file2.iCurLineNo;
				memset(g_file2.sCurLine, 0, 1024);
				g_file2.iCurLineNo++;
			}else if(g_file2.bisEnd == 1){
				bLineStt = 'd';
				g_filedel.bDelStartLine = g_file1.iCurLineNo;
				g_filedel.bDelEndLine = g_file1.iCurLineNo;
				memset(g_file1.sCurLine, 0, 1024);
				g_file1.iCurLineNo++;
			}else{
				bLineStt = 'd';
				g_file1.iCurLineNo++;
				g_file2.iCurLineNo++;
			}
#if DEBUG
			printf("@@%s@@%s", g_file1.sCurLine,g_file2.sCurLine);
			printf("2#####fgLineNormalHandle,r, CurLineNo, %d,%d\n",g_file1.iCurLineNo,g_file2.iCurLineNo);
#endif
			/*backup current line number*/
			g_filedel.bDelStartLine = g_file1.iCurLineNo;
			g_filedel.bDelEndLine = g_file1.iCurLineNo;
			g_fileadd.bAddStartLine = g_file2.iCurLineNo;
			g_fileadd.bAddEndLine = g_file2.iCurLineNo;
			g_filechange.bChangeStartLine1 = g_file1.iCurLineNo;
			g_filechange.bChangeEndLine1 = g_file1.iCurLineNo;
			g_filechange.bChangeStartLine2 = g_file2.iCurLineNo;
			g_filechange.bChangeEndLine2 = g_file2.iCurLineNo;

			g_file1.iFilePointBk = fgGetCurFilePlace(g_file1.fp);
			g_file2.iFilePointBk = fgGetCurFilePlace(g_file2.fp);

		}
	}

	return 0;
}




int main(int argc, char const *argv[])
{
	char bRunStt = 'r';	/*'c' for change, 'a' for add, 'd' for delete, 'r' for running*/
	int iRet = 0;

	memset(&g_fileadd, 0, sizeof(t_FileAdd));
	memset(&g_filedel, 0, sizeof(t_FileDel));
	memset(&g_filechange, 0, sizeof(t_FileChange));
	memset(&g_file1, 0, sizeof(t_FileStruct));
	memset(&g_file2, 0, sizeof(t_FileStruct));

	/*Check the param user enter*/
	iRet = checkParam(argc, argv);
	if(0 != iRet) {
		//printf("[diff]Param error, errcode[%d]\n", iRet);
		return -1;
	}

	/*Open the file need compare*/
	g_file1.fp = fopen(g_paramStruct.sfile1, "r");
	if(NULL == g_file1.fp) {
		printf("[diff]Cannot open %s\n", g_paramStruct.sfile1);
		return -1;
	}

	g_file2.fp = fopen(g_paramStruct.sfile2, "r");
	if(NULL == g_file2.fp) {
		printf("[diff]Cannot open %s\n", g_paramStruct.sfile2);
		return -1;
	}

	iRet = 0;
	bLineStt = 0;

	g_file1.iCurLineNo = 0;
	g_file2.iCurLineNo = 0;

	// g_fileadd.iFilePointBk = fgGetCurFilePlace(g_file2.fp);
	// g_fileadd.iFilePointCur = fgGetCurFilePlace(g_file2.fp);
	// g_filedel.iFilePointBk = fgGetCurFilePlace(g_file1.fp);
	// g_filedel.iFilePointCur = fgGetCurFilePlace(g_file1.fp);
	// g_filechange.iFilePointBk1 = fgGetCurFilePlace(g_file1.fp);
	// g_filechange.iFilePointBk2 = fgGetCurFilePlace(g_file2.fp);
	// g_filechange.iFilePointCur1 = fgGetCurFilePlace(g_file1.fp);
	// g_filechange.iFilePointCur2 = fgGetCurFilePlace(g_file2.fp);

	while(1) {
		switch(bRunStt)
		{
			case 'd':
				iRet = fgLineDelHandle(&bRunStt);
				break;

			case 'a':
				iRet = fgLineAddHandle(&bRunStt);
				break;

			case 'c':
				iRet = fgLineChangeHandle(&bRunStt);
				break;

			case 'r':
				iRet = fgLineNormalHandle(&bRunStt);
				break;

			default:
				break;
		}

		if(iRet != 0) {
			break;
		}
	}

#if DEBUG
	printf("g_file1.iCurLineNo=%d, g_file2.iCurLineNo=%d\n", g_file1.iCurLineNo, g_file2.iCurLineNo);
#endif

	/*free file point and set null*/
	if(g_file1.fp != NULL) {
		fclose(g_file1.fp);
		g_file1.fp = NULL;
	}

	if(g_file2.fp != NULL) {
		fclose(g_file2.fp);
		g_file2.fp = NULL;
	}

	return 0;
}