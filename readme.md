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

## 🧠 Architectural Rationale: Why These Data Structures & Algorithms?

Below is a detailed breakdown of why each specific data structure and algorithm was selected, along with its time/space complexity and practical relevance:

| Data Structure / Algorithm | Practical Purpose | Architectural Rationale & Why It Is Used | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- | :--- |
| **Graph (Adjacency List)** | Campus Map | Represents physical locations (vertices) and path connections (edges). The map is **sparse** (each building is only connected to a few nearby landmarks). An Adjacency List is chosen over a matrix because it saves memory ($O(V + E)$ vs $O(V^2)$) and speeds up neighbor iteration. | *Iteration:* $O(\text{deg}(V))$ | $O(V + E)$ |
| **Dijkstra's Algorithm** | Shortest Pathfinding | Guaranteed to find the mathematically shortest path between two vertices in a weighted graph with positive weights (representing distances in meters). | $O(V^2)$ *(simpl. array)* | $O(V)$ |
| **Breadth-First Search (BFS)** | Graph Traversal | Traverses the campus layer-by-layer. This is ideal for finding landmarks within $k$ hops/steps (shortest path on unweighted edges) or finding closest services first. | $O(V + E)$ | $O(V)$ |
| **Depth-First Search (DFS)** | Graph Traversal | Explores deep along each path branch. Excellent for validating overall network connectivity, finding loops, or solving maze-like routing structures. | $O(V + E)$ | $O(V)$ |
| **Binary Search Tree (BST)** | Alphabetical Directory | Maintains the locations list sorted alphabetically at all times. Ideal when users require range queries (e.g., retrieving items starting with 'A' through 'D') and sorted traversals. | *Average:* $O(\log n)$<br>*Worst:* $O(n)$ | $O(n)$ |
| **In-Order Traversal** | Directory Printing | Traverses the left subtree, the root, and then the right subtree of the BST. This naturally prints the directory in alphabetical order without sorting overhead. | $O(n)$ | $O(h)$ *(stack)* |
| **Hash Table (Chaining)** | Fast Detail Lookup | Provides immediate $O(1)$ access to building descriptions, opening hours, and room codes by hashing the building name. While a BST takes $O(\log n)$ to search, a Hash Table ensures instant lookup. | *Average:* $O(1)$<br>*Worst:* $O(n)$ | $O(n)$ |
| **Stack (LIFO)** | History / Undo Stack | Stores user activity. Since the last action performed is the first action that should be reversed/undone, the Last-In, First-Out (LIFO) property of a Stack fits this requirement perfectly. | $O(1)$ | $O(n)$ |
| **Queue (FIFO)** | Student Support Tickets | Implements the First-In, First-Out (FIFO) ticketing system. Requests must be resolved fairly in the exact order they were submitted, making a Queue the standard data structure. | $O(1)$ | $O(n)$ |
| **QuickSort** | Dynamic Sorting | Utilizes divide-and-conquer to sort location vectors. Highly efficient in practice and sorts the array in-place, avoiding the high memory overhead of Merge Sort. | *Average:* $O(n \log n)$<br>*Worst:* $O(n^2)$ | $O(\log n)$ *(stack)* |
| **Binary Search** | Logarithmic Searching | Searches for a specific location inside a sorted array. Eliminates half of the search space in each iteration, running in logarithmic time vs $O(n)$ linear search. | $O(\log n)$ | $O(1)$ |

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
