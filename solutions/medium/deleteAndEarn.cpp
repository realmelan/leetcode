//
//  deleteAndEarn.cpp
//  leetcode
//
//  Created by  Song Ding on 12/5/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;
/**
 740. Delete and Earn
 Medium

 668

 57

 Favorite

 Share
 Given an array nums of integers, you can perform operations on the array.

 In each operation, you pick any nums[i] and delete it to earn nums[i] points. After, you must delete every element equal to nums[i] - 1 or nums[i] + 1.

 You start with 0 points. Return the maximum number of points you can earn by applying such operations.

 Example 1:

 Input: nums = [3, 4, 2]
 Output: 6
 Explanation:
 Delete 4 to earn 4 points, consequently 3 is also deleted.
 Then, delete 2 to earn 2 points. 6 total points are earned.
  

 Example 2:

 Input: nums = [2, 2, 3, 3, 3, 4]
 Output: 9
 Explanation:
 Delete 3 to earn 3 points, deleting both 2's and the 4.
 Then, delete 3 again to earn 3 points, and 3 again to earn 3 points.
 9 total points are earned.
  

 Note:

 The length of nums is at most 20000.
 Each element nums[i] is an integer in the range [1, 10000].
 */

namespace deleteAndEarn {
    class Solution {
    public:
        /**
         sort nums into increasng order, and only consecutive nums will impact each other.
         let dp[i] = max points from start of consecutive numbers.
         */
        int deleteAndEarn(vector<int>& nums) {
            map<int, int> t;
            // or into a map increasing num=>sum of num
            for (auto i : nums) {
                t[i] += i;
            }
            
            int n = t.size();
            if (n <= 0) {
                return 0;
            }
            vector<int> dp(n, 0);
            auto it = t.begin();
            dp[0] = it->second;
            int i = 1;
            int last = it->first;
            int res = 0;
            for (++it; it != t.end(); ++it, ++i) {
                if (it->first - last == 1) {
                    dp[i] = max(dp[i-1], it->second + (i>1?dp[i-2]:0));
                } else {
                    dp[i] = dp[i-1] + it->second;
                }
                last = it->first;
            }
            return dp[n-1];
        }
        int deleteAndEarn_wrong(vector<int>& nums) {
            vector<int> t(nums);
            sort(t.begin(), t.end(), [](int& a, int& b){ return a > b; });
            
            if (t.empty()) {
                return 0;
            }
            
            int res = 0;
            int len = t.size();
            int sum1 = t[0], sum2 = 0;
            int last = t[0];
            int *sum = &sum1;
            
            
            for (int i = 1; i < len; ++i) {
                if (last - t[i] > 1) {
                    // choose the larger of sum1 & sum2
                    res += sum1 > sum2 ? sum1 : sum2;
                    sum1 = t[i];
                    sum2 = 0;
                    sum = &sum1;
                } else if (last == t[i]) {
                    *sum += t[i];
                } else { // flip sum
                    if (sum == &sum1) {
                        sum = &sum2;
                    } else {
                        sum = &sum1;
                    }
                    *sum += t[i];
                }
                last = t[i];
            }
            res += sum1 > sum2 ? sum1 : sum2;
            
            return res;
        }
    };
}
/*
int main() {
    vector<int> nums{10,8,4,2,1,3,4,8,2,9,10,4,8,5,9,1,5,1,6,8,1,1,6,7,8,9,1,7,6,8,4,5,4,1,5,9,8,6,10,6,4,3,8,4,10,8,8,10,6,4,4,4,9,6,9,10,7,1,5,3,4,4,8,1,1,2,1,4,1,1,4,9,4,7,1,5,1,10,3,5,10,3,10,2,1,10,4,1,1,4,1,2,10,9,7,10,1,2,7,5};
    cout << deleteAndEarn::Solution().deleteAndEarn(nums) << endl;
    
    vector<int> a{0,0};
    auto it = remove(a.begin(), a.end(), 0);
    if (it == a.begin()) {
        cout << "at begin" << endl;
    }
    return 0;
}
 //*/
