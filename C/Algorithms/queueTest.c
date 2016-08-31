#include <stdio.h>
#include <string.h>
/*此代码在于解决QQ号码解密问题：
 *将一个QQ号码按照一定方式加密，然后代码进行解密，则得到QQ号码
 *将加密数据的首数字放在末尾，第二个数据去掉；将第三个数据放在末尾，将第四个数据去掉，以此类推
 *直到所有数据去掉，再按刚刚去掉的数据按顺序写下，则是QQ号码
 *此处用队列来实现解密*/

/*737222666 --> 772662623*/

struct queue{
	int q[128];
	int head;
	int tail;
};


int main(int argc, char const *argv[])
{
	/* code */
	struct queue q;
	int qqnumberLength = 0;
	int realqq[128] = {0};
	int i=0;
	int j=0;

	memset(&q, 0x00, sizeof(struct queue));
	printf("请输入QQ号码长度：");
	scanf("%d", &qqnumberLength);
	printf("请输入QQ号码，数字间以空格隔开：");
	for(i=0; i<qqnumberLength; i++) {
		scanf("%d", &q.q[i]);
	}

	q.head = 0;
	q.tail = qqnumberLength;

	while(q.head != q.tail) {
		realqq[j++] = q.q[q.head++];
		q.q[q.tail++] = q.q[q.head++];
	}

	printf("解密后的QQ号为：")
	for(i=0; i< qqnumberLength; i++) {
		printf("%d",realqq[i]);
	}
	printf("\n");

	return 0;
}