#ifndef ALGAE_GRAPH_H
#define ALGAE_GRAPH_H

#include <stdio.h>
#include <vector>
#include <stack>

namespace algae 
{

/**
 * Defines an adjacency list based weighted graph representation, and also implements several well-known algorithms. Currently only supports double weights for graphs.
*/
class list_graph 
{
private:
    size_t m_n; // number of vertices 
    std::vector<std::vector<std::pair<size_t, double_t> > > m_adj_list; // adjacency list for edges

public:
    list_graph(); // Default constructor, creates an empty graph
    list_graph(size_t n); // Creates a graph with n vertices
    list_graph(size_t n, std::vector<std::vector<std::pair<size_t, double_t> > > adj_list); // creates a graph with n vertices using the adjacency list provided

    ~list_graph(); // Destructor

    void add_vertex(); // Increases the number of vertices by 1, adjusts m_AdjList
    void add_edge(size_t a, size_t b, double_t weight=1, bool directed=false); // Adds an edge from a to b
    void remove_edge(size_t a, size_t b, bool directed=false); // Removes any edge from a to b

    size_t vsize(); // get number of vertices
    double_t get_edge(size_t a, size_t b); // get weight of an edge
    std::vector<std::pair<size_t, double_t> > get_neighbors(size_t a); // get the neighbors of a
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

void dfs(list_graph g, std::function<void(size_t, size_t)> preVisit, std::function<void(size_t, size_t)> postVisit, size_t start=0, bool endFast=false);
std::vector<size_t> lin(list_graph g); // sorts by decreasing postorder

std::vector<double_t> dag_min_dist(list_graph g, size_t s);

}

#endif