#include "aathalg/graph.h"

#include <stack>
#include <queue>

namespace aathalg
{

ListGraph::ListGraph() 
    : m_n(0), m_adjList(std::vector<std::vector<std::pair<uint32_t, double_t> > >())
{}

ListGraph::ListGraph(uint32_t N) 
    : m_n(N), m_adjList(std::vector<std::vector<std::pair<uint32_t, double_t> > >())
{
    for (int i = 0; i < N; i++)
        m_adjList.push_back(std::vector<std::pair<uint32_t, double_t> >());
}

ListGraph::ListGraph(uint32_t N, std::vector<std::vector<std::pair<uint32_t, double_t> > > adjList) 
    : m_n(N), m_adjList(adjList)
{
    // TODO: check for issues with adjList
}

ListGraph::~ListGraph() 
{
}

void ListGraph::addVertex()
{
    m_n++;
    m_adjList.push_back(std::vector<std::pair<uint32_t, double_t> >());
}

// WARNING: current implementation doesn't check if b is already in the list
void ListGraph::addEdge(uint32_t a, uint32_t b, double_t weight, bool directed)
{
    m_adjList[a].push_back(std::make_pair(b, weight));
    if (!directed)
        m_adjList[b].push_back(std::make_pair(a, weight));
}

void ListGraph::removeEdge(uint32_t a, uint32_t b, bool directed)
{
    for (int i = 0; i < m_adjList[a].size(); i++)
    {
        if (m_adjList[a][i].first == b) 
        {
            m_adjList[a].erase(m_adjList[a].begin()+i);
            i--;
        }
    }
}

uint32_t ListGraph::vsize() { return m_n; } // get number of vertices

int32_t ListGraph::getEdge(uint32_t a, uint32_t b)
{
    for (int i = 0; i < m_adjList[a].size(); i++)
    {
        if (m_adjList[a][i].first == b) 
        {
            return m_adjList[a][i].second;
        }
    }
    return 0;
}


std::vector<std::pair<uint32_t, double_t> > ListGraph::getNeighbors(uint32_t a)
{
    return m_adjList[a];
}

void dfs(ListGraph g, std::function<void(uint32_t, uint32_t)> preVisit, std::function<void(uint32_t, uint32_t)> postVisit, uint32_t start, bool endFast)
{
    std::stack<uint32_t> toVisit;
    bool visited[g.vsize()];
    std::fill(visited, visited+g.vsize(), false);

    bool left[g.vsize()];
    std::fill(left, left+g.vsize(), false);

    toVisit.push(start);
    bool done = false;
    uint32_t counter = 0;
    while (!done)
    {
        while (!toVisit.empty()) // this is the explore method
        {
            uint32_t n = toVisit.top();
            if (visited[n]) 
            {
                if (!left[n])
                {
                    left[n] = true;
                    postVisit(n, counter);
                }
                toVisit.pop();
            }
            else
            {
                visited[n] = true;
                preVisit(n, counter);

                for (auto v : g.getNeighbors(n))
                    if (!visited[v.first])
                        toVisit.push(v.first);
            }
        }

        done = true;
        counter++;
        if (!endFast) // endfast is used to determine whether or not we just want to explore or do a full fledged dfs
        {
            for (int i = 0; i < g.vsize(); i++)
            {
                if (!visited[i])
                {
                    done = false;
                    toVisit.push(i);
                }
            }
        }
    }
}

std::vector<uint32_t> lin(ListGraph g)
{
    uint32_t * post = new uint32_t[g.vsize()];
    uint32_t clock = 0;

    auto previsit = [&post, &clock](uint32_t n, uint32_t counter) -> void
    {
        clock++;
    };

    auto postvisit = [&post, &clock](uint32_t n, uint32_t counter) -> void
    {
        post[n] = clock;
        clock++;
    };

    dfs(g, previsit, postvisit);

    std::priority_queue<std::pair<uint32_t, uint32_t> > pq;
    for (int i = 0; i < g.vsize(); i++)
        pq.push(std::make_pair(post[i], i));
    
    std::vector<uint32_t> res;
    while (!pq.empty())
    {
        res.push_back(pq.top().second);
        pq.pop();
    }
    return res;
}

}