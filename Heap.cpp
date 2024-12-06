#include "Heap.h"

Heap::Heap(bool maxHeap) : isMaxHeap(maxHeap) {}

void Heap::heapifyUp(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && 
           ((isMaxHeap && heapData[index] > heapData[parent]) ||
            (!isMaxHeap && heapData[index] < heapData[parent]))) {
        std::swap(heapData[index], heapData[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void Heap::heapifyDown(int index) {
    int size = heapData.size();
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    while (leftChild < size) {
        int swapIndex = index;

        if ((isMaxHeap && heapData[leftChild] > heapData[swapIndex]) ||
            (!isMaxHeap && heapData[leftChild] < heapData[swapIndex])) {
            swapIndex = leftChild;
        }

        if (rightChild < size &&
            ((isMaxHeap && heapData[rightChild] > heapData[swapIndex]) ||
             (!isMaxHeap && heapData[rightChild] < heapData[swapIndex]))) {
            swapIndex = rightChild;
        }

        if (swapIndex == index) break;

        std::swap(heapData[index], heapData[swapIndex]);
        index = swapIndex;
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
    }
}

void Heap::insert(int value) {
    heapData.push_back(value);
    heapifyUp(heapData.size() - 1);
}

int Heap::remove() {
    if (heapData.empty()) {
        throw std::out_of_range("Heap is empty");
    }

    int rootValue = heapData[0];
    heapData[0] = heapData.back();
    heapData.pop_back();
    if (!heapData.empty()) {
        heapifyDown(0);
    }
    return rootValue;
}

void Heap::display() const {
    for (const auto& val : heapData) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

bool Heap::isEmpty() const {
    return heapData.empty();
}