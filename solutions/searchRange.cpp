//
//  searchRange.cpp
//  leetcode
//
//  Created by Song Ding on 7/29/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace searchRange {
/*
// TODO: copy problem statement here
 34. Find First and Last Position of Element in Sorted Array
 Medium

 3610

 152

 Add to List

 Share
 Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.

 Your algorithm's runtime complexity must be in the order of O(log n).

 If the target is not found in the array, return [-1, -1].

 Example 1:

 Input: nums = [5,7,7,8,8,10], target = 8
 Output: [3,4]
 Example 2:

 Input: nums = [5,7,7,8,8,10], target = 6
 Output: [-1,-1]
  

 Constraints:

 0 <= nums.length <= 10^5
 -10^9 <= nums[i] <= 10^9
 nums is a non decreasing array.
 -10^9 <= target <= 10^9
*/
class Solution {
public:
    // TODO: copy function signature here
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        vector<int> res{-1,-1};
        // find left bound
        while (l < r) {
            int m = l + (r-l) / 2;
            if (nums[m] >= target) {
                r = m;
            } else {
                l = m+1;
            }
        }
        if (nums[l] != target) {
            return res;
        }
        res[0] = l;
        
        // right bound
        r = nums.size() - 1;
        while (l < r) {
            int m = l + (r-l + 1) / 2;
            if (nums[m] <= target) {
                l = m; // if l=m is used, then m = (l+r+1)/2, so that m is moving even if l=m
            } else {
                r = m-1;
            }
        }
        res[1] = l;
        return res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nums;
        int target;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{5,7,7,8,8,10},8},
        {{5,7,7,8,8,10},6},
    };
    // TODO: provide expected results here
    vector<vector<int>> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = searchRange::Solution().searchRange(dp.nums, dp.target);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
