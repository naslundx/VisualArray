/* TODO
 *
 * So many things
 */

template<class T>
VisualArray::VisualArray(int size) {
	if (size>0) {
		mData = new T[size];
		mOriginal = new T[size];
		mSize = 0;
	}
}

//TODO: Allow to init with existing array and {...} as in C++11

template<class T>
VisualArray::~VisualArray() {
	delete[] mData;
	delete[] mOriginal;
}

template<class T>
T VisualArray::operator[](int i) const {
	return mData[i];
}

template<class T>
T& VisualArray::operator [](const int i) {
	// This will not allow me to notice change :(
	// Figure out how to do this without specific set function

	// Add change to mHistory:
	std::vector<int> op;
	op.push_back(HISTORY_TYPE.SET);

	//...

	mHistory.push_back(op);
}

template<class T>
void VisualArray::gfxHighlight(int index, Color) {
	if (index >= 0 && index < mSize) {
		std::vector<int> op;  // std::vector<int> IS THE WRONG THING TO USE, USE THE VisualArrayData STRUCT!
		op.push_back(HISTORY_TYPE.HIGHLIGHT);
		op.push_back(index);

		// handle color

		mHistory.push_back(op);
	}
}

template<class T>
void VisualArray::gfxColor(int index, Color) {
	if (index >= 0 && index < mSize) {
		std::vector<int> op; // std::vector<int> IS THE WRONG THING TO USE, USE THE VisualArrayData STRUCT!
		op.push_back(HISTORY_TYPE.COLOR);
		op.push_back(index);

		// handle color

		mHistory.push_back(op);
	}
}

template<class T>
void VisualArray::gfxDecolor(int index) {
	if (index >= 0 && index < mSize) {
		std::vector<int> op; // std::vector<int> IS THE WRONG THING TO USE, USE THE VisualArrayData STRUCT!
		op.push_back(HISTORY_TYPE.DECOLOR);
		op.push_back(index);

		// handle color

		mHistory.push_back(op);
	}
}

template<class T>
void VisualArray::gfxSeparate(int leftindex, int size, Color) {
	if (leftindex >= -1 && index <= mSize) {
		std::vector<int> op; // std::vector<int> IS THE WRONG THING TO USE, USE THE VisualArrayData STRUCT!
		op.push_back(HISTORY_TYPE.SEPARATE);
		op.push_back(index);
		op.push_back(size);

		// handle color

		mHistory.push_back(op);
	}

}

template<class T>
void VisualArray::gfxDeseparate(int leftindex) {
	if (leftindex >= -1 && index <= mSize) {
		std::vector<int> op; // std::vector<int> IS THE WRONG THING TO USE, USE THE VisualArrayData STRUCT!
		op.push_back(HISTORY_TYPE.DESEPARATE);
		op.push_back(index);

		// handle color

		mHistory.push_back(op);
	}

}

template<class T>
void VisualArray::hideLastOperation() {
	if (!mHistory.empty()) {
		mHistory.pop_back();
	}
}

template<class T>
void VisualArray::clearHistory() {
	mHistory.clear();
	for (int i=0; i<mSize; i++) {
		mOriginal[i] = mData[i];
	}
	mGraphicsReady = true;
}

template<class T>
void VisualArray::render() {
	if (!mGraphicsReady) {
		// There is no data in mOriginal!
		return;
	}

	// Init rendering window, create rectangles
	mRectangles.clear();
	mLastHighlights.clear();

	// ... 

	// Start rendering loop
	// ...
}

template<class T>
std::vector<int> VisualArray::nextOperation() {
	std::vector<int> op = mHistory.pop_front(); // std::vector<int> IS THE WRONG THING TO USE, USE THE VisualArrayData STRUCT!

	if (op[0] == HISTORY_TYPE.SET) {
		if (!mHistory.empty()) {
			std::vector<int> opb = mHistory.pop_front(); // std::vector<int> IS THE WRONG THING TO USE, USE THE VisualArrayData STRUCT!

			// Check if swap
			if (opb[0] == HISTORY_TYPE.SET && op[2] == mOriginal[opb[1]] && opb[2] == mOriginal[op[1]]) {
				op[0] = HISTORY_TYPE.SWAP;
				op[2] = opb[1];

				// Swap elements
				// ...

				return op;
			}
			else {
				mHistory.push_front(opb);
			}
		}

		// If we didn't return already, we should perform set
		mOriginal[op[1]] = op[2];
	}

	return op;
}

template<class T>
void VisualArray::renderNext() {
	std::vector<int>::iterator it; 
	for (it = mLastHighlights.begin(); it != mLastHighlights.end(); ++it) {
		// Set rectangle to default color
	}

	if (!mHistory.empty()) {
		std::vector<int> op = nextOperation(); // std::vector<int> IS THE WRONG THING TO USE, USE THE VisualArrayData STRUCT!

		// Render this operation
	}
}