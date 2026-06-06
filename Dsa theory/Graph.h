#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

struct Edge {
    int destId;
    double weight;
    Edge* next;
    Edge(int d, double w) : destId(d), weight(w), next(nullptr) {}
};

struct VertexNode {
    int id;
    std::string name;
    Edge* edgeHead;
    VertexNode* next;
    VertexNode(int i, const std::string& n) : id(i), name(n), edgeHead(nullptr), next(nullptr) {}
};

class Graph {
private:
    VertexNode* verticesHead;
    int vertexCount;

    VertexNode* findVertex(int id) const;
    void clearEdges(Edge* head);

public:
    Graph();
    ~Graph();

    void addVertex(int id, const std::string& name);
    void addEdge(int srcId, int destId, double weight);
    bool removeEdge(int srcId, int destId);
    bool removeVertex(int id);
    
    bool hasVertex(int id) const;
    std::string getVertexName(int id) const;
    int getVertexId(const std::string& name) const;
    int getVertexCount() const;
    std::vector<std::pair<int, std::string>> getVerticesList() const;

    bool dijkstra(int srcId, int destId, std::vector<int>& path, double& totalDistance) const;
    void bfs(int startId, std::vector<int>& visitedOrder) const;
    void dfs(int startId, std::vector<int>& visitedOrder) const;
    void dfsHelper(int currId, std::vector<int>& visitedOrder, std::vector<bool>& visited, const std::vector<int>& allIds) const;
    
    void printGraph() const;
    void clear();
};

#endif // GRAPH_H
