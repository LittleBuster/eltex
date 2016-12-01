#include <stdio.h>


int main(void)
{
	int arr[10] = {100, 44, 22, 55, 23, 64, 98, 23, 54, 727};
	int max = arr[0];

	for (unsigned i = 1; i < 10; i++) {
		if (arr[i] > max)
			max = arr[i];
	}
	printf("Max: %d\n", max);
	return 0;
}