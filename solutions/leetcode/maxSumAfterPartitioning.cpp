// maxSumAfterPartitioning.cpp
// leetcode
//
// Created by  Song Ding on 5/31/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxSumAfterPartitioning {
/*
// TODO: copy problem statement here
 1043. Partition Array for Maximum Sum
 Medium
 
 136
 
 12
 
 Favorite
 
 Share
 Given an integer array A, you partition the array into (contiguous) subarrays of length at most K.  After partitioning, each subarray has their values changed to become the maximum value of that subarray.
 
 Return the largest sum of the given array after partitioning.
 
 
 
 Example 1:
 
 Input: A = [1,15,7,9,2,5,10], K = 3
 Output: 84
 Explanation: A becomes [15,15,15,9,10,10,10]
 
 
 Note:
 
 1 <= K <= A.length <= 500
 0 <= A[i] <= 10^6
 */

class Solution {
public:
    /**
     * DP:
     * let mp(i) = max sum after partition for A[0..i],
     * then mp(i) = max(mp(j) + (i-j)* max(A[j+1..i])) for all j in i-K+1 to i.
     *
     * Note, max(A[j+1..i]) can be updated each round iterating from i to i-K+1.
     */
    int maxSumAfterPartitioning(vector<int>& A, int K) {
        int n = A.size();
        vector<int> mp(n, 0);
        int i = 0;
        int me = 0;
        for (; i < K; ++i) {
            me = max(me, A[i]);
            mp[i] = me * (i+1);
        }
        
        for (; i < n; ++i) {
            int me = 0;
            int cmp = 0;
            for (int j = i; j > i - K; --j) {
                me = max(me, A[j]);
                cmp = max(cmp, mp[j-1] + me * (i-j+1));
            }
            mp[i] = cmp;
        }
        return mp[n-1];
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> A;
        int K;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,15,7,9,2,5,10}, 3},
        {{1,4,1,5,7,3,6,1,9,9,3}, 4}
    };

    vector< int > answers {
        84,
        83
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxSumAfterPartitioning::Solution().maxSumAfterPartitioning(dp.A, dp.K);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
