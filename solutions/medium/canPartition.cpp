// canPartition.cpp
// leetcode
//
// Created by  Song Ding on 10/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace canPartition {
/*
// TODO: copy problem statement here
 416. Partition Equal Subset Sum
 Medium

 1506

 40

 Favorite

 Share
 Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

 Note:

 Each of the array element will not exceed 100.
 The array size will not exceed 200.
  

 Example 1:

 Input: [1, 5, 11, 5]

 Output: true

 Explanation: The array can be partitioned as [1, 5, 5] and [11].
  

 Example 2:

 Input: [1, 2, 3, 5]

 Output: false

 Explanation: The array cannot be partitioned into equal sum subsets.
 */

class Solution {
public:
    /**
     * DP is straight forward:
     * let dp[i][j] = true if sum j can be achieved for nums[0..i].
     * then dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]]
     * basiscally I check all possible sums for nums[0..i].
     *
     * Here is more simple but subtle way: use bit shift to add nums[i] to all
     * sums based on nums[0..n-1].
     */
    bool canPartition(vector<int>& nums) {
        const int MAX_VAL = 100;
        const int MAX_SIZE = 200;
        bitset<MAX_VAL * MAX_SIZE + 1> bits(1);
        int sum = 0;
        for (auto i : nums) {
            sum += i;
            // <<i means adding i to all previous sums
            // | bits itself means not adding i to previous sums
            // or the above two, means all sums with/without i.
            bits |= (bits << i);
        }
        return !(sum%2) && bits[sum/2];
    }
    /**
     same as bitset shift but it uses vector<bool>
     dp records all possible sums.
     */
    bool canPartition_dp(vector<int>& nums) {
        int sum = accumulate(begin(nums), end(nums), 0);
        if (sum % 2 == 0) {
            vector<bool> dp(sum+1, false);
            dp[0] = true;
            for (auto k : nums) {
                for (int i = sum; i >= 0; --i) {
                    if (dp[i]) {
                        dp[i+k] = true;
                    }
                }
            }
            
            return dp[sum/2];
        }
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
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1, 5, 11, 5}},
        {{1, 2, 3, 5}},
    };

    vector< bool > answers {
        true,
        false,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = canPartition::Solution().canPartition(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
