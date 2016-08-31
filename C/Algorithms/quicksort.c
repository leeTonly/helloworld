#include <stdio.h>

/*快速查找，需要定义最左边的值为哨兵，然后从右从左开始查找，把左边比哨兵大的和右边比哨兵小的互换位置，
 *当两边找到同个值时，将当前值和哨兵位置互换，当次结束。再分别对左边和右边两边的小组再做同样排序，
 *一直排序下去，则最终排序完成。
 */

void quickSort(int *arr, int left, int right);

int main(int argc, char const *argv[])
{
	int array[128] = {0};
	int length = 0;
	int i = 0;

	scanf("%d", &length);
	for(i=0; i< length; i++) {
		scanf("%d", &array[i]);
	}

	for(i=0; i<length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	quickSort(array, 0, length-1);


	for(i=0; i<length; i++) {
		printf("%d ", array[i]);
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