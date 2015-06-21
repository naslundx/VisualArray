#ifndef __VISUALARRAY_H__
#define __VISUALARRAY_H__

#include <vector>
#include <deque>
#include <iostream>

enum HISTORY_TYPE { SET, SWAP, COLOR, DECOLOR, HIGHLIGHT, SEPARATE, DESEPARATE };

template<typename T> class VisualArrayData;
struct Color { int i; }; // Just temporary

//template<typename T>
struct VisualArrayHistory {
	HISTORY_TYPE type;
	int pos, pos2;
	int data;
	float size;
	Color color;
};

//template<typename T>
class VisualArray {
public:
	VisualArray(int size);
	~VisualArray();

	//VisualArray(std::initializer_list<int> list);

	VisualArrayData<int>& operator [](const int i);
	//int& operator [](const int i);

	void addSetEvent(int pos, int data);
	void gfxHighlight(int index, Color);
	void gfxColor(int index, Color);
	void gfxDecolor(int index);
	void gfxSeparate(int leftindex, float size, Color);
	void gfxDeseparate(int leftindex);
	void hideLastOperation();
	void clearHistory();
	void render();

private:
	VisualArrayHistory nextOperation();
	void renderNext();

	bool mGraphicsReady;
	int mSize;
	VisualArrayData<int> *mData;
	int *mOriginal;
	std::deque< VisualArrayHistory > mHistory;
	std::vector<int> mRectangles;
	std::vector<int> mLastHighlights;

	Color gfxDefaultColor, gfxDefaultHighlightColor, gfxDefaultSeparatorColor;
};

template<typename T> class VisualArrayData {
private:
	T data;
	int pos;
	VisualArray* parent;

public:
	VisualArrayData();
	VisualArrayData(int pos, VisualArray* parent);

	T get() { return data; }

	void reportChange() {
		if (parent != NULL) {
			parent->addSetEvent(this->pos, this->data);
		}	
	}	

	operator T() {
		return (T)(this->data); 
	}

	VisualArrayData<T>& operator = (T other) {
		data = other;
		reportChange();
		return *this;
	}

	// VisualArrayData<T>& operator = (T& other);
	
	VisualArrayData<T>& operator += (VisualArrayData<T>& right) {
		this->data += right;
		reportChange();
		return *this;
	}
	VisualArrayData<T>& operator -= (VisualArrayData<T>& right) {
		this->data -= right;
		reportChange();
		return *this;
	}
	VisualArrayData<T>& operator *= (VisualArrayData<T>& right) {
		this->data *= right;
		reportChange();
		return *this;
	}
	VisualArrayData<T>& operator /= (VisualArrayData<T>& right) {
		this->data /= right;
		reportChange();
		return *this;
	}
	VisualArrayData<T>& operator %= (VisualArrayData<T>& right) {
		this->data %= right;
		reportChange();
		return *this;
	}
	
	VisualArrayData<T>& operator += (T right) {
		this->data += right;
		reportChange();
		return *this;
	}
	VisualArrayData<T>& operator -= (T right) {
		this->data -= right;
		reportChange();
		return *this;
	}
	VisualArrayData<T>& operator *= (T right) {
		this->data *= right;
		reportChange();
		return *this;
	}
	VisualArrayData<T>& operator /= (T right) {
		this->data /= right;
		reportChange();
		return *this;
	}
	VisualArrayData<T>& operator %= (T right) {
		this->data %= right;
		reportChange();
		return *this;
	}

	VisualArrayData<T>& operator++() {
		++data;
		reportChange();
		return *this;
	} 

	VisualArrayData<T> operator++(int unused) {
		VisualArrayData result = *this;
		++data;
		reportChange();
		return result;
	}

	VisualArrayData<T>& operator--() {
		--data;
		reportChange();
		return *this;
	}

	VisualArrayData<T> operator--(int unused) {
		VisualArrayData result = *this;
		--data;
		reportChange();
		return result;
	}

	//TODO: Add bitwise operators & | ^ &= |= ^= << >> <<= >>= ~
	//TODO: Add cout << and cin >> overloads
};

#endif