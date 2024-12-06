#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <stdexcept>

class Queue {
private:
    std::queue<int> data; // Internal storage for queue

public:
    // Enqueue an element to the queue
    void enqueue(int value);

    // Dequeue an element from the queue
    int dequeue();

    // Get the front element without removing it
    int front() const;

    // Check if the queue is empty
    bool isEmpty() const;

    // Get the queue data (used for visualization)
    std::queue<int>& getData();
};

#endif // QUEUE_H