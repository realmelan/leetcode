// makesquare.cpp
// leetcode
//
// Created by  Song Ding on 9/29/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace makesquare {
/*
// TODO: copy problem statement here
 473. Matchsticks to Square
 Medium

 376

 42

 Favorite

 Share
 Remember the story of Little Match Girl? By now, you know exactly what matchsticks the little match girl has, please find out a way you can make one square by using up all those matchsticks. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.

 Your input will be several matchsticks the girl has, represented with their stick length. Your output will either be true or false, to represent whether you could make one square using all the matchsticks the little match girl has.

 Example 1:
 Input: [1,1,2,2,2]
 Output: true

 Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
 Example 2:
 Input: [3,3,3,3,4]
 Output: false

 Explanation: You cannot find a way to form a square with all the matchsticks.
 Note:
 The length sum of the given matchsticks is in the range of 0 to 10^9.
 The length of the given matchstick array will not exceed 15.
 */

class Solution {
public:
    bool makesquare2(vector<int>& nums) {
        int s = accumulate(begin(nums), end(nums), 0);
        if (s%4) {
            return false;
        }
        int edge = s/4;
        sort(begin(nums), end(nums), std::greater<int>());
        if (nums.front() > edge) {
            return false;
        }
        
        return dfs(0, edge, 0, 0, nums);
    }
    bool dfs(int len, int edge, int k, int s, vector<int>& nums) {
        if (len == edge) {
            if (k == 2) {
                return true;
            } else {
                return dfs(0, edge, k+1, 0, nums);
            }
        }
        for (int i = s; i < nums.size(); ++i) {
            if (nums[i] && nums[i] + len <= edge) {
                int t = nums[i];
                nums[i] = 0;
                if (dfs(len+t, edge, k, i+1, nums)) {
                    return true;
                }
                nums[i] = t;
            }
        }
        return false;
    }
    /**
     * dfs:
     * create one side at a time!
     */
    bool makesquare(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end(), [](int a, int b){return a > b;});
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 4 || sum == 0) {
            return false;
        }
        int target = sum / 4;
        for (auto i : nums) {
            if (i > target) {
                return false;
            }
        }
        vector<int> used(n, false);
        return dfs(0, 0, used, nums, 0, target);
    }
    bool dfs(int i, int k, vector<int>& used, vector<int>& nums, int side, int target) {
        if (k == 4) {
            return true;
        }
        if (side == target) {
            return dfs(0, k+1, used, nums, 0, target);
        }
        for (int j = i; j < nums.size() && side + nums[j] <= target; ++j) {
            if (!used[j]) {
                used[j] = true;
                if (dfs(j+1, k, used, nums, side+nums[j], target)) {
                    return true;
                }
                used[j] = false;
            }
        }
        return false;
    }
    /**
     * DFS:
     * use a vector<int> sums to represent each side
     * sort nums into descending order, so that we try the longest match first, which would
     * reduce the run time of finding a group for the longest match (few matches), and thus
     * total run time.
     *
     * Another optimization: if a previous partial sum doesn't work, then current partial will not
     * work neither. So during finding which side current match should go, check whether current
     * group has same side length as previous sides. If so, current match doesn't work previous
     * side length, and thus not work with current side length.
     */
    bool makesquare_slow(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 4 || sum == 0) {
            return false;
        }
        int target = sum / 4;
        for (auto i : nums) {
            if (i > target) {
                return false;
            }
        }
        vector<int> sides(4, target);
        sides[0] -= nums[0];
        return dfs(1, nums, sides);
    }

private:
    bool dfs(int i, vector<int>& nums, vector<int>& sides) {
        if (i == nums.size() && sides == vector<int>{0,0,0,0}) {
            return true;
        } else if (i >= nums.size()) {
            return false;
        }
        for (int j = 0; j < 4; ++j) {
            if (nums[i] <= sides[j]) {
                sides[j] -= nums[i];
                if (dfs(i+1, nums, sides)) {
                    return true;
                }
                sides[j] += nums[i];
            }
        }
        return false;
    }
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
        {{1,1,2,2,2}},
        {{3,3,3,3,4}},
    };

    vector< bool > answers {
        true,
        false,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = makesquare::Solution().makesquare2(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
