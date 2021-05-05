// lengthOfLIS.cpp
// leetcode
//
// Created by  Song Ding on 10/3/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace lengthOfLIS {
/*
// TODO: copy problem statement here
 300. Longest Increasing Subsequence
 Medium

 3031

 69

 Favorite

 Share
 Given an unsorted array of integers, find the length of longest increasing subsequence.

 Example:

 Input: [10,9,2,5,3,7,101,18]
 Output: 4
 Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
 Note:

 There may be more than one LIS combination, it is only necessary for you to return the length.
 Your algorithm should run in O(n2) complexity.
 Follow up: Could you improve it to O(n log n) time complexity?
 */

class Solution {
public:
    /**
     * https://en.wikipedia.org/wiki/Longest_increasing_subsequence#Efficient_algorithms
     * let m[i] = index of minimum value nums[k] of the ending element of a IS of length i up to current array element.
     * it is guaranteed that m[i] is increasing.
     * for nums[i], do a binary search to find m[j] such that nums[m[j]] < nums[i], then the length of IS ending at nums[i]
     * is at most j+1.
     */
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> m;
        for (int i = 0; i < n; ++i) {
            int num = nums[i];
            auto it = lower_bound(m.begin(), m.end(), num, [&nums](int a, int num){
                return nums[a] < num;
            });
            
            if (it == m.end()) {
                m.push_back(i);
            } else {
                int newL = distance(m.begin(), it);
                m[newL] = i;
            }
        }
        return m.size();
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
        {{10,9,2,5,3,7,101,18}},
        {{10,9,2,5,3,7,7,101,18}},
        {{10,9,2,5,3,4}},
    };

    vector< int > answers {
        4,
        4,
        3,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = lengthOfLIS::Solution().lengthOfLIS(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
