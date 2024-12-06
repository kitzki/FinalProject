#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <SFML/Graphics.hpp>  // Include SFML for visualization

class AVL {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        int height;
        Node(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int getHeight(Node* node) const;
    int getBalance(Node* node) const;
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* insert(Node* node, int value);
    Node* remove(Node* node, int value);
    Node* minNode(Node* node);
    bool search(Node* node, int value) const;
    void displayInOrder(Node* node) const;

public:
    AVL();
    ~AVL();

    void clear(Node* node);
    void insert(int value);
    void remove(int value);
    bool search(int value) const;
    void display() const;

    // Method for visualizing the tree
    void getNodesForVisualization(std::vector<std::pair<int, sf::Vector2f>>& nodes, Node* node, float x, float y, float offsetX);
    Node* getRoot() const { return root; } // Accessor for root (used in visualization)
};

#endif // AVL_H