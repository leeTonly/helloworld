#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int strChkAcct(char *sArgs, ...)
{
	char c;
	char sAcct[32+1];
	char sErrMsg[256+1];
	char *pt = NULL;
	char *qt = NULL;
	int n = 0;
	int iArgs = 0;
	static unsigned char ascii_tab[] = {'0','1','2','3','4','5','6','7','8','9',
										'A','B','C','D','E','F','G','H','I','J','K','L',
										'M','N','O','P','Q','R','S','T','U','V','W','X',
										'Y','Z','a','b','c','d','e','f','g','h','i','j',
										'k','l','m','n','o','p','q','r','s','t','u','v',
										'w','x','y','z','.',',','-','_','(',')','/','=',
										'+','?','!','&','*',';','@','#',':','%','[',']',
										'\n','\r','\t',' '};

	/*定义可变参数*/
	va_list arg_ptr;
	va_start(arg_ptr, sArgs);
	/*依次取可变参数中的账号*/
	iArgs = atoi(sArgs);
	while(iArgs != 0) {
		n = 1;
		pt = NULL;
		qt = NULL;
		memset(sAcct, 0x00, sizeof(sAcct));
		memset(sErrMsg, 0x00, sizeof(sErrMsg));

		qt = va_arg(arg_ptr, char*);
		strcpy(sAcct, qt);
		printf("qt -> sAcct[%d][%s]\n", iArgs, sAcct);

		if(strlen(sAcct) == 0) {
			iArgs--;
			continue;
		}

		/*依次取账号中的字符*/
		pt = sAcct;
		for( ; *pt != '\0'; ) {
			qt = NULL;
			/*判断是否在人行允许的X字符集内*/
			c = *pt;
			qt = strchr(ascii_tab, c);
			if(qt != NULL) {
				n++;
				pt++;
				continue;
			} else {
				sprintf(sErrMsg, "账号[%s]中第[%d]个字符非法!",sAcct, n);
				printf("账号[%s]中第[%d]个字符非法!\n", sAcct, n);
				va_end(arg_ptr);
				return -1;
			}
		}
		iArgs--;
	}
	va_end(arg_ptr);

	return 0;
}

int main(int argc, char const *argv[])
{
	/* code */
	strChkAcct("3", "110021518010000378", "101001512010008414", "9550880000012200156");
	
	return 0;
}