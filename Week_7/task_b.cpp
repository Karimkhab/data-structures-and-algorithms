// Karim Khabibrakhmanov DSAI - 05
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Node {
public:
    T key;
    int value;
    bool color; // black - true; red - false;
    Node<T>* parent;
    Node<T>* right;
    Node<T>* left;

    Node(T key, int value, Node<T>* parent) : key(key), value(value), color(false), parent(parent), right(nullptr), left(nullptr) {}
};

template <typename T>
class RedBlackTree {
private:
    void rotateLeft(Node<T>* node) {
        Node<T>* rightNode = node->right;
        node->right = rightNode->left;
        if (rightNode->left != nullptr) {
            rightNode->left->parent = node;
        }
        rightNode->parent = node->parent;
        if (node->parent == nullptr) {
            root = rightNode;
        } else if (node == node->parent->left) {
            node->parent->left = rightNode;
        } else {
            node->parent->right = rightNode;
        }
        rightNode->left = node;
        node->parent = rightNode;
        numOfRotations++;
    }

    void rotateRight(Node<T>* node) {
        Node<T>* leftNode = node->left;
        node->left = leftNode->right;
        if (leftNode->right != nullptr) {
            leftNode->right->parent = node;
        }
        leftNode->parent = node->parent;
        if (node->parent == nullptr) {
            root = leftNode;
        } else if (node == node->parent->right) {
            node->parent->right = leftNode;
        } else {
            node->parent->left = leftNode;
        }
        leftNode->right = node;
        node->parent = leftNode;
        numOfRotations++;
    }

