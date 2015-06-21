#include <iostream>
#include "visualarray.h"

//TODO: Write a sorting algorithm to use for debugging.

int main() {
	VisualArray<int> array(10);

	for (int i=9; i>=0; i--) {
		array[9-i] = i;
	}

	array.clearHistory();

	int temp = array[3];
	array[3] = array[8];
	array[8] = temp;
	array.gfxSeparate(3, 2.5f, Color(3));
	
	//array[9] = 100;

	/*array[0] += -array[0];
	array[1] += 10 + array[1];
	array[2] *= 2 * array[2];
	array[3]++;
	--array[4];
	array[5] = 2.5;
	array[6] = 3.7f - array[4];
	float temp2 = array[7];
	array[8] = temp2 + array[6] + 3;*/

	array.render();

	return 0;
}