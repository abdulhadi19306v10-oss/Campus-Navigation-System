#include "Graph.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Graph::Graph() : verticesHead(nullptr), vertexCount(0) {}

Graph::~Graph() {
    clear();
}

VertexNode* Graph::findVertex(int id) const {
    VertexNode* curr = verticesHead;
    while (curr != nullptr) {
        if (curr->id == id) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

void Graph::clearEdges(Edge* head) {
    Edge* curr = head;
    while (curr != nullptr) {
        Edge* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

void Graph::addVertex(int id, const std::string& name) {
    if (findVertex(id) != nullptr) {
        return; // Vertex already exists
    }
    VertexNode* newVertex = new VertexNode(id, name);
    newVertex->next = verticesHead;
    verticesHead = newVertex;
    vertexCount++;
}

void Graph::addEdge(int srcId, int destId, double weight) {
    VertexNode* src = findVertex(srcId);
    VertexNode* dest = findVertex(destId);
    if (src == nullptr || dest == nullptr) {
        return; // Vertices must exist
    }

    // Add edge from src to dest (undirected map, so we add both directions)
    // Check if edge already exists to prevent duplicate paths
    Edge* curr = src->edgeHead;
    bool exists = false;
    while (curr != nullptr) {
        if (curr->destId == destId) {
            curr->weight = weight; // update weight
            exists = true;
            break;
        }
        curr = curr->next;
    }

    if (!exists) {
        Edge* newEdge1 = new Edge(destId, weight);
        newEdge1->next = src->edgeHead;
        src->edgeHead = newEdge1;

        Edge* newEdge2 = new Edge(srcId, weight);
        newEdge2->next = dest->edgeHead;
        dest->edgeHead = newEdge2;
    }
}

bool Graph::removeEdge(int srcId, int destId) {
    VertexNode* src = findVertex(srcId);
    VertexNode* dest = findVertex(destId);
    if (src == nullptr || dest == nullptr) {
        return false;
    }

    // Remove from src edge list
    Edge* prev = nullptr;
    Edge* curr = src->edgeHead;
    bool foundSrc = false;
    while (curr != nullptr) {
        if (curr->destId == destId) {
            if (prev == nullptr) {
                src->edgeHead = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            foundSrc = true;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    // Remove from dest edge list
    prev = nullptr;
    curr = dest->edgeHead;
    bool foundDest = false;
    while (curr != nullptr) {
        if (curr->destId == srcId) {
            if (prev == nullptr) {
                dest->edgeHead = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            foundDest = true;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    return foundSrc && foundDest;
}

bool Graph::removeVertex(int id) {
    VertexNode* target = findVertex(id);
    if (target == nullptr) {
        return false;
    }

    // First remove all edges connected to this vertex
    Edge* edge = target->edgeHead;
    while (edge != nullptr) {
        int neighborId = edge->destId;
        edge = edge->next;
        removeEdge(id, neighborId);
    }

    // Now remove target from the vertices list
    VertexNode* prev = nullptr;
    VertexNode* curr = verticesHead;
    while (curr != nullptr) {
        if (curr->id == id) {
            if (prev == nullptr) {
                verticesHead = curr->next;
            } else {
                prev->next = curr->next;
            }
            clearEdges(curr->edgeHead);
            delete curr;
            vertexCount--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }

    return false;
}

bool Graph::hasVertex(int id) const {
    return findVertex(id) != nullptr;
}

std::string Graph::getVertexName(int id) const {
    VertexNode* v = findVertex(id);
    return v != nullptr ? v->name : "";
}

int Graph::getVertexId(const std::string& name) const {
    VertexNode* curr = verticesHead;
    while (curr != nullptr) {
        if (curr->name == name) {
            return curr->id;
        }
        curr = curr->next;
    }
    return -1;
}

int Graph::getVertexCount() const {
    return vertexCount;
}

std::vector<std::pair<int, std::string>> Graph::getVerticesList() const {
    std::vector<std::pair<int, std::string>> list;
    VertexNode* curr = verticesHead;
    while (curr != nullptr) {
        list.push_back({curr->id, curr->name});
        curr = curr->next;
    }
    return list;
}

bool Graph::dijkstra(int srcId, int destId, std::vector<int>& path, double& totalDistance) const {
    path.clear();
    totalDistance = 0.0;

    if (findVertex(srcId) == nullptr || findVertex(destId) == nullptr) {
        return false;
    }

    // Get all vertex IDs
    std::vector<int> allIds;
    VertexNode* curr = verticesHead;
    while (curr != nullptr) {
        allIds.push_back(curr->id);
        curr = curr->next;
    }

    int n = (int)allIds.size();
    std::vector<double> dist(n, 1e9);
    std::vector<int> parent(n, -1);
    std::vector<bool> visited(n, false);

    // Helper lambda to find index by ID
    auto getIdx = [&](int id) {
        for (int i = 0; i < n; i++) {
            if (allIds[i] == id) return i;
        }
        return -1;
    };

    int srcIdx = getIdx(srcId);
    dist[srcIdx] = 0;

    for (int i = 0; i < n; i++) {
        // Find min distance unvisited vertex
        int minIdx = -1;
        double minDist = 1e9;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIdx = j;
            }
        }

        if (minIdx == -1 || dist[minIdx] >= 1e9) {
            break; // All remaining vertices are unreachable
        }

        visited[minIdx] = true;

        if (allIds[minIdx] == destId) {
            break; // Reached target
        }

        // Relax neighbors
        int currId = allIds[minIdx];
        VertexNode* vNode = findVertex(currId);
        if (vNode != nullptr) {
            Edge* edge = vNode->edgeHead;
            while (edge != nullptr) {
                int neighborIdx = getIdx(edge->destId);
                if (neighborIdx != -1 && !visited[neighborIdx]) {
                    double newDist = dist[minIdx] + edge->weight;
                    if (newDist < dist[neighborIdx]) {
                        dist[neighborIdx] = newDist;
                        parent[neighborIdx] = minIdx;
                    }
                }
                edge = edge->next;
            }
        }
    }

    int destIdx = getIdx(destId);
    if (dist[destIdx] >= 1e9) {
        return false; // No path found
    }

    totalDistance = dist[destIdx];

    // Reconstruct path
    int currIdx = destIdx;
    while (currIdx != -1) {
        path.push_back(allIds[currIdx]);
        currIdx = parent[currIdx];
    }
    std::reverse(path.begin(), path.end());
    return true;
}

void Graph::bfs(int startId, std::vector<int>& visitedOrder) const {
    visitedOrder.clear();
    if (findVertex(startId) == nullptr) {
        return;
    }

    // Get all vertex IDs to track visited status
    std::vector<int> allIds;
    VertexNode* curr = verticesHead;
    while (curr != nullptr) {
        allIds.push_back(curr->id);
        curr = curr->next;
    }

    int n = (int)allIds.size();
    std::vector<bool> visited(n, false);

    auto getIdx = [&](int id) {
        for (int i = 0; i < n; i++) {
            if (allIds[i] == id) return i;
        }
        return -1;
    };

    std::vector<int> queue;
    queue.push_back(startId);
    visited[getIdx(startId)] = true;

    int head = 0;
    while (head < (int)queue.size()) {
        int currId = queue[head++];
        visitedOrder.push_back(currId);

        VertexNode* vNode = findVertex(currId);
        if (vNode != nullptr) {
            Edge* edge = vNode->edgeHead;
            while (edge != nullptr) {
                int neighborIdx = getIdx(edge->destId);
                if (neighborIdx != -1 && !visited[neighborIdx]) {
                    visited[neighborIdx] = true;
                    queue.push_back(edge->destId);
                }
                edge = edge->next;
            }
        }
    }
}

void Graph::dfsHelper(int currId, std::vector<int>& visitedOrder, std::vector<bool>& visited, const std::vector<int>& allIds) const {
    auto getIdx = [&](int id) {
        for (int i = 0; i < (int)allIds.size(); i++) {
            if (allIds[i] == id) return i;
        }
        return -1;
    };

    int idx = getIdx(currId);
    if (idx == -1 || visited[idx]) {
        return;
    }

    visited[idx] = true;
    visitedOrder.push_back(currId);

    VertexNode* vNode = findVertex(currId);
    if (vNode != nullptr) {
        Edge* edge = vNode->edgeHead;
        while (edge != nullptr) {
            int neighborIdx = getIdx(edge->destId);
            if (neighborIdx != -1 && !visited[neighborIdx]) {
                dfsHelper(edge->destId, visitedOrder, visited, allIds);
            }
            edge = edge->next;
        }
    }
}

void Graph::dfs(int startId, std::vector<int>& visitedOrder) const {
    visitedOrder.clear();
    if (findVertex(startId) == nullptr) {
        return;
    }

    std::vector<int> allIds;
    VertexNode* curr = verticesHead;
    while (curr != nullptr) {
        allIds.push_back(curr->id);
        curr = curr->next;
    }

    int n = (int)allIds.size();
    std::vector<bool> visited(n, false);

    dfsHelper(startId, visitedOrder, visited, allIds);
}

void Graph::printGraph() const {
    VertexNode* curr = verticesHead;
    while (curr != nullptr) {
        std::cout << curr->name << " (ID: " << curr->id << ") -> ";
        Edge* edge = curr->edgeHead;
        while (edge != nullptr) {
            std::cout << getVertexName(edge->destId) << " (" << edge->weight << "m)";
            if (edge->next != nullptr) std::cout << ", ";
            edge = edge->next;
        }
        std::cout << std::endl;
        curr = curr->next;
    }
}

void Graph::clear() {
    VertexNode* curr = verticesHead;
    while (curr != nullptr) {
        VertexNode* temp = curr;
        curr = curr->next;
        clearEdges(temp->edgeHead);
        delete temp;
    }
    verticesHead = nullptr;
    vertexCount = 0;
}
