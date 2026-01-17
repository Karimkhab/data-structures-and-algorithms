// Karim Khabibrakhmanov DSAI-05

import java.util.Stack;
import java.util.Scanner;

public class Main {

    public static boolean checkOp(String peek, String c){
        if ((peek.equals("+") || peek.equals("-")) && (c.equals("*") || c.equals("/"))) {
            return false;
        } else {
            return true;
        }
    }

    public static boolean opValue(String c){
        return c.equals("+") || c.equals("-") || c.equals("*") || c.equals("/");
    }

    public static String shuntingYardAlgo(String[] tokens){
        StringBuilder result = new StringBuilder();
        ArrayStack<String> arr = new ArrayStack<>();

        for (int i = 0; i < tokens.length; i++) {
            String token = tokens[i];

            if (token.matches("\\d+")) {
                result.append(token + " ");
            } else if (token.equals("min")) {
                arr.push("min");
            }else if (token.equals("max")) {
                arr.push("max");
            }else if (opValue(token)) {
                while (!arr.isEmpty() && checkOp(arr.peek(), token)) {
                    if (!arr.peek().equals("(")) {
                        result.append(arr.pop() + " ");
                    } else {
                        break;
                    }
                }
                arr.push(token);
            } else if (token.equals("(")) {
                arr.push(token);
            } else if (token.equals(")")) {
                while (!arr.isEmpty() && !arr.peek().equals("(")) {
                    result.append(arr.pop() + " ");
                }
                if (!arr.isEmpty() && arr.peek().equals("(")) {
                    arr.pop();
                }
            }else if (token.equals(",")) {
                while (!arr.peek().equals("(")) {
                    result.append(arr.pop() + " ");
                }
            }
        }

        while (!arr.isEmpty()) {
            result.append(arr.pop() + " ");
        }

        return result.toString().trim();
    }

    public static boolean checkTokenForFunc(String token){
        if (token.equals("+") || token.equals("-") || token.equals("*") || token.equals("/") || token.equals("min") || token.equals("max")) {
            return true;
        }
        return false;
    }

    public static int functionForSolveShYaAl(String[] tokens){
        ArrayStack<Integer> arrForInt = new ArrayStack<>();
        int result;

        for (int i = 0; i < tokens.length; i++) {
            String token = tokens[i];
            if (token.matches("\\d+")) {
                int intNumber = Integer.parseInt(token);
                arrForInt.push(intNumber);
            }else if (checkTokenForFunc(token)) {
                int num1,num2,res;
                if (token.equals("+")){
                    num1 = arrForInt.pop();
                    num2 = arrForInt.pop();
                    arrForInt.push(num2+num1);
                }else if (token.equals("-")){
                    num1 = arrForInt.pop();
                    num2 = arrForInt.pop();
                    arrForInt.push(num2-num1);
                }else if (token.equals("*")){
                    num1 = arrForInt.pop();
                    num2 = arrForInt.pop();
                    arrForInt.push(num2*num1);
                }else if (token.equals("/")){
                    num1 = arrForInt.pop();
                    num2 = arrForInt.pop();
                    res = num2 / num1;
                    arrForInt.push(res);
                }else if (token.equals("min")){
                    num1 = arrForInt.pop();
                    num2 = arrForInt.pop();
                    res = Math.min(num1, num2);
                    arrForInt.push(res);
                }else if (token.equals("max")){
                    num1 = arrForInt.pop();
                    num2 = arrForInt.pop();
                    arrForInt.push(Math.max(num1, num2));
                }
            }
        }
        result = arrForInt.pop();
        return result;
    }

    public static void main(String[] args) {
        Scanner in  = new Scanner(System.in);
        String string = in.nextLine();
        String[] tokens = string.split(" ");
        String str = shuntingYardAlgo(tokens);
        tokens = str.split(" ");
        System.out.println(functionForSolveShYaAl(tokens));
    }
}

interface KarimStack<T> {
    void push(T value);
    T pop();
    T peek();
    int size();
    boolean isEmpty();
}

class ArrayStack<T> implements KarimStack<T> {
    Stack<T> items;
    final int stackCapacity = 256;
    int stackSize;

    public ArrayStack() {
        this.items = new Stack<>();
        this.stackSize = 0;
    }

    @Override
    public int size() {
        return this.stackSize;
    }

    @Override
    public boolean isEmpty() {
        return (this.stackSize == 0);
    }

    @Override
    public void push(T value) {
        this.items.add(this.stackSize, value);
        this.stackSize++;
    }

    @Override
    public T pop() {
        if(this.stackSize == 0) {
            throw new RuntimeException("Pop from an empty stack");
        }
        this.stackSize--;
        T item = this.items.get(this.stackSize);
        this.items.remove(this.stackSize);
        return item;
    }

    @Override
    public T peek() {
        return this.items.get(this.stackSize - 1);
    }
}

class Node<T> {
    T data;
    Node<T> next;

    public Node(T data, Node<T> next) {
        this.data = data;
        this.next = next;
    }
}

interface KarimKhabibQueue<T> {
    void offer(T value);
    T pool();
    T peek();
    int size();
    boolean isEmpty();
}

class LinkedQueue<T> implements KarimKhabibQueue<T> {
    Node<T> head;
    Node<T> tail;
    int queueSize;

    public LinkedQueue() {
        this.head = null;
        this.tail = null;
        this.queueSize = 0;
    }

    @Override
    public int size() {
        return this.queueSize;
    }

    @Override
    public boolean isEmpty() {
        return (this.queueSize == 0);
    }

    @Override
    public void offer(T value) {
        if(this.head == null) {
            this.head = new Node<>(value, null);
            this.tail = this.head;
        }
        else {
            this.tail.next = new Node<>(value, null);
            this.tail = this.tail.next;
        }
        this.queueSize++;
    }

    @Override
    public T pool() {
        T item = this.head.data;
        this.head = this.head.next;

        if(this.head == null)   {
            this.tail = null;
        }

        this.queueSize--;
        return item;
    }

    @Override
    public T peek() {
        return this.head.data;
    }
}