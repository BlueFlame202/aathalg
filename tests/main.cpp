
#include "aathalg/graph.h"

#include <iostream>

int main()
{
    aathalg::ListGraph g(9);
    g.addEdge(0, 4);
    g.addEdge(0, 1);
    g.addEdge(1, 4);
    g.addEdge(1, 2);
    g.addEdge(2, 5);
    g.addEdge(3, 7); 
    g.addEdge(3, 6);
    g.addEdge(4, 5);
    g.addEdge(5, 8);
    g.addEdge(6, 7);

    uint32_t pre[9];
    uint32_t post[9];
    uint32_t clock = 0;

    auto previsit = [&pre, &post, &clock](uint32_t n, uint32_t counter) -> void
    {
        pre[n] = clock;
        clock++;
        std::cout << "Visiting " << n << std::endl;
    };

    auto postvisit = [&pre, &post, &clock](uint32_t n, uint32_t counter) -> void
    {
        post[n] = clock;
        clock++;
        std::cout << "Leaving " << n << std::endl;
    };

    aathalg::dfs(g, previsit, postvisit);
    for (int i = 0; i < 9; i++)
    {
        std::cout << "[" << pre[i] << ", " << post[i] << "]" << std::endl;
    }

    return 0;
}