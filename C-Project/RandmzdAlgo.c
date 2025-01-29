#include <stdio.h>
#include <time.h>
#include <c-project.h>

void RandomizedAlgos(int argc, char* argv[])
{
	time_t now;
	int Arr[10] = { 44, 22, 99, 111, 9, 23, 45, 67, 89, 100 };
	Srand((unsigned)time(&now));
	RandmzdQuickSort(Arr, 0, 9);
	printIntArray(Arr, 10);
	return;
}

void printIntArray(int* array, int size)
{
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	return;
}

#define SWAPV(v, i, j)	{\
											int temp;\
											temp = v[i];\
											v[i] = v[j];\
											v[j] = temp;\
										}

void RandmzdQuickSort(int Arr[], int i, int j)
{
	int k, pivot;
	if (i < j) {
		pivot = i + (Rand() % (j-i+1));
		printf("i = %d, j = %d, Pivot = %d\n", i, j, pivot);
		SWAPV(Arr, i, pivot);
		pivot = i;
		for (k = i + 1; k <= j; k++) {
			if (Arr[k] < Arr[i]) {
				pivot += 1;
				SWAPV(Arr, k, pivot);
			}
		}
		SWAPV(Arr, i, pivot);
		RandmzdQuickSort(Arr, i, pivot - 1);
		RandmzdQuickSort(Arr, pivot + 1, j);
	}
	return;
}