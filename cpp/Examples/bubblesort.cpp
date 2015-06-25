#include <stdlib.h>  
#include <time.h>   
#include "visualarray.h"

void bubbleSort(int* array, int n) {
	for (int i=n-1; i>=0; i--) {
		for (int j=0; j<=n; j++) {
			if (array[j] > array[j+1]) {
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}

int main() {
	const int SIZE = 10;
	VisualArray<int> varray = VisualArray(SIZE);
	srand(time(NULL));
	for (int i=0; i<SIZE; i++) {
		varray[i] = (rand() % 40) + 10;
	}
	bubbleSort(varray, SIZE);
	varray.render();

	return 0;
}