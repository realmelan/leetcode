// partitionDisjoint.cpp
// leetcode
//
// Created by  Song Ding on 10/7/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace partitionDisjoint {

class Solution {
public:
    /**
     * for each position, find the max value on its left
     * and min value on its right.
     * find the first position from left that the max value
     * is smaller than the min value.
     */
    int partitionDisjoint(vector<int>& A) {
        deque<int> maxq;
        vector<int> maxs;
        for (int i = 0; i < A.size(); ++i) {
            while (maxq.size() && maxq.back() <= A[i]) {
                maxq.pop_back();
            }
            maxq.push_back(A[i]);
            maxs.push_back(maxq.front());
        }
        
        deque<int> minq;
        vector<int> mins;
        for (int i = A.size() - 1; i >= 0; --i) {
            while (minq.size() && minq.back() >= A[i]) {
                minq.pop_back();
            }
            minq.push_back(A[i]);
            mins.insert(mins.begin(), minq.front());
        }
        
        int i = 1;
        for (; i < A.size(); ++i) {
            if (maxs[i - 1] < mins[i]) {
                break;
            }
        }
        return i;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> A {
        5,0,3,8,6
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = partitionDisjoint::Solution().partitionDisjoint(A);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
