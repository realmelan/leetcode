// minDeletionSize.cpp
// leetcode
//
// Created by  Song Ding on 3/26/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minDeletionSize {

class Solution {
public:
    /**
     * start from the 1st column, test whether the letters
     * at current column is in lex order. If not, then remove
     * current column; if in lex order, then return the number
     * of columns that have been removed.
     */
    int minDeletionSize(vector<string>& A) {
        int n = A.size();
        int N = A[0].size();
        int res = 0;
        int idx = 0;
        vector<pair<int,int>> groups{{0, n-1}};
        while (idx < N) {
            vector<pair<int,int>> next;
            bool badIdx = false;
            for (const auto& p : groups) {
                int last = p.first;
                for (int i = p.first + 1; i <= p.second; ++i) {
                    if (A[i][idx] < A[i-1][idx]) {
                        badIdx = true;
                        break;
                    }
                    
                    if (A[i][idx] != A[last][idx]) {
                        if (i - last > 1) {
                            next.push_back({last, i - 1});
                        }
                        last = i;
                    }
                }
                if (last < p.second) {
                    next.push_back({last, p.second});
                }
                if (badIdx) {
                    ++res;
                    break;
                }
            }
            if (!badIdx) {
                groups.swap(next);
            }
            ++idx;
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<string> > A {
        {"ca","bb","ac"},
        {"xc", "yb", "za"},
        {"acdaxx","adcbec","aeebdd","affcxx","bxxxxx","cfaeab","cebebc"},
        {"koccmoezl","hbccayhbd"}
    };

    vector< int  > answers {
        1,
        0,
        3,
        3
    };
    int i = 3;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = minDeletionSize::Solution().minDeletionSize(A[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
