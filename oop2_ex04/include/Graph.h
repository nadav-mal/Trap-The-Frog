#pragma once
#include <queue>
#include <vector>
#include <iostream>
using namespace std;
#include "Frog.h"

# define INF 0x3f3f3f3f

// This class represents a directed graph using adjacency list representation.
// Class to find Dijkstra's shortest path using STL set.
class Graph
{
public:
    Graph(int V);  // C-tor.

    // Graph edges management.
    // There's a difference between even row edges to odd row edges.
    void handleEdges(int i, int j, bool remove);
    void removeEdge(int u, int v);
    void remove(int u, int v);
    void restore(int u, int v);
    void addEdge(int u, int v, int w);
    void checkEdges(unsigned __int64 i, int& min, int& min_index, const vector<int> dist) const;
    bool inGraph(const int index) const { return (index < BOARD_SIZE) && (index >= 0); }
    bool isEven(const int row) const { return (row % 2 == 0); }

    // Shortest path for the frog to win (one step at a time).
    int shortestPath(int src);
    int findStep(const vector<int> dist, const vector<int> parent) const;

private:
    int V; // Number of vertices.
    vector<pair<int, int>>* adj; // Paired vertex and weight.
    void initEdges(); // Initiates the edges.
};

