#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <iostream>
#include <algorithm>

class Heap {
private:
    std::vector<int> heapData; // Declare heapData once
    bool isMaxHeap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    Heap(bool maxHeap = true); // Default is max-heap
    void insert(int value);
    int remove();
    void display() const;
    bool isEmpty() const;
    std::vector<int>& getData() {
        return heapData;  // Return the internal vector storing heap elements
    }
};

#endif // HEAP_H
