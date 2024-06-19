#ifndef ALGAE_LIST_H
#define ALGAE_LIST_H

#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

namespace algae
{

template <typename T>
std::pair<T, size_t> max(std::vector<T> seq, size_t max_index=-1)
{
    if (max_index == -1) max_index = seq.size() - 1;

    T max = seq[0];
    size_t idx = 0;
    for (size_t j = 1; j <= max_index; j++)
    {
        if (seq[j] > max)
        {
            max = seq[j];
            idx = j;
        }
    }
    return std::make_pair(max, idx);
}

/**
 * Currently it looks like its better to define ALGAE_LIS_BACKTRACK in terms of speed
 * Keeping the extra data rather than backtracking actually hurts time somehow, more investigation needed.
 * TODO: Maybe try a different implementation instead of a vector of std::pairs, like just having two std::vectors
 * TODO: Implement randomized tests and then see the distributions of times it takes.
*/
#define ALGAE_LIS_BACKTRACK
#ifdef ALGAE_LIS_BACKTRACK
template <typename T>
std::vector<T> longest_increasing_subsequence(std::vector<T> seq) // O(len(seq)^2) dp algorithm
{
    std::vector<T> lis_subproblem(seq.size()); // longest increasing subsequence ending at index i

    for (size_t i = 0; i < seq.size(); i++)
    {
        lis_subproblem[i] = 1;
        for (size_t j = 0; j < i; j++)
            if (seq[i] > seq[j] && lis_subproblem[j] >= lis_subproblem[i])
                lis_subproblem[i] = lis_subproblem[j] + 1;
    }

    // backtrack
    auto pair = max(lis_subproblem);

    std::vector<T> res(pair.first);
    res[pair.first-1] = seq[pair.second];

    for (size_t j = pair.second - 1; pair.first != 0; j--) // because we're using size_t, we get integer overflow if we try to force j >= 0 and get an infinite loop
    {
        if (seq[j] < seq[pair.second] && lis_subproblem[j] == pair.first - 1)
        {
            pair.first--;
            pair.second = j;
            res[pair.first-1] = seq[j];
        }
    }

    return res;
}
#else
template <typename T>
std::vector<T> longest_increasing_subsequence(std::vector<T> seq) // O(len(seq)^2) dp algorithm
{
    std::vector<std::pair<T, size_t> > lis_subproblem(seq.size()); // longest increasing subsequence ending at index i

    for (size_t i = 0; i < seq.size(); i++)
    {
        lis_subproblem[i] = std::make_pair(1, 0);
        for (size_t j = 0; j < i; j++)
        {
            if (seq[i] > seq[j] && lis_subproblem[j].first >= lis_subproblem[i].first)
            {
                lis_subproblem[i].first = lis_subproblem[j].first + 1;
                lis_subproblem[i].second = j;
            }
        }
    }

    auto pair = max(lis_subproblem);
    std::vector<T> res(pair.first.first);

    for (size_t j = pair.first.first; j > 0; j--)
    {
        res[j-1] = seq[pair.second];
        pair.second = pair.first.second;
        pair.first = lis_subproblem[pair.second];
    }

    return res;
}
#endif

size_t edit_distance(std::string a, std::string b)
{
    std::vector<std::vector<size_t>> dp(a.size()+1, std::vector<size_t>(b.size()+1));

    for (size_t i = 0; i <= a.size(); i++)
        dp[i][0] = i;
    for (size_t j = 0; j <= b.size(); j++)
        dp[0][j] = j;
    
    for (size_t i = 1; i <= a.size(); i++)
    {
        for (size_t j = 1; j <= b.size(); j++)
        {
            dp[i][j] = std::min(std::min(dp[i][j-1] + 1, dp[i-1][j] + 1), dp[i-1][j-1] + (a[i-1] != b[j-1])); 
            // you can do a[i] != b[j] and still pass the current test cases xD
        }
    }

    return dp[a.size()][b.size()];
}

#define KNAPSACK_NO_SORT // TODO: Implement KNAPSACK which sorts the costs/values first, so we get a speed boost
#ifdef KNAPSACK_NO_SORT
template <typename T> // T is an integer type
T knapsack_unlimited(T budget, std::vector<T> cost, std::vector<T> value) // returns best value given a budget
{
    if (cost.size() == 0) return 0;

    std::vector<T> dp(budget+1);
    for (int remaining = 0; remaining <= budget; remaining++)
    {
        dp[remaining] = 0;
        for (int j = 0; j < cost.size(); j++)
            if (cost[j] <= remaining)
                dp[remaining] = std::max(dp[remaining], dp[remaining-cost[j]] + value[j]);
    }
    return dp[budget];
}

template <typename T> // T is an integer type
T knapsack_up_to_one(T budget, std::vector<T> cost, std::vector<T> value) // returns best value given a budget
{
    std::vector<std::vector<T> > dp(budget+1, std::vector<T>(cost.size()+1));

    for (int i = 0; i <= budget; i++)
        dp[i][0] = 0;
    for (int j = 0; j <= cost.size(); j++)
        dp[0][j] = 0;
    
    // dp[i][j] = max(dp[i-cost[i-1]][j-1], dp[i][j-1])
    for (int j = 1; j <= cost.size(); j++) // item number
    {
        for (int i = 1; i <= budget; i++) // money number
        {
            if (i - cost[j-1] >= 0)
                dp[i][j] = std::max(dp[i-cost[j-1]][j-1] + value[j-1], dp[i][j-1]);
            else
                dp[i][j] = dp[i][j-1];
        }
    }

    return dp[budget][cost.size()];
}

#else

#endif


}

#endif