// constructArray.cpp
// leetcode
//
// Created by  Song Ding on 10/18/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace constructArray {
/*
// TODO: copy problem statement here
 667. Beautiful Arrangement II
 Medium

 257

 548

 Favorite

 Share
 Given two integers n and k, you need to construct a list which contains n different positive integers ranging from 1 to n and obeys the following requirement:
 Suppose this list is [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.

 If there are multiple answers, print any of them.

 Example 1:
 Input: n = 3, k = 1
 Output: [1, 2, 3]
 Explanation: The [1, 2, 3] has three different positive integers ranging from 1 to 3, and the [1, 1] has exactly 1 distinct integer: 1.
 Example 2:
 Input: n = 3, k = 2
 Output: [1, 3, 2]
 Explanation: The [1, 3, 2] has three different positive integers ranging from 1 to 3, and the [2, 1] has exactly 2 distinct integers: 1 and 2.
 Note:
 The n and k are in the range 1 <= k < n <= 104.
 */

class Solution {
public:
    /**
     * let A[0] = 1, and A[2] = A[0]+k, A[3] = A[2]-(k-1), A[4] = A[3]+k-2, etc
     */
    vector<int> constructArray(int n, int k) {
        vector<int> res(n);
        res[0] = 1;
        int sign = 1;
        for (int i = 1; i < n; ++i) {
            if (k) {
                res[i] = res[i-1] + sign * k;
                --k;
                sign = -sign;
            } else {
                res[i] = i+1;
            }
        }
        return res;
    }
    
    /**
     * https://leetcode.com/problems/beautiful-arrangement-ii/discuss/106948/C%2B%2B-Java-Clean-Code-4-liner
     * interleave n,n-1, with 1,2, etc, to get different gaps.
     * the extra elements can be in incremental order with diff = 1.
     * so the interleave should create k-1 diff
     *
     * Also, the last sequence is always increasing, so make sure the 1,2,... would
     * end the first part. If starting with 1, then the interleave would create even diff; adding
     * diff of 1, it would result in odd diffs. So, when k is even, should add n at the start.
     */
    vector<int> constructArray2(int n, int k) {
        vector<int> res;
        for (int i = 1, j = n; i <= j;) {
            if (k > 1) {
                if (k%2) {
                    res.push_back(i++);
                } else {
                    res.push_back(j--);
                }
                --k;
            } else {
                // either ++i or --j
                res.push_back(i);
                ++i;
            }
        }
        return res;
    }
    
    vector<int> constructArray3(int n, int k) {
        vector<int> res;
        for (int i = 1, j = n; i <= j; ) {
            if (k > 1) {
                res.push_back(k-- % 2 ? i++ : j--);
            }
            else {
                res.push_back(i++);
            }
        }

        return res;
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
        {3,1},
        {3,2},
        {10,3},
        {10,4},
    };

    vector< vector<int> > answers {
        {1,2,3},
        {1,3,2},
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = constructArray::Solution().constructArray2(dp.n, dp.k);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
