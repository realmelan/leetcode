// containsNearbyAlmostDuplicate.cpp
// leetcode
//
// Created by  Song Ding on 11/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace containsNearbyAlmostDuplicate {
/*
// TODO: copy problem statement here
 220. Contains Duplicate III
 Medium

 806

 806

 Favorite

 Share
 Given an array of integers, find out whether there are two distinct indices i and j in the array such that the absolute difference between nums[i] and nums[j] is at most t and the absolute difference between i and j is at most k.

 Example 1:

 Input: nums = [1,2,3,1], k = 3, t = 0
 Output: true
 Example 2:

 Input: nums = [1,0,1,1], k = 1, t = 2
 Output: true
 Example 3:

 Input: nums = [1,5,9,1,5,9], k = 2, t = 3
 Output: false
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        return false;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nums;
        int k;
        int t;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {}
    };

    vector< bool > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = containsNearbyAlmostDuplicate::Solution().containsNearbyAlmostDuplicate(dp.nums, dp.k, dp.t);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
