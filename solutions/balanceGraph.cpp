//
//  balanceGraph.cpp
//  leetcode
//
//  Created by Song Ding on 4/10/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace balanceGraph {
/*
// TODO: copy problem statement here
 707 · Optimal Account Balancing
 A group of friends went on holiday and sometimes lent each other money. For example, Alice paid for Bill's lunch for $10. Then later Chris gave Alice $5 for a taxi ride. We can model each transaction as a tuple (x, y, z) which means person x gave person y $z. Assuming Alice, Bill, and Chris are person 0, 1, and 2 respectively (0, 1, 2 are the person's ID), the transactions can be represented as [[0, 1, 10], [2, 0, 5]].
 Given a list of transactions between a group of people, return the minimum number of transactions required to settle the debt.
 Note:
 A transaction will be given as a tuple (x, y, z). Note that x â‰  y and z > 0.
 Person's IDs may not be linear, e.g. we could have the persons 0, 1, 2 or we could also have the persons 0, 2, 6.
 Example 1:
 Input:
 [[0,1,10], [2,0,5]]

 Output:
 2

 Explanation:
 Person #0 gave person #1 $10.
 Person #2 gave person #0 $5.

 Two transactions are needed. One way to settle the debt is person #1 pays person #0 and #2 $5 each.
 Example 2:
 Input:
 [[0,1,10], [1,0,1], [1,2,5], [2,0,5]]

 Output:
 1

 Explanation:
 Person #0 gave person #1 $10.
 Person #1 gave person #0 $1.
 Person #1 gave person #2 $5.
 Person #2 gave person #0 $5.

 Therefore, person #1 only need to give person #0 $4, and all debt is settled.
*/
class Solution {
public:
    // TODO: copy function signature here
    int balanceGraph(vector<vector<int>> &edges) {
        // Write your code here
        // use two priority queue
        unordered_map<int,int> inmout;
        for (auto& e : edges) {
          inmout[e[0]] -= e[2];
          inmout[e[1]] += e[2];
        }
        int res = 0;
        unordered_map<int,int> bal;
        for (auto& p : inmout) {
            if (p.second == 0) {
                continue;
            }
            if (bal[-p.second]) {
                ++res;
                --bal[-p.second];
            } else {
                ++bal[p.second];
            }
        }
        vector<int> nums;
        for (auto&p : bal) {
            for (int i = 0; i < p.second; ++i) {
                nums.push_back(p.first);
            }
        }
        int n = nums.size();
        vector<int> sums(1<<n,0), cnt(1<<n,0);
        for (int st = 0; st < 1<<n; ++st) {
            for (int j = 0; j < n; ++j) {
                if (st & 1<<j) {
                    sums[st] += nums[j];
                    ++cnt[st];
                }
            }
        }
        vector<int> dp(1<<n, INT_MAX);
        dp[0] = 0;
        for (int st = 1; st < 1<<n; ++st) {
            if (sums[st] == 0) {
                dp[st] = cnt[st]-1;
                for (int sub = st-1; sub; sub=(sub-1)&st) {
                    if (sums[sub] == 0) {
                        dp[st] = min(dp[st], dp[sub]+dp[st-sub]);
                    }
                }
            }
        }
        return dp[(1<<n)-1]+res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> edges;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{{0,1,10},{1,2,10},{2,0,10}}},
        {{{9,8,1},{6,8,59},{5,4,28},{5,4,43},{0,2,54},{4,3,17},{9,8,72},{0,1,68},{4,3,4},{2,0,74},{7,9,54},{5,4,58},{1,2,42},{4,5,91},{0,1,41},{6,8,6},{7,8,51},{0,2,30},{6,8,57},{8,6,32}}},
    };
    // TODO: provide expected results here
    vector<int> answers {
        0,
        7,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = balanceGraph::Solution().balanceGraph(dp.edges);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
