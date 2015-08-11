import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;

public class VisualArray<E> implements List<E>, Collection<E> {
	// ARRAYLIST ACCESS METHODS AND VARIABLES
	private ArrayList<E> data;
	
	public VisualArray<E>() {
		data = new VisualArray<>();
		history = new LinkedList<>();
	}
	
	public VisualArray<E>(Collection<? extends E> C) {
		data = new VisualArray<E>(C);
	}
	
	public VisualArray<E>(int initialCapacity) {
		data = new VisualArray<E>(initialCapacity);
	}
	
	public boolean add(E e) {
		//TODO: Monitor
		boolean b = data.add(e);
		
		return b;
	}
	
	public void add(int index, E element) {
		//TODO: Monitor
		boolean b = data.add(index, element);
		
		return b;
	}
	
	public boolean addAll(Collection<? extends E> c) {
		//TODO: Monitor
		boolean b = data.addAll(c);
		
		return b;
	}
	
	public boolean	addAll(int index, Collection<? extends E> c) {
		//TODO: Monitor
		boolean b = data.addAll(index, c);
		
		return b;
	}

	public void	clear() {
		//TODO: Monitor
		data.clear();
	}

	public Object clone() {
		return data.clone();
	}

	public boolean contains(Object o) {
		return data.contains(o);
	}

	public void	ensureCapacity(int minCapacity) {
		//TODO: Monitor
		data.ensureCapacity(minCapacity);
	}

	public E get(int index) {
		return data.get(index);
	}

	public int indexOf(Object o) {
		return data.indexOf(o);
	}

	public boolean isEmpty() {
		return data.isEmpty();
	}

	public Iterator<E> iterator() {
		return data.iterator();
	}

	public int lastIndexOf(Object o) {
		return data.lastIndexOf(o);
	}

	public ListIterator<E> listIterator() {
		return data.listIterator();
	}

	public ListIterator<E> listIterator(int index) {
		return data.listIterator(index);
	}

	public E remove(int index) {
		//TODO: Monitor
		
		E temp = data.remove(index);
		return temp;
	}

	public boolean remove(Object o) {
		//TODO: Monitor
		
		boolean b = data.remove(o);
		return b;
	}

	public boolean removeAll(Collection<?> c) {
		//TODO: Monitor
		
		boolean b = data.remove(c);
		return b;
	}

	protected void	removeRange(int fromIndex, int toIndex) {
		//TODO: Monitor
		
		data.removeRange(fromIndex, toIndex);
	}

	public boolean retainAll(Collection<?> c) {
		//TODO: Monitor
		
		boolean b = data.retainAll(c);
		return b;
	}

	public E set(int index, E element) {
		//TODO: Monitor
		
		E temp = data.set(index, element);
		return temp;
	}

	public int size() {
		return data.size();
	}

	public List<E> subList(int fromIndex, int toIndex) {
		return data.subList(fromIndex, toIndex);
	}

	public Object[]	toArray() {
		return data.toArray();
	}

	public <T> T[] toArray(T[] a) {
		return data.toArray(a);
	}

	public void	trimToSize() {
		//TODO: Monitor
		data.trimToSize();
	}
	
	public int hashCode() {
		return data.hashCode();
	}
	
	public boolean containsAll(Collection<?> c) {
		return data.containsAll(c);
	}
	
	//TODO: Add equals method?
	
	// VISUALARRAY METHODS AND VARIABLES
	private class VisualArrayHistory<T> {
		public static int SET = 1;
		public static int SWAP = 2;
		public static int EXTEND = 3;
		public static int TRIM = 4;
		public static int REMOVE = 5;
		public static int ADD = 6;
		
		public int type;
		public T data;
		public float width;
		public Color color;
	}
	
	private Deque<VisualArrayHistory<E>> history;
	private Stack<VisualArrayHistory<E>> historyPlayed;
	
	private void swapOperation() {
		//TODO
	}
	
	public void hideLatestOperation() {
		history.removeLast();
	}
	
	public void clearHistory() {
		history.clear();
		historyPlayed.clear();
	}
	
	public void nextOperation() {
		if (history.isEmpty()) {
			return;
		}
		
		//TODO
	}
	
	public void prevOperation() {
		if (historyPlayed.isEmpty()) {
			return;
		}
		
		//TODO
	}
	
	public void gfxColor(int index, Color color) {
		//TODO
	}
	
	public void gfxDecolor(int index) {
		//TODO
	}
	
	public void gfxSeparate(int leftIndex, Color color, float width) {
		//TODO
	}
	
	public void gfxDeseparate(int leftIndex) {
		//TODO
	}
	
	// GRAPHICS RENDERING VARIABLES AND METHODS
	public void render() {
		//TODO
	}
	
	public void renderConsole() {
		//TODO
	}
}