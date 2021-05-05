// jump.cpp
// leetcode
//
// Created by  Song Ding on 10/16/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace jump {
/*
// TODO: copy problem statement here
 45. Jump Game II
 Hard

 1522

 87

 Favorite

 Share
 Given an array of non-negative integers, you are initially positioned at the first index of the array.

 Each element in the array represents your maximum jump length at that position.

 Your goal is to reach the last index in the minimum number of jumps.

 Example:

 Input: [2,3,1,1,4]
 Output: 2
 Explanation: The minimum number of jumps to reach the last index is 2.
     Jump 1 step from index 0 to 1, then 3 steps to the last index.
 Note:

 You can assume that you can always reach the last index.
 */

class Solution {
public:
    /**
     * let k be the farthest index that can be reached after current jump,
     * and i be the farthest index that wes reached after last jump.
     * then to find next farthest index, just check from i+1 to k, and then update k accordingly
     *
     * This will TLE when nums is {1,1,1,...}
     */
    int jump(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        int i = -1, k = 0;
        while (k < n-1) {
            int r = k;
            ++res;
            for (int j = i+1; j <= k; ++j) {
                r = max(r, j+nums[j]);
                if (r >= n-1) {
                    return res;
                }
            }
            k = r;
        }
        return res;
    }
    
    /**
    Solution 1:
      breadth first search, using a set to keep track the positions
      after the k'th jump.
      
    Solution 2:
      always jump at a position that would enable another fartherest
      jump.
    */
    int jump2(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        int i = 0;
        while (i < n - 1) {
            int l = nums[i];
            if (i + l >= n - 1) {
                ++res;
                break;
            }
            int far = i;
            int jp = 0;
            for (int j = 1; j <= l; ++j) {
                int t = i + j + nums[i + j];
                if (t > far) {
                    far = t;
                    jp = j;
                }
            }
            
            ++res;
            i += jp;
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
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{0}},
        {{2,3,1,1,4}},
    };

    vector< int > answers {
        0,
        2
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = jump::Solution().jump(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
