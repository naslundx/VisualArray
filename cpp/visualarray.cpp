/* TODO:
 * Complete the VisualArrayData class - it should be a wrapper of int that reports all changes to its parent
 * Make sure everything compiles
 * Fix "rendering" in console to debug (forget about colors and highlights)
 *
 * When everything works:
 * Template VisualArray and VisualArrayData to work with arbitrary members
 * Fix proper rendering and interactivity (play/pause, step next)
 */
 
//template<class T>
VisualArrayData::VisualArrayData() {
	parent = NULL;
}

//template<class T>
VisualArrayData::VisualArrayData(int _pos, VisualArray* _parent) {
	pos = _pos;
	parent = _parent;
}

//template<class T>
VisualArrayData::operator int() {
	// not sure how to do this
	
	// how to report changes:
	//parent->addSetEvent(this->pos, this->data);
}

// many operators on VisualArrayData missing

//template<class T>
VisualArray::VisualArray(int size) {
	if (size>0) {
		mData = new VisualArrayData[size];
		mOriginal = new VisualArrayData[size];
		mSize = size;
		
		for (int i=0; i<size; i++) {
			mData = VisualArrayData(i, this);
			mOriginal = VisualArrayData(i, this);
		}
	}
}

//TODO: Allow to init with existing array and {...} as in C++11

//template<class T>
VisualArray::~VisualArray() {
	delete[] mData;
	delete[] mOriginal;
}

//template<class T>
VisualArrayData VisualArray::operator[](int i) const {
	return mData[i];
}

//template<class T>
VisualArrayData& VisualArray::operator [](const int i) {
	// Note: History is tracked from the VisualArrayData class
	return &(mData[i]);
}

//template<class T>
void VisualArray::gfxHighlight(int index, Color color) {
	if (index >= 0 && index < mSize) {
		VisualArrayHistory event;
		
		event.type = VisualArray.HISTORY_TYPE.HIGHLIGHT;
		event.pos = index;
		event.color = color;

		mHistory.push_back(event);
	}
}

//template<class T>
void VisualArray::gfxColor(int index, Color) {
	if (index >= 0 && index < mSize) {
		VisualArrayHistory event;
		
		event.type = VisualArray.HISTORY_TYPE.COLOR;
		event.pos = index;
		event.color = color;

		mHistory.push_back(op);
	}
}

//template<class T>
void VisualArray::gfxDecolor(int index) {
	if (index >= 0 && index < mSize) {
		VisualArrayHistory event;
		
		event.type = VisualArray.HISTORY_TYPE.DECOLOR;
		event.pos = index;

		mHistory.push_back(op);
	}
}

//template<class T>
void VisualArray::gfxSeparate(int leftindex, float size, Color color) {
	if (leftindex >= -1 && index <= mSize) {
		VisualArrayHistory event;
		
		event.type = VisualArray.HISTORY_TYPE.SEPARATE;
		event.pos = leftindex;
		event.size = size;
		event.color = color;

		mHistory.push_back(op);
	}
}

//template<class T>
void VisualArray::gfxDeseparate(int leftindex) {
	if (leftindex >= -1 && index <= mSize) {
		VisualArrayHistory event;
		
		event.type = VisualArray.HISTORY_TYPE.DESEPARATE;
		event.pos = index;

		mHistory.push_back(op);
	}
}

//template<class T>
void VisualArray::hideLastOperation() {
	if (!mHistory.empty()) {
		mHistory.pop_back();
	}
}

//template<class T>
void VisualArray::clearHistory() {
	mHistory.clear();
	for (int i=0; i<mSize; i++) {
		mOriginal[i] = mData[i];
	}
	mGraphicsReady = true;
}

//template<class T>
void VisualArray::addSetEvent(int pos, int data) {
	VisualArrayHistory event;
	event.type = HISTORY_TYPE.SET;
	event.pos = pos;
	event.data = data;
	mHistory.push_back(event);
}

//template<class T>
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

//template<class T>
VisualArrayHistory VisualArray::nextOperation() {
	VisualArrayHistory op = mHistory.pop_front(); 
	
	if (op[0] == HISTORY_TYPE.SET) {
		if (!mHistory.empty()) {
			VisualArrayHistory opb = mHistory.pop_front();

			// Check if swap
			if (opb.event == HISTORY_TYPE.SET && op.data == mOriginal[opb.pos] && opb.data == mOriginal[op.pos]) {
				mOriginal[op.pos] = op.data;
				mOriginal[opb.pos] = opb.data;
				
				op.event = HISTORY_TYPE.SWAP;
				op.data = opb.pos;

				return op;
			}
			else {
				mHistory.push_front(opb);
			}
		}

		// If we didn't return already, we should perform set
		mOriginal[op.pos] = op.data;
	}

	return op;
}

//template<class T>
void VisualArray::renderNext() {
	std::vector<int>::iterator it; 
	for (it = mLastHighlights.begin(); it != mLastHighlights.end(); ++it) {
		// Set rectangle to default color
	}

	if (!mHistory.empty()) {
		VisualArrayHistory op = nextOperation();

		// Render this operation
	}
}
