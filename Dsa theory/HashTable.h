#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

struct HashNode {
    std::string key;
    std::string value;
    HashNode* next;
    HashNode(const std::string& k, const std::string& v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    HashNode** table;
    int tableSize;
    int count;

    int hashFunction(const std::string& key) const;

public:
    HashTable(int size = 101);
    ~HashTable();

    void insert(const std::string& key, const std::string& value);
    std::string search(const std::string& key) const;
    bool remove(const std::string& key);
    int size() const;
    void clear();
};

#endif // HASHTABLE_H
