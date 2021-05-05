//
//  maxSumOfThreeSubarrays.cpp
//  leetcode
//
//  Created by  Song Ding on 1/29/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace maxSumOfThreeSubarrays {
    class Solution {
    public:
        /**
         * for each k-sum at i, find out the max sum to the left of i and right of i+k-1.
         */
        vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
            int n = nums.size();
            vector<int> left(n, 0), right(n, 0), res, sum(n+1, 0);
            for (int i = 0; i < n; ++i) {
                sum[i+1] = sum[i] + nums[i];
            }
            left[k-1] = 0;
            int lm = sum[k] - sum[0];
            for (int i = k; i+k <= n; ++i) {
                if (sum[i+1]-sum[i-k+1] > lm) {
                    left[i] = i-k+1;
                    lm = sum[i+1] - sum[i-k+1];
                } else {
                    left[i] = left[i-1];
                }
            }
            
            int rm = sum[n] - sum[n-k];
            right[n-k] = n-k;
            for (int i = n-k-1; i >= 0; --i) {
                if (sum[i+k] - sum[i] > rm) {
                    rm = sum[i+k] - sum[i];
                    right[i] = i;
                } else {
                    right[i] = right[i+1];
                }
            }
            
            int tm = INT_MIN;
            for (int i = k; i+k <= n-k; ++i) {
                int l = left[i-1], r = right[i+k];
                if (sum[l+k]-sum[l] + sum[r+k] - sum[r] + sum[i+k] - sum[i] > tm) {
                    res = {l,i,r};
                    tm = sum[l+k]-sum[l] + sum[r+k] - sum[r] + sum[i+k] - sum[i];
                }
            }
            return res;
        }
        /**
         DP: do it in 3 rounds.
         
         1st round: for subarray nums[0, i], compute max k-sum;
         2nd round: for subarray nums[0, i], compute max 2 k-sum;
         3rd round: for subarray nums[0, i], compute max 3 k-sum.
         
         1st round is simple loop.
         2nd round: for the i'th element, sum the last k elements,
         if sum is no less than the 2nd k-sum, update 2nd k-sum,
         and use 1st round result to find the 1st k-sum.
         3rd round: same as 2nd round.
         */
        vector<int> maxSumOfThreeSubarrays2(vector<int>& nums, int k) {
            vector<int> res;
            int n = nums.size();
            if (n < 3*k) {
                return res;
            }
            
            // 1st round
            vector<int> prev(n, 0);
            vector<vector<int>> previds(n);
            for (auto& v : previds) {
                v.resize(1, -1);
            }
            
            int i = 0;
            int sum = 0;
            for (; i < k; ++i) {
                sum += nums[i];
            }
            prev[k - 1] = sum;
            previds[k - 1][0] = 0;
            
            for (; i < n; ++i) {
                sum += nums[i];
                sum -= nums[i - k];
                if (sum > prev[i - 1]) {
                    prev[i] = sum;
                    previds[i][0] = i - k + 1;
                } else {
                    prev[i] = prev[i - 1];
                    previds[i] = previds[i - 1];
                }
            }
            
            for (int r = 2; r <= 3; ++r) {
                vector<int> cur(n, 0);
                vector<vector<int>> curids(n);
                
                // init the first 3 k-sums
                int sum = 0;
                for (int ir = 0; ir < r; ++ir) {
                    sum = 0;
                    for (int j = 0; j < k; ++j) {
                        sum += nums[j + k * ir];
                    }
                    cur[r * k - 1] += sum;
                    curids[r * k - 1].push_back(k * ir);
                }
                
                for (int i = r * k; i < n; ++i) {
                    sum += nums[i];
                    sum -= nums[i - k];
                    if (sum + prev[i - k] > cur[i - 1]) {
                        cur[i] = sum + prev[i - k];
                        curids[i] = previds[i - k];
                        curids[i].push_back(i - k + 1);
                    } else {
                        cur[i] = cur[i - 1];
                        curids[i] = curids[i - 1];
                    }
                }
                prev.swap(cur);
                previds.swap(curids);
            }
            return previds[n - 1];
        }
    };
}

/*
int main() {
    vector<int> nums{17,7,19,11,1,19,17,6,13,18,2,7,12,16,16,18,9,3,19,5};
    int k = 6;
    vector<int> res = maxSumOfThreeSubarrays::Solution().maxSumOfThreeSubarrays2(nums, k);
    printVector(res);
    return 0;
}
// */
