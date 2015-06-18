/* TODO
 *
 * So many things
 * Missing: Window and graphics management
 */

template<class T>
VisualArray::VisualArray(int size) {
	if (size>0) {
		mData = new T[size];
		mOriginal = new T[size];
		mSize = 0;
	}
}

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
	// Will this allow me to notice change?
}

void VisualArray::gfxHighlight(index, Color) {

}

void VisualArray::gfxColor(index, Color) {

}

void VisualArray::gfxDecolor(index) {

}

void VisualArray::gfxSeparate(index) {

}

void VisualArray::hideLastOperation() {
	if (!mHistory.empty()) {
		mHistory.pop_back();
	}
}

void VisualArray::clearHistory() {
	mHistory.clear();
}

void VisualArray::render() {

}

std::vector<int> VisualArray::nextOperation() {

}

void VisualArray::renderNext() {

}