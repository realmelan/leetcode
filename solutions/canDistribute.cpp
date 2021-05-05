//
//  canDistribute.cpp
//  leetcode
//
//  Created by Song Ding on 2/24/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace canDistribute {
/*
// TODO: copy problem statement here
 1655. Distribute Repeating Integers
 Hard

 102

 11

 Add to List

 Share
 You are given an array of n integers, nums, where there are at most 50 unique values in the array. You are also given an array of m customer order quantities, quantity, where quantity[i] is the amount of integers the ith customer ordered. Determine if it is possible to distribute nums such that:

 The ith customer gets exactly quantity[i] integers,
 The integers the ith customer gets are all equal, and
 Every customer is satisfied.
 Return true if it is possible to distribute nums according to the above conditions.

  

 Example 1:

 Input: nums = [1,2,3,4], quantity = [2]
 Output: false
 Explanation: The 0th customer cannot be given two different integers.
 Example 2:

 Input: nums = [1,2,3,3], quantity = [2]
 Output: true
 Explanation: The 0th customer is given [3,3]. The integers [1,2] are not used.
 Example 3:

 Input: nums = [1,1,2,2], quantity = [2,2]
 Output: true
 Explanation: The 0th customer is given [1,1], and the 1st customer is given [2,2].
 Example 4:

 Input: nums = [1,1,2,3], quantity = [2,2]
 Output: false
 Explanation: Although the 0th customer could be given [1,1], the 1st customer cannot be satisfied.
 Example 5:

 Input: nums = [1,1,1,1,1], quantity = [2,3]
 Output: true
 Explanation: The 0th customer is given [1,1], and the 1st customer is given [1,1,1].
  

 Constraints:

 n == nums.length
 1 <= n <= 105
 1 <= nums[i] <= 1000
 m == quantity.length
 1 <= m <= 10
 1 <= quantity[i] <= 105
 There are at most 50 unique values in nums.
*/
class Solution {
public:
    // TODO: copy function signature here
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        int n = quantity.size();
        unordered_map<int,int> cnts;
        for (auto i : nums) {
            ++cnts[i];
        }
        vector<int> qcnts;
        for (auto & p : cnts) {
            qcnts.push_back(p.second);
        }
        int m = qcnts.size();
        
        vector<int> need(1<<n, 0);
        for (int j = 0; j < (1<<n); ++j) {
            int k = 0;
            while (j >= (1<<k)) {
                if (j&(1<<k)) {
                    need[j] += quantity[k];
                }
                ++k;
            }
        }
        // dp[i][j] => whether qcnts[0..i] can cover quantities represented by bitset j
        int all = (1<<n) - 1;
        vector<vector<bool>> dp(1+m, vector<bool>(1<<n, false));
        dp[0][0] = true;
        for (int i = 0; i < m; ++i) {
            dp[i+1][0] = true;
            for (int j = 0; j < (1<<n); ++j) {
                if (dp[i][j]) {
                    dp[i+1][j] = true;
                    int bs = all ^ j;
                    for (int sub = bs; sub > 0; sub = (sub-1)&bs) {
                        if (qcnts[i] > need[sub]) {
                            dp[i+1][j|sub] = true;
                        }
                    }
                }
            }
            if (dp[i+1][all]) {
                return true;
            }
        }
        return false;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nums;
        vector<int> quantity;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{1,2,3,4},{2}},
        {{1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,24,25,25,26,26,27,27,28,28,29,29,30,30,31,31,32,32,33,33,34,34,35,35,36,36,37,37,38,38,39,39,40,40,41,41,42,42,43,43,44,44,45,45,46,46,47,47,48,48,49,49,50,50},{2,2,2,2,2,2,2,2,2,3}},
    };
    // TODO: provide expected results here
    vector<bool> answers {
        false,
        false,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = canDistribute::Solution().canDistribute(dp.nums, dp.quantity);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
