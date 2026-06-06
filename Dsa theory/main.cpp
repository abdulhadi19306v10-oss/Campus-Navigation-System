#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>

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
    std::cout << WHITE << "══════════════════════════════════════════════════════════════" << RESET << std::endl;
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
void simulateTravel(const std::vector<int>& path) {
    std::cout << YELLOW << "\n[!] Starting travel simulation..." << RESET << std::endl;
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << GREEN << " -> " << campusMap.getVertexName(path[i]) << RESET;
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << GREEN << "\n[✓] Arrived safely at your destination!" << RESET << std::endl;
}

// Callback for BST traversal printing
void printLocationBrief(const Location& loc) {
    std::cout << "  • " << CYAN << std::left << std::setw(25) << loc.name << RESET
              << MAGENTA << std::setw(15) << loc.category << RESET
              << " (ID: " << loc.id << ")" << std::endl;
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

// Press Enter to Continue prompt
void pressEnter() {
    std::cout << WHITE << "\nPress Enter to return to menu...";
    std::cin.ignore();
    std::cin.get();
}

int main() {
    enableVirtualTerminalColors();
    initializeCampusData();

    while (true) {
        clearScreen();
        std::cout << CYAN << BOLD;
        std::cout << "╔═════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║          SMART CAMPUS MANAGEMENT SYSTEM (DSA PROJECT)       ║" << std::endl;
        std::cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << std::endl;
        std::cout << WHITE << "  [1] Navigation Module (Shortest Path & BFS/DFS)" << RESET << std::endl;
        std::cout << WHITE << "  [2] Location Directory (BST In-Order list & Add/Delete)" << RESET << std::endl;
        std::cout << WHITE << "  [3] Fast Details Lookup (HashTable Metadata)" << RESET << std::endl;
        std::cout << WHITE << "  [4] History and Undo (Stack)" << RESET << std::endl;
        std::cout << WHITE << "  [5] Student Support Queue (Queue)" << RESET << std::endl;
        std::cout << WHITE << "  [6] Advanced Directory Search (QuickSort & Binary Search)" << RESET << std::endl;
        std::cout << WHITE << "  [7] Print Campus Map Adjacency List" << RESET << std::endl;
        std::cout << WHITE << "  [8] Exit System" << RESET << std::endl;
        printSeparator();
        std::cout << MAGENTA << "Select an option [1-8]: " << RESET;

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: { // Navigation Module
                clearScreen();
                std::cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║                      NAVIGATION MODULE                      ║" << std::endl;
                std::cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << std::endl;
                std::cout << "  [1] Find Shortest Path (Dijkstra)" << std::endl;
                std::cout << "  [2] Graph Traversal BFS (Breadth-First Search)" << std::endl;
                std::cout << "  [3] Graph Traversal DFS (Depth-First Search)" << std::endl;
                printSeparator();
                std::cout << MAGENTA << "Select sub-option [1-3]: " << RESET;
                
                int subChoice;
                std::cin >> subChoice;

                if (subChoice == 1) {
                    std::cout << "\nAvailable Locations:" << std::endl;
                    auto verts = campusMap.getVerticesList();
                    for (const auto& v : verts) {
                        std::cout << "  [" << v.first << "] " << v.second << std::endl;
                    }
                    printSeparator();
                    int src, dest;
                    std::cout << "Enter Source Location ID: ";
                    std::cin >> src;
                    std::cout << "Enter Destination Location ID: ";
                    std::cin >> dest;

                    if (!campusMap.hasVertex(src) || !campusMap.hasVertex(dest)) {
                        std::cout << RED << "\n[Error] Invalid location ID entered!" << RESET << std::endl;
                    } else {
                        std::vector<int> path;
                        double dist = 0.0;
                        if (campusMap.dijkstra(src, dest, path, dist)) {
                            std::cout << GREEN << BOLD << "\n[Path Found!]" << RESET << std::endl;
                            std::cout << "Total Route Distance: " << YELLOW << dist << " meters" << RESET << std::endl;
                            std::cout << "Directions: ";
                            for (size_t i = 0; i < path.size(); i++) {
                                std::cout << campusMap.getVertexName(path[i]);
                                if (i + 1 < path.size()) std::cout << " ➔ ";
                            }
                            std::cout << std::endl;

                            // Add to search history stack
                            std::string historyItem = "Route: " + campusMap.getVertexName(src) + " to " + campusMap.getVertexName(dest) + " (" + std::to_string((int)dist) + "m)";
                            searchHistory.push(historyItem);

                            simulateTravel(path);
                        } else {
                            std::cout << RED << "\n[Error] No path exists between the selected locations." << RESET << std::endl;
                        }
                    }
                } else if (subChoice == 2 || subChoice == 3) {
                    int startId;
                    std::cout << "Enter Starting Location ID: ";
                    std::cin >> startId;

                    if (!campusMap.hasVertex(startId)) {
                        std::cout << RED << "\n[Error] Location ID not found!" << RESET << std::endl;
                    } else {
                        std::vector<int> visited;
                        if (subChoice == 2) {
                            campusMap.bfs(startId, visited);
                            std::cout << GREEN << "\n[BFS Traversal Order]:\n  " << RESET;
                        } else {
                            campusMap.dfs(startId, visited);
                            std::cout << GREEN << "\n[DFS Traversal Order]:\n  " << RESET;
                        }
                        for (size_t i = 0; i < visited.size(); i++) {
                            std::cout << campusMap.getVertexName(visited[i]);
                            if (i + 1 < visited.size()) std::cout << " ➔ ";
                        }
                        std::cout << std::endl;
                    }
                }
                pressEnter();
                break;
            }

            case 2: { // Location Directory
                clearScreen();
                std::cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║                 LOCATION DIRECTORY (BST)                    ║" << std::endl;
                std::cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << std::endl;
                std::cout << "  [1] List All Locations (Alphabetical Order)" << std::endl;
                std::cout << "  [2] Add New Location" << std::endl;
                std::cout << "  [3] Delete Location" << std::endl;
                printSeparator();
                std::cout << MAGENTA << "Select sub-option [1-3]: " << RESET;

                int subChoice;
                std::cin >> subChoice;
                std::cin.ignore(); // Consume newline

                if (subChoice == 1) {
                    std::cout << GREEN << "\nAlphabetical Campus Directory (In-Order Traversal):" << RESET << std::endl;
                    locationDirectory.inorderTraversal(printLocationBrief);
                    std::cout << "Total Locations: " << locationDirectory.size() << std::endl;
                } else if (subChoice == 2) {
                    Location newLoc;
                    std::cout << "Enter Location Name: ";
                    std::getline(std::cin, newLoc.name);
                    std::cout << "Enter Category (Academic, Cafeteria, Sports, Admin, Housing, etc.): ";
                    std::getline(std::cin, newLoc.category);
                    std::cout << "Enter Short Description: ";
                    std::getline(std::cin, newLoc.description);
                    std::cout << "Enter Unique ID for Graph Vertex: ";
                    std::cin >> newLoc.id;

                    if (campusMap.hasVertex(newLoc.id)) {
                        std::cout << RED << "\n[Error] ID already in use on campus map!" << RESET << std::endl;
                    } else {
                        // Insert into BST, Graph, and HashTable
                        locationDirectory.insert(newLoc);
                        campusMap.addVertex(newLoc.id, newLoc.name);
                        detailsLookup.insert(newLoc.name, newLoc.description);

                        // Connect to Admin Block (Default connection) by default
                        campusMap.addEdge(newLoc.id, 2, 200.0);

                        std::cout << GREEN << "\n[✓] Location added successfully!" << RESET << std::endl;
                        std::cout << "Note: Automatically linked to Admin Block (distance 200m) for routing." << std::endl;
                    }
                } else if (subChoice == 3) {
                    std::string targetName;
                    std::cout << "Enter exact Location Name to delete: ";
                    std::getline(std::cin, targetName);

                    Location l;
                    if (locationDirectory.search(targetName, l)) {
                        locationDirectory.remove(targetName);
                        campusMap.removeVertex(l.id);
                        detailsLookup.remove(targetName);
                        std::cout << GREEN << "\n[✓] Location \"" << targetName << "\" successfully removed!" << RESET << std::endl;
                    } else {
                        std::cout << RED << "\n[Error] Location not found in database!" << RESET << std::endl;
                    }
                }
                pressEnter();
                break;
            }

            case 3: { // Fast Details Lookup
                clearScreen();
                std::cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║                 FAST DETAILS LOOKUP (HASH TABLE)            ║" << std::endl;
                std::cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << std::endl;
                std::cin.ignore();
                std::string searchKey;
                std::cout << "Enter Location Name (e.g., Computer Science Dept): ";
                std::getline(std::cin, searchKey);

                std::string details = detailsLookup.search(searchKey);
                if (!details.empty()) {
                    std::cout << GREEN << "\n[Match Found in Hash Table!]" << RESET << std::endl;
                    std::cout << BOLD << "Location: " << RESET << searchKey << std::endl;
                    std::cout << BOLD << "Details & Metadata: " << RESET << details << std::endl;
                    
                    searchHistory.push("Lookup: " + searchKey);
                } else {
                    std::cout << RED << "\n[Error] No detailed metadata found for this location name." << RESET << std::endl;
                    std::cout << "Make sure to match the exact spelling and case (e.g., \"Central Library\")." << std::endl;
                }
                pressEnter();
                break;
            }

            case 4: { // Search and Request History
                clearScreen();
                std::cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║                SEARCH & LOOKUP HISTORY (STACK)              ║" << std::endl;
                std::cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << std::endl;
                std::cout << "  [1] View History (Peek/Display)" << std::endl;
                std::cout << "  [2] Undo Last Action (Pop)" << std::endl;
                std::cout << "  [3] Clear All History" << std::endl;
                printSeparator();
                std::cout << MAGENTA << "Select sub-option [1-3]: " << RESET;

                int subChoice;
                std::cin >> subChoice;

                if (subChoice == 1) {
                    if (searchHistory.isEmpty()) {
                        std::cout << YELLOW << "\nHistory is currently empty." << RESET << std::endl;
                    } else {
                        std::cout << GREEN << "\nMost Recent Action: " << RESET << searchHistory.peek() << std::endl;
                        std::cout << "Total items in stack: " << searchHistory.size() << std::endl;
                    }
                } else if (subChoice == 2) {
                    if (searchHistory.isEmpty()) {
                        std::cout << RED << "\n[Error] History stack underflow! No actions to undo." << RESET << std::endl;
                    } else {
                        std::string popped = searchHistory.pop();
                        std::cout << GREEN << "\n[✓] Undone last action: " << RESET << popped << std::endl;
                    }
                } else if (subChoice == 3) {
                    searchHistory.clear();
                    std::cout << GREEN << "\n[✓] Search history cleared." << RESET << std::endl;
                }
                pressEnter();
                break;
            }

            case 5: { // Student Support Queue
                clearScreen();
                std::cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║                CAMPUS SUPPORT TICKETS (QUEUE)               ║" << std::endl;
                std::cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << std::endl;
                std::cout << "  [1] File a New Support Request" << std::endl;
                std::cout << "  [2] Process Next Request (Admin Mode)" << std::endl;
                std::cout << "  [3] View Current Queue Size" << std::endl;
                printSeparator();
                std::cout << MAGENTA << "Select sub-option [1-3]: " << RESET;

                int subChoice;
                std::cin >> subChoice;
                std::cin.ignore();

                if (subChoice == 1) {
                    Request req;
                    req.id = ++requestCounter;
                    std::cout << "Enter your Name: ";
                    std::getline(std::cin, req.studentName);
                    std::cout << "Enter issue details: ";
                    std::getline(std::cin, req.issueDescription);
                    std::cout << "Enter urgency (Low/Medium/High): ";
                    std::getline(std::cin, req.urgency);

                    supportQueue.enqueue(req);
                    std::cout << GREEN << "\n[✓] Request submitted successfully! Ticket ID: " << req.id << RESET << std::endl;
                } else if (subChoice == 2) {
                    Request nextReq;
                    if (supportQueue.dequeue(nextReq)) {
                        std::cout << GREEN << "\n[Processing Support Ticket]" << RESET << std::endl;
                        std::cout << BOLD << "Ticket ID: " << RESET << nextReq.id << std::endl;
                        std::cout << BOLD << "Student Name: " << RESET << nextReq.studentName << std::endl;
                        std::cout << BOLD << "Issue: " << RESET << nextReq.issueDescription << std::endl;
                        std::cout << BOLD << "Urgency: " << RESET << nextReq.urgency << std::endl;
                        std::cout << GREEN << "[✓] Ticket processed and closed." << RESET << std::endl;
                    } else {
                        std::cout << YELLOW << "\nNo pending support tickets in queue." << RESET << std::endl;
                    }
                } else if (subChoice == 3) {
                    std::cout << GREEN << "\nTotal Pending Tickets: " << RESET << supportQueue.size() << std::endl;
                }
                pressEnter();
                break;
            }

            case 6: { // Advanced Search & Sorting Module
                clearScreen();
                std::cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║                 SORTING & SEARCHING MODULE                  ║" << std::endl;
                std::cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << std::endl;
                std::cout << "  [1] Sort Locations Alphabetically (QuickSort)" << std::endl;
                std::cout << "  [2] Search Location Details (Binary Search)" << std::endl;
                printSeparator();
                std::cout << MAGENTA << "Select sub-option [1-2]: " << RESET;

                int subChoice;
                std::cin >> subChoice;
                std::cin.ignore();

                // Extract locations from BST
                std::vector<Location> locList = locationDirectory.getAllLocationsSorted();

                if (subChoice == 1) {
                    std::cout << YELLOW << "\nScrambling data order before sort to demonstrate QuickSort..." << RESET << std::endl;
                    // Scramble vector manually (simple reverse)
                    std::reverse(locList.begin(), locList.end());
                    
                    std::cout << "Before Sort (Reversed BST Output):" << std::endl;
                    for (const auto& loc : locList) {
                        std::cout << "  - " << loc.name << " (" << loc.category << ")" << std::endl;
                    }

                    // Apply QuickSort
                    Sorting::quickSortByName(locList, 0, (int)locList.size() - 1);

                    std::cout << GREEN << "\nAfter QuickSort (A-Z):" << RESET << std::endl;
                    for (const auto& loc : locList) {
                        std::cout << "  - " << loc.name << " (" << loc.category << ")" << std::endl;
                    }
                } else if (subChoice == 2) {
                    // QuickSort first to make sure it's sorted for Binary Search
                    Sorting::quickSortByName(locList, 0, (int)locList.size() - 1);

                    std::string targetName;
                    std::cout << "Enter Location Name to search via Binary Search: ";
                    std::getline(std::cin, targetName);

                    int idx = Sorting::binarySearchByName(locList, targetName);
                    if (idx != -1) {
                        std::cout << GREEN << "\n[Match Found via Binary Search!]" << RESET << std::endl;
                        std::cout << BOLD << "Name: " << RESET << locList[idx].name << std::endl;
                        std::cout << BOLD << "Category: " << RESET << locList[idx].category << std::endl;
                        std::cout << BOLD << "Description: " << RESET << locList[idx].description << std::endl;
                        std::cout << BOLD << "Map ID: " << RESET << locList[idx].id << std::endl;
                    } else {
                        std::cout << RED << "\n[Error] Location not found!" << RESET << std::endl;
                    }
                }
                pressEnter();
                break;
            }

            case 7: { // Display Map
                clearScreen();
                std::cout << CYAN << BOLD << "╔═════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║                 CAMPUS MAP ADJACENCY LIST                   ║" << std::endl;
                std::cout << "╚═════════════════════════════════════════════════════════════╝" << RESET << std::endl;
                campusMap.printGraph();
                pressEnter();
                break;
            }

            case 8: // Exit
                clearScreen();
                std::cout << GREEN << BOLD << "\nThank you for using the Smart Campus Management System. Exiting...\n" << RESET << std::endl;
                return 0;

            default:
                std::cout << RED << "\n[Error] Invalid choice! Please select 1-8." << RESET << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
        }
    }

    return 0;
}
