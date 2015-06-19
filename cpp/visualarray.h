#include <vector>
#include <deque>

// USE THIS STRUCT INSTEAD OF std::vector<int> FOR HISTORY
template<class T>
struct VisualArrayData {
	VisualArray.HISTORY_TYPE type;
	T data;
	float size;
	Color color;
};

template<class T>
class VisualArray {
public:
	static enum HISTORY_TYPE { SET, SWAP, COLOR, DECOLOR, HIGHLIGHT, SEPARATE, DESEPARATE };

	VisualArray(int size);
	~VisualArray();

	//TODO: If tracking changes cannot be done, implement set() and swap() functions instead.
	// Perhaps a really smart pointer can track changes
	unsigned T operator [](int i) const;
	unsigned T& operator [](const int i);

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
	T *mData;
	T *mOriginal;
	std::deque< VisualArrayData<T> > mHistory;
	std::vector<int> mRectangles;
	std::vector<int> mLastHighlights;

	// Missing: default color, highlight color
};

