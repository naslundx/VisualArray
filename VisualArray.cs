//Note: Adapted from the C++ version. Nothing really works yet.

//TODO: Add extra class/struct which handles the history events

//TODO: Template this class so that it works with all kinds of comparable members

public class VisualArray
{
    private static enum HISTORY_TYPE { SET, SWAP, COLOR, DECOLOR, HIGHLIGHT, SEPARATE, DESEPARATE };
    private Color gfxDefaultColor, gfxDefaultHighlightColor, gfxDefaultSeparatorColor;
    private int[] mData, mOriginal;
	  private int mSize; // is this necessary?

	  //std::deque< VisualArrayHistory > mHistory;
	  //std::vector<int> mRectangles;
	  //std::vector<int> mLastHighlights; 
	  
	  //TODO: get/set default colors
	  
	  //TODO: add whatever operators that are standard on C# arrays

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
    
    //TODO: Handle get reference to elements?
    
	  public void gfxHighlight(int index, Color color)
	  {
	    if (index >= 0 && index < mData.Length)
	    {
	    
	    }
	  }
	  
	  public void gfxColor(int index, Color)
	  {
	    if (index >= 0 && index < mData.Length)
	    {
	    
	    }
	  }
	  
	  public void gfxDecolor(int index)
	  {
	    if (index >= 0 && index < mData.Length)
	    {
	    
	    }
	  }
	  
	  public void gfxSeparate(int leftindex, int size, Color)
	  {
	    if (index >= -1 && index <= mData.Length)
	    {
	    
	    }
	  }
	  
	  public void gfxDeseparate(int leftindex)
	  {
	    if (index >= -1 && index <= mData.Length)
	    {
	    
	    }
	  }
	  
	  public void hideLastOperation()
	  {
	    
	  }
	  
	  public void clearHistory()
	  {
	    mHistory.clear();
	  }
	  
	  public void render()
	  {
	  
	  }
	  
	  private VisualArrayHistory nextOperation()
	  {
	  
	  }
	  
	  private void renderNext()
	  {
	  
	  }
}
