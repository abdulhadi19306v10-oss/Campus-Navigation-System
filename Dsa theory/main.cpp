#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

// Include custom data structure headers
#include "Stack.h"
#include "Queue.h"
#include "BST.h"
#include "HashTable.h"
#include "Graph.h"
#include "Sorting.h"

using namespace std;

// Color codes for premium console output
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define MAGENTA "\033[1;35m"
#define WHITE   "\033[1;37m"

// Function to enable virtual terminal processing on Windows for ANSI colors
void enableVirtualTerminalColors() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}

// Global instances of Data Structures
Graph campusMap;
BST locationDirectory;
HashTable detailsLookup;
Stack searchHistory;
Queue supportQueue;

int requestCounter = 100; // Counter for support request IDs

// Print a horizontal separator line
void printSeparator() {
    cout << WHITE << "══════════════════════════════════════════════════════════════" << RESET << endl;
}

// Function to clear screen (cross-platform helper)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Simulates travel animation
void simulateTravel(const vector<int>& path) {
    cout << YELLOW << "\n[!] Starting travel simulation..." << RESET << endl;
    for (size_t i = 0; i < path.size(); i++) {
        cout << GREEN << " -> " << campusMap.getVertexName(path[i]) << RESET;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << GREEN << "\n[✓] Arrived safely at your destination!" << RESET << endl;
}

// Callback for BST traversal printing
void printLocationBrief(const Location& loc) {
    cout << "  • " << CYAN << left << setw(25) << loc.name << RESET
              << MAGENTA << setw(15) << loc.category << RESET
              << " (ID: " << loc.id << ")" << endl;
}

// Initialize system with pre-populated campus data
void initializeCampusData() {
    // 1. Add Vertices to Graph
    campusMap.addVertex(1, "Main Gate");
    campusMap.addVertex(2, "Admin Block");
    campusMap.addVertex(3, "Central Cafeteria");
    campusMap.addVertex(4, "Computer Science Dept");
    campusMap.addVertex(5, "Central Library");
    campusMap.addVertex(6, "Sports Complex");
    campusMap.addVertex(7, "Student Hostel");
    campusMap.addVertex(8, "Auditorium");

    // 2. Add Edges to Graph
    campusMap.addEdge(1, 2, 100.0); // Main Gate <-> Admin Block
    campusMap.addEdge(1, 5, 250.0); // Main Gate <-> Central Library
    campusMap.addEdge(2, 3, 150.0); // Admin Block <-> Cafeteria
    campusMap.addEdge(2, 5, 200.0); // Admin Block <-> Library
    campusMap.addEdge(3, 4, 120.0); // Cafeteria <-> CS Dept
    campusMap.addEdge(3, 8, 180.0); // Cafeteria <-> Auditorium
    campusMap.addEdge(4, 5, 80.0);  // CS Dept <-> Library
    campusMap.addEdge(4, 6, 220.0); // CS Dept <-> Sports Complex
    campusMap.addEdge(4, 7, 300.0); // CS Dept <-> Student Hostel
    campusMap.addEdge(5, 6, 150.0); // Library <-> Sports Complex
    campusMap.addEdge(6, 7, 180.0); // Sports Complex <-> Hostel
    campusMap.addEdge(8, 7, 250.0); // Auditorium <-> Hostel

    // 3. Add to BST (Location Management)
    locationDirectory.insert({"Main Gate", "The primary entry and exit point of the university campus.", "Gate", 1});
    locationDirectory.insert({"Admin Block", "Central administrative offices, admissions office, and registrar.", "Admin", 2});
    locationDirectory.insert({"Central Cafeteria", "Offers a variety of meals, snacks, and drinks for students.", "Cafeteria", 3});
    locationDirectory.insert({"Computer Science Dept", "State-of-the-art computer labs, classrooms, and faculty offices.", "Academic", 4});
    locationDirectory.insert({"Central Library", "Home to over 50,000 books, research papers, and study spaces.", "Academic", 5});
    locationDirectory.insert({"Sports Complex", "Includes a gymnasium, basketball court, and outdoor athletics track.", "Sports", 6});
    locationDirectory.insert({"Student Hostel", "Residential facility housing undergraduate and postgraduate students.", "Housing", 7});
    locationDirectory.insert({"Auditorium", "Large hall for guest lectures, cultural events, and orientations.", "Facility", 8});

    // 4. Add metadata to HashTable (Fast Lookup)
    detailsLookup.insert("Main Gate", "Open 24/7. Visitors must present identification. Security staff present.");
    detailsLookup.insert("Admin Block", "Working hours: 09:00 AM - 05:00 PM (Monday-Friday). Admissions desk on Ground Floor.");
    detailsLookup.insert("Central Cafeteria", "Working hours: 08:00 AM - 09:00 PM. Offers vegetarian and non-vegetarian menus.");
    detailsLookup.insert("Computer Science Dept", "Open 08:00 AM - 06:00 PM. High-speed Wi-Fi and specialized AI laboratories available.");
    detailsLookup.insert("Central Library", "Working hours: 08:00 AM - 10:00 PM. Silent study zones on the 2nd floor.");
    detailsLookup.insert("Sports Complex", "Open 06:00 AM - 09:00 PM. Equipment rental requires student ID card.");
    detailsLookup.insert("Student Hostel", "24/7 access for residents. Curfew time is 10:00 PM for visitors.");
    detailsLookup.insert("Auditorium", "Booking required 1 week in advance through Admin Block. Capacity: 500 seats.");
}

const string LOCATIONS_FILE = "locations.txt";
const string EDGES_FILE = "edges.txt";

void saveData() {
    ofstream locFile(LOCATIONS_FILE);
    if (locFile.is_open()) {
        vector<Location> locations = locationDirectory.getAllLocationsSorted();
        for (const auto& loc : locations) {
            locFile << loc.id << "|" << loc.name << "|" << loc.category << "|" << loc.description << "\n";
        }
        locFile.close();
    } else {
        cerr << RED << "[Error] Could not open " << LOCATIONS_FILE << " for writing." << RESET << endl;
    }

    ofstream edgeFile(EDGES_FILE);
    if (edgeFile.is_open()) {
        vector<pair<pair<int, int>, double>> edges = campusMap.getEdgesList();
        for (const auto& edge : edges) {
            edgeFile << edge.first.first << "|" << edge.first.second << "|" << edge.second << "\n";
        }
        edgeFile.close();
    } else {
        cerr << RED << "[Error] Could not open " << EDGES_FILE << " for writing." << RESET << endl;
    }
}

void loadData() {
    ifstream locFile(LOCATIONS_FILE);
    ifstream edgeFile(EDGES_FILE);

    if (!locFile.good() || !edgeFile.good()) {
        cout << YELLOW << "[!] Persistent data files not found. Initializing with default campus data..." << RESET << endl;
        if (locFile.is_open()) locFile.close();
        if (edgeFile.is_open()) edgeFile.close();
        
        initializeCampusData();
        saveData();
        return;
    }

    campusMap.clear();
    locationDirectory.clear();
    detailsLookup.clear();

    string line;
    while (getline(locFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, name, category, description;
        if (getline(ss, idStr, '|') &&
            getline(ss, name, '|') &&
            getline(ss, category, '|') &&
            getline(ss, description)) {
            
            int id = stoi(idStr);
            Location loc = {name, description, category, id};
            locationDirectory.insert(loc);
            campusMap.addVertex(id, name);
            detailsLookup.insert(name, description);
        }
    }
    locFile.close();

    while (getline(edgeFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string srcIdStr, destIdStr, weightStr;
        if (getline(ss, srcIdStr, '|') &&
            getline(ss, destIdStr, '|') &&
            getline(ss, weightStr)) {
            
            int srcId = stoi(srcIdStr);
            int destId = stoi(destIdStr);
            double weight = stod(weightStr);
            campusMap.addEdge(srcId, destId, weight);
        }
    }
    edgeFile.close();
    
    cout << GREEN << "[✓] Successfully loaded campus data from persistent storage." << RESET << endl;
    this_thread::sleep_for(chrono::milliseconds(800));
}

// Press Enter to Continue prompt
void pressEnter() {
    cout << WHITE << "\nPress Enter to return to menu...";
    cin.ignore();
    cin.get();
}

int main() {
    enableVirtualTerminalColors();
    loadData();

    while (true) {
        clearScreen();
        cout << CYAN << BOLD;
        cout << "╔═════════════════════════════════════════════════════════════╗" << endl;
        cout << "║          SMART CAMPUS MANAGEMENT SYSTEM (DSA PROJECT)       ║" << endl;
        cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << endl;
        cout << WHITE << "  [1] Navigation Module (Shortest Path & BFS/DFS)" << RESET << endl;
        cout << WHITE << "  [2] Location Directory (BST In-Order list & Add/Delete)" << RESET << endl;
        cout << WHITE << "  [3] Fast Details Lookup (HashTable Metadata)" << RESET << endl;
        cout << WHITE << "  [4] History and Undo (Stack)" << RESET << endl;
        cout << WHITE << "  [5] Student Support Queue (Queue)" << RESET << endl;
        cout << WHITE << "  [6] Advanced Directory Search (QuickSort & Binary Search)" << RESET << endl;
        cout << WHITE << "  [7] Print Campus Map Adjacency List" << RESET << endl;
        cout << WHITE << "  [8] Exit System" << RESET << endl;
        printSeparator();
        cout << MAGENTA << "Select an option [1-8]: " << RESET;

        int choice;
        if (!(cin >> choice)) {
            if (cin.eof()) {
                break;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: { // Navigation Module
                clearScreen();
                cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << endl;
                cout << "║                      NAVIGATION MODULE                      ║" << endl;
                cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << endl;
                cout << "  [1] Find Shortest Path (Dijkstra)" << endl;
                cout << "  [2] Graph Traversal BFS (Breadth-First Search)" << endl;
                cout << "  [3] Graph Traversal DFS (Depth-First Search)" << endl;
                printSeparator();
                cout << MAGENTA << "Select sub-option [1-3]: " << RESET;
                
                int subChoice;
                cin >> subChoice;

                if (subChoice == 1) {
                    cout << "\nAvailable Locations:" << endl;
                    auto verts = campusMap.getVerticesList();
                    for (const auto& v : verts) {
                        cout << "  [" << v.first << "] " << v.second << endl;
                    }
                    printSeparator();
                    int src, dest;
                    cout << "Enter Source Location ID: ";
                    cin >> src;
                    cout << "Enter Destination Location ID: ";
                    cin >> dest;

                    if (!campusMap.hasVertex(src) || !campusMap.hasVertex(dest)) {
                        cout << RED << "\n[Error] Invalid location ID entered!" << endl;
                    } else {
                        vector<int> path;
                        double dist = 0.0;
                        if (campusMap.dijkstra(src, dest, path, dist)) {
                            cout << GREEN << BOLD << "\n[Path Found!]" << RESET << endl;
                            cout << "Total Route Distance: " << YELLOW << dist << " meters" << RESET << endl;
                            cout << "Directions: ";
                            for (size_t i = 0; i < path.size(); i++) {
                                cout << campusMap.getVertexName(path[i]);
                                if (i + 1 < path.size()) cout << " ➔ ";
                            }
                            cout << endl;

                            // Add to search history stack
                            string historyItem = "Route: " + campusMap.getVertexName(src) + " to " + campusMap.getVertexName(dest) + " (" + to_string((int)dist) + "m)";
                            searchHistory.push(historyItem);

                            simulateTravel(path);
                        } else {
                            cout << RED << "\n[Error] No path exists between the selected locations." << endl;
                        }
                    }
                } else if (subChoice == 2 || subChoice == 3) {
                    int startId;
                    cout << "Enter Starting Location ID: ";
                    cin >> startId;

                    if (!campusMap.hasVertex(startId)) {
                        cout << RED << "\n[Error] Location ID not found!" << endl;
                    } else {
                        vector<int> visited;
                        if (subChoice == 2) {
                            campusMap.bfs(startId, visited);
                            cout << GREEN << "\n[BFS Traversal Order]:\n  " << RESET;
                        } else {
                            campusMap.dfs(startId, visited);
                            cout << GREEN << "\n[DFS Traversal Order]:\n  " << RESET;
                        }
                        for (size_t i = 0; i < visited.size(); i++) {
                            cout << campusMap.getVertexName(visited[i]);
                            if (i + 1 < visited.size()) cout << " ➔ ";
                        }
                        cout << endl;
                    }
                }
                pressEnter();
                break;
            }

            case 2: { // Location Directory
                clearScreen();
                cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << endl;
                cout << "║                 LOCATION DIRECTORY (BST)                    ║" << endl;
                cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << endl;
                cout << "  [1] List All Locations (Alphabetical Order)" << endl;
                cout << "  [2] Add New Location" << endl;
                cout << "  [3] Delete Location" << endl;
                printSeparator();
                cout << MAGENTA << "Select sub-option [1-3]: " << RESET;

                int subChoice;
                cin >> subChoice;
                cin.ignore(); // Consume newline

                if (subChoice == 1) {
                    cout << GREEN << "\nAlphabetical Campus Directory (In-Order Traversal):" << RESET << endl;
                    locationDirectory.inorderTraversal(printLocationBrief);
                    cout << "Total Locations: " << locationDirectory.size() << endl;
                } else if (subChoice == 2) {
                    Location newLoc;
                    cout << "Enter Location Name: ";
                    getline(cin, newLoc.name);
                    cout << "Enter Category (Academic, Cafeteria, Sports, Admin, Housing, etc.): ";
                    getline(cin, newLoc.category);
                    cout << "Enter Short Description: ";
                    getline(cin, newLoc.description);
                    cout << "Enter Unique ID for Graph Vertex: ";
                    cin >> newLoc.id;

                    if (campusMap.hasVertex(newLoc.id)) {
                        cout << RED << "\n[Error] ID already in use on campus map!" << endl;
                    } else {
                        // Insert into BST, Graph, and HashTable
                        locationDirectory.insert(newLoc);
                        campusMap.addVertex(newLoc.id, newLoc.name);
                        detailsLookup.insert(newLoc.name, newLoc.description);

                        // Connect to Admin Block (Default connection) by default
                        campusMap.addEdge(newLoc.id, 2, 200.0);

                        cout << GREEN << "\n[✓] Location added successfully!" << RESET << endl;
                        cout << "Note: Automatically linked to Admin Block (distance 200m) for routing." << endl;
                        saveData();
                    }
                } else if (subChoice == 3) {
                    string targetName;
                    cout << "Enter exact Location Name to delete: ";
                    getline(cin, targetName);

                    Location l;
                    if (locationDirectory.search(targetName, l)) {
                        locationDirectory.remove(targetName);
                        campusMap.removeVertex(l.id);
                        detailsLookup.remove(targetName);
                        cout << GREEN << "\n[✓] Location \"" << targetName << "\" successfully removed!" << RESET << endl;
                        saveData();
                    } else {
                        cout << RED << "\n[Error] Location not found in database!" << endl;
                    }
                }
                pressEnter();
                break;
            }

            case 3: { // Fast Details Lookup
                clearScreen();
                cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << endl;
                cout << "║                 FAST DETAILS LOOKUP (HASH TABLE)            ║" << endl;
                cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << endl;
                cin.ignore();
                string searchKey;
                cout << "Enter Location Name (e.g., Computer Science Dept): ";
                getline(cin, searchKey);

                string details = detailsLookup.search(searchKey);
                if (!details.empty()) {
                    cout << GREEN << "\n[Match Found in Hash Table!]" << RESET << endl;
                    cout << BOLD << "Location: " << RESET << searchKey << endl;
                    cout << BOLD << "Details & Metadata: " << RESET << details << endl;
                    
                    searchHistory.push("Lookup: " + searchKey);
                } else {
                    cout << RED << "\n[Error] No detailed metadata found for this location name." << endl;
                    cout << "Make sure to match the exact spelling and case (e.g., \"Central Library\")." << endl;
                }
                pressEnter();
                break;
            }

            case 4: { // Search and Request History
                clearScreen();
                cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << endl;
                cout << "║                SEARCH & LOOKUP HISTORY (STACK)              ║" << endl;
                cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << endl;
                cout << "  [1] View History (Peek/Display)" << endl;
                cout << "  [2] Undo Last Action (Pop)" << endl;
                cout << "  [3] Clear All History" << endl;
                printSeparator();
                cout << MAGENTA << "Select sub-option [1-3]: " << RESET;

                int subChoice;
                cin >> subChoice;

                if (subChoice == 1) {
                    if (searchHistory.isEmpty()) {
                        cout << YELLOW << "\nHistory is currently empty." << RESET << endl;
                    } else {
                        cout << GREEN << "\nMost Recent Action: " << RESET << searchHistory.peek() << endl;
                        cout << "Total items in stack: " << searchHistory.size() << endl;
                    }
                } else if (subChoice == 2) {
                    if (searchHistory.isEmpty()) {
                        cout << RED << "\n[Error] History stack underflow! No actions to undo." << endl;
                    } else {
                        string popped = searchHistory.pop();
                        cout << GREEN << "\n[✓] Undone last action: " << RESET << popped << endl;
                    }
                } else if (subChoice == 3) {
                    searchHistory.clear();
                    cout << GREEN << "\n[✓] Search history cleared." << RESET << endl;
                }
                pressEnter();
                break;
            }

            case 5: { // Student Support Queue
                clearScreen();
                cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << endl;
                cout << "║                CAMPUS SUPPORT TICKETS (QUEUE)               ║" << endl;
                cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << endl;
                cout << "  [1] File a New Support Request" << endl;
                cout << "  [2] Process Next Request (Admin Mode)" << endl;
                cout << "  [3] View Current Queue Size" << endl;
                printSeparator();
                cout << MAGENTA << "Select sub-option [1-3]: " << RESET;

                int subChoice;
                cin >> subChoice;
                cin.ignore();

                if (subChoice == 1) {
                    Request req;
                    req.id = ++requestCounter;
                    cout << "Enter your Name: ";
                    getline(cin, req.studentName);
                    cout << "Enter issue details: ";
                    getline(cin, req.issueDescription);
                    cout << "Enter urgency (Low/Medium/High): ";
                    getline(cin, req.urgency);

                    supportQueue.enqueue(req);
                    cout << GREEN << "\n[✓] Request submitted successfully! Ticket ID: " << req.id << RESET << endl;
                } else if (subChoice == 2) {
                    Request nextReq;
                    if (supportQueue.dequeue(nextReq)) {
                        cout << GREEN << "\n[Processing Support Ticket]" << RESET << endl;
                        cout << BOLD << "Ticket ID: " << RESET << nextReq.id << endl;
                        cout << BOLD << "Student Name: " << RESET << nextReq.studentName << endl;
                        cout << BOLD << "Issue: " << RESET << nextReq.issueDescription << endl;
                        cout << BOLD << "Urgency: " << RESET << nextReq.urgency << endl;
                        cout << GREEN << "[✓] Ticket processed and closed." << RESET << endl;
                    } else {
                        cout << YELLOW << "\nNo pending support tickets in queue." << RESET << endl;
                    }
                } else if (subChoice == 3) {
                    cout << GREEN << "\nTotal Pending Tickets: " << RESET << supportQueue.size() << endl;
                }
                pressEnter();
                break;
            }

            case 6: { // Advanced Search & Sorting Module
                clearScreen();
                cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << endl;
                cout << "║                 SORTING & SEARCHING MODULE                  ║" << endl;
                cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << endl;
                cout << "  [1] Sort Locations Alphabetically (QuickSort)" << endl;
                cout << "  [2] Search Location Details (Binary Search)" << endl;
                printSeparator();
                cout << MAGENTA << "Select sub-option [1-2]: " << RESET;

                int subChoice;
                cin >> subChoice;
                cin.ignore();

                // Extract locations from BST
                vector<Location> locList = locationDirectory.getAllLocationsSorted();

                if (subChoice == 1) {
                    cout << YELLOW << "\nScrambling data order before sort to demonstrate QuickSort..." << RESET << endl;
                    // Scramble vector manually (simple reverse)
                    reverse(locList.begin(), locList.end());
                    
                    cout << "Before Sort (Reversed BST Output):" << endl;
                    for (const auto& loc : locList) {
                        cout << "  - " << loc.name << " (" << loc.category << ")" << endl;
                    }

                    // Apply QuickSort
                    Sorting::quickSortByName(locList, 0, (int)locList.size() - 1);

                    cout << GREEN << "\nAfter QuickSort (A-Z):" << RESET << endl;
                    for (const auto& loc : locList) {
                        cout << "  - " << loc.name << " (" << loc.category << ")" << endl;
                    }
                } else if (subChoice == 2) {
                    // QuickSort first to make sure it's sorted for Binary Search
                    Sorting::quickSortByName(locList, 0, (int)locList.size() - 1);

                    string targetName;
                    cout << "Enter Location Name to search via Binary Search: ";
                    getline(cin, targetName);

                    int idx = Sorting::binarySearchByName(locList, targetName);
                    if (idx != -1) {
                        cout << GREEN << "\n[Match Found via Binary Search!]" << RESET << endl;
                        cout << BOLD << "Name: " << RESET << locList[idx].name << endl;
                        cout << BOLD << "Category: " << RESET << locList[idx].category << endl;
                        cout << BOLD << "Description: " << RESET << locList[idx].description << endl;
                        cout << BOLD << "Map ID: " << RESET << locList[idx].id << endl;
                    } else {
                        cout << RED << "\n[Error] Location not found!" << endl;
                    }
                }
                pressEnter();
                break;
            }

            case 7: { // Display Map
                clearScreen();
                cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << endl;
                cout << "║                 CAMPUS MAP ADJACENCY LIST                   ║" << endl;
                cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << endl;
                campusMap.printGraph();
                pressEnter();
                break;
            }

            case 8: // Exit
                clearScreen();
                cout << GREEN << BOLD << "\nThank you for using the Smart Campus Management System. Exiting...\n" << RESET << endl;
                return 0;

            default:
                cout << RED << "\n[Error] Invalid choice! Please select 1-8." << RESET << endl;
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    }

    return 0;
}
