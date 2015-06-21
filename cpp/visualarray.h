#ifndef __VISUALARRAY_H__
#define __VISUALARRAY_H__

#include <vector>
#include <deque>
#include <iostream>

// Temporary color
struct Color { int i; };

enum HISTORY_TYPE { SET, SWAP, COLOR, DECOLOR, HIGHLIGHT, SEPARATE, DESEPARATE };

class VisualArray;

//template<typename T>
class VisualArrayData {
public:
	VisualArrayData();
	VisualArrayData(int pos, VisualArray* parent);
	void reportChange();
	int get() { return data; }

	operator int();

	VisualArrayData& operator = (const int& other);
	//VisualArrayData& operator = (VisualArrayData& other);
	
	VisualArrayData& operator += (VisualArrayData& right);
	VisualArrayData& operator -= (VisualArrayData& right);
	VisualArrayData& operator *= (VisualArrayData& right);
	VisualArrayData& operator /= (VisualArrayData& right);
	VisualArrayData& operator %= (VisualArrayData& right);
	
	VisualArrayData& operator += (int right);
	VisualArrayData& operator -= (int right);
	VisualArrayData& operator *= (int right);
	VisualArrayData& operator /= (int right);
	VisualArrayData& operator %= (int right);

	VisualArrayData& operator++(); 
	VisualArrayData operator++(int unused);
	VisualArrayData& operator--();
	VisualArrayData operator--(int unused);

	//TODO: Add bitwise operators & | ^ &= |= ^= << >> <<= >>= ~

private:
	int data;
	int pos;
	VisualArray* parent;
};

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

	VisualArrayData& operator [](const int i);
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
	VisualArrayData *mData;
	int *mOriginal;
	std::deque< VisualArrayHistory > mHistory;
	std::vector<int> mRectangles;
	std::vector<int> mLastHighlights;

	Color gfxDefaultColor, gfxDefaultHighlightColor, gfxDefaultSeparatorColor;
};

#endif