#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

template<typename T>
class Stack {
private:
    std::vector<T> elements;
    int maxSize;

public:
    Stack(int max = 100) : maxSize(max) {}
    
    void push(const T& element) {
        if (elements.size() >= maxSize) {
            throw std::overflow_error("Stack overflow");
        }
        elements.push_back(element);
    }
    
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack underflow");
        }
        T top = elements.back();
        elements.pop_back();
        return top;
    }
    
    T& top() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return elements.back();
    }
    
    bool isEmpty() const {
        return elements.empty();
    }
    
    int size() const {
        return elements.size();
    }
    
    void clear() {
        elements.clear();
    }
};

#endif