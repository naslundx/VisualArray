#ifndef __VISUALARRAY_H__
#define __VISUALARRAY_H__

#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

enum HISTORY_TYPE { SET, SWAP, COLOR, DECOLOR, HIGHLIGHT, SEPARATE, DESEPARATE };

template<typename T> class VisualArrayData;
struct Color { Color() {i=0;} Color(int j) {i=j;} int i; }; // Just temporary

template<typename T> struct VisualArrayHistory {
	HISTORY_TYPE type;
	int pos, pos2;
	T data;
	float size;
	Color color;
};

template<typename T> class VisualArray {
public:
	VisualArray(int size)  {
		mGraphicsReady = false;

		if (size>0) {
			mData = new VisualArrayData<T>[size];
			mOriginal = new T[size];
			mSize = size;
			
			for (int i=0; i<size; i++) {
				mData[i].setInformation(i, this);
			}
		}
	}

	~VisualArray() {
		delete[] mData;
		delete[] mOriginal;
	}

	//VisualArray(std::initializer_list<int> list);

	VisualArrayData<T>& operator [](const int i) {
		return (mData[i]);
	}

	/*T& operator [](const int i) {
		return (mData[i]);
	}*/

	void addSetEvent(int pos, T data) {
		if (pos >= 0 && pos < mSize) {
			VisualArrayHistory<T> event;
			event.type = SET;
			event.pos = pos;
			event.data = data;
			mHistory.push_back(event);
		}		
	}

	void gfxHighlight(int index, Color color) {
		if (index >= 0 && index < mSize) {
			VisualArrayHistory<T> event;
			
			event.type = HIGHLIGHT;
			event.pos = index;
			event.color = color;

			mHistory.push_back(event);
		}
	}

	void gfxColor(int index, Color color) {
		if (index >= 0 && index < mSize) {
			VisualArrayHistory<T> event;
			
			event.type = COLOR;
			event.pos = index;
			event.color = color;

			mHistory.push_back(event);
		}
	}

	void gfxDecolor(int index) {
		if (index >= 0 && index < mSize) {
			VisualArrayHistory<T> event;
			
			event.type = DECOLOR;
			event.pos = index;

			mHistory.push_back(event);
		}
	}

	void gfxSeparate(int leftindex, float size, Color color) {
		if (leftindex >= -1 && leftindex <= mSize) {
			VisualArrayHistory<T> event;
			
			event.type = SEPARATE;
			event.pos = leftindex;
			event.size = size;
			event.color = color;

			mHistory.push_back(event);
		}
	}

	void gfxDeseparate(int leftindex) {
		if (leftindex >= -1 && leftindex <= mSize) {
			VisualArrayHistory<T> event;
			
			event.type = DESEPARATE;
			event.pos = leftindex;

			mHistory.push_back(event);
		}
	}

	void hideLastOperation() {
		if (!mHistory.empty()) {
			mHistory.pop_back();
		}
	}

	void clearHistory() {
		mHistory.clear();
		for (int i=0; i<mSize; i++) {
			mOriginal[i] = mData[i];
		}
		mGraphicsReady = true;
	}

	void render() {
		if (!mGraphicsReady) {
			// There is no data in mOriginal!
			return;
		}

		// Find maximal value
		//TODO: Update this value (and scale if needed) whenever set occurs
		T maxvalue = 0;
		for (int i=0; i<mSize; i++) {
			if (mOriginal[i] > maxvalue) {
				maxvalue = mOriginal[i];
			}
		}	

		// Init rendering window		
		float gfxWindowWidth = 200;
		float gfxWindowHeight = 200;
		float gfxRectangleWidth = 10;			
		float gfxLeft = 10;
		float gfxTop = 10;
		float gfxRectangleScale = (gfxWindowHeight-gfxTop*2)/maxvalue;
		sf::RenderWindow window(sf::VideoMode(gfxWindowWidth, gfxWindowHeight), "VisualArray");
	    
	    // Create rectangles
	    for (int i=0; i<mSize; i++) {
	    	sf::RectangleShape rectangle(sf::Vector2f(gfxRectangleWidth, gfxRectangleScale * (float)mOriginal[i]));
	    	rectangle.setPosition(gfxLeft + gfxRectangleWidth * i, gfxTop);
	    	mRectangles.push_back(rectangle);
	    }
	    
	    // Start rendering loop
	    while (window.isOpen())
	    {
	    	//TODO: Nothing happens...?

	    	std::vector<int>::iterator it; 
			for (it = mLastHighlights.begin(); it != mLastHighlights.end(); ++it) {
				//TODO: Set rectangle to default color
			}
			mLastHighlights.clear();

	        sf::Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();

	            //TODO: Handle interactivity via a GUI
	        }

	        // Draw to window
	        window.clear();
	        std::vector<sf::RectangleShape>::iterator iter;
	        for (iter=mRectangles.begin(); iter!=mRectangles.end(); ++iter) {
	        	window.draw(*iter);
	    	}
	        window.display();

	        //TODO: Draw a GUI

	        // Render next event
	        if (!mHistory.empty()) {
				VisualArrayHistory<T> op = nextOperation();

				if (op.type == SWAP) {
					mRectangles[op.pos].setPosition(mRectangles[op.pos].getPosition());
					mRectangles[op.pos2].setPosition(mRectangles[op.pos2].getPosition());

					iter_swap(mRectangles.begin() + op.pos, mRectangles.begin() + op.pos2);
				}
				else if (op.type == SET) {
					mRectangles[op.pos].setSize(sf::Vector2f(gfxRectangleWidth, gfxRectangleScale * (float)mOriginal[op.pos]))
				}
				else if (op.type == HIGHLIGHT) {
					//TODO: Render highligh, store in mLastHighlights
				}
				else if (op.type == COLOR) {
					//TODO: Render coloring op.pos
				}
				else if (op.type == DECOLOR) {
					//TODO: Color op.pos the default color
				}
				else if (op.type == SEPARATE) {
					//TODO: Separate op.pos and op.pos+1 with a line
				}
				else if (op.type == DESEPARATE) {
					//TODO: Merge op.pos and op.pos+1 - remove the line
				}
			}
	    }
	}

