#include <stdio.h>
#include <string.h>

/*此处代码用于体验栈结构，
 *用栈来判断当前传入的字符串是否回文结构，也就是中间对称。
 */

struct stack{
	char data[128];
	int top;
};

int main(int argc, char const *argv[])
{
	/* code */
	char string[128];
	struct stack st;
	int i=0;
	char ifsame = 1;
	int mid = 0;

	memset(string, 0x00, sizeof(string));
	memset(&st, 0x00, sizeof(struct stack));

	//gets(string);
	scanf("%s",string);
	printf("You enter :%s,strlen=%d\n",string,strlen(string));

	mid = strlen(string)/2;

	/*将string里的前半段存入栈中*/
	for(i=0; i<mid; i++) {
		st.data[i] = string[i];
		st.top = i;
	}

	if((strlen(string)%2) == 1) {
		mid++;	
	}

	for(i=mid; i<strlen(string); i++) {
		if(st.data[st.top] == string[i]) {
			st.top--;
		} else {
			ifsame=0;
			break;
		}
	}

	if(ifsame == 1) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}

	return 0;
}