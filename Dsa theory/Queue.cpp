#include "Queue.h"

Queue::Queue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

Queue::~Queue() {
    clear();
}

void Queue::enqueue(const Request& req) {
    QueueNode* newNode = new QueueNode(req);
    if (isEmpty()) {
        frontNode = rearNode = newNode;
    } else {
        rearNode->next = newNode;
        rearNode = newNode;
    }
    count++;
}

bool Queue::dequeue(Request& outReq) {
    if (isEmpty()) {
        return false;
    }
    QueueNode* temp = frontNode;
    outReq = temp->data;
    frontNode = frontNode->next;
    if (frontNode == nullptr) {
        rearNode = nullptr;
    }
    delete temp;
    count--;
    return true;
}

bool Queue::peek(Request& outReq) const {
    if (isEmpty()) {
        return false;
    }
    outReq = frontNode->data;
    return true;
}

bool Queue::isEmpty() const {
    return frontNode == nullptr;
}

int Queue::size() const {
    return count;
}

void Queue::clear() {
    Request temp;
    while (dequeue(temp)) {
        // Just empty the queue
    }
}
