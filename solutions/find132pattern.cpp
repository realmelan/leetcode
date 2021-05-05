// find132pattern.cpp
// leetcode
//
// Created by  Song Ding on 9/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace find132pattern {
/*
// TODO: copy problem statement here
 456. 132 Pattern
 Medium

 743

 45

 Favorite

 Share
 Given a sequence of n integers a1, a2, ..., an, a 132 pattern is a subsequence ai, aj, ak such that i < j < k and ai < ak < aj. Design an algorithm that takes a list of n numbers as input and checks whether there is a 132 pattern in the list.

 Note: n will be less than 15,000.

 Example 1:
 Input: [1, 2, 3, 4]

 Output: False

 Explanation: There is no 132 pattern in the sequence.
 Example 2:
 Input: [3, 1, 4, 2]

 Output: True

 Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
 Example 3:
 Input: [-1, 3, 2, 0]

 Output: True

 Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].
 */

class Solution {
public:
    /**
     * https://leetcode.com/problems/132-pattern/discuss/94071/Single-pass-C%2B%2B-O(n)-space-and-time-solution-(8-lines)-with-detailed-explanation.
     * monotonic queue
     */
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        stack<int> dec;
        int s3 = INT_MIN;
        for (int i = n-1; i >= 0; --i) {
            int num = nums[i];
            if (nums[i] < s3) {
                return true;
            }
            while (dec.size() && dec.top() < num) {
                s3 = dec.top();
                dec.pop();
            }
            dec.push(num);
        }
        return false;
    }

private:
};

}

//*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nums;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //*
        {{1, 2, 3, 4}},
        {{3, 1, 4, 2}},
        {{-1, 3, 2, 0}},
         //*/
        {{1,0,1,-4,-3}},
        {{3,5,0,3,4}},
    };

    vector< bool > answers {
        false,
        true,
        true,
        false,
        true,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = find132pattern::Solution().find132pattern(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
