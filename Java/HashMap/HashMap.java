import java.util.ArrayList;
import java.util.LinkedList;

// HashMap class for storing (key, value) pairs in a HashMap
public class HashMap<K, V> {
    private static final double LOAD_FACTOR_THRESHOLD = 0.75;
    private LinkedList<Node>[] hashArray;
    public ArrayList<K> keys;
    public int size;

    public HashMap() {
        this(16);
    }

    @SuppressWarnings("unchecked")
    public HashMap(int initialLength) {
        this.hashArray = new LinkedList[initialLength];
        this.keys = new ArrayList<>();
        this.size = 0;
    }

    // Get the value for the given key
    public V get(K key) {
        return get(key, hashArray);
    }

    // Set the given value for the given key
    public void set(K key, V value) {
        if (set(key, value, hashArray)) {
            keys.add(key);
            size++;
        }

        if ((double) size / hashArray.length > LOAD_FACTOR_THRESHOLD)
            rehash();
    }

    public V remove(K key) {
        int index = hash(key, hashArray);
        LinkedList<Node> nodeList = hashArray[index];
        if (nodeList == null)
            return null;

        for (int i = 0; i < nodeList.size(); i++) {
            Node node = nodeList.get(i);
            if (key.equals(node.key)) {
                V val = node.value;
                nodeList.remove(i);
                keys.remove(key);
                size--;
                return val;
            }
        }
        return null;
    }

    // Return true if the map contains the given key, false otherwise
    public boolean contains(K key) {
        return get(key) != null;
    }

    // Helper get method
    private V get(K key, LinkedList<Node>[] array) {
        int index = hash(key, array);
        if (array[index] == null) {
            return null;
        }

        for (Node candidate : array[index]) {
            if (key.equals(candidate.key)) {
                return candidate.value;
            }
        }

        return null;
    }

    // Helper set method
    private boolean set(K key, V value, LinkedList<Node>[] array) {
        int index = hash(key, array);
        LinkedList<Node> nodeList = array[index] == null ? array[index] = new LinkedList<>() : array[index];

        for (Node other : nodeList) {
            if (key.equals(other.key)) {
                other.value = value;
                return false;
            }
        }

        Node node = new Node(key, value);
        nodeList.addFirst(node);
        return true;

    }

    // Helper hash method to hash the keys
    private int hash(K key, LinkedList<Node>[] array) {
        return (key.hashCode() & 0x7FFFFFFF) % array.length;
    }

    // Helper rehash method to resize the array of the map and rehash everything
    @SuppressWarnings("unchecked")
    private void rehash() {
        LinkedList<Node>[] newArray = new LinkedList[hashArray.length * 2];

        for (K key : keys)
            set(key, get(key), newArray);

        hashArray = newArray;
    }

    // Node class for storing (key, value) pairs
    class Node {
        public K key;
        public V value;

        public Node(K key, V value) {
            this.key = key;
            this.value = value;
        }
    }
}
