#include "AVL.h"

AVL::AVL() : root(nullptr) {}

AVL::~AVL() {
    clear(root);
}

void AVL::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

int AVL::getHeight(Node* node) const {
    return node ? node->height : 0;
}

int AVL::getBalance(Node* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVL::Node* AVL::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVL::Node* AVL::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVL::Node* AVL::insert(Node* node, int value) {
    if (!node) return new Node(value);

    if (value < node->value) {
        node->left = insert(node->left, value);
    } else if (value > node->value) {
        node->right = insert(node->right, value);
    } else {
        return node; // Duplicates not allowed
    }

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalance(node);

    // Left heavy case
    if (balance > 1 && value < node->left->value) {
        return rightRotate(node);
    }

    // Right heavy case
    if (balance < -1 && value > node->right->value) {
        return leftRotate(node);
    }

    // Left-right case
    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-left case
    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVL::Node* AVL::remove(Node* node, int value) {
    if (!node) return node;

    if (value < node->value) {
        node->left = remove(node->left, value);
    } else if (value > node->value) {
        node->right = remove(node->right, value);
    } else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node* temp = minNode(node->right);
            node->value = temp->value;
            node->right = remove(node->right, temp->value);
        }
    }

    if (!node) return node;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVL::Node* AVL::minNode(Node* node) {
    Node* current = node;
    while (current->left) {
        current = current->left;
    }
    return current;
}

bool AVL::search(int value) const {
    return search(root, value);
}

bool AVL::search(Node* node, int value) const {
    if (!node) return false;
    if (value < node->value) return search(node->left, value);
    if (value > node->value) return search(node->right, value);
    return true;
}

void AVL::display() const {
    displayInOrder(root);
    std::cout << std::endl;
}

void AVL::displayInOrder(Node* node) const {
    if (node) {
        displayInOrder(node->left);
        std::cout << node->value << " ";
        displayInOrder(node->right);
    }
}

// Get nodes for visualization (adds position info to vector)
void AVL::getNodesForVisualization(std::vector<std::pair<int, sf::Vector2f>>& nodes, Node* node, float x, float y, float offsetX) {
    if (node == nullptr) {
        return;
    }

    // Store the node's value and its position
    nodes.push_back({node->value, sf::Vector2f(x, y)});

    // Recursively traverse left and right children
    getNodesForVisualization(nodes, node->left, x - offsetX, y + 100, offsetX / 1.5);
    getNodesForVisualization(nodes, node->right, x + offsetX, y + 100, offsetX / 1.5);
}

void AVL::insert(int value) {
    root = insert(root, value);
}

void AVL::remove(int value) {
    root = remove(root, value);
}