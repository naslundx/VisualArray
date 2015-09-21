#ifndef __VISUALARRAY_H__
#define __VISUALARRAY_H__

#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <stack>
#include <SFML/Graphics.hpp>

template<typename T> class VisualArrayData;
struct Color { Color() {i=1;} Color(int j) {i=j;} int i; }; // Just temporary

// Struct for storing events
template<typename T> struct VisualArrayHistory { 12345
	HISTORY_TYPE type;
	int pos, pos2;
	T data;
	float size;
	Color color;
};

// Main VisualArray class
template<typename T> class VisualArray {
public:
	VisualArray(int size)  {
		gfxWindowWidth = 124;
		gfxWindowHeight = 120;
		gfxRectangleWidth = 10;
		gfxLeft = 10;
		gfxTop = 10;

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
		while (!mHistoryPlayed.empty()) {
			mHistoryPlayed.pop(); // std::stack has no clear() method because... ?
		}

		for (int i=0; i<mSize; i++) {
			mOriginal[i] = mData[i];
		}

		mGraphicsReady = true;
	}

	// This is very the visualization happens
	void render() {
		if (!mGraphicsReady) {
			// There is no data in mOriginal!
			return;
		}

		//TODO: Update this value (and scale if needed) whenever set occur
		T maxvalue  = findMaxValue(mOriginal);

		// Init rendering window
		VisualArrayHistory<T> op;
		sf::Event event;
		gfxRectangleScale = (gfxWindowHeight-gfxTop*2)/maxvalue;
		sf::RenderWindow window(sf::VideoMode(gfxWindowWidth, gfxWindowHeight), "VisualArray");
		bool keypress = true;

	    // Start rendering loop
	    while (window.isOpen())
	    {
	    	//TODO: Nothing happens...?

	        while (window.pollEvent(event))
	        {
						chooseEvent(event, window, op, keypress);
	        }

	        // Draw to window
	        // TODO: Do this through GUI
	        if (keypress) {
	        	op = nextOperation();
	        	executeOperation(op);
	        	renderFrame(window, op);
	        	keypress = false;
	        }
	    }
	}

private:
	// Get the next operation
	VisualArrayHistory<T> nextOperation() {
		VisualArrayHistory<T> op = mHistory.front();
		mHistory.pop_front();

		if (op.type == SET) {
			if (!mHistory.empty()) {
				VisualArrayHistory<T> opb = mHistory.front();

				// Check if swap
				if (opb.type == SET && op.data == mOriginal[opb.pos] && opb.data == mOriginal[op.pos]) {
					op.type = SWAP;
					op.pos2 = opb.pos;

					mHistory.pop_front();
				}
			}
		}

		VisualArrayHistory<T> flip = flipOperation(op);
		mHistoryPlayed.push(flip);

		return op;
	}

	// Get previous operation (used for stepping back) - not used yet
	VisualArrayHistory<T> prevOperation() {
		VisualArrayHistory<T> op = mHistoryPlayed.top();
		mHistoryPlayed.pop();

		VisualArrayHistory<T> flip = flipOperation(op);
		mHistory.push_front(flip);

		return op;
	}

	// Step back to the beginning
	void gfxRestart() {
		while (!mHistoryPlayed.empty()) {
			VisualArrayHistory<T> op = prevOperation();
			executeOperation(op);
		}
	}

	// Execute a SET and SWAP operation
	void executeOperation(VisualArrayHistory<T> &op) {
		if (op.type == SET) {
			mOriginal[op.pos] = op.data;
		}
		else if (op.type == SWAP) {
			T temp = mOriginal[op.pos];
			mOriginal[op.pos] = mOriginal[op.pos2];
			mOriginal[op.pos2] = temp;
		}
	}

	// Render the current frame, latest operation was op
	void renderFrame(sf::RenderWindow& window, VisualArrayHistory<T>& op) {
		mRectangles.clear();

		// Create rectangles
	    for (int i=0; i<mSize; i++) {
	    	sf::RectangleShape rectangle(sf::Vector2f(gfxRectangleWidth, gfxRectangleScale * (float)mOriginal[i]));
	    	rectangle.setFillColor(sf::Color(255, 255, 255));
	    	rectangle.setPosition(gfxLeft + gfxRectangleWidth * i, gfxTop);
	    	mRectangles.push_back(rectangle);
	    }

	    // Handle gfx events
		if (op.type == COLOR) {
			mRectangleColors.push_front(std::pair<int, sf::Color>(op.pos, sf::Color(0, 0, 255)));
		}
		else if (op.type == DECOLOR) {
			for (std::deque< std::pair<int, sf::Color> >::iterator it = mRectangleColors.begin(); it != mRectangleColors.end(); ++it) {
				if (it->first == op.pos) {
					mRectangleColors.erase(it);
					break;
				}
			}
		}
		else if (op.type == SEPARATE) {
			sf::RectangleShape line(sf::Vector2f(2, gfxWindowHeight));
			line.setPosition(gfxLeft + gfxRectangleWidth * op.pos, gfxTop-5);
			mSeparators.push_front(std::pair<int, sf::RectangleShape>(op.pos, line));
		}
		else if (op.type == DESEPARATE) {
			for (std::deque< std::pair<int, sf::RectangleShape> >::iterator it = mSeparators.begin(); it != mSeparators.end(); ++it) {
				if (it->first == op.pos) {
					mSeparators.erase(it);
					break;
				}
			}
		}

		// Use coloring already introduced
		for (std::deque< std::pair<int, sf::Color> >::iterator it = mRectangleColors.begin(); it != mRectangleColors.end(); ++it) {
			mRectangles[it->first].setFillColor(it->second);
		}

		//TODO: Color the most recent rectangles that were swapped or set

		// Render to buffer
	    window.clear();

        for (std::vector<sf::RectangleShape>::iterator it=mRectangles.begin(); it!=mRectangles.end(); ++it) {
        	window.draw(*it);
    	}

    	for (std::deque< std::pair<int, sf::RectangleShape> >::iterator it=mSeparators.begin(); it!=mSeparators.end(); ++it) {
        	window.draw(it->second);
    	}

    	// Draw a GUI
    	//TODO

    	// Display on screen
        window.display();
	}

	// Use this function to flip the operation, and then put on stack so that we can play back
	VisualArrayHistory<T> flipOperation(VisualArrayHistory<T> op) {
		VisualArrayHistory<T> flip = op;

		if (flip.type == COLOR) {
			flip.type = DECOLOR;
		}
		else if (flip.type == DECOLOR) {
			flip.type = COLOR;

			//TODO: Find current color of this rectangle and store
		}
		else if (flip.type == SEPARATE) {
			flip.type = DESEPARATE;
		}
		else if (flip.type == DESEPARATE) {
			flip.type = SEPARATE;

			//TODO: Find latest separator color and width at this position
		}

		return flip;
	}

	// Find maximum value of an array
	T findMaxValue(T *data){
		T maxvalue = 0;
		for (int i=0; i<mSize; i++) {
			if (data[i] > maxvalue) {
				maxvalue = data[i];
			}
		}
		return maxvalue;
	}

	void chooseEvent(sf::Event event, sf::RenderWindow &window,
	                 VisualArrayHistory<T> &op, bool &keypress){
		switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				//TODO: Reposition and resize everything
				renderFrame(window, op);
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code) {
					case sf::Keyboard::Left:
						if (!mHistoryPlayed.empty()) {
							op = prevOperation();
							keypress = true;
						}
						break;

					case sf::Keyboard::Right:
						if (!mHistory.empty()) {
							op = nextOperation();
							keypress = true;
						}
						break;

					case sf::Keyboard::Space:
						//TODO: Toggle play/pause
						break;

					case sf::Keyboard::Escape:
						gfxRestart();
						renderFrame(window, op);
						break;
				}
				break;
		}
	}

	// Private data
	bool mGraphicsReady;
	int mSize;
	VisualArrayData<T> *mData;
	T *mOriginal;
	std::deque< VisualArrayHistory<T> > mHistory;
	std::stack< VisualArrayHistory<T> > mHistoryPlayed;
	std::vector<sf::RectangleShape> mRectangles;
	std::deque< std::pair<int, sf::Color> > mRectangleColors;
	std::deque< std::pair<int, sf::RectangleShape> > mSeparators;

	// Data for graphics rendering
	float gfxWindowWidth;
	float gfxWindowHeight;
	float gfxRectangleWidth;
	float gfxLeft;
	float gfxTop;
	float gfxRectangleScale;

	Color gfxDefaultNoColor, gfxDefaultColor, gfxDefaultSeparatorColor;
	//TODO: Set default colors
};

