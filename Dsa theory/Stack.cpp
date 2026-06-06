#include "Stack.h"

Stack::Stack() : topNode(nullptr), count(0) {}

Stack::~Stack() {
    clear();
}

void Stack::push(const std::string& item) {
    StackNode* newNode = new StackNode(item);
    newNode->next = topNode;
    topNode = newNode;
    count++;
}

std::string Stack::pop() {
    if (isEmpty()) {
        return "";
    }
    StackNode* temp = topNode;
    std::string data = temp->data;
    topNode = topNode->next;
    delete temp;
    count--;
    return data;
}

std::string Stack::peek() const {
    if (isEmpty()) {
        return "";
    }
    return topNode->data;
}

bool Stack::isEmpty() const {
    return topNode == nullptr;
}

int Stack::size() const {
    return count;
}

void Stack::clear() {
    while (!isEmpty()) {
        pop();
    }
}
