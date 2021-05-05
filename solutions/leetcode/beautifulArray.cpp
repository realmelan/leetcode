// beautifulArray.cpp
// leetcode
//
// Created by  Song Ding on 5/27/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace beautifulArray {
/*
// TODO: copy problem statement here
 932. Beautiful Array
 Medium
 
 168
 
 217
 
 Favorite
 
 Share
 For some fixed N, an array A is beautiful if it is a permutation of the integers 1, 2, ..., N, such that:
 
 For every i < j, there is no k with i < k < j such that A[k] * 2 = A[i] + A[j].
 
 Given N, return any beautiful array A.  (It is guaranteed that one exists.)
 
 
 
 Example 1:
 
 Input: 4
 Output: [2,1,4,3]
 Example 2:
 
 Input: 5
 Output: [3,1,2,5,4]
 
 
 Note:
 
 1 <= N <= 1000
 */

class Solution {
public:
    /**
     * Let all odd numbers in [0,N] be the first half,
     * and the even ones the other. Then only pairs within
     * each half may produce possible bad pairs.
     *
     * Now, for the odd half, add 1 to all numbers by 1, and divide
     * each by 2, then it becames [1..(n+1)/2]
     * for the even half, divide each by 2, it also becames [1..n/2]
     */
    vector<int> beautifulArray(int N) {
        if (N <= 1) {
            return {1};
        } else if (N <= 2) {
            return {1,2};
        } else {
            vector<int> res;
            vector<int> odd = beautifulArray((N+1)/2);
            for (auto i : odd) {
                res.push_back((i << 1) - 1);
            }
            vector<int> even = beautifulArray(N/2);
            for (auto i : even) {
                res.push_back(i << 1);
            }
            return res;
        }
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int N;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {1000}
    };

    vector< vector<int> > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = beautifulArray::Solution().beautifulArray(dp.N);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
