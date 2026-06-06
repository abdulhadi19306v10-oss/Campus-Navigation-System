#include "HashTable.h"

HashTable::HashTable(int size) : tableSize(size), count(0) {
    table = new HashNode*[tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    clear();
    delete[] table;
}

int HashTable::hashFunction(const std::string& key) const {
    unsigned long hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % tableSize;
}

void HashTable::insert(const std::string& key, const std::string& value) {
    int index = hashFunction(key);
    HashNode* prev = nullptr;
    HashNode* curr = table[index];

    while (curr != nullptr && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        // Insert new node
        HashNode* newNode = new HashNode(key, value);
        if (prev == nullptr) {
            table[index] = newNode;
        } else {
            prev->next = newNode;
        }
        count++;
    } else {
        // Update existing node
        curr->value = value;
    }
}

std::string HashTable::search(const std::string& key) const {
    int index = hashFunction(key);
    HashNode* curr = table[index];
    while (curr != nullptr) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }
    return ""; // Not found
}

bool HashTable::remove(const std::string& key) {
    int index = hashFunction(key);
    HashNode* prev = nullptr;
    HashNode* curr = table[index];

    while (curr != nullptr && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        return false; // Key not found
    }

    if (prev == nullptr) {
        table[index] = curr->next;
    } else {
        prev->next = curr->next;
    }

    delete curr;
    count--;
    return true;
}

int HashTable::size() const {
    return count;
}

void HashTable::clear() {
    for (int i = 0; i < tableSize; i++) {
        HashNode* curr = table[i];
        while (curr != nullptr) {
            HashNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        table[i] = nullptr;
    }
    count = 0;
}
