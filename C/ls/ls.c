#include <stdio.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <dirent.h>
#include <sys/dir.h>


#define SUCCESS 		(0)
#define FAIL			(-1)
#define OUTPUT_NORMAL  	(1<<1)
#define OUTPUT_LIST		(1<<2)
#define OUTPUT_ALL		(1<<3)
#define CUR_PATH		"./"

/*
#define __DEBUG__
*/

#ifdef __DEBUG__
#define DBGPRINT(format,...) printf("["__FILE__"],%05d:"format"\n",__LINE__,##__VA_ARGS__)
#else
#define DBGPRINT(format,...)   
#endif


typedef struct _lsParam
{
	char cmd[64];
	char Desc[1024];
	char output_mode;
	char output_mode_mask;
}E_lsParam;

typedef struct _lsSys
{
	char filepath[1024];
	char output_mode;
	struct stat st;
}E_lsSys;

E_lsParam CMD_LIST[]=
{
	{"", "默认输出", OUTPUT_NORMAL, ~OUTPUT_NORMAL},
	{"-a", "显示全部文件", OUTPUT_ALL, ~OUTPUT_ALL},
	{"-l", "显示详细列表", OUTPUT_LIST, ~OUTPUT_LIST},
	{"-al", "详细列表形式显示所有文件", OUTPUT_ALL|OUTPUT_LIST, ~(OUTPUT_ALL|OUTPUT_LIST)},
	{"-la", "详细列表形式显示所有文件", OUTPUT_ALL|OUTPUT_LIST, ~(OUTPUT_ALL|OUTPUT_LIST)}
};


void printUsage(void)
{
	printf("Usage: ls <option> <filepath>\n");
	return;
}

char *get_usr_name(uid_t uid)
{
	struct passwd *pw;
	pw = getpwuid(uid);
	
	return pw->pw_name;
}

char *get_grp_name(gid_t gid)
{
	struct group *gr;
	gr = getgrgid(gid);
	
	return gr->gr_name;
}

void printtype(struct stat st)
{
    /* check the type of the file */
    if((st.st_mode & S_IFMT) == S_IFSOCK) printf("s");
    else if((st.st_mode & S_IFMT) == S_IFLNK) printf("l");
    else if((st.st_mode & S_IFMT) == S_IFDIR) printf("d");
    else if((st.st_mode & S_IFMT) == S_IFREG) printf("-");
    else if((st.st_mode & S_IFMT) == S_IFBLK) printf("b");
    else if((st.st_mode & S_IFMT) == S_IFCHR) printf("c");
    else if((st.st_mode & S_IFMT) == S_IFIFO) printf("f");
    else printf(" ");
	return;
}


void printperm(struct stat st)
{
    /* check the user's permisions */
    if((st.st_mode & S_IRWXU) == S_IRUSR) printf("r--");
    else if((st.st_mode & S_IRWXU) == S_IWUSR) printf("-w-");
    else if((st.st_mode & S_IRWXU) == S_IXUSR) printf("--x");
    else if((st.st_mode & S_IRWXU) == (S_IRUSR|S_IWUSR)) printf("rw-");
    else if((st.st_mode & S_IRWXU) == (S_IRUSR|S_IXUSR)) printf("r-x");
    else if((st.st_mode & S_IRWXU) == (S_IXUSR|S_IWUSR)) printf("-wx");
    else if((st.st_mode & S_IRWXU) == (S_IXUSR|S_IWUSR|S_IRUSR)) printf("rwx");
    else printf("---");
    /* check the group's permisions */
    if((st.st_mode & S_IRWXG) == S_IRGRP) printf("r--");
    else if((st.st_mode & S_IRWXG) == S_IWGRP) printf("-w-");
    else if((st.st_mode & S_IRWXG) == S_IXGRP) printf("--x");
    else if((st.st_mode & S_IRWXG) == (S_IRGRP|S_IWGRP)) printf("rw-");
    else if((st.st_mode & S_IRWXG) == (S_IRGRP|S_IXGRP)) printf("r-x");
    else if((st.st_mode & S_IRWXG) == (S_IXGRP|S_IWGRP)) printf("-wx");
    else if((st.st_mode & S_IRWXG) == (S_IXGRP|S_IWGRP|S_IRGRP)) printf("rwx");
    else printf("---");
    /* check the other's permisions */
    if((st.st_mode & S_IRWXO) == S_IROTH) printf("r--");
    else if((st.st_mode & S_IRWXO) == S_IWOTH) printf("-w-");
    else if((st.st_mode & S_IRWXO) == S_IXOTH) printf("--x");
    else if((st.st_mode & S_IRWXO) == (S_IROTH|S_IWOTH)) printf("rw-");
    else if((st.st_mode & S_IRWXO) == (S_IROTH|S_IXOTH)) printf("r-x");
    else if((st.st_mode & S_IRWXO) == (S_IXOTH|S_IWOTH)) printf("-wx");
    else if((st.st_mode & S_IRWXO) == (S_IXOTH|S_IWOTH|S_IROTH)) printf("rwx");
    else printf("---");
}

