// maxSubarraySumCircular.cpp
// leetcode
//
// Created by  Song Ding on 3/11/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxSubarraySumCircular {

class Solution {
public:
    /**
     * For each i in 0 to n-1, let mfs(i) = max sub array
     * sum from subarray A[0 to i]
     * let mie(i) = max sub array sum for subarray A[i, n-1].
     * for each i in 0 to n-1, let mss(i) = max circular subarray
     * sum ending at A[i].
     * then mss(i) = max(mfs(i), subSum(0 to i) + mie(i+1))
     *
     * The result is the max(mss(i) for i from 0 to n -1).
     */
    int maxSubarraySumCircular(vector<int>& A) {
        int n = A.size();
        if (n <= 0) {
            return 0;
        }
        
        int t = 0;
        vector<int> subSum(n, 0);
        for (int i = 0; i < n; ++i) {
            subSum[i] = (t += A[i]);
        }
        
        vector<int> maxSubSum{A[0]};
        for (int i = 1; i < n; ++i) {
            if (maxSubSum[i-1] > 0) {
                maxSubSum.push_back(maxSubSum.back() + A[i]);
            } else {
                maxSubSum.push_back(A[i]);
            }
        }
        
        t = A[n - 1];
        vector<int> maxReverseSubSum(n, 0);
        maxReverseSubSum[n-1] = A[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            maxReverseSubSum[i] = maxReverseSubSum[i+1];
            t += A[i];
            if (t > maxReverseSubSum[i]) {
                maxReverseSubSum[i] = t;
            }
        }
        
        int res = maxSubSum[n - 1];
        for (int i = 0; i < n - 1; ++i) {
            int t = subSum[i] + maxReverseSubSum[i + 1];
            if (t < maxSubSum[i]) {
                t = maxSubSum[i];
            }
            if (res < t) {
                res = t;
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<int> > A {
        {1,-2,3,-2},
        {5,-3,5},
        {3,-1,2,-1},
        {3,-2,2,-3},
        {-2,-3,-1}
    };

    vector< int  > answers {
        3,
        10,
        4,
        3,
        -1
    };
    int i = 4;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = maxSubarraySumCircular::Solution().maxSubarraySumCircular(A[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
