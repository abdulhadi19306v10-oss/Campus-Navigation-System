#ifndef BST_H
#define BST_H

#include <string>
#include <vector>

struct Location {
    std::string name;
    std::string description;
    std::string category; // Academic, Admin, Cafeteria, Sports, etc.
    int id;               // ID used in Graph vertices
};

struct BSTNode {
    Location data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(const Location& loc) : data(loc), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;
    int count;

    // Helper functions
    BSTNode* insertHelper(BSTNode* node, const Location& loc);
    BSTNode* findMin(BSTNode* node) const;
    BSTNode* removeHelper(BSTNode* node, const std::string& name, bool& success);
    BSTNode* searchHelper(BSTNode* node, const std::string& name) const;
    void inorderHelper(BSTNode* node, void (*visit)(const Location&)) const;
    void collectHelper(BSTNode* node, std::vector<Location>& list) const;
    void clearHelper(BSTNode* node);

public:
    BST();
    ~BST();

    void insert(const Location& loc);
    bool remove(const std::string& name);
    bool search(const std::string& name, Location& outLoc) const;
    void inorderTraversal(void (*visit)(const Location&)) const;
    std::vector<Location> getAllLocationsSorted() const;
    bool isEmpty() const;
    int size() const;
    void clear();
};

#endif // BST_H
