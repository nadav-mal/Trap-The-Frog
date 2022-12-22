#include "Graph.h"

// Constructor.
Graph::Graph(int V)
{
    this->V = V;
    // Allocates memory for adjacency list.
    adj = new vector<pair<int, int>>[V];
    this->initEdges();
}

// Initiates the edges of the graph.
void Graph::initEdges()
{
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            this->handleEdges(i, j, false);
}

// Adds an edge.
void Graph::addEdge(int u, int v, int w)
{
    this->adj[u].push_back(make_pair(v, w));
}

// Removes an edge (in both directions).
void Graph::removeEdge(int u, int v)
{
    this->remove(u, v);
    this->remove(v, u);
}

// Removes an edge from the shortest path by setting its weight to INF.
void Graph::remove(int u, int v)
{
    int index = 0;
    while (adj[u][index].first != v)
        index++;

    adj[u][index].second = INF;
}

// Restores an edge to the shortest path by setting its weight to the default weight (1).
void Graph::restore(int u, int v) 
{
    int index = 0;
    while (adj[u][index].first != v)
        index++;

    adj[u][index].second = DefaultWeight;
}

// Prints shortest paths from src to all other vertices
int Graph::shortestPath(int src)
{
    // Create a priority queue to store vertices that
    // are being preprocessed.
    priority_queue< pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>> > pq;

    // Creates a vector for distances and initialize all
    // distances as infinite (INF)
    vector<int> dist(V, INF);

    // Creates a vector for path information
    vector<int> parent(V, 0);
    parent[src] = -1;  //soruce vertex doesnt have a parent

    // Inserts source itself in priority queue and initialize
    // its distance as 0.
    pq.push(make_pair(0, src));
    dist[src] = 0;

    /* Looping till priority queue becomes empty (or all
    distances are not finalized). */
    while (!pq.empty())
    {
        // The first vertex in a pair is the minimum distance
        // vertex, extract it from priority queue.
        // The vertex' label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be the first item in pair). 
        int u = pq.top().second;
        pq.pop();
        
        // Gets all adjacent of u. 
        for (pair<int, int> x : adj[u])
        {
            // Gets the vertex index and weight of current adjacent of u.
            int v = x.first;
            int weight = x.second;

            // If there's a shorter path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updates distance of v.
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
                parent[v] = u;
            }
        }
    }

    // Returns the next step of the frog.
    return findStep(dist, parent);
}

// Removes/adds edges to the graph.
void Graph::handleEdges(int row, int col, bool remove)
{
    unsigned int convertFormula = col + (row * BOARD_SIZE);
    sf::Vector2i neighborLoc;
    for (int index = 0; index < MAX_EDGES; index++)
    {
        if (isEven(row))
            neighborLoc = sf::Vector2i((row + evenRowEdges[index].x), (col + evenRowEdges[index].y));
        else
            neighborLoc = sf::Vector2i((row + oddRowEdges[index].x), (col + oddRowEdges[index].y));

        if (this->inGraph(neighborLoc.x) && this->inGraph(neighborLoc.y))
        {
            if (remove)
                this->removeEdge(convertFormula, (neighborLoc.y + (neighborLoc.x * BOARD_SIZE)));
            else
                this->addEdge(convertFormula, (neighborLoc.y + (neighborLoc.x * BOARD_SIZE)), DefaultWeight);
        }
    }
}

// Checks which of the edge-tiles of the board is the closest.
void Graph::checkEdges(unsigned __int64 i, int& min, int& min_index, const vector<int> dist) const
{
    if (dist[(i * sqrt(V))] < min) // Left edge
    {
        min = dist[(i * sqrt(V))];
        min_index = (i * sqrt(V));
    }

    if (dist[(sqrt(V) * (i + 1)) - 1] < min) // Right edge
    {
        min = dist[(sqrt(V) * (i + 1)) - 1];
        min_index = (sqrt(V) * (i + 1)) - 1;
    }

    if (dist[i] < min) // Upper edge
    {
        min = dist[i];
        min_index = i;
    }

    if (dist[(sqrt(V) - 1) * sqrt(V) + i] < min) // Down edge
    {
        min = dist[(sqrt(V) - 1) * sqrt(V) + i];
        min_index = (sqrt(V) - 1) * sqrt(V) + i;
    }
}

// Finds and returns the next step of the frog.
int Graph::findStep(const vector<int> dist, const vector<int> parent) const
{
    int min = INF; // Assuming the first distance is the shortest.
    int min_index = 0;

    for (unsigned __int64 index = 0; index < sqrt(V); index++)
        this->checkEdges(index, min, min_index, dist);

    // No existing path to escape.
    if (min == INF)
        return -1;

    while (parent[parent[min_index]] != -1)
        min_index = parent[min_index];

    return min_index;
}
