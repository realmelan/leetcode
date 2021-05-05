//
//  countRangeSum.cpp
//  leetcode
//
//  Created by  Song Ding on 3/14/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace countRangeSum {
    class Solution {
    public:
        /**
         first, get sums of ranges [0,i] (0 <= i <= n - 1).
         sort the sum array.
         Now, for each element in the sum array, sum[i], find other elements
         in the sum array that lower <= sum[j] - sum[i] <= upper. mark the
         two indices.
         
         For the next element, sum[i + 1], because sum[i + 1] >= sum[i], the new
         indices will be no smaller than current indices.
         */
        int countRangeSum(vector<int>& nums, int lower, int upper) {
            int n = nums.size();
            int res = 0;
            vector<pair<int,int>> sums;
            int s = 0;
            for (int i = 0; i < n; ++i) {
                s += nums[i];
                sums.push_back(make_pair(s, i));
                if (s >= lower && s <= upper) {
                    ++res;
                }
            }
            sort(sums.begin(), sums.end(), [](const pair<int,int>& a, const pair<int,int>& b){
                return a.first < b.first;
            });
            
            int ilower = 0;
            for (int i = 0; i < n; ++i) {
                int csum = sums[i].first;
                int idx = sums[i].second;
                
                int j = ilower;
                while (j < n && sums[j].first - csum < lower) {
                    ++j;
                }
                if (j >= n) {
                    break;
                }
                ilower = j;
                while (j < n && sums[j].first - csum <= upper) {
                    if (sums[j].second > idx) {
                        ++res;
                    }
                    ++j;
                }
            }
            return res;
        }
    };
}
/*
int main() {
    vector<int> nums{0,0};
    int lower = 0;
    int upper = 0;
    cout << countRangeSum::Solution().countRangeSum(nums, lower, upper) << endl;
    return 0;
}
 */