    void fixInsert(Node<T>* node) {
        while (node != root && node->parent->color == false) {
            if (node->parent == node->parent->parent->left) {
                Node<T>* uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == false) {
                    node->parent->color = true;
                    uncle->color = true;
                    node->parent->parent->color = false;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = true;
                    node->parent->parent->color = false;
                    rotateRight(node->parent->parent);
                }
            } else {
                Node<T>* uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == false) {
                    node->parent->color = true;
                    uncle->color = true;
                    node->parent->parent->color = false;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = true;
                    node->parent->parent->color = false;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->color = true;
    }

    Node<T>* fixAdd(Node<T>* midNodeParent, Node<T>* midNode, T key, int value) {
        if (midNode == nullptr) {
            Node<T>* newNode = new Node<T>(key, value, midNodeParent);
            return newNode;
        }

        if (midNode->key == key) {
            cout << "KEY ALREADY EXISTS\n";
            return midNode;
        }
        if (key < midNode->key) {
            midNode->left = fixAdd(midNode, midNode->left, key, value);
        } else {
            midNode->right = fixAdd(midNode, midNode->right, key, value);
        }

        return midNode;
    }

    int countBlackNodesTree(Node<T>* node) {
        if (node == nullptr) return 0;
        int count = (node->color) ? 1 : 0;
        return count + countBlackNodesTree(node->left) + countBlackNodesTree(node->right);
    }

    int countRedNodesTree(Node<T>* node) {
        if (node == nullptr) return 0;
        int count = (!node->color) ? 1 : 0;
        return count + countRedNodesTree(node->left) + countRedNodesTree(node->right);
    }

    Node<T>* findMin(Node<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void transplant(Node<T>* u, Node<T>* v) {
        if (u == nullptr) return;
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void fixDelete(Node<T>* node) {
        while (node != root && node->color) {
            if (node == node->parent->left) {
                Node<T>* sibling = node->parent->right;
                if (sibling == nullptr) break;
                if (!sibling->color) {
                    sibling->color = true;
                    node->parent->color = false;
                    rotateLeft(node->parent);
                    sibling = node->parent->right;
                }
                if ((sibling->left == nullptr || sibling->left->color) &&
                    (sibling->right == nullptr || sibling->right->color)) {
                    sibling->color = false;
                    node = node->parent;
                } else {
                    if (sibling->right == nullptr || sibling->right->color) {
                        if (sibling->left != nullptr) {
                            sibling->left->color = true;
                        }
                        sibling->color = false;
                        rotateRight(sibling);
                        sibling = node->parent->right;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = true;
                    if (sibling->right != nullptr) {
                        sibling->right->color = true;
                    }
                    rotateLeft(node->parent);
                    node = root;
                }
            } else {
                Node<T>* sibling = node->parent->left;
                if (sibling == nullptr) break;
                if (!sibling->color) {
                    sibling->color = true;
                    node->parent->color = false;
                    rotateRight(node->parent);
                    sibling = node->parent->left;
                }
                if ((sibling->right == nullptr || sibling->right->color) &&
                    (sibling->left == nullptr || sibling->left->color)) {
                    sibling->color = false;
                    node = node->parent;
                } else {
                    if (sibling->left == nullptr || sibling->left->color) {
                        if (sibling->right != nullptr) {
                            sibling->right->color = true;
                        }
                        sibling->color = false;
                        rotateLeft(sibling);
                        sibling = node->parent->left;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = true;
                    if (sibling->left != nullptr) {
                        sibling->left->color = true;
                    }
                    rotateRight(node->parent);
                    node = root;
                }
            }
        }
        if (node != nullptr) {
            node->color = true;
        }
    }

    void deleteNodeHelper(Node<T>* node, T key) {
        Node<T>* z = nullptr;
        Node<T>* x;
        Node<T>* y;

        while (node != nullptr) {
            if (node->key == key) {
                z = node;
                break;
            }
            if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        if (z == nullptr) {
            cout << "KEY NOT FOUND\n";
            return;
        }

        y = z;
        bool yOriginalColor = y->color;
        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = findMin(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                if (x != nullptr) {
                    x->parent = y;
                }
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (yOriginalColor && x != nullptr) {
            fixDelete(x);
        }
    }

public:
    int numOfRotations;
    Node<T>* root;

    RedBlackTree() : numOfRotations(0), root(nullptr) {}

    void add(T key, int value) {
        if (root == nullptr) {
            root = new Node<T>(key, value, nullptr);
            root->color = true;
            return;
        }

        root = fixAdd(nullptr, root, key, value);
        Node<T>* newNode = lookUp(root, key);
        fixInsert(newNode);
    }

    Node<T>* lookUp(Node<T>* midNode, T key) {
        if (midNode == nullptr) {
            return nullptr;
        }
        if (midNode->key == key) {
            return midNode;
        }

        if (key < midNode->key) {
            return lookUp(midNode->left, key);
        }
        return lookUp(midNode->right, key);
    }

    void deleteNode(T key) {
        deleteNodeHelper(root, key);
    }

    int getBlackNodesCount() {
        return countBlackNodesTree(root);
    }

    int getRedNodesCount() {
        return countRedNodesTree(root);
    }
};

int main() {
    int numOfOper;
    cin >> numOfOper;
    RedBlackTree<int> karimTree;
    for (int i = 0; i < numOfOper; i++) {
        string operation;
        cin >> operation;
        if (operation == "ADD") {
            int k, v;
            cin >> k >> v;
            karimTree.add(k, v);
        } else if (operation == "LOOKUP") {
            int k;
            cin >> k;
            Node<int>* result = karimTree.lookUp(karimTree.root, k);
            if (result != nullptr) {
                cout << result->value << "\n";
            } else {
                cout << "KEY NOT FOUND\n";
            }
        } else if (operation == "DELETE") {
            int k;
            cin >> k;
            karimTree.deleteNode(k);
        } else if (operation == "PRINT_ROTATIONS") {
            cout << karimTree.numOfRotations << "\n";
        } else if (operation == "PRINT_COUNT_BLACK_KEYS") {
            cout << karimTree.getBlackNodesCount() << "\n";
        } else if (operation == "PRINT_COUNT_RED_KEYS") {
            cout << karimTree.getRedNodesCount() << "\n";
        }
    }
}