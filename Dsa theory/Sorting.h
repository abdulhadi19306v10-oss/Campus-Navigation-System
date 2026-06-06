#ifndef SORTING_H
#define SORTING_H

#include "BST.h" // For Location struct
#include <vector>
#include <string>

class Sorting {
private:
    static int partition(std::vector<Location>& arr, int low, int high);

public:
    static void quickSortByName(std::vector<Location>& arr, int low, int high);
    static int binarySearchByName(const std::vector<Location>& arr, const std::string& name);
};

#endif // SORTING_H
