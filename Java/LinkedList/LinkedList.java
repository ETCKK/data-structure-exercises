/**
 * Basic LinkedList implementation. This is a doubly-linked implementation, so
 * accessing the first and the last
 * element is easy.
 */

public class LinkedList<E> {

    private Node<E> first;
    private Node<E> last;
    private int size;

    public LinkedList() {
        this.first = null;
        this.last = null;
        this.size = 0;
    }

    // check if the list is empty
    public boolean isEmpty() {
        return size == 0;
    }

    // return the size of the list
    public int size() {
        return size;
    }

    // get the first element in the list
    public E getFirst() {
        return isEmpty() ? null : first.data;
    }

    // get the last element in the list
    public E getLast() {
        return isEmpty() ? null : last.data;
    }

    // add an element to the start of the list
    public void addFirst(E element) {
        Node<E> newNode = new Node<>(element, null, first);
        if (isEmpty()) {
            first = last = newNode;
        } else {
            first.prev = newNode;
            first = newNode;
        }
        size++;
    }

    // add an element to the end of the list
    public void addLast(E element) {
        Node<E> newNode = new Node<>(element, last, null);
        if (isEmpty()) {
            first = last = newNode;
        } else {
            last.next = newNode;
            last = newNode;
        }
        size++;
    }

    // remove the first element from the list
    public E removeFirst() {
        if (isEmpty())
            return null;

        E data = first.data;
        first = first.next;
        if (first == null)
            last = null;
        else
            first.prev = null;
        size--;
        return data;
    }

    // remove the last element from the list
    public E removeLast() {
        if (isEmpty())
            return null;

        E data = last.data;
        last = last.prev;
        if (last == null)
            first = null;
        else
            last.next = null;
        size--;
        return data;
    }

    // Node class for tracking next/previous elements
    private static class Node<E> {
        E data;
        Node<E> next;
        Node<E> prev;

        Node(E data, Node<E> prev, Node<E> next) {
            this.data = data;
            this.prev = prev;
            this.next = next;
        }
    }

}