#include "stdio.h"

/*二分法查找前提，数组是已经排好序的*/

int main(int argc, char const *argv[])
{

	int array[] = {1,2,3,4,5,6,8,10,12,13,14,15,18,20};

	int idx = 0;
	int result = 0;

	for(idx = 0; idx<sizeof(array)/sizeof(int); idx++) {
		printf("%d ",array[idx]);
	}
	printf("\n");

	scanf("%d", &idx);

	printf("You enter [%d]\n", idx);

	result = search(array, 0, sizeof(array)/sizeof(int)-1, idx);

	printf("result idx is [%d]\n",result);

	return 0;
}

int search(int *arr, int start, int end, int value)
{
	int mid = (start+end)/2;

	if(start > end) {
		return -1;
	} else {
		if(arr[mid] == value) {
			return mid;
		} else if (arr[mid] < value) {
			return search(arr, mid+1, end, value);
		} else {
			return search(arr, start, mid-1, value);
		}
	}
}