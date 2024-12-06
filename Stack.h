#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

class Stack {
private:
    std::vector<int> data; // Internal storage for stack

public:
    // Push an element to the stack
    void push(int value);

    // Pop an element from the stack
    int pop();

    // Get the top element without removing it
    int top() const;

    // Check if the stack is empty
    bool isEmpty() const;

    // Get the stack data (used for visualization)
    std::vector<int>& getData();
};

#endif // STACK_H