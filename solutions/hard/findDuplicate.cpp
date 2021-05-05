// findDuplicate.cpp
// leetcode
//
// Created by  Song Ding on 6/18/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findDuplicate {
/*
// TODO: copy problem statement here
 287. Find the Duplicate Number
 Medium
 
 2508
 
 279
 
 Favorite
 
 Share
 Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.
 
 Example 1:
 
 Input: [1,3,4,2,2]
 Output: 2
 Example 2:
 
 Input: [3,1,3,4,2]
 Output: 3
 Note:
 
 You must not modify the array (assume the array is read only).
 You must use only constant, O(1) extra space.
 Your runtime complexity should be less than O(n2).
 There is only one duplicate number in the array, but it could be repeated more than once.
 */

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        return findDuplicate_place(nums);
    }
    int findDuplicate_place(vector<int>& nums) {
        int n = nums.size()-1, i = 0, k = n+1;
        for (; i <= n && k>= 0; ++i) {
            while (nums[i] != i && k--) {
                swap(nums[i], nums[nums[i]]);
            }
        }
        return nums[i];
    }
    /**
     * http://keithschwarz.com/interesting/code/?dir=find-duplicate
     * Here is a summary:
     * An explanation about finding the entry point part.
     First assume when fast and slow meet, slow has moved a steps, and fast has moved 2a steps. They meet in the circle, so the difference a must be a multiple of the length of the circle.
     Next assume the distance between beginning to the entry point is x, then we know that the slow has traveled in the circle for a-x steps.
     How do we find the entry point? Just let slow move for another x steps, then slow will have moved a steps in the circle, which is a multiple of length of the circle.
     So we start another pointer at the beginning and let slow move with it. Remember x is the distance between beginning to the entry point, after x steps, both pointer will meet at the entry of circle.
     *
     * we can start from 0 without -1, or start from n with -1.
     */
    int findDuplicate_cycledetect(vector<int>& nums) {
        int n = nums.size();
        int slow = nums[n-1];
        int fast = nums[nums[n-1]-1];
        while (slow != fast) {
            slow = nums[slow-1];
            fast = nums[nums[fast-1]-1];
        }
        int finder = n;
        while (finder != slow) {
            finder = nums[finder-1];
            slow = nums[slow-1];
        }
        return finder;
    }
    /**
     * Use binary search to find a mid number such that # of elements that is <= mid > mid
     * then mid is the upper bound value that has duplicate. We need to count equal numbers.
     */
    int findDuplicate_binarysearch(vector<int>& nums) {
        int lb = INT_MAX;
        int ub = INT_MIN;
        for (auto i : nums) {
            lb = min(lb, i);
            ub = max(ub, i);
        }
        
        while (lb < ub) {
            int mid = lb + (ub - lb) / 2;
            int eq = 0;
            int lt = 0;
            for (auto i : nums) {
                if (i < mid) {
                    ++lt;
                } else if (i == mid) {
                    ++eq;
                }
            }
            if (eq > 1) {
                return mid;
            }
            if (lt + eq > mid) {
                ub = mid;
            } else {
                lb = mid + 1;
            }
        }
        return lb;
    }
    /**
     * This seems O(n^2)
     * at i-th step:
     *   start at position i, and walk to next position j, such that nums[i] = j;
     *   mark start position and start value
     *   at most n-i steps are allowed; or if position matches starting position, or
     *   value matches start value (then result is this start value).
     */
    int findDuplicate2(vector<int>& nums) {
        int n = nums.size() - 1;
        for (int i = 0; i < n; ++i) {
            int t = n - i;
            int j = 0;
            int p = nums[i];
            while (j < t && p != i && nums[p] != nums[i]) {
                p = nums[p];
                ++j;
            }
            if (p != i && nums[p] == nums[i]) {
                return nums[i];
            }
        }
        return nums[n];
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
        {{1,3,4,2,2}},
        {{3,1,3,4,2}}
    };

    vector< int > answers {
        2,
        3
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findDuplicate::Solution().findDuplicate(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
