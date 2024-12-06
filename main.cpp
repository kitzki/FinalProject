#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

#include "Heap.h"
#include "BST.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "AVL.h"
#include "RedBlack.h"


using namespace std;

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>  // For calculating positions

void visualizeHeap(const std::vector<int>& heap, sf::RenderWindow& window, sf::Font& font) {
    float xOffset = 300; // Horizontal space between levels
    float yOffset = 100; // Vertical distance between levels
    float radius = 20;   // Radius of each node (circle)

    for (size_t i = 0; i < heap.size(); ++i) {
        int level = std::floor(std::log2(i + 1)); // Determine the level in the tree
        int posInLevel = i - std::pow(2, level) + 1; // Position in the current level

        float x = xOffset * posInLevel + 400; // Horizontal position
        float y = yOffset * level + 50;      // Vertical position

        // Draw the node as a circle
        sf::CircleShape node(radius);
        node.setFillColor(sf::Color::Blue);
        node.setPosition(x - radius, y - radius); // Center the circle
        window.draw(node);

        // Draw the value inside the circle
        sf::Text value;
        value.setFont(font); // Use the provided font
        value.setString(std::to_string(heap[i]));
        value.setCharacterSize(18);         // Font size
        value.setFillColor(sf::Color::White);
        value.setPosition(x - 10, y - 10);  // Center text inside the circle
        window.draw(value);

        // Draw lines to connect the parent and child nodes
        if (i > 0) {
            size_t parentIndex = (i - 1) / 2; // Calculate the parent index

            // Calculate parent node's position
            int parentLevel = std::floor(std::log2(parentIndex + 1));
            int parentPosInLevel = parentIndex - std::pow(2, parentLevel) + 1;
            float parentX = xOffset * parentPosInLevel + 400;
            float parentY = yOffset * parentLevel + 50;

            // Draw the line connecting parent and child
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y)),
                sf::Vertex(sf::Vector2f(parentX, parentY))
            };
            window.draw(line, 2, sf::Lines);
        }
    }
}


void visualizeBST(BST::Node* node, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY) {
    if (!node) return;

    // Draw the node as a circle
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x - 20, y - 20); // Center the circle
    window.draw(circle);

    // Draw the value inside the circle
    sf::Font font;
    font.loadFromFile("Oswald.ttf");
    sf::Text value;
    value.setFont(font);
    value.setString(std::to_string(node->value));
    value.setCharacterSize(20);
    value.setFillColor(sf::Color::White);
    value.setPosition(x - 10, y - 10);
    window.draw(value);

    // Recursively draw left and right subtrees
    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x - offsetX, y + offsetY))
        };
        window.draw(line, 2, sf::Lines);
        visualizeBST(node->left, window, x - offsetX, y + offsetY, offsetX / 1.5, offsetY);
    }
    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x + offsetX, y + offsetY))
        };
        window.draw(line, 2, sf::Lines);
        visualizeBST(node->right, window, x + offsetX, y + offsetY, offsetX / 1.5, offsetY);
    }
}

void visualizeStackAndQueue(const std::vector<int>& data, sf::RenderWindow& window, sf::Font& font, bool isStack) {
    float x = 50;          // Starting x-position for stack (fixed horizontally)
    float y = 500;         // Starting y-position for stack (bottom of the stack)
    float offsetX = 80;    // Horizontal spacing for Queue (queue visualization)
    float offsetY = 40;    // Vertical spacing for Stack (stack visualization)
    float rectWidth = 80;  // Width of each rectangle
    float rectHeight = 30; // Height of each rectangle

    // Loop through all elements in the data (either stack or queue)
    for (size_t i = 0; i < data.size(); ++i) {
        // For stack, adjust y-position (elements go upwards)
        float posX = x;
        float posY = y - i * offsetY; // Stack visualization

        if (!isStack) { 
            // For queue, adjust x-position (elements are displayed horizontally)
            posX = x + i * offsetX;  // Queue visualization
            posY = y;                 // Keep the queue elements at the same y-position
        }

        // Draw the rectangle for each element
        sf::RectangleShape rect(sf::Vector2f(rectWidth, rectHeight));
        rect.setFillColor(sf::Color::Blue);
        rect.setPosition(posX, posY);
        window.draw(rect);

        // Draw the value inside the rectangle
        sf::Text value;
        value.setFont(font);
        value.setString(std::to_string(data[i]));
        value.setCharacterSize(18);
        value.setFillColor(sf::Color::White);
        value.setPosition(posX + rectWidth / 4, posY + 5); // Center the text inside the rectangle
        window.draw(value);
    }
}

