// firstMissingPositive.cpp
// leetcode
//
// Created by  Song Ding on 4/1/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

/**
 41. First Missing Positive
 Hard

 2151

 652

 Favorite

 Share
 Given an unsorted integer array, find the smallest missing positive integer.

 Example 1:

 Input: [1,2,0]
 Output: 3
 Example 2:

 Input: [3,4,-1,1]
 Output: 2
 Example 3:

 Input: [7,8,9,11,12]
 Output: 1
 Note:

 Your algorithm should run in O(n) time and uses constant extra space.
 */
namespace firstMissingPositive {

class Solution {
public:
    /**
     https://leetcode.com/problems/first-missing-positive/discuss/17071/My-short-c%2B%2B-solution-O(1)-space-and-O(n)-time
     */
    int firstMissingPositive(vector<int>& nums) {
        int counter = 0;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
                cout << "swap(nums[" << i << "](" << nums[i] << ") with nums[" << nums[i]-1 << "](" << nums[nums[i] - 1] << ")\n";
                ++counter;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        cout << "# of swap = " << counter << endl;
        return n + 1;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> nums{8,7,6,5,4,3,2,1};
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = firstMissingPositive::Solution().firstMissingPositive(nums);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
