//
//  numSubarrayProductLessThanK.cpp
//  leetcode
//
//  Created by  Song Ding on 12/20/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace numSubarrayProductLessThanK {
    class Solution2 {
    public:
        int numSubarrayProductLessThanK(vector<int>& nums, int k) {
            int len = nums.size();
            if (len <= 0 || k <= 1) {
                return 0;
            }
            
            int ps = 0;
            while (ps < len && nums[ps] >= k) {
                ++ps;
            }
            if (ps == len) {
                return 0;
            }
            
            long p = nums[ps];
            int pe = ps;
            for (pe = ps + 1; pe < len; ++pe) {
                p *= nums[pe];
                if (p >= k) {
                    break;
                }
            }
            if (pe == len) {
                int c = pe - ps;
                long res = c;
                res *= c + 1;
                res /= 2;
                return static_cast<int>(res);
            }
            
            int res = 0;
            res += pe - ps;
            p /= nums[pe];
            p /= nums[ps];
            
            for (int i = ps + 1; i < len; ++i) {
                int j = pe;
                if (j < i) {
                    j = i;
                }
                while (j < len) {
                    p *= nums[j];
                    if (p >= k) {
                        break;
                    }
                    ++j;
                }
                if (j == len) {
                    int c = j - i;
                    long tres = c;
                    tres *= c + 1;
                    tres /= 2;
                    res += tres;
                    break;
                }
                
                res += j - i;
                pe = j;
                p /= nums[j];
                if (i != j) {
                    p /= nums[i];
                }
            }
            return res;
        }
    };
    class Solution1 {
    public:
        int numSubarrayProductLessThanK(vector<int>& nums, int k) {
            int n = nums.size(), ans = 0, prod = 1, j = 0;
            for (int i = 0; i < n; i++) {
                if (i > 0 && i <= j)
                    prod =  prod/nums[i-1];
                else
                    j = i;
                while (j < n &&  prod*nums[j] < k) prod *= nums[j++];
                ans += j-i;
            }
            return ans;
        }
    };
}

/*
int main() {
    vector<int> nums{};
    int k = 5;
    cout << numSubarrayProductLessThanK::Solution2().numSubarrayProductLessThanK(nums, k) << endl;
    return 0;
}
 */
