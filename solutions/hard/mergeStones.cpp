// mergeStones.cpp
// leetcode
//
// Created by  Song Ding on 8/20/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace mergeStones {
/*
// TODO: copy problem statement here
 1000. Minimum Cost to Merge Stones
 Hard
 
 225
 
 19
 
 Favorite
 
 Share
 There are N piles of stones arranged in a row.  The i-th pile has stones[i] stones.
 
 A move consists of merging exactly K consecutive piles into one pile, and the cost of this move is equal to the total number of stones in these K piles.
 
 Find the minimum cost to merge all piles of stones into one pile.  If it is impossible, return -1.
 
 
 
 Example 1:
 
 Input: stones = [3,2,4,1], K = 2
 Output: 20
 Explanation:
 We start with [3, 2, 4, 1].
 We merge [3, 2] for a cost of 5, and we are left with [5, 4, 1].
 We merge [4, 1] for a cost of 5, and we are left with [5, 5].
 We merge [5, 5] for a cost of 10, and we are left with [10].
 The total cost was 20, and this is the minimum possible.
 Example 2:
 
 Input: stones = [3,2,4,1], K = 3
 Output: -1
 Explanation: After any merge operation, there are 2 piles left, and we can't merge anymore.  So the task is impossible.
 Example 3:
 
 Input: stones = [3,5,1,2,6], K = 3
 Output: 25
 Explanation:
 We start with [3, 5, 1, 2, 6].
 We merge [5, 1, 2] for a cost of 8, and we are left with [3, 8, 6].
 We merge [3, 8, 6] for a cost of 17, and we are left with [17].
 The total cost was 25, and this is the minimum possible.
 
 
 Note:
 
 1 <= stones.length <= 30
 2 <= K <= 30
 1 <= stones[i] <= 100
 */

class Solution {
public:
    /**
     https://leetcode.com/problems/minimum-cost-to-merge-stones/discuss/247567/JavaC%2B%2BPython-DP
            stones[i] ~ stones[j] will merge as much as possible.

            Finally (j - i) % (K - 1) + 1 piles will be left.

            It's less than K piles and no more merger happens.

            dp[i][j] means the minimum cost needed to merge stones[i] ~ stones[j].
     */
    int mergeStones_dp2(vector<int>& stones, int K) {
        int n = stones.size();
        if ((n - 1) % (K - 1)) return -1;

        vector<int> prefix(n + 1);
        for (int i = 0; i <  n; i++)
            prefix[i + 1] = prefix[i] + stones[i];

        vector<vector<int> > dp(n, vector<int>(n));
        for (int m = K; m <= n; ++m)
            for (int i = 0; i + m <= n; ++i) {
                int j = i + m - 1;
                dp[i][j] = INT_MAX;
                for (int mid = i; mid < j; mid += K - 1)
                    dp[i][j] = min(dp[i][j], dp[i][mid] + dp[mid + 1][j]);
                if ((j - i) % (K - 1) == 0)
                    dp[i][j] += prefix[j + 1] - prefix[i];
            }
        return dp[0][n - 1];
    }
    /**
     * Let dp(t, i, x) = min cost of merge t consecutives pile startng at index i into
     * x piles, then dp(t, i, x) = for ti in (1, t-1), xi in (1, x-1), find min cost
     * from dp(ti, i, xi) + dp(t-ti, i+ti, x-xi). Note, x will be in [2, min(K, t)].
     * but when x = K, do a merge to fill dp(t, i, 1).
     */
    int mergeStones(vector<int>& stones, int K) {
        int n = stones.size();
        if (n == 1) {
            return 0;
        } else if (n < K || (K > 2 && n%(K-1) != 1)) {
            return -1;
        }
        
        vector<int> sum(n+1, 0);
        int t = 0;
        for (int i = 0; i < n; ++i) {
            t += stones[i];
            sum[i+1] = t;
        }
        
        // layers:
        // # of piles before merge
        // index of starting pile
        // # of piles after merge
        vector<vector<vector<int>>> res(n+1);
        for (int t = 0; t <= n; ++t) {
            res[t].resize(n-t+1);
            for (int i = 0; i <= n-t; ++i) {
                int k = min(K, t);
                res[t][i].resize(k+1, INT_MIN);
            }
        }
        
        // t=1
        for (int i = 0; i < n; ++i) {
            res[1][i][1] = 0;
        }
        
        // merge t piles of stones
        for (int t = 2; t <= n; ++t) {
            for (int i = 0; i <= n-t; ++i) {
                for (int x = 2; x <= min(K, t); ++x) {
                    // fill res[t][i][j]
                    // divide into x1 and x-x1 piles
                    int mm = INT_MAX;
                    for (int t1 = 1; t1 < t; ++t1) {
                        for (int x1 = 1; x1 <= t1 && x1 < x && x-x1 <= t-t1; ++x1) {
                            if (res[t1][i][x1] >= 0 && res[t-t1][i+t1][x-x1] >= 0) {
                                mm = min(mm, res[t1][i][x1] + res[t-t1][i+t1][x-x1]);
                            }
                        }
                    }
                    int y = x == K ? 1 : x;
                    if (mm != INT_MAX) {
                        if (y == 1) {
                            mm += sum[i+t] - sum[i];
                        }
                        res[t][i][y] = mm;
                    } else {
                        res[t][i][y] = -1;
                    }
                }
            }
        }
        return res[n][0][1];
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> stones;
        int K;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{{3,2,4,1},2},
        //{{3,2,4,1},3},
        {{3,5,1,2,6},3},
        {{1},2}
    };

    vector< int > answers {
        20,
        -1,
        25,
        0
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = mergeStones::Solution().mergeStones(dp.stones, dp.K);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
