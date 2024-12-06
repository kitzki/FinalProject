#include "Stack.h"

void Stack::push(int value) {
    data.push_back(value);
}

int Stack::pop() {
    if (data.empty()) {
        throw std::out_of_range("Stack is empty!");
    }
    int value = data.back();
    data.pop_back();
    return value;
}

int Stack::top() const {
    if (data.empty()) {
        throw std::out_of_range("Stack is empty!");
    }
    return data.back();
}

bool Stack::isEmpty() const {
    return data.empty();
}

std::vector<int>& Stack::getData() {
    return data;
}