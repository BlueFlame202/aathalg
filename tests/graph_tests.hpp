
#ifndef GRAPH_TESTING
#define GRAPH_TESTING

#include "testing.hpp"

bool dfs_test()
{
    START_TEST
    algae::list_graph g(9);
    g.add_edge(0, 4);
    g.add_edge(0, 1);
    g.add_edge(1, 4);
    g.add_edge(1, 2);
    g.add_edge(2, 5);
    g.add_edge(3, 7); 
    g.add_edge(3, 6);
    g.add_edge(4, 5);
    g.add_edge(5, 8);
    g.add_edge(6, 7);

    size_t pre[9];
    size_t post[9];
    size_t clock = 0;

    auto previsit = [&pre, &post, &clock](size_t n, size_t counter) -> void
    {
        pre[n] = clock;
        clock++;
    };

    auto postvisit = [&pre, &post, &clock](size_t n, size_t counter) -> void
    {
        post[n] = clock;
        clock++;
    };

    auto t1 = std::chrono::high_resolution_clock::now();
    algae::dfs(g, previsit, postvisit);
    auto t2 = std::chrono::high_resolution_clock::now();

    size_t correct_pre[9] = { 0, 1, 2, 14, 6, 3, 13, 12, 4 };
    size_t correct_post[9] = { 11, 10, 9, 15, 7, 8, 16, 17, 5 };

    for (int i = 0; i < 9; i++)
    {
        if (correct_pre[i] != pre[i])
            AFAIL(to_string(correct_pre, 9), to_string(pre, 9))
        if (correct_post[i] != post[i])
            AFAIL(to_string(correct_post, 9), to_string(post, 9))
    }
    PASS(t2-t1) // return statement in here, idk if I like this practice 
}

// tests linearization
bool lin_test()
{
    START_TEST

    algae::list_graph g(6);
    g.add_edge(0, 1, 1, true);
    g.add_edge(0, 3, 2, true);
    g.add_edge(3, 1, 4, true);
    g.add_edge(3, 4, 3, true);
    g.add_edge(1, 2, 6, true);
    g.add_edge(2, 4, 1, true); 
    g.add_edge(2, 5, 2, true);
    g.add_edge(4, 5, 1, true);

    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<size_t> res = lin(g);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::vector<size_t> correct = { 0, 3, 1, 2, 4, 5 };

    for (int i = 0; i < 6; i++)
        if (res[i] != correct[i])
            AFAIL(to_string(correct), to_string(res));

    PASS(t2-t1)
}

// tests min distance through a dag 
bool dag_min_dist_test()
{
    START_TEST

    algae::list_graph g(6);
    g.add_edge(0, 1, 1, true);
    g.add_edge(0, 3, 2, true);
    g.add_edge(3, 1, 4, true);
    g.add_edge(3, 4, 3, true);
    g.add_edge(1, 2, 6, true);
    g.add_edge(2, 4, 1, true); 
    g.add_edge(2, 5, 2, true);
    g.add_edge(4, 5, 1, true);

    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<double_t> res = dag_min_dist(g, 0);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::vector<double_t> correct = { 0, 1, 7, 2, 5, 6 };

    for (int i = 0; i < 6; i++)
        if (res[i] != correct[i])
            AFAIL(to_string(correct), to_string(res));

    PASS(t2-t1)
}

#endif