void printtime(struct stat st)
{
	struct tm *ptm, *plt;
	time_t ltime;

	ltime = time((time_t*)NULL);
	plt = localtime(&ltime);
	ptm = localtime(&st.st_ctime);
	
	if ((plt->tm_year == ptm->tm_year) && (plt->tm_mon == ptm->tm_mon) && (ptm->tm_mday <= plt->tm_mday))
	{
		printf("%2d月%02d %02d时%02d ", ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min);
	} else {
		printf("%2d月%02d %-6d ", ptm->tm_mon+1,ptm->tm_mday,ptm->tm_year);
	}
	
}

void printOneLineListMode(char *filepath, char *filename)
{
	struct stat st;
	char pathname[1024];

	memset(pathname, 0, sizeof(pathname));
	strcpy(pathname, filepath);
	strcat(pathname, "/");
	strcat(pathname, filename);
	
	stat(filename, &st);
	
	printtype(st);
	printperm(st);
	printf(" ");
	printf("%4d ", st.st_nlink);
	printf("%-8s %-8s ", get_usr_name(st.st_uid), get_grp_name(st.st_gid));
	printf("%10d ", (int)st.st_size);
	printtime(st);
	printf("%-4s\n", filename);
	
	return;
}

int fgGetMaxFilenameFromPath(char *filepath, int *ilength)
{
	DIR *pdir;
	struct dirent *pdirent;
	int len = 0;
	int tmp = 0;
	
	if((pdir = opendir(filepath)) == NULL) {
		perror("opendir");
		return FAIL;
	}

	while((pdirent=readdir(pdir)) != NULL)
	{
		tmp = strlen(pdirent->d_name);
		len = (len > tmp)?len:tmp;
	}
	
	*ilength = len;
	
	if(closedir(pdir)){
		perror("closedir");
		return FAIL;
	}
	
	return SUCCESS;
}

int fgAnalyzeParam(int argc, char const *argv[], E_lsSys *psys)
{
	int iRet = 0;
	int iloop, jargvloop;
	E_lsSys *sys = psys;

	switch(argc)
	{
		case 1:
			/*Cmd: ls 只有一个参数，则执行ls，路径为当前目录，模式为默认输出*/
			sys->output_mode = OUTPUT_NORMAL;
			memset(sys->filepath, 0, sizeof(sys->filepath));
			strcpy(sys->filepath, CUR_PATH);
			break;

		case 2:
			/*查询当前参数是否有定义*/
			for(iloop = 0; iloop < sizeof(CMD_LIST)/sizeof(E_lsParam); iloop++)
			{
				DBGPRINT("[DEBUG]argc=%d,iloop=%d,argv[1]=%s,CMD_LIST[iloop].cmd=%s,CMD_LIST[iloop].output_mode_mask=%x.",
						argc,  iloop, argv[1], CMD_LIST[iloop].cmd, CMD_LIST[iloop].output_mode_mask);
				if(strcmp(CMD_LIST[iloop].cmd, argv[1]) == 0)
				{
					DBGPRINT("[DEBUG]##%d",1);
					sys->output_mode = CMD_LIST[iloop].output_mode;
					memset(sys->filepath, 0, sizeof(sys->filepath));
					strcpy(sys->filepath, CUR_PATH);
					break;
				}
			}
			DBGPRINT("[DEBUG]##%d",2);
			if(strlen(sys->filepath) == 0)
			{
				/*当前参数没有定义，则认为是路径*/
				sys->output_mode |= OUTPUT_NORMAL;
				memset(sys->filepath, 0, sizeof(sys->filepath));
				strcpy(sys->filepath, argv[1]);			
			}
			break;

		default:
			/*轮询所有参数*/
			for(jargvloop = 1; jargvloop < argc; jargvloop++)
			{
				/*查询当前参数是否有定义*/
				for(iloop = 0; iloop < sizeof(CMD_LIST)/sizeof(E_lsParam); iloop++)
				{
					DBGPRINT("[DEBUG]argc=%d,jargvloop=%d,iloop=%d,argv[jargvloop]=%s,CMD_LIST[iloop].cmd=%s,CMD_LIST[iloop].output_mode_mask=%x.",
							argc, jargvloop, iloop, argv[jargvloop], CMD_LIST[iloop].cmd, CMD_LIST[iloop].output_mode_mask);
					if(strcmp(CMD_LIST[iloop].cmd, argv[jargvloop]) == 0)
					{
						DBGPRINT("[DEBUG]##%d",1);
						if((sys->output_mode & CMD_LIST[iloop].output_mode_mask) == 0) {
							sys->output_mode |= CMD_LIST[iloop].output_mode;
							DBGPRINT("[DEBUG]##%d",2);
						}
						break;
					}
				}
				DBGPRINT("[DEBUG]##%d",3);
				/*当前参数没有定义，则认为是路径*/
				memset(sys->filepath, 0, sizeof(sys->filepath));
				strcpy(sys->filepath, argv[jargvloop]);	
			}
			break;
	}

	DBGPRINT("filepath=%s",sys->filepath);
	
	if(lstat(sys->filepath, &sys->st))
	{
		perror("stat");
		return FAIL;
	}
	
	return SUCCESS;
}

