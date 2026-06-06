#ifndef QUEUE_H
#define QUEUE_H

#include <string>

using namespace std;

struct Request {
    int id;
    string studentName;
    string issueDescription;
    string urgency; // Low, Medium, High
};

struct QueueNode {
    Request data;
    QueueNode* next;
    QueueNode(const Request& val) : data(val), next(nullptr) {}
};

class Queue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int count;

public:
    Queue();
    ~Queue();

    void enqueue(const Request& req);
    bool dequeue(Request& outReq);
    bool peek(Request& outReq) const;
    bool isEmpty() const;
    int size() const;
    void clear();
};

#endif // QUEUE_H
