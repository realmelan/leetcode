// findDuplicates.cpp
// leetcode
//
// Created by  Song Ding on 10/28/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findDuplicates {
/*
// TODO: copy problem statement here
 442. Find All Duplicates in an Array
 Medium

 1360

 125

 Favorite

 Share
 Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

 Find all the elements that appear twice in this array.

 Could you do it without extra space and in O(n) runtime?

 Example:
 Input:
 [4,3,2,7,8,2,3,1]

 Output:
 [2,3]
 */

class Solution {
public:
    /**
     * place all elements to their proper array position.
     */
    vector<int> findDuplicates(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> res;
        int i = 0;
        while (i < n) {
            if (nums[i] == i+1) {
                ++i;
                continue;
            }
            // nums[i] is already at its right position
            // it means nums[i] is duplicated.
            if (nums[nums[i]-1] == nums[i]) {
                res.insert(nums[i]);
                ++i;
            } else {
                // move value of nums[i] to its right position, and move the value
                // at the right position to i
                // and check position i again.
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        return vector<int>(res.begin(), res.end());
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
        {{4,3,2,7,8,2,3,1}},
    };

    vector< vector<int> > answers {
        {2,3},
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findDuplicates::Solution().findDuplicates(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
