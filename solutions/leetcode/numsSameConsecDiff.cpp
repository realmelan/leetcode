// numsSameConsecDiff.cpp
// leetcode
//
// Created by  Song Ding on 6/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numsSameConsecDiff {
/*
// TODO: copy problem statement here
 967. Numbers With Same Consecutive Differences
 Medium
 
 80
 
 28
 
 Favorite
 
 Share
 Return all non-negative integers of length N such that the absolute difference between every two consecutive digits is K.
 
 Note that every number in the answer must not have leading zeros except for the number 0 itself. For example, 01 has one leading zero and is invalid, but 0 is valid.
 
 You may return the answer in any order.
 
 
 
 Example 1:
 
 Input: N = 3, K = 7
 Output: [181,292,707,818,929]
 Explanation: Note that 070 is not a valid number, because it has leading zeroes.
 Example 2:
 
 Input: N = 2, K = 1
 Output: [10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]
 
 
 Note:
 
 1 <= N <= 9
 0 <= K <= 9
 */

class Solution {
public:
    /**
     * iterative
     */
    vector<int> numsSameConsecDiff(int N, int K) {
        unordered_set<int> cur;
        for (int i = 1; i <= 9; ++i) {
            cur.insert(i);
        }
        
        for (int i = 1; i < N; ++i) {
            unordered_set<int> next;
            for (auto c : cur) {
                int d = c % 10;
                if (d + K < 10) {
                    next.insert(c*10+d+K);
                }
                if (d - K >= 0) {
                    next.insert(c*10+d-K);
                }
            }
            cur.swap(next);
        }
        if (N == 1) {
            cur.insert(0);
        }
        vector<int> res(cur.begin(), cur.end());
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int N;
        int K;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {3,7},
        {2,1},
        {1,0}
    };

    vector< vector<int> > answers {
        {181,292,707,818,929},
        {10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = numsSameConsecDiff::Solution().numsSameConsecDiff(dp.N, dp.K);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