std::vector<int> queueToVector(std::queue<int>& q) {
    std::vector<int> vec;
    while (!q.empty()) {
        vec.push_back(q.front());
        q.pop();
    }
    return vec;
}

void visualizePriorityQueue(const std::vector<int>& pqData, sf::RenderWindow& window, sf::Font& font) {
    float x = 50;             // Starting x-position for elements
    float y = 50;             // Starting y-position for the highest priority element
    float offsetX = 60;       // Horizontal distance between elements for each level
    float offsetY = 60;       // Vertical distance between levels (depth of tree)

    // Loop through all elements in the priority queue
    for (size_t i = 0; i < pqData.size(); ++i) {
        float posX = x + (i * offsetX);  // Adjust x position for each element
        float posY = y + (offsetY * (std::log2(i + 1))); // Adjust y position based on level

        // Draw the rectangle representing the element
        sf::RectangleShape rect(sf::Vector2f(50, 30)); // Width and height of each element
        rect.setFillColor(sf::Color::Blue);
        rect.setPosition(posX, posY);
        window.draw(rect);

        // Draw the value inside the rectangle
        sf::Text value;
        value.setFont(font);
        value.setString(std::to_string(pqData[i]));
        value.setCharacterSize(18);
        value.setFillColor(sf::Color::White);
        value.setPosition(posX + 15, posY + 5); // Center the text inside the rectangle
        window.draw(value);
    }
}




