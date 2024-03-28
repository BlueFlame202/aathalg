#ifndef AATHALG_GRAPH_H
#define AATHALG_GRAPH_H

#include <stdio.h>
#include <vector>
#include <stack>

namespace aathalg 
{

/**
 * Defines an adjacency list based weighted graph representation, and also implements several well-known algorithms. Currently only supports double weights for graphs.
*/
class ListGraph 
{
private:
    uint32_t m_n; // number of vertices 
    std::vector<std::vector<std::pair<uint32_t, double_t> > > m_adjList; // adjacency list for edges

public:
    ListGraph(); // Default constructor, creates an empty graph
    ListGraph(uint32_t n); // Creates a graph with n vertices
    ListGraph(uint32_t n, std::vector<std::vector<std::pair<uint32_t, double_t> > > adjList); // creates a graph with n vertices using the adjacency list provided

    ~ListGraph(); // Destructor

    void addVertex(); // Increases the number of vertices by 1, adjusts m_AdjList
    void addEdge(uint32_t a, uint32_t b, double_t weight=1, bool directed=false); // Adds an edge from a to b
    void removeEdge(uint32_t a, uint32_t b, bool directed=false); // Removes any edge from a to b

    uint32_t vsize(); // get number of vertices
    int32_t getEdge(uint32_t a, uint32_t b); // get weight of an edge
    std::vector<std::pair<uint32_t, double_t> > getNeighbors(uint32_t a); // get the neighbors of a
}; // class ListGraph

// /**
//  * Defines an adjacency matrix based weighted graph representation, and also implements several well-known algorithms.
// */
// class MatrixGraph 
// {
// private:
//     uint32_t m_n; // number of vertices 
//     std::vector<std::vector<double_t> > m_adjList; // adjacency list for edges

// public:
//     MatrixGraph(); // Default constructor, creates an empty graph
//     MatrixGraph(uint32_t n); // Creates a graph with n vertices
//     MatrixGraph(uint32_t n, double_t ** adjList); // creates a graph with n vertices using the adjacency list provided

//     ~MatrixGraph(); // Destructor

//     void addVertex(); // Increases the number of vertices by 1, adjusts m_AdjList
//     void addEdge(uint32_t a, uint32_t b, bool directed=false); // Adds an edge from a to b
// }; // class MatrixGraph

// template<typename L1, typename L2> // L1, L2 intended to be some lambda accepting two uint32_ts, a node id and a counter value from the dfs
// void dfs(ListGraph g, L1 preVisit, L2 postVisit, uint32_t start=0, bool endFast=false); // depth first search, with lambda functions previsit and postvisit.

void dfs(ListGraph g, std::function<void(uint32_t, uint32_t)> preVisit, std::function<void(uint32_t, uint32_t)> postVisit, uint32_t start=0, bool endFast=false);

}

#endif