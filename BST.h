#ifndef BST_H
#define BST_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BST {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, int value);
    Node* remove(Node* node, int value);
    Node* findMin(Node* node);
    bool search(Node* node, int value) const;
    void displayInOrder(Node* node) const;

public:
    BST();
    ~BST();

    void insert(int value);
    void remove(int value);
    bool search(int value) const;
    void display() const;

    // Getter for root node
    Node* getRoot() const {
        return root;
    }

    // Declare visualizeBST as a friend to access private members
    friend void visualizeBST(Node* node, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY);

    void clear(Node* node);
};

#endif // BST_H