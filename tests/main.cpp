
#include "algae/graph.hpp"
#include "algae/list.hpp"

#include "graph_tests.hpp"
#include "list_tests.hpp"
#include "numerics_tests.hpp"

#define FIXED_SEED

int main()
{
    std::vector<std::function<bool()> > tests = 
    { 
        dfs_test, 
        lin_test, 
        dag_min_dist_test,

        longest_increasing_subsequence_test,
        edit_distance_test_1,
        edit_distance_test_2,
        knapsack_unlimited_test,
        knapsack_up_to_one_test
    };
    run_tests(tests);

    return 0;
}