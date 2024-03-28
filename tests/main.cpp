
#include "aathalg/graph.h"

#include <iostream>
#include <string>
#include <sstream>
#include <functional>

#define START_TEST { std::cout << "Running " << __FUNCTION__ << "..." << std::endl; }
#define PASS { std::cout << __FUNCTION__ << " passed!" << std::endl; return true; }
#define FAIL(x, y) { std::cerr << __FUNCTION__ << " failed... expected " << x << " but got " << y << std::endl; return false; }

template<typename T>
std::string toString(const T arr[], size_t size) {
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < size; ++i) {
        if (i > 0) ss << ", ";
        ss << arr[i];
    }
    ss << "]";
    return ss.str();
}

void runTests(std::vector<std::function<bool()> > tests)
{
    uint32_t passCount = 0;
    uint32_t totalCount = 0;
    for (auto test : tests)
    {
        passCount += test();
        totalCount++;
    }
    std::cout << "Passed " << passCount << "/" << totalCount << " tests!" << std::endl;
}

bool dfsTest()
{
    START_TEST
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
    };

    auto postvisit = [&pre, &post, &clock](uint32_t n, uint32_t counter) -> void
    {
        post[n] = clock;
        clock++;
    };

    aathalg::dfs(g, previsit, postvisit);

    uint32_t correctPre[9] = { 0, 1, 2, 14, 6, 3, 13, 12, 4 };
    uint32_t correctPost[9] = { 11, 10, 9, 15, 7, 8, 16, 17, 5 };

    for (int i = 0; i < 9; i++)
    {
        if (correctPre[i] != pre[i])
            FAIL(toString(correctPre, 9), toString(pre, 9))
        if (correctPost[i] != post[i])
            FAIL(toString(correctPost, 9), toString(post, 9))
    }
    PASS // return statement in here, idk if I like this practice 
}




int main()
{
    std::vector<std::function<bool()> > tests = { dfsTest };
    runTests(tests);

    return 0;
}