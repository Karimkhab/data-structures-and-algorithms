// Karim Khabibrakhmanov DSAI-05
import java.util.*;

public class Main {

    public static List<String> functionDistinctWords(int n, int m, String[] tokens1, String[] tokens2) {
        HashMap<String, Integer> hashMap1 = new HashMap<>(n + 1);
        HashMap<String, Integer> hashMap2 = new HashMap<>(m + 1);
        for (int i = 0; i < tokens2.length; i++) {
            String token = tokens2[i];
            if (token != null) {
                hashMap2.put(token, 1);
            }
        }
        List<String> result = new ArrayList<>();
        for (int i = 0; i < tokens1.length; i++) {
            String token = tokens1[i];
            if (token != null) {
                if ((hashMap1.get(token) == null) && (hashMap2.get(token) == null)) {
                    result.add(token);
                    hashMap1.put(token, 1);
                }
            }
        }

        return result;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();
        scanner.nextLine();
        String[] tokens1 = scanner.nextLine().split(" ");

        int m = scanner.nextInt();
        scanner.nextLine();
        String[] tokens2 = scanner.nextLine().split(" ");

        List<String> distinctWords = functionDistinctWords(n, m, tokens1, tokens2);
        System.out.println(distinctWords.size());
        for (String distinctWord : distinctWords) {
            System.out.println(distinctWord);
        }
    }
}

interface Map<K,V>
{
    V get(K key);
    void put(K key, V value);
    void remove(K key);
    int size();
    boolean isEmpty();
}

class KeyValuePair<K, V> {
    K key;
    V value;

    public KeyValuePair(K key, V value) {
        this.key = key;
        this.value = value;
    }
}

class HashMap<K, V> implements Map<K, V>{
    LinkedList<KeyValuePair<K, V>>[] hashTable;
    int capacity;
    int numberOfElements;

    public HashMap(int capacity) {
        this.capacity = capacity;
        this.numberOfElements = 0;
        this.hashTable = new LinkedList[capacity];
        for (int i = 0; i < capacity; i++) {
            this.hashTable[i] = new LinkedList<>();
        }
    }
    @Override
    public void put(K key, V value) {
        int index = Math.abs(key.hashCode()) % this.capacity;
        for (KeyValuePair<K, V> kv : this.hashTable[index]) {
            if (kv.key.equals(key)) {
                kv.value = value;
                return;
            }
        }
        this.hashTable[index].add(new KeyValuePair<>(key, value));
        this.numberOfElements++;
    }
    @Override
    public V get(K key) {
        int index = Math.abs(key.hashCode()) % this.capacity;
        for (KeyValuePair<K, V> kv : this.hashTable[index]) {
            if (kv.key.equals(key)) {
                return kv.value;
            }
        }
        return null;
    }
    @Override
    public void remove(K key) {
        int index = Math.abs(key.hashCode()) % this.capacity;
        this.hashTable[index].removeIf(kv -> kv.key.equals(key));
        this.numberOfElements--;
    }
    @Override
    public int size() {
        return this.numberOfElements;
    }
    @Override
    public boolean isEmpty() {
        return this.numberOfElements == 0;
    }
}