int fgOutput(E_lsSys sys)
{
	int nRet;
	int sNamesOneLine = 0;
	struct stat sb1;
	char isfolder = 0;
	int iMaxLength = 0;
	struct dirent *pdirent;

	E_lsSys psys;
	DIR *pdir;
	
	memcpy(&psys, &sys, sizeof(E_lsSys));
	
	if((sys.st.st_mode & S_IFMT) == S_IFDIR)
	{
		/* 判断当前路径是否文件夹 */
		isfolder = 1;
	} else {
		/* 判断当前路径是否文件*/
		isfolder = 0;
	}
	
	if(isfolder) {

		nRet = fgGetMaxFilenameFromPath(sys.filepath, &iMaxLength);
		if(nRet != SUCCESS)
		{
			printf("fgGetMaxFilenameFromPath, FAIL\n");
			return FAIL;
		}
		
		DBGPRINT("iMaxLength=%d",iMaxLength);
		
		if((pdir = opendir(sys.filepath)) == NULL) {
			perror("opendir");
			return FAIL;
		}
		
		/* 如果是文件夹，则读取文件夹里的每一个文件 */
		while((pdirent=readdir(pdir)) != NULL)
		{			
			switch(sys.output_mode)
			{
				case OUTPUT_ALL|OUTPUT_LIST:
					printOneLineListMode(psys.filepath, pdirent->d_name);
					break;
				
				case OUTPUT_LIST:
					if(pdirent->d_name[0] == '.')
						break;
					printOneLineListMode(psys.filepath, pdirent->d_name);
					break;
					
				case OUTPUT_ALL:
					printf("%-*s  ", iMaxLength, pdirent->d_name);
					sNamesOneLine++;
					if(sNamesOneLine == 4)
					{
						sNamesOneLine=0;
						printf("\n");
					}
					break;	
					
				case OUTPUT_NORMAL:
					if(pdirent->d_name[0] == '.')
						break;
					printf("%-*s  ", iMaxLength, pdirent->d_name);
					sNamesOneLine++;
					if(sNamesOneLine == 4)
					{
						sNamesOneLine=0;
						printf("\n");
					}
					break;
				
				default:
					break;
			}				
		}
		
		if(sys.output_mode == OUTPUT_ALL || sys.output_mode == OUTPUT_NORMAL)
		{
			printf("\n");
		}
		
		if(closedir(pdir))
		{
			perror("closedir");
			return FAIL;
		}
	
	} else {
		switch(sys.output_mode)
		{
			case OUTPUT_ALL|OUTPUT_LIST:
			case OUTPUT_LIST:
				printtype(psys.st);
				printperm(psys.st);
				printf(" ");
				printf("%4d ", sys.st.st_nlink);
				printf("%-8s %-8s ", get_usr_name(sys.st.st_uid), get_grp_name(sys.st.st_gid));
				printf("%10d ", (int)sys.st.st_size);
				printtime(psys.st);
				printf("%-4s\n", sys.filepath);
				break;
				
			case OUTPUT_ALL:
			case OUTPUT_NORMAL:
				printf("%s\n", sys.filepath);
				break;
			
			default:
				break;
		}		
	}
	
	return SUCCESS;
}

int main(int argc, char const *argv[])
{
	int iRet = FAIL;
	E_lsSys lsSys;
	
	memset(lsSys, 0, sizeof(E_lsSys));
	
	
	iRet = fgAnalyzeParam(argc, argv, &lsSys);
	if(iRet != SUCCESS)
	{
		printUsage();
		exit(1);
	}
	
	DBGPRINT("[DEBUG]##filepath[%s], output_mode[%x], st_mode[%x]", lsSys.filepath, lsSys.output_mode, lsSys.st.st_mode);
	
	iRet = fgOutput(lsSys);
	if(iRet != SUCCESS)
	{
		printUsage();
		exit(1);
	}
	
	/* code */
	exit(0);
}