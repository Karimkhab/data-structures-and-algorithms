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

public static void main(String[] args) {
        Scanner in  = new Scanner(System.in);
        String string = in.nextLine();
        String[] tokens = string.split(" ");
        System.out.println(shuntingYardAlgo(tokens));
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
