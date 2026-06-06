#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

using namespace std;

struct Edge {
    int destId;
    double weight;
    Edge* next;
    Edge(int d, double w) : destId(d), weight(w), next(nullptr) {}
};

struct VertexNode {
    int id;
    string name;
    Edge* edgeHead;
    VertexNode* next;
    VertexNode(int i, const string& n) : id(i), name(n), edgeHead(nullptr), next(nullptr) {}
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

    void addVertex(int id, const string& name);
    void addEdge(int srcId, int destId, double weight);
    bool removeEdge(int srcId, int destId);
    bool removeVertex(int id);
    
    bool hasVertex(int id) const;
    string getVertexName(int id) const;
    int getVertexId(const string& name) const;
    int getVertexCount() const;
    vector<pair<int, string>> getVerticesList() const;
    vector<pair<pair<int, int>, double>> getEdgesList() const;

    bool dijkstra(int srcId, int destId, vector<int>& path, double& totalDistance) const;
    void bfs(int startId, vector<int>& visitedOrder) const;
    void dfs(int startId, vector<int>& visitedOrder) const;
    void dfsHelper(int currId, vector<int>& visitedOrder, vector<bool>& visited, const vector<int>& allIds) const;
    
    void printGraph() const;
    void clear();
};

#endif // GRAPH_H
