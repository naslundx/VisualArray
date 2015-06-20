#include <vector>
#include <deque>

//template<class T>
struct VisualArrayHistory {
	VisualArray.HISTORY_TYPE type;
	int pos;
	int data;
	float size;
	Color color;
};

//template<typename T>
class VisualArrayData {
public:
	VisualArrayData();
	VisualArrayData(int _pos, VisualArray& _parent);
	operator int();
	
	// usual arithmetical operations
	// comparator operations between itself and int
	// add any extra friend functions between this class and int
private:
	int data;
	int pos;
	VisualArray& parent;
};

//template<class T>
class VisualArray {
public:
	static enum HISTORY_TYPE { SET, SWAP, COLOR, DECOLOR, HIGHLIGHT, SEPARATE, DESEPARATE };

	VisualArray(int size);
	~VisualArray();

	VisualArrayData operator [](int i) const;
	VisualArrayData& operator [](const int i);

	void gfxHighlight(int index, Color);
	void gfxColor(int index, Color);
	void gfxDecolor(int index);
	void gfxSeparate(int leftindex, int size, Color);
	void gfxDeseparate(int leftindex);
	void hideLastOperation();
	void clearHistory();
	void render();

private:
	std::vector<int> nextOperation();
	void renderNext();

	bool mGraphicsReady = false;
	int mSize;
	VisualArrayData *mData;
	VisualArrayData *mOriginal;
	std::deque< VisualArrayHistory > mHistory;
	std::vector<int> mRectangles;
	std::vector<int> mLastHighlights;

	Color gfxDefaultColor, gfxDefaultHighlightColor, gfxDefaultSeparatorColor;
};
