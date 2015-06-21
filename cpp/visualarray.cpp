/* TODO:
 * Complete the VisualArrayData class - it should be a wrapper of int that reports all changes to its parent
 * Make sure everything compiles
 * Fix "rendering" in console to debug (forget about colors and highlights)
 *
 * When everything works:
 * Template VisualArray and VisualArrayData to work with arbitrary members
 * Fix proper rendering and interactivity (play/pause, step next)
 */

 #include "visualarray.h"
 
//template<typename T>
VisualArrayData::VisualArrayData() {
	parent = NULL;
}

//template<typename T>
VisualArrayData::VisualArrayData(int _pos, VisualArray* _parent) {
	pos = _pos;
	parent = _parent;
}

//template<typename T>
VisualArrayData::operator int() {
	return this->data; 
}

//template<typename T>
VisualArrayData& VisualArrayData::operator=(const int& other) {
	data = other;
	parent->addSetEvent(this->pos, this->data);

	return *this;
}

/*VisualArrayData& VisualArrayData::operator=(const VisualArrayData& other) {
	data = other;
	parent->addSetEvent(this->pos, this->data);

	return *this;
}*/

VisualArrayData& VisualArrayData::operator += (VisualArrayData& right) {
	this->data += right;
	return *this;
}

VisualArrayData& VisualArrayData::operator -= (VisualArrayData& right) {
	this->data -= right;
	return *this;
}

VisualArrayData& VisualArrayData::operator *= (VisualArrayData& right) {
	this->data = this->data * right;
	return *this;
}

VisualArrayData& VisualArrayData::operator /= (VisualArrayData& right) {
	this->data = this->data / right;
	return *this;
}

VisualArrayData& VisualArrayData::operator += (int right) {
	this->data += right;
	return *this;
}

VisualArrayData& VisualArrayData::operator -= (int right) {
	this->data -= right;
	return *this;
}

VisualArrayData& VisualArrayData::operator *= (int right) {
	this->data *= right;
	return *this;
}

VisualArrayData& VisualArrayData::operator /= (int right) {
	this->data /= right;
	return *this;
}

VisualArrayData& VisualArrayData::operator++() {
	++data;
	return *this;
}

VisualArrayData VisualArrayData::operator++(int unused) {
	VisualArrayData result = *this;
	++data;
	return result;
}

VisualArrayData& VisualArrayData::operator--() {
	--data;
	return *this;
}

VisualArrayData VisualArrayData::operator--(int unused) {
	VisualArrayData result = *this;
	--data;
	return result;
}

//template<typename T>
VisualArray::VisualArray(int size) {
	mGraphicsReady = false;

	if (size>0) {
		//mData = new int[size];
		//mOriginal = new int[size];
		mData = new VisualArrayData[size];
		mOriginal = new VisualArrayData[size];
		mSize = size;
		
		for (int i=0; i<size; i++) {
			mData[i] = VisualArrayData(i, this);
			mOriginal[i] = VisualArrayData(i, this);
		}
	}
}

//TODO: Allow to init with existing array and {...} as in C++11

//template<typename T>
VisualArray::~VisualArray() {
	delete[] mData;
	delete[] mOriginal;
}

//template<typename T>
VisualArrayData& VisualArray::operator [](const int i) {
	return (mData[i]);
}

//template<typename T>
void VisualArray::gfxHighlight(int index, Color color) {
	if (index >= 0 && index < mSize) {
		VisualArrayHistory event;
		
		event.type = HIGHLIGHT;
		event.pos = index;
		event.color = color;

		mHistory.push_back(event);
	}
}

//template<typename T>
void VisualArray::gfxColor(int index, Color color) {
	if (index >= 0 && index < mSize) {
		VisualArrayHistory event;
		
		event.type = COLOR;
		event.pos = index;
		event.color = color;

		mHistory.push_back(event);
	}
}

//template<typename T>
void VisualArray::gfxDecolor(int index) {
	if (index >= 0 && index < mSize) {
		VisualArrayHistory event;
		
		event.type = DECOLOR;
		event.pos = index;

		mHistory.push_back(event);
	}
}

//template<typename T>
void VisualArray::gfxSeparate(int leftindex, float size, Color color) {
	if (leftindex >= -1 && leftindex <= mSize) {
		VisualArrayHistory event;
		
		event.type = SEPARATE;
		event.pos = leftindex;
		event.size = size;
		event.color = color;

		mHistory.push_back(event);
	}
}

//template<typename T>
void VisualArray::gfxDeseparate(int leftindex) {
	if (leftindex >= -1 && leftindex <= mSize) {
		VisualArrayHistory event;
		
		event.type = DESEPARATE;
		event.pos = leftindex;

		mHistory.push_back(event);
	}
}

//template<typename T>
void VisualArray::hideLastOperation() {
	if (!mHistory.empty()) {
		mHistory.pop_back();
	}
}

//template<typename T>
void VisualArray::clearHistory() {
	mHistory.clear();
	for (int i=0; i<mSize; i++) {
		mOriginal[i] = mData[i];
	}
	mGraphicsReady = true;
}

//template<typename T>
void VisualArray::addSetEvent(int pos, int data) {
	VisualArrayHistory event;
	event.type = SET;
	event.pos = pos;
	event.data = data;
	mHistory.push_back(event);
}

// Temporary print function
void temp_print(VisualArrayData* array, int length) {
	
}

//template<typename T>
void VisualArray::render() {
	TODO: FIX
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


	// ------------------------------------------

	// Temporary debug
	std::cout << "\n";
	for (int i=0; i<mSize; i++) {
		std::cout << mOriginal[i] << " ";
	}

	while (!mHistory.empty()) {
		VisualArrayHistory event = nextOperation();

		std::cout << "\n";
		for (int i=0; i<mSize; i++) {
			std::cout << mOriginal[i] << " ";
		}
	}

	std::cout << "\n";
}

//template<typename T>
VisualArrayHistory VisualArray::nextOperation() {
	VisualArrayHistory op = mHistory.front(); 
	mHistory.pop_front();
	
	if (op.type == SET) {
		if (!mHistory.empty()) {
			VisualArrayHistory opb = mHistory.front();

			// Check if swap
			if (opb.type == SET && op.data == mOriginal[opb.pos] && opb.data == mOriginal[op.pos]) {
				mOriginal[op.pos] = op.data;
				mOriginal[opb.pos] = opb.data;
				
				op.type = SWAP;
				op.pos2 = opb.pos;

				mHistory.pop_front();

				return op;
			}
		}

		// If we didn't return already, we should perform set
		mOriginal[op.pos] = op.data;
	}

	return op;
}

//template<typename T>
void VisualArray::renderNext() {
	std::vector<int>::iterator it; 
	for (it = mLastHighlights.begin(); it != mLastHighlights.end(); ++it) {
		// Set rectangle to default color
	}
	mLastHighlights.clear();

	if (!mHistory.empty()) {
		VisualArrayHistory op = nextOperation();

		// Render this operation
	}
}
