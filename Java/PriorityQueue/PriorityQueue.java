import java.util.ArrayList;

/**
 * Basic PriorityQueue implementation. Uses a binary heap to store items
 * (somewhat) sorted efficiently. This is a min-heap implementation, but a
 * max-heap one is easily achieved by changing the signs used in comparing
 * items.
 */

public class PriorityQueue<T extends Comparable<T>> {
    private ArrayList<T> heapList;

    public PriorityQueue() {
        this.heapList = new ArrayList<>();
    }

    // check if the queue is empty
    public boolean isEmpty() {
        return size() == 0;
    }

    // return the size of the queue
    public int size() {
        return heapList.size();
    }

    // insert an item into the queue
    public void insert(T item) {
        int index = size();
        heapList.add(item);
        percolateUp(index);
    }

    // return the minimum item of the queue
    public T getMin() {
        return isEmpty() ? null : heapList.get(0);
    }

    // remove the minimum item of the queue and return it
    public T removeMin() {
        if (isEmpty())
            return null;

        if (size() == 1)
            return heapList.remove(0);

        T item = heapList.get(0);
        heapList.set(0, heapList.remove(size() - 1));
        percolateDown(0);
        return item;
    }

    // percolate down the item at the given index
    private void percolateDown(int i) {
        T item = heapList.get(i);
        while (2 * i + 1 < size()) {
            int c = 2 * i + 1;
            T child = heapList.get(c);
            if (c + 1 < size() && heapList.get(c + 1).compareTo(child) < 0) {
                c++;
                child = heapList.get(c);
            }
            if (item.compareTo(child) < 0)
                break;
            heapList.set(i, child);
            i = c;
        }
        heapList.set(i, item);
    }

    // percolate up the item at the given index
    private void percolateUp(int i) {
        T item = heapList.get(i);
        while (i > 0) {
            int p = (i - 1) / 2;
            T parent = heapList.get(p);
            if (parent.compareTo(item) < 0)
                break;
            heapList.set(i, parent);
            i = p;
        }
        heapList.set(i, item);
    }

}
