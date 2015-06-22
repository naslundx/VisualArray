//Note: This code has not been tested or debugged at all
//Missing graphics and GUI (use System.Drawable)

// Possibility: Use Observable.ToObservable<TSource>
// https://msdn.microsoft.com/en-us/library/hh212140(v=vs.103).aspx

public class VisualArray<T>
{
	public class VisualArrayHistory<T>
	{
		public VisualArray.HISTORY_TYPE type;
		public int pos, pos2;
		public T data;
		public float width;
		public Color color;
	}
    
	private static enum HISTORY_TYPE { SET, SWAP, COLOR, DECOLOR, HIGHLIGHT, SEPARATE, DESEPARATE };
    
	private T[] mData, mOriginal;
    
	List< VisualArrayHistory<T> > mHistory;

	//TODO: Add whatever we need for graphics
	private Color gfxDefaultColor, gfxDefaultHighlightColor, gfxDefaultSeparatorColor;
	//List<int> mRectangles;
	//List<int> mLastHighlights;

	//TODO: get/set default colors
	  
	//TODO: add whatever operators that are standard on C# arrays

	public VisualArray(int size)
	{
		mData = new T[size];
		mOriginal = new T[size];
	}

	public VisualArray(T[] array) 
	{
		mData = array;
		mOriginal = array;
	}

	public T this[int i] 
	{
		get 
		{
			return mData[i];
		}
		set
		{
			mData[i] = value;

			VisualArrayHistory _event;
			_event.type = HISTORY_TYPE.SET;
			_event.pos = index;
			_event.data = mData[i];
			mHistory.Add(_event);
		}
	}
    
	public int Length
	{
		get
		{
			return mData.Length;
		}
	}
    
    public IEnumerator<T> GetEnumerator() 
    { 
    	return mData.GetEnumerator();
    }

    IEnumerator IEnumerable.GetEnumerator()
    { 
    	return GetEnumerator();
    }
    
	public void gfxHighlight(int index, Color color)
	{
		if (index >= 0 && index < mData.Length)
		{
			VisualArrayHistory _event;
			_event.type = HISTORY_TYPE.HIGHLIGHT;
			_event.pos = index;
			_event.color = color;
			mHistory.Add(_event);
		}
	}
	  
	public void gfxColor(int index, Color color)
	{
		if (index >= 0 && index < mData.Length)
		{
			VisualArrayHistory _event;
			_event.type = HISTORY_TYPE.COLOR;
			_event.pos = index;
			_event.color = color;
			mHistory.Add(_event);
		}
	}

	public void gfxDecolor(int index)
	{
		if (index >= 0 && index < mData.Length)
		{
			VisualArrayHistory _event;
			_event.type = HISTORY_TYPE.DECOLOR;
			_event.pos = index;
			mHistory.Add(_event);
		}
	}

	public void gfxSeparate(int leftindex, int size, Color color)
	{
		if (index >= -1 && index <= mData.Length)
		{
			VisualArrayHistory _event;
			_event.type = HISTORY_TYPE.SEPARATE;
			_event.pos = leftindex;
			_event.color = color;
			_event.size = size;
			mHistory.Add(_event);
		}
	}

	public void gfxDeseparate(int leftindex)
	{
		if (index >= -1 && index <= mData.Length)
		{
			VisualArrayHistory _event;
			_event.type = HISTORY_TYPE.DESEPARATE;
			_event.pos = leftindex;
			mHistory.Add(_event);
		}
	}

	public void hideLastOperation()
	{
		if (mHistory.Count > 0) 
		{
			mHistory.RemoveAt(mHistory.Count - 1); 	
		}
	}

	public void clearHistory()
	{
		mHistory.Clear();
		Array.Copy(mData, 0, mHistory, 0, mData.Length)
	}

	public void render()
	{
		//TODO: Init a rendering window

		//TODO: Init the GUI

		//TODO: Start rendering loop (use renderNext)
	}

	private VisualArrayHistory nextOperation()
	{
		if (mHistory.Length > 0)
		{
			VisualArrayHistory op = mHistory[mHistory.Count - 1];

			if (op.type == HISTORY_TYPE.SET && mHistory.Length > 1)
			{
				VisualArrayHistory next = mHistory[mHistory.Count - 2];

				if (next.type == HISTORY_TYPE.SET && op.data == mOriginal[next.pos] &&
					next.data == mOriginal[op.pos])
				{
					mOriginal[op.pos] = op.data;
					mOriginal[next.pos] = next.data;
					mHistory.RemoveAt(mHistory.Count - 1);
					mHistory.RemoveAt(mHistory.Count - 1);

					op.type = HISTORY_TYPE.SWAP;
					op.pos2 = next.pos;

					return op;
				}

				// If we did not return here, we should set
				mOriginal[op.pos] = op.data;
				mHistory.RemoveAt(mHistory.Count - 1);
			}

			return op;
		}
		else
		{
			return null;
		}
	}
	  
	private void renderNext()
	{
		if (mHistory.Count > 0)
		{
			VisualArrayHistory op = nextOperation();

			//TODO: Render the changes that are stored in op
		}
	}
}
