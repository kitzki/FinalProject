#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <iostream>
using namespace std;

class PriorityQueue {
private:
    vector<int> pqData;  // Internal data structure for the priority queue

    // Helper functions to maintain heap property
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    // Public methods for managing the priority queue
    void enqueue(int value);
    int dequeue();
    bool isEmpty() const;
    void display() const;

    // Public method to access the internal priority queue data (for visualization)
    vector<int>& getData();  // Only declare here
};

#endif // PRIORITYQUEUE_H