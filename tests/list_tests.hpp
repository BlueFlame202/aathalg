
#ifndef LIST_TESTING
#define LIST_TESTING

#include "testing.hpp"

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



// tests longest increasing subsequence
bool longest_increasing_subsequence_test()
{
    START_TEST

    std::vector<int> seq = { 5, 2, 8, 6, 3, 6, 9, 7 };

    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<int> res = algae::longest_increasing_subsequence(seq);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::vector<int> correct = { 2, 3, 6, 9 };

    for (int i = 0; i < 4; i++)
        if (res[i] != correct[i])
            AFAIL(to_string(correct), to_string(res));

    PASS(t2-t1)
}

// tests edit distance
bool edit_distance_test_1()
{
    START_TEST

    std::string a = "snowy";
    std::string b = "sunny";

    auto t1 = std::chrono::high_resolution_clock::now();
    size_t res = algae::edit_distance(a, b);
    auto t2 = std::chrono::high_resolution_clock::now();

    size_t correct = 3;
    
    if (!(correct == res))
        AFAIL(correct, res);

    PASS(t2-t1)
}

// tests edit distance
bool edit_distance_test_2()
{
    START_TEST

    std::string a = "polynomial";
    std::string b = "exponential";

    auto t1 = std::chrono::high_resolution_clock::now();
    size_t res = algae::edit_distance(a, b);
    auto t2 = std::chrono::high_resolution_clock::now();

    size_t correct = 6;
    
    if (!(correct == res))
        AFAIL(correct, res);

    PASS(t2-t1)
}

// tests knapsack
bool knapsack_unlimited_test()
{
    START_TEST

    std::vector<int> w = { 6, 3, 4, 2 };
    std::vector<int> v = { 30, 14, 16, 9 };

    auto t1 = std::chrono::high_resolution_clock::now();
    size_t res = algae::knapsack_unlimited(10, w, v);
    auto t2 = std::chrono::high_resolution_clock::now();

    size_t correct = 48;
    
    if (!(correct == res))
        AFAIL(correct, res);

    PASS(t2-t1)
}

// tests knapsack
bool knapsack_up_to_one_test()
{
    START_TEST

    std::vector<int> w = { 6, 3, 4, 2 };
    std::vector<int> v = { 30, 14, 16, 9 };

    auto t1 = std::chrono::high_resolution_clock::now();
    size_t res = algae::knapsack_up_to_one(10, w, v);
    auto t2 = std::chrono::high_resolution_clock::now();

    size_t correct = 46;
    
    if (!(correct == res))
        AFAIL(correct, res);

    PASS(t2-t1)
}

#endif