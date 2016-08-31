#include <stdio.h>

/*冒泡排序*/

int main(int argc, char const *argv[])
{
	/* code */
	int idx = 0;

	int arr[] = {1,3,5,7,9,2,3,4,8,6,7,0,10,2,11,5};

	for(idx = 0; idx < sizeof(arr)/sizeof(int)-1; idx++) {
		printf("%d ",arr[idx]);
	}
	printf("\n");

	sort(arr, sizeof(arr)/sizeof(int));

	for(idx = 0; idx < sizeof(arr)/sizeof(int)-1; idx++) {
		printf("%d ",arr[idx]);
	}
	printf("\n");

	return 0;
}

int sort(int *array, int length) 
{
	int i = 0;
	int j= 0;
	int idx = 0;
	int tmp = 0;
	char changed = 1;

	for(i = length-1; i>0 && changed; i--) {
		changed = 0;
		for(j = 0; j< i; j++) {
			if(array[j] > array[j+1]) {
				tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
				changed = 1;
			}
		}

		printf("%d->",length-1-i);
		for(idx = 0; idx < length-1; idx++) {
			printf("%d ",array[idx]);
		}
		printf("\n");
	}

	return 0;
}