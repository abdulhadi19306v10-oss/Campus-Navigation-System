#ifndef STACK_H
#define STACK_H

#include <string>

using namespace std;

struct StackNode {
    string data;
    StackNode* next;
    StackNode(const string& val) : data(val), next(nullptr) {}
};

class Stack {
private:
    StackNode* topNode;
    int count;

public:
    Stack();
    ~Stack();

    void push(const string& item);
    string pop();
    string peek() const;
    bool isEmpty() const;
    int size() const;
    void clear();
};

#endif // STACK_H