Heap heap;
BST bst;
PriorityQueue pq;
AVL avlTree;
RedBlack rbTree;
Stack stack;
Queue queue1;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Menu Navigation");
    window.setFramerateLimit(60);

    sf::Font font;
    // Load font
    if (!font.loadFromFile("Oswald.ttf")) {
        cerr << "Failed to load font!" << endl;
        return -1;
    }

    vector<string> menuOptions;
    menuOptions.push_back("1. Select ADT");
    menuOptions.push_back("2. Insert");
    menuOptions.push_back("3. Delete");
    menuOptions.push_back("4. Search");
    menuOptions.push_back("5. Import File");
    menuOptions.push_back("6. Heap Operations");
    menuOptions.push_back("7. BST Operations");
    menuOptions.push_back("8. Stack Operations");
    menuOptions.push_back("9. Queue Operations");
    menuOptions.push_back("10. Priority Queue Operations");
    menuOptions.push_back("11. AVL Tree Operations");
    menuOptions.push_back("12. Red-Black Tree Operations");
    menuOptions.push_back("13. Exit");

    vector<sf::Text> menuItems;
    for (size_t index = 0; index < menuOptions.size(); ++index) {
        sf::Text item(menuOptions[index], font, 24);
        item.setPosition(50, 50 + index * 40);
        item.setFillColor(sf::Color::White);
        menuItems.push_back(item);
    }

    size_t selectedIndex = 0;
    menuItems[selectedIndex].setFillColor(sf::Color::Blue);

    vector<int> data;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menuItems[selectedIndex].setFillColor(sf::Color::White);
                    if (selectedIndex > 0) selectedIndex--;
                    menuItems[selectedIndex].setFillColor(sf::Color::Blue);
                } else if (event.key.code == sf::Keyboard::Down) {
                    menuItems[selectedIndex].setFillColor(sf::Color::White);
                    if (selectedIndex < menuItems.size() - 1) selectedIndex++;
                    menuItems[selectedIndex].setFillColor(sf::Color::Blue);
                } else if (event.key.code == sf::Keyboard::Enter) {
                    switch (selectedIndex) {
                        // Select ADT
                        case 0: {
                            cout << "ADT Selected!" << endl;
                            break;
                        }
                        // Insert
                        case 1: {
                            cout << "Enter a number to insert: ";
                            int insertValue;
                            cin >> insertValue;
                            data.push_back(insertValue);
                            cout << "Inserted: " << insertValue << endl;
                            break;
                        }
                        // Delete
                        case 2: {
                            if (!data.empty()) {
                                int removed = data.back();
                                data.pop_back();
                                cout << "Deleted: " << removed << endl;
                            } else {
                                cout << "No values to delete!" << endl;
                            }
                            break;
                        }
                        // Search
                        case 3: {
                            cout << "Enter a number to search: ";
                            int searchValue;
                            cin >> searchValue;
                            bool found = false;
                            for (size_t index = 0; index < data.size(); index++) {
                                if (data[index] == searchValue) {
                                    found = true;
                                    break;
                                }
                            }
                            if (found) {
                                cout << "Found: " << searchValue << endl;
                            } else {
                                cout << "Value not found!" << endl;
                            }
                            break;
                        }
                        // Import file
                        case 4: {
                            string filename;
                            cout << "Enter file name to import: ";
                            cin >> filename;
                            ifstream file(filename);
                            if (!file.is_open()) {
                                cerr << "Error: Could not open file!" << endl;
                                break;
                            }
                            string line;
                            while (getline(file, line)) {
                                stringstream ss(line);
                                string token;
                                while (getline(ss, token, ',')) {
                                    try {
                                        data.push_back(stoi(token));
                                    } catch (...) {
                                        cerr << "Error: Invalid number in file!" << endl;
                                    }
                                }
                            }
                            file.close();
                            cout << "File imported successfully!" << endl;
                            break;
                        }
                        // Heap Operations
                       case 5: {
                            cout << "Heap Operations:" << endl;
                            cout << "1. Insert into Heap" << endl;
                            cout << "2. Remove from Heap" << endl;
                            cout << "3. Visualize Heap" << endl;
                            cout << "Enter your choice: ";
                            int heapChoice;
                            cin >> heapChoice;

                            switch (heapChoice) {
                                case 1: {
                                    cout << "Enter value to insert: ";
                                    int value;
                                    cin >> value;
                                    heap.insert(value);
                                    cout << "Value inserted." << endl;
                                    break;
                                }
                                case 2: {
                                    try {
                                        int removed = heap.remove();
                                        cout << "Removed: " << removed << endl;
                                    } catch (const std::exception& e) {
                                        cout << e.what() << endl;
                                    }
                                    break;
                                }
                                case 3: {
                                    // Visualize the heap
                                    sf::RenderWindow heapWindow(sf::VideoMode(800, 600), "Heap Visualization");
                                    heapWindow.setFramerateLimit(60);

                                    while (heapWindow.isOpen()) {
                                        sf::Event event;
                                        while (heapWindow.pollEvent(event)) {
                                            if (event.type == sf::Event::Closed || 
                                                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                                                heapWindow.close();
                                            }
                                        }

                                        heapWindow.clear(sf::Color::Black);
                                        visualizeHeap(heap.getData(), heapWindow, font); // Pass the font
                                        heapWindow.display();
                                    }
                                    break;
                                }
                                default:
                                    cout << "Invalid choice!" << endl;
                            }
                            break;
                        }
                        // BST Operations
                        case 6: {
                            cout << "BST Operations:" << endl;
                            cout << "1. Insert into BST" << endl;
                            cout << "2. Delete from BST" << endl;
                            cout << "3. Search BST" << endl;
                            cout << "4. Display BST" << endl;
                            cout << "Enter your choice: ";
                            int bstChoice;
                            cin >> bstChoice;
                            switch (bstChoice) {
                                case 1: {
                                    cout << "Enter value to insert: ";
                                    int value;
                                    cin >> value;
                                    bst.insert(value);
                                    cout << "Value inserted." << endl;
                                    break;
                                }
                                case 2: {
                                    cout << "Enter value to delete: ";
                                    int value;
                                    cin >> value;
                                    bst.remove(value);
                                    cout << "Value deleted (if it existed)." << endl;
                                    break;
                                }
                                case 3: {
                                    cout << "Enter value to search: ";
                                    int value;
                                    cin >> value;
                                    if (bst.search(value)) {
                                        cout << "Value found in BST." << endl;
                                    } else {
                                        cout << "Value not found in BST." << endl;
                                    }
                                    break;
                                }
                                case 4: {
                                    // Open a new window for BST visualization
                                    sf::RenderWindow visualWindow(sf::VideoMode(800, 600), "BST Visualization");
                                    visualWindow.setFramerateLimit(60);

                                    while (visualWindow.isOpen()) {
                                        sf::Event event;
                                        while (visualWindow.pollEvent(event)) {
                                            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                                                visualWindow.close();
                                            }
                                        }

                                        visualWindow.clear(sf::Color::Black);
                                        visualizeBST(bst.getRoot(), visualWindow, 400, 50, 200, 100); // Adjust positions for the BST
                                        visualWindow.display();
                                    }
                                    break;
                                }
                                default:
                                    cout << "Invalid choice!" << endl;
                            }
                            break;
                        }      
                                case 7: { // Stack Operations
                                    cout << "Stack Operations:" << endl;
                                    cout << "1. Push to Stack" << endl;
                                    cout << "2. Pop from Stack" << endl;
                                    cout << "3. Visualize Stack" << endl;
                                    cout << "Enter your choice: ";
                                    int stackChoice;
                                    cin >> stackChoice;

                                    switch (stackChoice) {
                                        case 1: { // Push to Stack
                                            cout << "Enter value to push: ";
                                            int value;
                                            cin >> value;
                                            stack.push(value);
                                            cout << "Value pushed to stack." << endl;
                                            break;
                                        }
                                        case 2: { // Pop from Stack
                                            try {
                                                int value = stack.pop();
                                                cout << "Popped from stack: " << value << endl;
                                            } catch (const std::exception& e) {
                                                cout << e.what() << endl;
                                            }
                                            break;
                                        }
                                        case 3: { // Visualize Stack
                                            // Open a separate window for Stack visualization
                                            sf::RenderWindow stackWindow(sf::VideoMode(800, 600), "Stack Visualization");
                                            stackWindow.setFramerateLimit(60);

                                            while (stackWindow.isOpen()) {
                                                sf::Event event;
                                                while (stackWindow.pollEvent(event)) {
                                                    if (event.type == sf::Event::Closed || 
                                                        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                                                        stackWindow.close();
                                                    }
                                                }

                                                stackWindow.clear(sf::Color::Black);
                                                visualizeStackAndQueue(stack.getData(), stackWindow, font, true); // Visualize Stack
                                                stackWindow.display();
                                            }
                                            break;
                                        }
                                        default:
                                            cout << "Invalid choice!" << endl;
                                            break;
                                    }
                                    break;
                                }
                                case 8: { // Queue Operations
                                    cout << "Queue Operations:" << endl;
                                    cout << "1. Enqueue to Queue" << endl;
                                    cout << "2. Dequeue from Queue" << endl;
                                    cout << "3. Visualize Queue" << endl;
                                    cout << "Enter your choice: ";
                                    int queueChoice;
                                    cin >> queueChoice;

                                    switch (queueChoice) {
                                        case 1: { // Enqueue to Queue
                                            cout << "Enter value to enqueue: ";
                                            int value;
                                            cin >> value;
                                            queue1.enqueue(value);
                                            cout << "Value enqueued to queue." << endl;
                                            break;
                                        }
                                        case 2: { // Dequeue from Queue
                                            try {
                                                int value = queue1.dequeue();
                                                cout << "Dequeued from queue: " << value << endl;
                                            } catch (const std::exception& e) {
                                                cout << e.what() << endl;
                                            }
                                            break;
                                        }
                                        case 3: { // Visualize Queue
                                            // Convert the queue to a vector for visualization
                                            std::vector<int> queueData;
                                            std::queue<int> tempQueue = queue1.getData(); // Make a copy of the queue
                                            while (!tempQueue.empty()) {
                                                queueData.push_back(tempQueue.front());
                                                tempQueue.pop();
                                            }

                                            // Open a separate window for Queue visualization
                                            sf::RenderWindow queueWindow(sf::VideoMode(800, 600), "Queue Visualization");
                                            queueWindow.setFramerateLimit(60);

                                            while (queueWindow.isOpen()) {
                                                sf::Event event;
                                                while (queueWindow.pollEvent(event)) {
                                                    if (event.type == sf::Event::Closed || 
                                                        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                                                        queueWindow.close();
                                                    }
                                                }

                                                queueWindow.clear(sf::Color::Black);
                                                visualizeStackAndQueue(queueData, queueWindow, font, false); // Visualize Queue
                                                queueWindow.display();
                                            }
                                            break;
                                        }
                                        default:
                                            cout << "Invalid choice!" << endl;
                                            break;
                                    }
                                    break;
                                }
                                case 9: { // Priority Queue Operations
                                    cout << "Priority Queue Operations:" << endl;
                                    cout << "1. Enqueue to Priority Queue" << endl;
                                    cout << "2. Dequeue from Priority Queue" << endl;
                                    cout << "3. Visualize Priority Queue" << endl;
                                    cout << "Enter your choice: ";
                                    int pqChoice;
                                    cin >> pqChoice;

                                    switch (pqChoice) {
                                        case 1: { // Enqueue to Priority Queue
                                            cout << "Enter value to enqueue: ";
                                            int value;
                                            cin >> value;
                                            pq.enqueue(value);
                                            cout << "Value enqueued to priority queue." << endl;
                                            break;
                                        }
                                        case 2: { // Dequeue from Priority Queue
                                            try {
                                                int value = pq.dequeue();
                                                cout << "Dequeued from priority queue: " << value << endl;
                                            } catch (const std::exception& e) {
                                                cout << e.what() << endl;
                                            }
                                            break;
                                        }
                                        case 3: { // Visualize Priority Queue
                                            // Convert the priority queue to a vector for visualization
                                            std::vector<int> pqData;
                                            std::priority_queue<int> tempQueue;  // Make a copy of the priority queue
                                            
                                            // Copy elements from the priority queue to a vector
                                            while (!pq.isEmpty()) {
                                                tempQueue.push(pq.dequeue()); // Pop elements from the original priority queue
                                            }

                                            // Transfer the data from the priority queue to a vector
                                            while (!tempQueue.empty()) {
                                                pqData.push_back(tempQueue.top());
                                                tempQueue.pop();
                                            }

                                            // Open a separate window for Priority Queue visualization
                                            sf::RenderWindow pqWindow(sf::VideoMode(800, 600), "Priority Queue Visualization");
                                            pqWindow.setFramerateLimit(60);

                                            while (pqWindow.isOpen()) {
                                                sf::Event event;
                                                while (pqWindow.pollEvent(event)) {
                                                    if (event.type == sf::Event::Closed || 
                                                        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                                                        pqWindow.close();
                                                    }
                                                }

                                                pqWindow.clear(sf::Color::Black);
                                                visualizePriorityQueue(pqData, pqWindow, font); // Visualize Priority Queue
                                                pqWindow.display();
                                            }
                                            break;
                                        }
                                        default:
                                            cout << "Invalid choice!" << endl;
                                            break;
                                    }
                                    break;
                                }
                                case 10: { // AVL Tree Operations
                                    cout << "AVL Tree Operations:" << endl;
                                    cout << "1. Insert into AVL Tree" << endl;
                                    cout << "2. Remove from AVL Tree" << endl;
                                    cout << "3. Search AVL Tree" << endl;
                                    cout << "4. Display AVL Tree" << endl;
                                    cout << "5. Visualize AVL Tree" << endl;
                                    cout << "Enter your choice: ";
                                    int avlChoice;
                                    cin >> avlChoice;

                                    switch (avlChoice) {
                                        case 1: { // Insert into AVL Tree
                                            cout << "Enter value to insert: ";
                                            int value;
                                            cin >> value;
                                            avlTree.insert(value);
                                            cout << "Value inserted." << endl;
                                            break;
                                        }
                                        case 2: { // Remove from AVL Tree
                                            cout << "Enter value to remove: ";
                                            int value;
                                            cin >> value;
                                            avlTree.remove(value);
                                            cout << "Value removed (if it existed)." << endl;
                                            break;
                                        }
                                        case 3: { // Search AVL Tree
                                            cout << "Enter value to search: ";
                                            int value;
                                            cin >> value;
                                            if (avlTree.search(value)) {
                                                cout << "Value found in AVL Tree." << endl;
                                            } else {
                                                cout << "Value not found in AVL Tree." << endl;
                                            }
                                            break;
                                        }
                                        case 4: { // Display AVL Tree
                                            cout << "AVL Tree Elements (in-order): ";
                                            avlTree.display();
                                            break;
                                        }
                                        case 5: { // Visualize AVL Tree
                                            // Open a new window for AVL Tree visualization
                                            sf::RenderWindow avlWindow(sf::VideoMode(800, 600), "AVL Tree Visualization");
                                            avlWindow.setFramerateLimit(60);

                                            // Get nodes for visualization
                                            std::vector<std::pair<int, sf::Vector2f>> nodes;
                                            avlTree.getNodesForVisualization(nodes, avlTree.getRoot(), 400, 50, 200); // Starting position for the root

                                            // Loop to visualize
                                            while (avlWindow.isOpen()) {
                                                sf::Event event;
                                                while (avlWindow.pollEvent(event)) {
                                                    if (event.type == sf::Event::Closed || 
                                                        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                                                        avlWindow.close();
                                                    }
                                                }

                                                avlWindow.clear(sf::Color::White);

                                                // Draw all nodes
                                                for (const auto& node : nodes) {
                                                    sf::CircleShape circle(20);
                                                    circle.setFillColor(sf::Color::Green);
                                                    circle.setPosition(node.second.x - 20, node.second.y - 20); // Center the circle
                                                    avlWindow.draw(circle);

                                                    // Display node value
                                                    sf::Font font;
                                                    font.loadFromFile("Oswald.ttf"); // You can replace this with a valid font
                                                    sf::Text text;
                                                    text.setFont(font);
                                                    text.setString(std::to_string(node.first));
                                                    text.setCharacterSize(20);
                                                    text.setFillColor(sf::Color::Black);
                                                    text.setPosition(node.second.x - 10, node.second.y - 10);
                                                    avlWindow.draw(text);
                                                }

                                                // Draw edges (lines connecting parent and child nodes)
                                                for (size_t i = 0; i < nodes.size(); ++i) {
                                                    if (2 * i + 1 < nodes.size()) {  // Left child
                                                        sf::Vertex line[] =
                                                            { sf::Vertex(nodes[i].second), sf::Vertex(nodes[2 * i + 1].second) };
                                                        avlWindow.draw(line, 2, sf::Lines);
                                                    }
                                                    if (2 * i + 2 < nodes.size()) {  // Right child
                                                        sf::Vertex line[] =
                                                            { sf::Vertex(nodes[i].second), sf::Vertex(nodes[2 * i + 2].second) };
                                                        avlWindow.draw(line, 2, sf::Lines);
                                                    }
                                                }

                                                avlWindow.display();
                                            }
                                            break;
                                        }
                                        default:
                                            cout << "Invalid choice!" << endl;
                                            break;
                                    }
                                    break;
                                }
                                case 11: { // Red-Black Tree Operations
                                    cout << "Red-Black Tree Operations:" << endl;
                                    cout << "1. Insert into Red-Black Tree" << endl;
                                    cout << "2. Remove from Red-Black Tree" << endl;
                                    cout << "3. Search Red-Black Tree" << endl;
                                    cout << "4. Display Red-Black Tree" << endl;
                                    cout << "5. Visualize Red-Black Tree" << endl;
                                    cout << "Enter your choice: ";
                                    int rbChoice;
                                    cin >> rbChoice;

                                    switch (rbChoice) {
                                        case 1: { // Insert into Red-Black Tree
                                            cout << "Enter value to insert: ";
                                            int value;
                                            cin >> value;
                                            rbTree.insert(value);
                                            cout << "Value inserted." << endl;
                                            break;
                                        }
                                        case 2: { // Remove from Red-Black Tree
                                            cout << "Enter value to remove: ";
                                            int value;
                                            cin >> value;
                                            rbTree.remove(value);
                                            cout << "Value removed (if it existed)." << endl;
                                            break;
                                        }
                                        case 3: { // Search Red-Black Tree
                                            cout << "Enter value to search: ";
                                            int value;
                                            cin >> value;
                                            if (rbTree.search(value)) {
                                                cout << "Value found in Red-Black Tree." << endl;
                                            } else {
                                                cout << "Value not found in Red-Black Tree." << endl;
                                            }
                                            break;
                                        }
                                        case 4: { // Display Red-Black Tree
                                            cout << "Red-Black Tree Elements (in-order): ";
                                            rbTree.display();
                                            break;
                                        }
                                        case 5: { // Visualize Red-Black Tree
                                            // Open a new window for Red-Black Tree visualization
                                            sf::RenderWindow rbWindow(sf::VideoMode(800, 600), "Red-Black Tree Visualization");
                                            rbWindow.setFramerateLimit(60);

                                            std::vector<std::pair<int, sf::Vector2f>> nodes;
                                            rbTree.getNodesForVisualization(nodes, rbTree.getRoot(), 400, 50, 200); // Starting position for the root

                                            while (rbWindow.isOpen()) {
                                                sf::Event event;
                                                while (rbWindow.pollEvent(event)) {
                                                    if (event.type == sf::Event::Closed || 
                                                        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                                                        rbWindow.close();
                                                    }
                                                }

                                                rbWindow.clear(sf::Color::White);

                                                // Draw all nodes
                                                for (const auto& node : nodes) {
                                                    sf::CircleShape circle(20);
                                                    circle.setFillColor(sf::Color::Red);  // Set color for Red-Black nodes (Red color for Red nodes)
                                                    circle.setPosition(node.second.x - 20, node.second.y - 20); // Center the circle
                                                    rbWindow.draw(circle);

                                                    // Display node value
                                                    sf::Font font;
                                                    font.loadFromFile("Oswald.ttf"); // You can replace this with a valid font
                                                    sf::Text text;
                                                    text.setFont(font);
                                                    text.setString(std::to_string(node.first));
                                                    text.setCharacterSize(20);
                                                    text.setFillColor(sf::Color::Black);
                                                    text.setPosition(node.second.x - 10, node.second.y - 10);
                                                    rbWindow.draw(text);
                                                }

                                                // Draw edges (lines connecting parent and child nodes)
                                                for (size_t i = 0; i < nodes.size(); ++i) {
                                                    if (2 * i + 1 < nodes.size()) {  // Left child
                                                        sf::Vertex line[] =
                                                            { sf::Vertex(nodes[i].second), sf::Vertex(nodes[2 * i + 1].second) };
                                                        rbWindow.draw(line, 2, sf::Lines);
                                                    }
                                                    if (2 * i + 2 < nodes.size()) {  // Right child
                                                        sf::Vertex line[] =
                                                            { sf::Vertex(nodes[i].second), sf::Vertex(nodes[2 * i + 2].second) };
                                                        rbWindow.draw(line, 2, sf::Lines);
                                                    }
                                                }

                                                rbWindow.display();
                                            }
                                            break;
                                        }
                                        default:
                                            cout << "Invalid choice!" << endl;
                                            break;
                                    }
                                    break;
                                }
                                return 0;
                    }
                }
            }
        }
    }
}
