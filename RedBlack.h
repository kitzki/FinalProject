#ifndef REDBLACK_H
#define REDBLACK_H

#include <vector>
#include <SFML/Graphics.hpp>  // For visualization

class RedBlack {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node* parent;
        bool isRed;

        Node(int value) : data(value), left(nullptr), right(nullptr), 
                          parent(nullptr), isRed(true) {}
    };

    Node* root;

    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void fixInsertion(Node* node);
    void fixDeletion(Node* node);
    void transplant(Node* u, Node* v);
    Node* minimum(Node* node);
    Node* maximum(Node* node);
    void clearTree(Node* node);
    Node* findNode(int value) const;
    void inorderTraversalHelper(Node* node) const;
    void displayHelper(Node* node) const;

public:
    RedBlack();
    ~RedBlack();

    void insert(int value);
    void remove(int value);
    bool search(int value) const;
    void display() const;
    void clear();

    // Visualization method to collect nodes and their positions
    void getNodesForVisualization(std::vector<std::pair<int, sf::Vector2f>>& nodes, Node* node, float x, float y, float offsetX);

    // Getter for the root of the tree (if needed for visualization purposes)
    Node* getRoot() const { return root; }
};

#endif // REDBLACK_H
