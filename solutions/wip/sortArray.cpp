// sortArray.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace sortArray {
/*
// TODO: copy problem statement here
 912. Sort an Array
 Medium
 
 48
 
 59
 
 Favorite
 
 Share
 Given an array of integers nums, sort the array in ascending order.
 
 
 
 Example 1:
 
 Input: [5,2,3,1]
 Output: [1,2,3,5]
 Example 2:
 
 Input: [5,1,1,2,0,0]
 Output: [0,0,1,1,2,5]
 
 
 Note:
 
 1 <= A.length <= 10000
 -50000 <= A[i] <= 50000
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    vector<int> sortArray(vector<int>& nums) {
        return {};
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nums;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{5,2,3,1}},
        {{5,1,1,2,0,0}}
    };

    vector< vector<int> > answers {
        {1,2,3,5},
        {0,0,1,1,2,5}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = sortArray::Solution().sortArray(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
