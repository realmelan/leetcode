// maxWidthRamp.cpp
// leetcode
//
// Created by  Song Ding on 5/6/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxWidthRamp {

class Solution {
public:
    int maxWidthRamp1(vector<int>& A) {
        int res = 0;
        int n = A.size();
        map<int, int> inc;
        for (int i = n - 1; i >= 0; --i) {
            if (inc.empty() || inc.rbegin()->first < A[i]) {
                inc.insert(make_pair(A[i], i));
            } else {
                auto it = inc.lower_bound(A[i]);
                if (it->second - i > res) {
                    res = it->second - i;
                }
            }
        }
        return res;
    }
    int maxWidthRamp(vector<int>& A) {
        int res = 0;
        int n = A.size();
        stack<int> s;
        for (int i = 0; i < n; ++i) {
            if (s.empty() || A[s.top()] > A[i]) {
                s.push(i);
            }
        }
        
        for (int i = n - 1; i >= 0; --i) {
            while (s.size() && A[s.top()] <= A[i]) {
                if (res < i - s.top()) {
                    res = i - s.top();
                }
                s.pop();
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
        {6,0,8,2,1,5},
        {9,8,1,0,1,9,4,0,4,1},
        {1,0}
    };

    vector< int  > answers {
        4,
        7,
        0
    };
    int i = 2;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = maxWidthRamp::Solution().maxWidthRamp(A[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
