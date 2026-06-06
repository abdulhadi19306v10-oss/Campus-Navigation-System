#include "Stack.h"

using namespace std;

Stack::Stack() : topNode(nullptr), count(0) {}

Stack::~Stack() {
    clear();
}

void Stack::push(const string& item) {
    StackNode* newNode = new StackNode(item);
    newNode->next = topNode;
    topNode = newNode;
    count++;
}

string Stack::pop() {
    if (isEmpty()) {
        return "";
    }
    StackNode* temp = topNode;
    string data = temp->data;
    topNode = topNode->next;
    delete temp;
    count--;
    return data;
}

string Stack::peek() const {
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
