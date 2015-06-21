#include <iostream>
#include "visualarray.h"

//TODO: Write a sorting algorithm to use for debugging.

int main() {
	std::cout << "Creating";
	VisualArray array(10);

	for (int i=9; i>=0; i--) {
		array[9-i] = i;
	}

	if (array[0] != array[5]) {
		array[0] += -array[0];
		array[1] += 10;
		array[2] *= 2 * array[2];
		array[3]++;
		--array[4];
	}

	array.clearHistory();
	array.render();

	return 0;
}