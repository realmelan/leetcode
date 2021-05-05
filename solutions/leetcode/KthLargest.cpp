//
//  KthLargest.cpp
//  leetcode
//
//  Created by  Song Ding on 11/15/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace findKthLargest {
    class Solution {
    public:
        /**
         The optimal solution would cost O(n). However it is quite
         difficult to implement.
         
         A quick-sort style way can be used, to divide the entire
         array into two parts, with the first parts no less than
         the second. Based on the numbers of either part, and descend
         into one of them with updated k.
         
         Always use the first element as pivot.
         */
        int findKthLargest(vector<int>& nums, int k) {
            return recur(nums, 0, nums.size(), k);
        }
    private:
        int recur(vector<int>& nums, int start, int len, int k) {
            if (k == 1 && len == 1) {
                return nums[start];
            }
            
            int pivot = nums[start];
            int i = start + 1;
            int j = start + len - 1;
            while (i < j) {
                while (i < j && nums[i] >= pivot) {
                    ++i;
                }
                if (i >= j) {
                    break;
                }
                while (i < j && nums[j] < pivot) {
                    --j;
                }
                if (i >= j) {
                    break;
                }
                
                if (i < j) {
                    int t = nums[i];
                    nums[i] = nums[j];
                    nums[j] = t;
                }
            } //end split
            // check pivot and the i-th
            if (i < len && pivot < nums[i]) {
                nums[start] = nums[i];
                nums[i] = pivot;
            }
            // swap nums[start] and nums[i - 1];
            int frontCount = i - start;
            int backCount = len - frontCount;
            
            if (k <= frontCount) {
                int t = nums[start];
                nums[start] = nums[i - 1];
                nums[i - 1] = t;
                return recur(nums, start, frontCount, k);
            } else {
                return recur(nums, i, backCount, k - frontCount);
            }
        }
    };
}
/*
int main() {
    vector<int> nums{-1,2,0};
    int k = 2;
    cout << findKthLargest::Solution().findKthLargest(nums, k) << endl;
    return 0;
}
 */
