#include "PriorityQueue.h"

// Helper function to maintain the heap property while moving up the tree
void PriorityQueue::heapifyUp(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && pqData[index] > pqData[parent]) {
        swap(pqData[index], pqData[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

// Helper function to maintain the heap property while moving down the tree
void PriorityQueue::heapifyDown(int index) {
    int size = pqData.size();
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    while (leftChild < size) {
        int swapIndex = index;
        if (pqData[leftChild] > pqData[swapIndex]) {
            swapIndex = leftChild;
        }
        if (rightChild < size && pqData[rightChild] > pqData[swapIndex]) {
            swapIndex = rightChild;
        }
        if (swapIndex == index) break;

        swap(pqData[index], pqData[swapIndex]);
        index = swapIndex;
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
    }
}

// Enqueue: Insert a new value and maintain the heap property
void PriorityQueue::enqueue(int value) {
    pqData.push_back(value);
    heapifyUp(pqData.size() - 1); // Reorder to maintain heap property
}

// Dequeue: Remove the highest priority element (root) and rebuild the heap
int PriorityQueue::dequeue() {
    if (pqData.empty()) {
        throw out_of_range("Priority Queue is empty.");
    }

    int rootValue = pqData[0];  // The highest priority element (root)
    pqData[0] = pqData.back();  // Move the last element to the root
    pqData.pop_back();          // Remove the last element
    if (!pqData.empty()) {
        heapifyDown(0);          // Rebuild the heap from the root
    }
    return rootValue;
}

// Check if the priority queue is empty
bool PriorityQueue::isEmpty() const {
    return pqData.empty();
}

// Display the elements in the priority queue
void PriorityQueue::display() const {
    for (const auto& val : pqData) {
        cout << val << " ";
    }
    cout << endl;
}

// Implement the method to return the internal data for visualization
vector<int>& PriorityQueue::getData() {
    return pqData;  // Return a reference to the vector holding the priority queue's data
}