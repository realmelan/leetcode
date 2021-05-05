// findDerrangement.cpp
// leetcode
//
// Created by  Song Ding on 10/21/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findDerrangement {
/*
// TODO: copy problem statement here
 634. Find the Derangement of An Array

 In combinatorial mathematics, a derangement is a permutation of the elements of a set, such that no element appears in its original position.

 There's originally an array consisting of n integers from 1 to n in ascending order, you need to find the number of derangement it can generate.

 Also, since the answer may be very large, you should return the output mod 10^9 + 7.

 Example 1:

 Input: 3
 Output: 2
 Explanation: The original array is [1,2,3]. The two derangements are [2,3,1] and [3,1,2].
 Note:
 n is in the range of [1, 106].
 */

class Solution {
public:
    /**
     * let dp[i] = # of dearrangement for i, then to get dp[i+1],
     * dp[i+1]=# of all permutations - # of permutations that has at least one position equals its value.
     * dp[i+1]=(i+1)! - C(i+1,1)*dp[i] - C(i+1,2)*dp[i+1-2]-C(i+1,3)*DP[I+1-3]...
     * Note, dp[0]=1, dp[1] = 0, dp[2] = 1;
     */
    int findDerrangement2(int n) {
        static const int mod = 1000000007;
        vector<int> dp(n+1);
        dp[0]=1;
        dp[1]=0;
        long all = 1;
        for (int i = 2; i <= n; ++i) {
            all *= i;
            all %= mod;
            dp[i] = all;
            // coefficient will be too large!
            unsigned long long co = 1;
            for (int j = 1; j <= i; ++j) {
                co *= (i-j+1);
                co /= j;
                //cout << co << endl;
                dp[i] += mod - (co * dp[i-j]) % mod;
                dp[i] %= mod;
            }
        }
        return dp[n];
    }
    /**
     * https://en.wikipedia.org/wiki/Derangement
     * Suppose that there are n people who are numbered 1, 2, ..., n. Let there be n hats also numbered 1, 2, ..., n. We have to find the number of ways in which no one gets the hat having the same number as their number. Let us assume that the first person takes hat i. There are n − 1 ways for the first person to make such a choice. There are now two possibilities, depending on whether or not person i takes hat 1 in return:

     Person i does not take the hat 1. This case is equivalent to solving the problem with n − 1 persons and n − 1 hats: each of the remaining n − 1 people has precisely 1 forbidden choice from among the remaining n − 1 hats (i's forbidden choice is hat 1).
     Person i takes the hat 1. Now the problem reduces to n − 2 persons and n − 2 hats.
     */
    int findDerrangement(int n) {
        vector<int> dp(n+1,0);
        dp[1] = 0;
        dp[2] = 1;
        for (int i = 3; i <= n; ++i) {
            dp[i] = (dp[i-1]+dp[i-2])*(i-1)%1000000007;
        }
        return dp[n];
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int n;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {3},
        {4},
        {5},
        {6},
        {7},
        //{106},
    };

    vector< int > answers {
        2,
        9,
        44,
        265,
        1854
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findDerrangement::Solution().findDerrangement2(dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
