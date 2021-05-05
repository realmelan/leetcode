// kInversePairs.cpp
// leetcode
//
// Created by  Song Ding on 9/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace kInversePairs {
/*
// TODO: copy problem statement here
 629. K Inverse Pairs Array
 Hard
 
 228
 
 73
 
 Favorite
 
 Share
 Given two integers n and k, find how many different arrays consist of numbers from 1 to n such that there are exactly k inverse pairs.
 
 We define an inverse pair as following: For ith and jth element in the array, if i < j and a[i] > a[j] then it's an inverse pair; Otherwise, it's not.
 
 Since the answer may be very large, the answer should be modulo 109 + 7.
 
 Example 1:
 
 Input: n = 3, k = 0
 Output: 1
 Explanation:
 Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pair.
 
 
 Example 2:
 
 Input: n = 3, k = 1
 Output: 2
 Explanation:
 The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
 
 
 Note:
 
 The integer n is in the range [1, 1000] and k is in the range [0, 1000].
 */

class Solution {
public:
    int kInversePairs2(int n, int k) {
        // dp[i][k] = dp[i-1][]
        vector<vector<int>> dp(n+1, vector<int>(k+1, 0));
        dp[1][0] = 1;
        for (int i = 2; i <= n; ++i) { // # of integers
            dp[i][0] = 1;
            long sum = dp[i-1][0];
            for (int j = 1; j <= k && j <= (i-1)*i/2; ++j) { // # of reverse pairs
                sum += dp[i-1][j];
                if (j-i>=0) {
                    sum -= dp[i-1][j-i];
                }
                dp[i][j] = sum % 1000000007;
            }
        }
        return dp[n][k];
    }
    /**
     * let f(i,k) = # of array for 1 to i with k inverse pairs.
     * then f(i,k)=f(i-1,k)+f(i-1,k-1)+...+f(i-1,0), where for f(i-1,j)
     * we put i at i-k+1 position.
     */
    int kInversePairs(int n, int k) {
        if (k > n*(n-1)/2) {
            return 0;
        }
        vector<long> dp(k+1,0);
        for (int i = 1; i <= n; ++i) {
            vector<long> next(k+1, 0);
            next[0] = 1;
            long sum = dp[0];
            for (int j = 1; j <= k&&j<=i*(i-1)/2; ++j) {
                //for (int K = max(0, j-i+1); K <= j; ++K) {
                //    next[j] += dp[K];
                //}
                //next[j] %= 1000000007;
                
                sum += dp[j];
                if (j-i>= 0) {
                    sum += (1000000007 - dp[j-i]);
                }
                sum %= 1000000007;
                next[j] = sum;
            }
            dp.swap(next);
        }
        return dp[k];
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int n;
        int k;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{3,0},
        //{3,1},
        {3,3},
    };

    vector< int > answers {
        1,
        2,
        1,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = kInversePairs::Solution().kInversePairs2(dp.n, dp.k);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
