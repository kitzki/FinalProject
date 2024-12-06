#include "RedBlack.h"
#include <iostream>

// Constructor
RedBlack::RedBlack() : root(nullptr) {}

// Destructor
RedBlack::~RedBlack() {
    clear();
}

// Left rotation
void RedBlack::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != nullptr) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// Right rotation
void RedBlack::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;

    if (y->right != nullptr) {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

// Insert a value into the tree
void RedBlack::insert(int value) {
    Node* newNode = new Node(value);

    // Perform standard BST insertion
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (newNode->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    newNode->parent = y;

    if (y == nullptr) {
        root = newNode;
    } else if (newNode->data < y->data) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }

    // Fix Red-Black Tree properties
    fixInsertion(newNode);
}

// Fix Red-Black Tree properties after insertion
void RedBlack::fixInsertion(Node* node) {
    while (node->parent != nullptr && node->parent->isRed) {
        Node* grandparent = node->parent->parent;

        if (node->parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle != nullptr && uncle->isRed) {
                // Case 1: Recoloring
                node->parent->isRed = false;
                uncle->isRed = false;
                grandparent->isRed = true;
                node = grandparent;
            } else {
                // Cases 2 & 3
                if (node == node->parent->right) {
                    // Case 2: Left-Right case
                    node = node->parent;
                    rotateLeft(node);
                }

                // Case 3: Left-Left case
                node->parent->isRed = false;
                grandparent->isRed = true;
                rotateRight(grandparent);
            }
        } else {
            // Mirror cases for right side
            Node* uncle = grandparent->left;

            if (uncle != nullptr && uncle->isRed) {
                node->parent->isRed = false;
                uncle->isRed = false;
                grandparent->isRed = true;
                node = grandparent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);
                }

                node->parent->isRed = false;
                grandparent->isRed = true;
                rotateLeft(grandparent);
            }
        }

        if (node == root) break;
    }

    // Ensure root is always black
    root->isRed = false;
}

// Remove a value from the tree
void RedBlack::remove(int value) {
    Node* z = findNode(value);
    if (z == nullptr) return;

    Node* y = z;
    Node* x = nullptr;
    bool yOriginalRed = y->isRed;

    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalRed = y->isRed;
        x = y->right;

        if (y->parent == z) {
            if (x) x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->isRed = z->isRed;
    }

    delete z;

    if (!yOriginalRed) {
        if (x) fixDeletion(x);
    }
}

// Fix Red-Black Tree properties after deletion
void RedBlack::fixDeletion(Node* x) {
    while (x != root && !x->isRed) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;

            if (w->isRed) {
                w->isRed = false;
                x->parent->isRed = true;
                rotateLeft(x->parent);
                w = x->parent->right;
            }

            if (!w->left->isRed && !w->right->isRed) {
                w->isRed = true;
                x = x->parent;
            } else {
                if (!w->right->isRed) {
                    w->left->isRed = false;
                    w->isRed = true;
                    rotateRight(w);
                    w = x->parent->right;
                }

                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->right->isRed = false;
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            // Mirror cases
            Node* w = x->parent->left;

            if (w->isRed) {
                w->isRed = false;
                x->parent->isRed = true;
                rotateRight(x->parent);
                w = x->parent->left;
            }

            if (!w->right->isRed && !w->left->isRed) {
                w->isRed = true;
                x = x->parent;
            } else {
                if (!w->left->isRed) {
                    w->right->isRed = false;
                    w->isRed = true;
                    rotateLeft(w);
                    w = x->parent->left;
                }

                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->left->isRed = false;
                rotateRight(x->parent);
                x = root;
            }
        }
    }

    x->isRed = false;
}

// Replace one subtree as a child of its parent with another subtree
void RedBlack::transplant(Node* u, Node* v) {
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

// Find minimum value node in a subtree
RedBlack::Node* RedBlack::minimum(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Search for a value in the tree
bool RedBlack::search(int value) const {
    return findNode(value) != nullptr;
}

// Find a node with the given value
RedBlack::Node* RedBlack::findNode(int value) const {
    Node* current = root;
    while (current != nullptr) {
        if (value == current->data) {
            return current;
        } else if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

// Inorder traversal helper (for display)
void RedBlack::inorderTraversalHelper(Node* node) const {
    if (node == nullptr) return;
    inorderTraversalHelper(node->left);
    std::cout << node->data << " ";
    inorderTraversalHelper(node->right);
}

// Display tree in-order
void RedBlack::display() const {
    inorderTraversalHelper(root);
    std::cout << std::endl;
}

// Clear entire tree
void RedBlack::clear() {
    clearTree(root);
    root = nullptr;
}

// Recursive tree clearing
void RedBlack::clearTree(Node* node) {
    if (node == nullptr) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

void RedBlack::getNodesForVisualization(std::vector<std::pair<int, sf::Vector2f>>& nodes, Node* node, float x, float y, float offsetX) {
    if (node == nullptr) return;

    // Store the node's value and position (position based on tree structure)
    nodes.push_back({node->data, sf::Vector2f(x, y)});

    // Recursively call for left and right children with adjusted positions
    getNodesForVisualization(nodes, node->left, x - offsetX, y + 100, offsetX / 1.5);
    getNodesForVisualization(nodes, node->right, x + offsetX, y + 100, offsetX / 1.5);
}
