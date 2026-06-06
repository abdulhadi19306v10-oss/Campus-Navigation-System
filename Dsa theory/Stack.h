#ifndef STACK_H
#define STACK_H

#include <string>

struct StackNode {
    std::string data;
    StackNode* next;
    StackNode(const std::string& val) : data(val), next(nullptr) {}
};

class Stack {
private:
    StackNode* topNode;
    int count;

public:
    Stack();
    ~Stack();

    void push(const std::string& item);
    std::string pop();
    std::string peek() const;
    bool isEmpty() const;
    int size() const;
    void clear();
};

#endif // STACK_H
