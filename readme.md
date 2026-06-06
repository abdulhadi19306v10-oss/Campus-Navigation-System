# Smart Campus Management System (DSA Theory Project)

A premium, console-based application that integrates various fundamental Data Structures and Algorithms (DSA) to manage campus navigation, location directories, fast metadata lookups, support tickets, and history management.

---

## 🚀 Key Modules & DSA Implementation

This system showcases the practical application of multiple key computer science concepts:

1. **Navigation Module (Graph Data Structure)**
   - Represented as an adjacency list of locations.
   - **Dijkstra's Algorithm** to calculate and simulate the shortest path between any two locations.
   - **Breadth-First Search (BFS)** and **Depth-First Search (DFS)** traversals starting from any selected landmark.

2. **Location Directory (Binary Search Tree - BST)**
   - Stores locations alphabetically.
   - Supports insertion, lookup, and deletion of campus landmarks in $O(\log n)$ average time.
   - Performs **In-Order Traversal** to display an alphabetical list of all registered landmarks.

3. **Fast Details Lookup (Hash Table)**
   - Provides $O(1)$ average time complexity lookups for descriptions/metadata of campus locations.
   - Uses collision resolution to manage entries.

4. **History & Undo System (Stack)**
   - Records the user's action history (navigation queries, lookups, directory additions).
   - Allows users to **Undo** the last recorded action.

5. **Student Support Tickets (Queue)**
   - Manages support requests using First-In-First-Out (FIFO) ordering.
   - Features support ticket generation, queue size inspection, and sequential resolution.

6. **Advanced Directory Search (QuickSort & Binary Search)**
   - **QuickSort** is used to sort locations dynamically.
   - **Binary Search** is used on the sorted array to find specific landmark entries with high efficiency.

---

## 📁 File Structure

```text
Dsa theory/
│
├── readme.md                           # Project documentation
├── Dsa theory.slnx                     # Visual Studio Solution metadata
├── Dsa Ccp Project Document.docx       # Project documentation document
│
└── Dsa theory/                         # Source directory
    ├── main.cpp                        # Main entry point & CLI Console Interface
    │
    ├── Graph.h / Graph.cpp             # Graph structure, Dijkstra, BFS, DFS
    ├── BST.h / BST.cpp                 # Binary Search Tree for locations
    ├── HashTable.h / HashTable.cpp     # Hash Table for O(1) metadata lookup
    ├── Stack.h / Stack.cpp             # Stack for history tracking and undo
    ├── Queue.h / Queue.cpp             # Queue for student support tickets
    ├── Sorting.h / Sorting.cpp         # QuickSort and Binary Search implementations
    │
    ├── Dsa theory.vcxproj              # VS Project file
    └── Dsa theory.vcxproj.filters      # VS Filters file
```

---

## 🛠️ Compilation & Execution

### Option 1: Microsoft Visual Studio (Recommended)
1. Open the project folder or the `.slnx` / `.vcxproj` file inside Microsoft Visual Studio.
2. Select the `Debug` or `Release` configuration and target architecture (e.g., `x64`).
3. Press **F5** or click **Start Debugging** to compile and run.

### Option 2: Using Command Line (GCC/Clang)
Compile all files using a standard C++ compiler supporting C++11 or higher:

```bash
g++ -std=c++17 -o CampusNavigation "Dsa theory/main.cpp" "Dsa theory/Graph.cpp" "Dsa theory/BST.cpp" "Dsa theory/HashTable.cpp" "Dsa theory/Stack.cpp" "Dsa theory/Queue.cpp" "Dsa theory/Sorting.cpp"
```

Run the executable:
```bash
./CampusNavigation
```

---

## 🎨 Visuals & Aesthetics
The program utilizes **ANSI escape codes** to present a color-coded console output. Features such as:
- Cyan/Magenta headings and panels.
- Green confirmation checkmarks (`[✓]`).
- Red error indicators (`[Error]`).
- Active travel simulations between vertices displaying paths step-by-step.
