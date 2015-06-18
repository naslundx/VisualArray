#include <vector>
#include <deque>

template<class T>
class VisualArray {
public:
	VisualArray(int size);
	~VisualArray();

	unsigned T operator [](int i) const;
	unsigned T& operator [](const int i);

	void gfxHighlight(index, Color);
	void gfxColor(index, Color);
	void gfxDecolor(index);
	void gfxSeparate(index);
	void hideLastOperation();
	void clearHistory();
	void render();

private:
	std::vector<int> nextOperation();
	void renderNext();

	int mSize;
	T *mData;
	T *mOriginal;
	std::deque<std::vector<int>> mHistory;
	std::vector<int> mRectangles;
	std::vector<int> mLastHighlights;
};