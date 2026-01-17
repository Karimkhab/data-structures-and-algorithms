// Karim Khabibrakhmanov DSAI-05

import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.AbstractMap;

public class Main {

public static ArrayList<AbstractMap.SimpleEntry<String, Integer>> bubbleSort(ArrayList<AbstractMap.SimpleEntry<String, Integer>> list, String[] tokens) {
        int n = list.size();
        boolean swapped;
        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                int freqCompare = list.get(j + 1).getValue().compareTo(list.get(j).getValue());
                if (freqCompare > 0 || (freqCompare == 0 && indexOf(tokens, list.get(j + 1).getKey()) < indexOf(tokens, list.get(j).getKey()))) {
                    AbstractMap.SimpleEntry<String, Integer> temp = list.get(j);
                    list.set(j, list.get(j + 1));
                    list.set(j + 1, temp);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
        return list;
    }

public static String searchWord(int n, int k, String[] tokens) {
        HashMap<String, Integer> hashMap = new HashMap<>(n);
        for (String token : tokens) {
            hashMap.put(token, hashMap.get(token) + 1);
        }

        ArrayList<AbstractMap.SimpleEntry<String, Integer>> list = hashMap.mapToArrayList();

        list = bubbleSort(list, tokens);

        return list.get(k - 1).getKey();
    }

private static int indexOf(String[] tokens, String word) {
        for (int i = 0; i < tokens.length; i++) {
            if (tokens[i].equals(word)) {
                return i;
            }
        }
        return -1;
    }

public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int k = scanner.nextInt();
        scanner.nextLine();
        String[] tokens = scanner.nextLine().split(" ");
        System.out.println(searchWord(n, k, tokens));
    }
}

// Interface of Map ADT
interface Map<K,V>
{
V get(K key);
void put(K key, V value);
void remove(K key);
int size();
boolean isEmpty();
}

class KeyValuePair<K, V>
{
    K key;
    V value;

public KeyValuePair(K key, V value)
    {
        this.key = key;
        this.value = value;
    }
}

class HashMap<K, V> implements Map<K, V> {
LinkedList<KeyValuePair<K, V>>[] hashTable;
int capacity; // size of hashTable (# of slots)
int numberOfElements;// number of key-value pairs
int id =0;

public HashMap(int capacity) {
    this.capacity = capacity;
    this.numberOfElements = 0;
    this.hashTable = new LinkedList[capacity];
    for (int i = 0; i < capacity; i++)
        this.hashTable[i] = new LinkedList<>();
}

public ArrayList<AbstractMap.SimpleEntry<K, V>> mapToArrayList() {
    ArrayList<AbstractMap.SimpleEntry<K, V>> list = new ArrayList<>();
    for (int i = 0; i < this.capacity; i++) {
        for (KeyValuePair<K, V> elem : this.hashTable[i]) {
            list.add(new AbstractMap.SimpleEntry<>(elem.key, elem.value));
        }
    }
    return list;
}

@Override
public void put(K key, V value) {
    int i = Math.abs(key.hashCode()) % this.capacity;
    for (KeyValuePair<K, V> kv : this.hashTable[i]) {
        if (kv.key.equals(key)) {
            kv.value = (V) Integer.valueOf((Integer) kv.value + (Integer) value);
            return;
        }
    }
    this.hashTable[i].add(new KeyValuePair<>(key, value));
    this.numberOfElements++;
}


@Override
public void remove(K key)
{
    int i = key.hashCode() % this.capacity;
    if(i < 0)
        i *= -1;
    for (KeyValuePair<K,V> kv : this.hashTable[i])
    {
        if (kv.key.equals(key))
            kv.value = null;
        break;
    }
}

@Override
public V get(K key) {
    int i = Math.abs(key.hashCode()) % this.capacity;
    for (KeyValuePair<K, V> kv : this.hashTable[i]) {
        if (kv.key.equals(key)) {
            return kv.value;
        }
    }
    return (V) Integer.valueOf(0);
}

@Override
public int size() { return this.numberOfElements; }

@Override
public boolean isEmpty() { return (this.numberOfElements == 0); }
}