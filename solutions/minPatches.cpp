// minPatches.cpp
// leetcode
//
// Created by  Song Ding on 11/12/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minPatches {
/*
// TODO: copy problem statement here
 330. Patching Array
 Hard

 375

 65

 Favorite

 Share
 Given a sorted positive integer array nums and an integer n, add/patch elements to the array such that any number in range [1, n] inclusive can be formed by the sum of some elements in the array. Return the minimum number of patches required.

 Example 1:

 Input: nums = [1,3], n = 6
 Output: 1
 Explanation:
 Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
 Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
 Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
 So we only need 1 patch.
 Example 2:

 Input: nums = [1,5,10], n = 20
 Output: 2
 Explanation: The two patches can be [2, 4].
 Example 3:

 Input: nums = [1,2,2], n = 5
 Output: 0
 */

class Solution {
public:
    /**
    Iteratively add a larger number to cover larger range.
    Say, current set of i numbers, s, would cover a range [1, r(i)],
    r(i) = SUM(s), then to expand, need to add r(i) + 1, and
    the new range expand to [1, 2*r(i) + 1].
    
    However, for the first group of numbers, say [1, k], make sure they
    can be covered, by just using existing numbers.
    */
    int minPatches(vector<int>& nums, int n) {
        vector<long> t(nums.begin(), nums.end());
        sort(t.begin(), t.end());
        t.push_back((long)n + 1); // guarding point
        
        // start from 1.
        int res = 0;
        auto it = t.begin();
        long c = 1;
        long s = 0;
        while (s < n && it != t.end()) {
            if (c < *it) {
                ++res;
                s += c;
                c = s + 1;
            } else {
                s += *it;
                c = s + 1;
                ++it;
            }
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
        int n;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,3},6},
        {{1,5,10},20},
        {{1,2,2},5},
    };

    vector< int > answers {
        1,
        2,
        0,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minPatches::Solution().minPatches(dp.nums, dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