// This class imitates the elements of the VisualArray
// Issue: You cannot do int& reference = VisualArrayData<int> other;
// Can this be fixed somehow?
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
		this->data = other;
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

	//DK
	VisualArrayData<T> operator & (VisualArrayData<T> right) {
		//reportChange();
		return this->data & right;
	}

	VisualArrayData<T> operator | (VisualArrayData<T> right) {
		//reportChange();
		return this->data | right;
	}

	VisualArrayData<T> operator ^ (VisualArrayData<T> right) {
		//reportChange();
		return this->data ^ right;
	}

	VisualArrayData<T> operator << (VisualArrayData<T> right) {
		//reportChange();
		return this->data << right;
	}

	VisualArrayData<T> operator >> (VisualArrayData<T> right) {
		//reportChange();
		return this->data >> right;
	}

	VisualArrayData<T> operator ~ () {
		//reportChange();
		return ~this->data;
	}

	VisualArrayData<T>& operator &= (VisualArrayData<T>& right) {
		this->data = this->data & right;
		reportChange();
		return *this;
	}

	VisualArrayData<T>& operator |= (VisualArrayData<T>& right) {
		this->data = this->data | right;
		reportChange();
		return *this;
	}

	VisualArrayData<T>& operator ^= (VisualArrayData<T>& right) {
		this->data = this->data ^ right;
		reportChange();
		return *this;
	}

	VisualArrayData<T>& operator <<= (VisualArrayData<T>& right) {
		this->data = this->data << right;
		reportChange();
		return *this;
	}

	VisualArrayData<T>& operator >>= (VisualArrayData<T>& right) {
		this->data = this->data >> right;
		reportChange();
		return *this;
	}

	//TODO: Add cout << and cin >> overloads (if needed?)
};

#endif
