// maxSlidingWindow.cpp
// leetcode
//
// Created by  Song Ding on 10/4/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxSlidingWindow {
/*
// TODO: copy problem statement here
 239. Sliding Window Maximum
 Hard

 2130

 124

 Favorite

 Share
 Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Return the max sliding window.

 Example:

 Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
 Output: [3,3,5,5,6,7]
 Explanation:

 Window position                Max
 ---------------               -----
 [1  3  -1] -3  5  3  6  7       3
  1 [3  -1  -3] 5  3  6  7       3
  1  3 [-1  -3  5] 3  6  7       5
  1  3  -1 [-3  5  3] 6  7       5
  1  3  -1  -3 [5  3  6] 7       6
  1  3  -1  -3  5 [3  6  7]      7
 Note:
 You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty array.

 Follow up:
 Could you solve it in linear time?
 */

class Solution {
public:
    /**
     * an obvious solution is monotonic queue of value+index
     * Here is another different O(n) solution, that is:
     * https://leetcode.com/problems/sliding-window-maximum/discuss/65881/O(n)-solution-in-Java-with-two-simple-pass-in-the-array
     * divide the array into blocks of k, and find accumulated left/right max in the boundary of block.
     */
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        if (n <= 0) {
            return {};
        }
        vector<int> res(n-k+1, 0);
        vector<int> lm(n+1, INT_MIN), rm(n+1, INT_MIN);
        for (int i = 0; i < n; ++i) {
            lm[i] = i % k == 0 ? nums[i] : max(lm[i-1], nums[i]);
            int j = n - i - 1;
            rm[j] = j % k == 0 ? nums[j] : max(rm[j+1], nums[j]);
        }
        for (int i = 0; i <= n-k; ++i) {
            res[i] = max(lm[i+k-1], rm[i]);
        }
        return res;
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
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,3,-1,-3,5,3,6,7},3}
        
    };

    vector< vector<int> > answers {
        {3,3,5,5,6,7},
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxSlidingWindow::Solution().maxSlidingWindow(dp.nums, dp.k);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
