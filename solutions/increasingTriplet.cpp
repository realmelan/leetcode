// increasingTriplet.cpp
// leetcode
//
// Created by  Song Ding on 10/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace increasingTriplet {
/*
// TODO: copy problem statement here
 334. Increasing Triplet Subsequence
 Medium

 1037

 98

 Favorite

 Share
 Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.

 Formally the function should:

 Return true if there exists i, j, k
 such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
 Note: Your algorithm should run in O(n) time complexity and O(1) space complexity.

 Example 1:

 Input: [1,2,3,4,5]
 Output: true
 Example 2:

 Input: [5,4,3,2,1]
 Output: false

 */

class Solution {
public:
    /**
     * we keep the pair (min1, min2) where min1 < min2 and min2 is the minimal.
     */
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        int min1 = nums[0];
        int min2 = INT_MIN;
        for (int i = 1; i < n; ++i) {
            int num = nums[i];
            if (num > min1) {
                if (min2 == INT_MIN) {
                    min2 = num;
                } else if (num <= min2) {
                    min2 = num;
                } else {
                    return true;
                }
            } else {
                min1 = num;
            }
        }
        return false;
    }
    /**
     * use monotonic queue (decreasing) when nums[i] pushes number
     * out of the queue, check whether the number itself already pushes out
     * some numbers.
     *
     * This doesn't work for cases when triplets are surrounded by larger numbers.
     */
    bool increasingTriplet_wrong(vector<int>& nums) {
        // <value, # of numbers pushed out>
        stack<pair<int,int>> dec;
        for (auto num : nums) {
            int cnt = 0;
            while (dec.size() && num > dec.top().first) {
                cnt = max(cnt, dec.top().second);
                if (cnt >= 2) {
                    return true;
                }
                dec.pop();
            }
            dec.push(make_pair(num,cnt+1));
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
        {{1,2,0,1}},
        {{1,2,3,4,5}},
        {{5,4,3,2,1}},
        {{2,1,5,0,3}},
        {{5,1,5,5,2,5,4}},
    };

    vector< bool > answers {
        true,
        false,
        false,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = increasingTriplet::Solution().increasingTriplet(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
