#include "BST.h"

BST::BST() : root(nullptr), count(0) {}

BST::~BST() {
    clear();
}

BSTNode* BST::insertHelper(BSTNode* node, const Location& loc) {
    if (node == nullptr) {
        count++;
        return new BSTNode(loc);
    }
    if (loc.name < node->data.name) {
        node->left = insertHelper(node->left, loc);
    } else if (loc.name > node->data.name) {
        node->right = insertHelper(node->right, loc);
    }
    // Duplicate location names are not inserted
    return node;
}

void BST::insert(const Location& loc) {
    root = insertHelper(root, loc);
}

BSTNode* BST::findMin(BSTNode* node) const {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

BSTNode* BST::removeHelper(BSTNode* node, const std::string& name, bool& success) {
    if (node == nullptr) {
        success = false;
        return nullptr;
    }

    if (name < node->data.name) {
        node->left = removeHelper(node->left, name, success);
    } else if (name > node->data.name) {
        node->right = removeHelper(node->right, name, success);
    } else {
        // Node found
        success = true;
        count--;

        // Case 1: No child or 1 child
        if (node->left == nullptr) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }

        // Case 2: 2 children
        BSTNode* temp = findMin(node->right);
        node->data = temp->data;
        node->right = removeHelper(node->right, temp->data.name, success);
        // Compensate count decrease since recursive call will reduce count again
        count++; 
    }
    return node;
}

bool BST::remove(const std::string& name) {
    bool success = false;
    root = removeHelper(root, name, success);
    return success;
}

BSTNode* BST::searchHelper(BSTNode* node, const std::string& name) const {
    if (node == nullptr || node->data.name == name) {
        return node;
    }
    if (name < node->data.name) {
        return searchHelper(node->left, name);
    }
    return searchHelper(node->right, name);
}

bool BST::search(const std::string& name, Location& outLoc) const {
    BSTNode* result = searchHelper(root, name);
    if (result != nullptr) {
        outLoc = result->data;
        return true;
    }
    return false;
}

void BST::inorderHelper(BSTNode* node, void (*visit)(const Location&)) const {
    if (node != nullptr) {
        inorderHelper(node->left, visit);
        visit(node->data);
        inorderHelper(node->right, visit);
    }
}

void BST::inorderTraversal(void (*visit)(const Location&)) const {
    inorderHelper(root, visit);
}

void BST::collectHelper(BSTNode* node, std::vector<Location>& list) const {
    if (node != nullptr) {
        collectHelper(node->left, list);
        list.push_back(node->data);
        collectHelper(node->right, list);
    }
}

std::vector<Location> BST::getAllLocationsSorted() const {
    std::vector<Location> list;
    collectHelper(root, list);
    return list;
}

bool BST::isEmpty() const {
    return root == nullptr;
}

int BST::size() const {
    return count;
}

void BST::clearHelper(BSTNode* node) {
    if (node != nullptr) {
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }
}

void BST::clear() {
    clearHelper(root);
    root = nullptr;
    count = 0;
}
