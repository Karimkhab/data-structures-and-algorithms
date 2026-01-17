// Karim Khabibrakhmanov DSAI - 05
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class AVLTreeNode {
public:
    T key;
    int value;
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;

    AVLTreeNode(T key, int value) {
        this->key = key;
        this->value = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }

    int balanceFactor() {
        int leftHeight = (left != nullptr) ? left->height : 0;
        int rightHeight = (right != nullptr) ? right->height : 0;
        return leftHeight - rightHeight;
    }
};

template <typename T>
class KarimKhabibrakhmanovAVLTREE {
public:
    AVLTreeNode<T>* root;
    int numberOfRotations;

    KarimKhabibrakhmanovAVLTREE() {
        root = nullptr;
        numberOfRotations = 0;
    }

    int height(AVLTreeNode<T>* node) {
        return (node != nullptr) ? node->height : 0;
    }

    AVLTreeNode<T>* rightRotate(AVLTreeNode<T>* nodeY) {
        AVLTreeNode<T>* nodeX = nodeY->left;
        AVLTreeNode<T>* tempNode = nodeX->right;
        nodeX->right = nodeY;
        nodeY->left = tempNode;
        nodeY->height = 1 + max(height(nodeY->left), height(nodeY->right));
        nodeX->height = 1 + max(height(nodeX->left), height(nodeX->right));
        numberOfRotations++;
        return nodeX;
    }

    AVLTreeNode<T>* leftRotate(AVLTreeNode<T>* nodeX) {
        AVLTreeNode<T>* nodeY = nodeX->right;
        AVLTreeNode<T>* tempNode = nodeY->left;
        nodeY->left = nodeX;
        nodeX->right = tempNode;
        nodeX->height = 1 + max(height(nodeX->left), height(nodeX->right));
        nodeY->height = 1 + max(height(nodeY->left), height(nodeY->right));
        numberOfRotations++;
        return nodeY;
    }

    AVLTreeNode<T>* balance(AVLTreeNode<T>* node) {
        if (!node) {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balanceFactor = node->balanceFactor();

        if (balanceFactor > 1) {
            if (node->left->balanceFactor() >= 0) {
                return rightRotate(node);
            } else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        } else if (balanceFactor < -1) {
            if (node->right->balanceFactor() <= 0) {
                return leftRotate(node);
            } else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    void add(T key, int value) {
        root = addRecursive(root, key, value);
    }

    AVLTreeNode<T>* addRecursive(AVLTreeNode<T>* node, T key, int value) {
        if (!node) {
            return new AVLTreeNode<T>(key, value);
        }

        if (key < node->key) {
            node->left = addRecursive(node->left, key, value);
        } else if (key > node->key) {
            node->right = addRecursive(node->right, key, value);
        } else {
            cout << "KEY ALREADY EXISTS" << "\n";
            return node;
        }

        return balance(node);
    }

    void remove(T key) {
        root = removeRecursive(root, key);
    }

    AVLTreeNode<T>* removeRecursive(AVLTreeNode<T>* node, T key) {
        if (!node) {
            cout << "KEY NOT FOUND" << "\n";
            return node;
        }

        if (key < node->key) {
            node->left = removeRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = removeRecursive(node->right, key);
        } else {
            if (!node->left || !node->right) {
                AVLTreeNode<T>* temp = (node->left != nullptr) ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                AVLTreeNode<T>* temp = node->right;
                while (temp->left) {
                    temp = temp->left;
                }
                node->key = temp->key;
                node->value = temp->value;
                node->right = removeRecursive(node->right, temp->key);
            }
        }

        if (!node) {
            return node;
        }

        return balance(node);
    }

    AVLTreeNode<T>* search(AVLTreeNode<T>* node, T key) {
        if (!node || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return search(node->left, key);
        }

        return search(node->right, key);
    }

    void lookup(T key) {
        AVLTreeNode<T>* result = search(root, key);
        if (!result) {
            cout << "KEY NOT FOUND" << "\n";
        } else {
            cout << result->value << "\n";
        }
    }
};

int main() {
    int numberOfOperations;
    cin >> numberOfOperations;
    KarimKhabibrakhmanovAVLTREE<int> avlTree;

    for (int i = 0; i < numberOfOperations; i++) {
        string operation;
        cin >> operation;

        if (operation == "ADD") {
            int key, value;
            cin >> key >> value;
            avlTree.add(key, value);
        } else if (operation == "LOOKUP") {
            int key;
            cin >> key;
            avlTree.lookup(key);
        } else if (operation == "DELETE") {
            int key;
            cin >> key;
            avlTree.remove(key);
        } else if (operation == "PRINT_ROTATIONS") {
            cout << avlTree.numberOfRotations << "\n";
        }
    }
}