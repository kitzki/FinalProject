#include "BST.h"

// Constructor: Initialize the root as nullptr
BST::BST() : root(nullptr) {}

// Destructor: Clear all nodes in the tree
BST::~BST() {
    clear(root);
}

// Helper to clear nodes recursively
void BST::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

// Public insert function
void BST::insert(int value) {
    insert(root, value);
}

// Recursive insert helper
void BST::insert(Node*& node, int value) {
    if (!node) {
        node = new Node(value);
    } else if (value < node->value) {
        insert(node->left, value);
    } else if (value > node->value) {
        insert(node->right, value);
    }
}

// Public remove function
void BST::remove(int value) {
    root = remove(root, value);
}

// Recursive remove helper
BST::Node* BST::remove(Node* node, int value) {
    if (!node) return nullptr;

    if (value < node->value) {
        node->left = remove(node->left, value);
    } else if (value > node->value) {
        node->right = remove(node->right, value);
    } else {
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        } else {
            Node* minNode = findMin(node->right);
            node->value = minNode->value;
            node->right = remove(node->right, minNode->value);
        }
    }
    return node;
}

// Helper to find the minimum node in a subtree
BST::Node* BST::findMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Public search function
bool BST::search(int value) const {
    return search(root, value);
}

// Recursive search helper
bool BST::search(Node* node, int value) const {
    if (!node) return false;

    if (value < node->value) {
        return search(node->left, value);
    } else if (value > node->value) {
        return search(node->right, value);
    } else {
        return true;
    }
}

// Public display function
void BST::display() const {
    displayInOrder(root);
    cout << endl;
}

// Helper to display tree in-order
void BST::displayInOrder(Node* node) const {
    if (node) {
        displayInOrder(node->left);
        cout << node->value << " ";
        displayInOrder(node->right);
    }
}
