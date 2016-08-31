#include <stdio.h>

/*此处代码对应于啊哈算法的第一个练习，也就是ISBN码买书的问题：
 *假设学校要买书，找N位同学来写出想买的书的ISBN码（每本书的ISBN码唯一），
 *这时候，就需要对N位同学写出的ISBN码进行去重，因为有可能有两位同学都想买同一本书；
 *还需要对所有ISBN码进行排序，最后按序输出。
 *
 *这里可以用两个方法：1.先去重，再排序；
 *					2.先排充，再去重；
 *这里需要根据N的范围和ISBN码的范围来选择排序方法：
 *如果N的范围很大，则不能用冒泡算法，所耗时间过长，应用桶排序O(N+M)或者快速排序。
 *如果ISBN的值太大，则不能用桶排序，没有办法创建太大的数组，应该用冒泡算法O（N^2）或者快速排序。
 *结合情况，建议用快速排序O(NlogN)，
 */

void quickSort(int *arr, int left, int right);

int main(int argc, char const *argv[])
{
	/* code */
	int array[128] = {0};
	int number = 0;
	int i = 0;

	printf("请输入书本数：");
	scanf("%d", &number);
	printf("请输入所有书本ISBN：");
	for(i=0; i<number; i++) {
		scanf("%d", &array[i]);
	}

	/*用快速排序先对所有ISBN排序*/
	quickSort(array, 0, number-1);

	/*对排好序的ISBN进行去重打印*/
	for(i = 0; i<number; i++) {
		if(i>0 && array[i]!=array[i-1] || i==0) {
			printf("%d ",array[i]);
		}
	}
	printf("\n");

	return 0;
}



void quickSort(int *arr, int left, int right) 
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	int bing = 0;

	/*如果left大于right，则没必要再排序*/
	if(left > right) {
		return;
	}

	i = left;
	j = right;
	/*获取哨兵值，哨兵值为最左边的值*/
	bing = arr[left]; 
	while(i != j) {

		/*要从右开始比较*/
		while(arr[j]>=bing && i<j) {
			j--;
		}

		/*从左开始和哨兵比较*/
		while(arr[i]<=bing && i<j) {
			i++;
		}

		/*从左和从右都找完后，左还小于右的话，则值互换*/
		if(i < j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}

	/*将i=j的值和最左边哨兵互换值*/
	arr[left] = arr[i];
	arr[i] = bing;

	/*对哨兵左边的分组进行排序*/
	quickSort(arr, left, i-1);
	/*对哨兵右边的分组进行排序*/
	quickSort(arr, i+1, right);

}