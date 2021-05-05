//
//  minCost.cpp
//  leetcode
//
//  Created by Song Ding on 8/12/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minCost {
/*
// TODO: copy problem statement here
 There are
 N+2 blocks numbered from 0 to N+1. Given an array A of integers of size N
  and an integer K, where Ai is the cost of stepping on i-th block.
 Calculate the minimum cost to go from position 0 to (N+1) if we can only jump at most
 K blocks.
 
 Constraints:

 1≤Ai≤10^9
 1≤K≤N≤10^6
*/
class Solution {
public:
    // TODO: copy function signature here
    // to jump to position i, find a position within K steps that has the smallest cost.
    // and monotonic queue is for this purpose.
    int minCost(vector<int>& A, int N, int K) {
        vector<int> costs(N+2, 0);
        deque<int> q;
        for (int i = 0; i <= N+1; ++i) {
            while (q.size() && q.front()+K < i) {
                q.pop_front();
            }
            costs[i] = (q.size() ? costs[q.front()] : 0) + A[i];
            while (q.size() && costs[q.back()] >= costs[i]) {
                q.pop_back();
            }
            q.push_back(i);
        }
        return costs[N+1];
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> A;
        int N;
        int K;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
    };
    // TODO: provide expected results here
    vector<int> answers {
        {}
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minCost::Solution().minCost(dp.A, dp.N, dp.K);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
