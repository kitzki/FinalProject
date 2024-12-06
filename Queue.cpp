#include "Queue.h"

void Queue::enqueue(int value) {
    data.push(value);
}

int Queue::dequeue() {
    if (data.empty()) {
        throw std::out_of_range("Queue is empty!");
    }
    int value = data.front();
    data.pop();
    return value;
}

int Queue::front() const {
    if (data.empty()) {
        throw std::out_of_range("Queue is empty!");
    }
    return data.front();
}

bool Queue::isEmpty() const {
    return data.empty();
}

std::queue<int>& Queue::getData() {
    return data;
}