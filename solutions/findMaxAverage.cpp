// findMaxAverage.cpp
// leetcode
//
// Created by  Song Ding on 11/7/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findMaxAverage {
/*
// TODO: copy problem statement here
 644. Maximum Average Subarray II

 Given an array consisting of n integers, find the contiguous subarray whose length is greater than or equal to k that has the maximum average value. And you need to output the maximum average value.

 Example 1:

 Input: [1,12,-5,-6,50,3], k = 4
 Output: 12.75
 Explanation:
 when length is 5, maximum average value is 10.8,
 when length is 6, maximum average value is 9.16667.
 Thus return 12.75.
 Note:

 1 <= k <= n <= 10,000.
 Elements of the given array will be in range [-10,000, 10,000].
 The answer with the calculation error less than 10^-5 will be accepted.
 */

class Solution {
public:
    /**
     * A regular solution: use sum[i+k]-sum[i] to get the sum of nums[i...i+k-1] and compute average
     * However, this might be O(n^2).
     * Another solution is to try possible maximum average candidate, m,  and see whether there is a range
     * whose sum > m * length of range. if there is a one such range, then we can search another one larger than m.
     * this is binary search.
     */
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        double left = *min_element(nums.begin(), nums.end());
        double right = *max_element(nums.begin(), nums.end());
        while (right - left > 0.000001) {
            bool found = false;
            double mid = left + (right - left) / 2;
            vector<double> sum(n+1, 0);
            double minSum = 0;
            for (int i = 1; i <= n; ++i) {
                sum[i] = sum[i-1] + nums[i-1] - mid;
                // get min sum up to i - k, which might be a candidate for i
                if (i >= k) {
                    minSum = min(minSum, sum[i-k]);
                    if (sum[i] > minSum) {
                        found = true;
                        break;
                    }
                }
            }
            if (found) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return left;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nums;
        int k;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,12,-5,-6,50,3},4}
    };

    vector< double > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findMaxAverage::Solution().findMaxAverage(dp.nums, dp.k);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
