
#include "aathalg/graph.hpp"
#include "aathalg/list.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <chrono>


#define START_TEST { std::cout << "Running " << __FUNCTION__ << "... "; }
#define PASS(dur) { std::cout << "and passed!" << " Took " << ((std::chrono::duration<double, std::milli>)(dur)).count() << " milliseconds. B-)" << std::endl; return true; }
#define AFAIL(x, y) { std::cerr << __FUNCTION__ << " failed... expected " << x << " but got " << y << ". :-(" << std::endl; return false; }
#define TFAIL(x, y) { std::cerr << "but failed... took " << x << " milliseconds but should take at most " << y << " milliseconds. :-(" << std::endl; return false; }



template <typename T>
std::string to_string(const T arr[], size_t size) 
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

template <typename T>
std::string to_string(std::vector<T> vec) 
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

void run_tests(std::vector<std::function<bool()> > tests)
{
    uint32_t pass_count = 0;
    uint32_t total_count = 0;
    for (auto test : tests)
    {
        pass_count += test();
        total_count++;
    }
    std::cout << "Passed " << pass_count << "/" << total_count << " tests!" << std::endl;
}

bool dfs_test()
{
    START_TEST
    aathalg::list_graph g(9);
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
    aathalg::dfs(g, previsit, postvisit);
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

bool lin_test()
{
    START_TEST

    aathalg::list_graph g(6);
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

bool dag_min_dist_test()
{
    START_TEST

    aathalg::list_graph g(6);
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

bool longest_indcreasing_subsequence_test()
{
    START_TEST

    std::vector<int> seq = { 5, 2, 8, 6, 3, 6, 9, 7 };

    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<int> res = aathalg::longest_increasing_subsequence(seq);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::vector<int> correct = { 2, 3, 6, 9 };

    for (int i = 0; i < 4; i++)
        if (res[i] != correct[i])
            AFAIL(to_string(correct), to_string(res));

    PASS(t2-t1)
}

bool edit_distance_test_1()
{
    START_TEST

    std::string a = "snowy";
    std::string b = "sunny";

    auto t1 = std::chrono::high_resolution_clock::now();
    size_t res = aathalg::edit_distance(a, b);
    auto t2 = std::chrono::high_resolution_clock::now();

    size_t correct = 3;
    
    if (!(correct == res))
        AFAIL(correct, res);

    PASS(t2-t1)
}

bool edit_distance_test_2()
{
    START_TEST

    std::string a = "polynomial";
    std::string b = "exponential";

    auto t1 = std::chrono::high_resolution_clock::now();
    size_t res = aathalg::edit_distance(a, b);
    auto t2 = std::chrono::high_resolution_clock::now();

    size_t correct = 6;
    
    if (!(correct == res))
        AFAIL(correct, res);

    PASS(t2-t1)
}

bool knapsack_unlimited_test()
{
    START_TEST

    std::vector<int> w = { 6, 3, 4, 2 };
    std::vector<int> v = { 30, 14, 16, 9 };

    auto t1 = std::chrono::high_resolution_clock::now();
    size_t res = aathalg::knapsack_unlimited(10, w, v);
    auto t2 = std::chrono::high_resolution_clock::now();

    size_t correct = 48;
    
    if (!(correct == res))
        AFAIL(correct, res);

    PASS(t2-t1)
}

bool knapsack_up_to_one_test()
{
    START_TEST

    std::vector<int> w = { 6, 3, 4, 2 };
    std::vector<int> v = { 30, 14, 16, 9 };

    auto t1 = std::chrono::high_resolution_clock::now();
    size_t res = aathalg::knapsack_up_to_one(10, w, v);
    auto t2 = std::chrono::high_resolution_clock::now();

    size_t correct = 46;
    
    if (!(correct == res))
        AFAIL(correct, res);

    PASS(t2-t1)
}


int main()
{
    std::vector<std::function<bool()> > tests = 
    { 
        dfs_test, 
        lin_test, 
        dag_min_dist_test, 
        longest_indcreasing_subsequence_test,
        edit_distance_test_1,
        edit_distance_test_2,
        knapsack_unlimited_test,
        knapsack_up_to_one_test
    };
    run_tests(tests);

    return 0;
}