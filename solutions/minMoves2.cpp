// minMoves2.cpp
// leetcode
//
// Created by  Song Ding on 10/28/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minMoves2 {
/*
// TODO: copy problem statement here
 462. Minimum Moves to Equal Array Elements II
 Medium

 392

 35

 Favorite

 Share
 Given a non-empty integer array, find the minimum number of moves required to make all array elements equal, where a move is incrementing a selected element by 1 or decrementing a selected element by 1.

 You may assume the array's length is at most 10,000.

 Example:

 Input:
 [1,2,3]

 Output:
 2

 Explanation:
 Only two moves are needed (remember each move increments or decrements one element):

 [1,2,3]  =>  [2,2,3]  =>  [2,2,2]
 */

class Solution {
public:
    /**
     * the target number should be the median of the array.
     */
    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        sort(nums.begin(), nums.end());
        for (int i = 0, j = n-1; i < j; ++i, --j) {
            res += nums[j] - nums[i];
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
        {{1,2,3}},
        {{1,0,0,8,6}},
    };

    vector< int > answers {
        2,
        14,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minMoves2::Solution().minMoves2(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
