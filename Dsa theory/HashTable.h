#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

using namespace std;

struct HashNode {
    string key;
    string value;
    HashNode* next;
    HashNode(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    HashNode** table;
    int tableSize;
    int count;

    int hashFunction(const string& key) const;

public:
    HashTable(int size = 101);
    ~HashTable();

    void insert(const string& key, const string& value);
    string search(const string& key) const;
    bool remove(const string& key);
    int size() const;
    void clear();
};

#endif // HASHTABLE_H
