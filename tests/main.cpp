
#include "aathalg/graph.h"

#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <chrono>



#define START_TEST { std::cout << "Running " << __FUNCTION__ << "... "; }
#define PASS(dur) { std::cout << __FUNCTION__ << " passed!" << " Took " << ((std::chrono::duration<double, std::milli>)(dur)).count() << " milliseconds. B-)" << std::endl; return true; }
#define AFAIL(x, y) { std::cerr << __FUNCTION__ << " failed... expected " << x << " but got " << y << ". :-(" << std::endl; return false; }
#define TFAIL(x, y) { std::cerr << __FUNCTION__ << " failed... took " << x << " milliseconds but should take at most " << y << " milliseconds. :-(" << std::endl; return false; }

template<typename T>
std::string toString(const T arr[], size_t size) 
{
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < size; ++i) {
        if (i > 0) ss << ", ";
        ss << arr[i];
    }
    ss << "]";
    return ss.str();
}

template<typename T>
std::string toString(std::vector<T> vec) 
{
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << vec[i];
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

    auto t1 = std::chrono::high_resolution_clock::now();
    aathalg::dfs(g, previsit, postvisit);
    auto t2 = std::chrono::high_resolution_clock::now();

    uint32_t correctPre[9] = { 0, 1, 2, 14, 6, 3, 13, 12, 4 };
    uint32_t correctPost[9] = { 11, 10, 9, 15, 7, 8, 16, 17, 5 };

    for (int i = 0; i < 9; i++)
    {
        if (correctPre[i] != pre[i])
            AFAIL(toString(correctPre, 9), toString(pre, 9))
        if (correctPost[i] != post[i])
            AFAIL(toString(correctPost, 9), toString(post, 9))
    }
    PASS(t2-t1) // return statement in here, idk if I like this practice 
}

bool linTest()
{
    START_TEST

    aathalg::ListGraph g(6);
    g.addEdge(0, 1, 1, true);
    g.addEdge(0, 3, 2, true);
    g.addEdge(3, 1, 4, true);
    g.addEdge(3, 4, 3, true);
    g.addEdge(1, 2, 6, true);
    g.addEdge(2, 4, 1, true); 
    g.addEdge(2, 5, 2, true);
    g.addEdge(4, 5, 1, true);

    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<uint32_t> res = lin(g);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::vector<uint32_t> correct = { 0, 3, 1, 2, 4, 5 };

    for (int i = 0; i < 6; i++)
        if (res[i] != correct[i])
            AFAIL(toString(correct), toString(res));

    PASS(t2-t1)
}


int main()
{
    std::vector<std::function<bool()> > tests = { dfsTest, linTest };
    runTests(tests);

    return 0;
}