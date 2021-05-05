// fourSum.cpp
// leetcode
//
// Created by  Song Ding on 6/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace fourSum {
/*
// TODO: copy problem statement here
 18. 4Sum
 Medium
 
 1092
 
 218
 
 Favorite
 
 Share
 Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
 
 Note:
 
 The solution set must not contain duplicate quadruplets.
 
 Example:
 
 Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.
 
 A solution set is:
 [
 [-1,  0, 0, 1],
 [-2, -1, 1, 2],
 [-2,  0, 0, 2]
 ]
 */

class Solution {
public:
    /**
     * DFS
     *
     * method 2:
     *   3 loop: outside for loop;
     *   1 inner loop of 1st and last element
     *   for the 2 outside loop, some pruning can be done by check the possible minimum sum and maximum sum.
     */
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        int n = nums.size();
        if (n > 0) {
            // make quadruplets unique
            sort(nums.begin(), nums.end());
            int t = 0;
            if (nums[0] < 0) {
                t = -nums[0];
                for (auto& i : nums) {
                    i += t;
                }
                target += (t<<2);
            }
            
            vector<int> path;
            vector<vector<int>> tres;
            dfs(nums, 0, target, path, tres);
            
            int rn = tres.size();
            if (rn > 0) {
                sort(tres.begin(), tres.end());
                res.push_back(tres[0]);
                for (auto&k : res.back()) {
                    k -= t;
                }
                for (int i = 1; i < rn; ++i){
                    if (tres[i-1] != tres[i]) {
                        res.push_back(tres[i]);
                        for (auto&k : res.back()) {
                            k -= t;
                        }
                    }
                }
            }
        }
        return res;
    }

private:
    void dfs(vector<int>& nums, int start, int target, vector<int>& path, vector<vector<int>>& res) {
        if (path.size() == 4 && target == 0) {
            res.push_back(path);
            return;
        }
        
        int n = nums.size();
        if (start >= n || nums[start] > target || path.size() >= 4) {
            return;
        }
        
        for (int i = start; i < n && nums[i] <= target; ++i) {
            path.push_back(nums[i]);
            dfs(nums, i+1, target - nums[i], path, res);
            path.pop_back();
        }
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nums;
        int target;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1, 0, -1, 0, -2, 2},0}
    };

    vector< vector<vector<int>> > answers {
        {
            {-1,  0, 0, 1},
            {-2, -1, 1, 2},
            {-2,  0, 0, 2}
        }
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = fourSum::Solution().fourSum(dp.nums, dp.target);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