private:
	VisualArrayHistory<T> nextOperation() {
		VisualArrayHistory<T> op = mHistory.front(); 
		mHistory.pop_front();
		
		if (op.type == SET) {
			if (!mHistory.empty()) {
				VisualArrayHistory<T> opb = mHistory.front();

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

	bool mGraphicsReady;
	int mSize;
	VisualArrayData<T> *mData;
	T *mOriginal;
	std::deque< VisualArrayHistory<T> > mHistory;
	std::vector<sf::RectangleShape> mRectangles;
	std::vector<int> mLastHighlights;

	Color gfxDefaultColor, gfxDefaultHighlightColor, gfxDefaultSeparatorColor;
	//TODO: Set default colors
};

template<typename T> class VisualArrayData {
private:
	T data;
	int pos;
	VisualArray<T>* parent;

public:
	VisualArrayData() {
		parent = NULL;
	}

	void setInformation(int pos, VisualArray<T>* parent) {
		this->pos = pos; 
		this->parent = parent;
	}

	T get() { 
		return data; 
	}

	void reportChange() {
		if (parent != NULL) {
			parent->addSetEvent(this->pos, this->data);
		}	
	}	

	operator T() {
		return (T)(this->data); 
	}

	VisualArrayData<T>& operator = (T& other) {
		data = other;
		reportChange();
		return *this;
	}

	VisualArrayData<T>& operator = (VisualArrayData<T>& other) {
		this->data = other.get();
		reportChange();
		return *this;
	}
	
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
	//TODO: Add cout << and cin >> overloads???
};

#endif