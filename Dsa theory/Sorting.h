#ifndef SORTING_H
#define SORTING_H

#include "BST.h" // For Location struct
#include <vector>
#include <string>

using namespace std;

class Sorting {
private:
    static int partition(vector<Location>& arr, int low, int high);

public:
    static void quickSortByName(vector<Location>& arr, int low, int high);
    static int binarySearchByName(const vector<Location>& arr, const string& name);
};

#endif // SORTING_H
