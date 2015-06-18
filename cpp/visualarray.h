#include <vector>
#include <deque>

template<class T>
class VisualArray {
public:
	VisualArray(int size);
	~VisualArray();

	unsigned T operator [](int i) const;
	unsigned T& operator [](const int i);

	void gfxHighlight(int index, Color);
	void gfxColor(int index, Color);
	void gfxDecolor(int index);
	void gfxSeparate(int leftindex);
	void gfxDeseparate(int leftindex);
	void hideLastOperation();
	void clearHistory();
	void render();

private:
	static enum HISTORY_TYPE { SET, SWAP, COLOR, DECOLOR, HIGHLIGHT, SEPARATE, DESEPARATE };

	std::vector<int> nextOperation();
	void renderNext();

	int mSize;
	T *mData;
	T *mOriginal;
	std::deque< std::vector<int> > mHistory;
	std::vector<int> mRectangles;
	std::vector<int> mLastHighlights;

	// Missing: default color, highlight color
};