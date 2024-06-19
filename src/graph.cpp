#include "algae/graph.hpp"

#include <stack>
#include <queue>
#include <limits>
#include <cfloat>

namespace algae
{

list_graph::list_graph() 
    : m_n(0), m_adj_list(std::vector<std::vector<std::pair<size_t, double_t> > >())
{}

list_graph::list_graph(size_t N) 
    : m_n(N), m_adj_list(std::vector<std::vector<std::pair<size_t, double_t> > >())
{
    for (size_t i = 0; i < N; i++)
        m_adj_list.push_back(std::vector<std::pair<size_t, double_t> >());
}

list_graph::list_graph(size_t N, std::vector<std::vector<std::pair<size_t, double_t> > > adjList) 
    : m_n(N), m_adj_list(adjList)
{
    // TODO: check for issues with adjList
}

list_graph::~list_graph() 
{
}

void list_graph::add_vertex()
{
    m_n++;
    m_adj_list.push_back(std::vector<std::pair<size_t, double_t> >());
}

// WARNING: current implementation doesn't check if b is already in the list
void list_graph::add_edge(size_t a, size_t b, double_t weight, bool directed)
{
    m_adj_list[a].push_back(std::make_pair(b, weight));
    if (!directed)
        m_adj_list[b].push_back(std::make_pair(a, weight));
}

void list_graph::remove_edge(size_t a, size_t b, bool directed)
{
    for (size_t i = 0; i < m_adj_list[a].size(); i++)
    {
        if (m_adj_list[a][i].first == b) 
        {
            m_adj_list[a].erase(m_adj_list[a].begin()+i);
            i--;
        }
    }
}

size_t list_graph::vsize() { return m_n; } // get number of vertices

double_t list_graph::get_edge(size_t a, size_t b)
{
    for (size_t i = 0; i < m_adj_list[a].size(); i++)
    {
        if (m_adj_list[a][i].first == b) 
        {
            return m_adj_list[a][i].second;
        }
    }
    return std::numeric_limits<double>::quiet_NaN();;
}


std::vector<std::pair<size_t, double_t> > list_graph::get_neighbors(size_t a)
{
    return m_adj_list[a];
}

void dfs(list_graph g, std::function<void(size_t, size_t)> preVisit, std::function<void(size_t, size_t)> postVisit, size_t start, bool endFast)
{
    std::stack<size_t> toVisit;
    bool visited[g.vsize()];
    std::fill(visited, visited+g.vsize(), false);

    bool left[g.vsize()];
    std::fill(left, left+g.vsize(), false);

    toVisit.push(start);
    bool done = false;
    size_t counter = 0;
    while (!done)
    {
        while (!toVisit.empty()) // this is the explore method
        {
            size_t n = toVisit.top();
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

                for (auto v : g.get_neighbors(n))
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

std::vector<size_t> lin(list_graph g)
{
    std::vector<size_t> post(g.vsize());
    uint32_t clock = 0;

    auto previsit = [&post, &clock](size_t n, size_t counter) -> void
    {
        clock++;
    };

    auto postvisit = [&post, &clock](size_t n, size_t counter) -> void
    {
        post[n] = clock;
        clock++;
    };

    dfs(g, previsit, postvisit);

    std::priority_queue<std::pair<size_t, size_t> > pq;
    for (int i = 0; i < g.vsize(); i++)
        pq.push(std::make_pair(post[i], i));
    
    std::vector<size_t> res;
    while (!pq.empty())
    {
        res.push_back(pq.top().second);
        pq.pop();
    }
    return res;
}

std::vector<double_t> dag_min_dist(list_graph g, size_t s)
{
    auto l = lin(g);

    std::vector<double_t> dist(g.vsize());
    
    size_t i;
    for (i = 0; l[i] != s && i < g.vsize(); i++) dist[l[i]] = DBL_MAX; // use DBL_MAX as infinity
    dist[s] = 0;
    for (i++; i < g.vsize(); i++)
    {
        dist[l[i]] = DBL_MAX;
        for (size_t j = 0; j < g.vsize(); j++) 
        {
            double_t w = g.get_edge(j, l[i]);
            if (w != DBL_MAX && dist[l[i]] > dist[j] + w)
                dist[l[i]] = dist[j] + w;
        }
    }
    return dist;
}

}