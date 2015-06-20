//Note: Adapted from the C++ version. Nothing really works yet.

//TODO: Template this class so that it works with all kinds of comparable members
public class VisualArray
{
    public class VisualArrayHistory
    {
	public VisualArray.HISTORY_TYPE type;
	public int pos;
	public int data;
	public float width;
	public Color color;
    }
    
    private static enum HISTORY_TYPE { SET, SWAP, COLOR, DECOLOR, HIGHLIGHT, SEPARATE, DESEPARATE };
    
    private int[] mData, mOriginal;
    
    List<VisualArrayHistory> mHistory;
    List<int> mRectangles;
    List<int> mLastHighlights;

    private Color gfxDefaultColor, gfxDefaultHighlightColor, gfxDefaultSeparatorColor;
    //TODO: get/set default colors
	  
	  //TODO: add whatever operators that are standard on C# arrays

    public VisualArray(int size)
    {
    	mData = new int[size];
    	mOriginal = new int[size];
    }

    public VisualArray(int[] array) 
    {
        mData = array;
        mOriginal = array;
    }

    public int this[int i] 
    {
        get 
        {
            return mData[i];
        }
        set
        {
            //TODO: Store change in mHistory
            mData[i] = value;
        }
    }
    
    public int Length
    {
      get
      {
        return mData.Length;
      }
    }
    
    public IEnumerator<int> GetEnumerator() 
    { 
    	return mData.GetEnumerator();
    }

    IEnumerator IEnumerable.GetEnumerator()
    { 
    	return GetEnumerator();
    }
    
    //TODO: Handle get reference to elements?
    
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
	  }
	  
	  public void render()
	  {
	  
	  }
	  
	  private VisualArrayHistory nextOperation()
	  {
	  	VisualArrayHistory op = mHistory[mHistory.Count - 1];
	  	
	  	//TODO: Check swap
	  	
	  	return op;
	  }
	  
	  private void renderNext()
	  {
	  	if (mHistory.Count > 0)
	  	{
	  		VisualArrayHistory op = nextOperation();
	  		
	  		//TODO ...
	  	}
	  }
}
