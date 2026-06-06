#include "Sorting.h"

using namespace std;

int Sorting::partition(vector<Location>& arr, int low, int high) {
    string pivot = arr[high].name;
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j].name < pivot) {
            i++;
            // Swap arr[i] and arr[j]
            Location temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i + 1] and arr[high] (or pivot)
    Location temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void Sorting::quickSortByName(vector<Location>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSortByName(arr, low, pi - 1);
        quickSortByName(arr, pi + 1, high);
    }
}

int Sorting::binarySearchByName(const vector<Location>& arr, const string& name) {
    int low = 0;
    int high = (int)arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid].name == name) {
            return mid; // Found
        }
        if (arr[mid].name < name) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Not found
}
