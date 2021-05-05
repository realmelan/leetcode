// kSmallestPairs.cpp
// leetcode
//
// Created by  Song Ding on 3/30/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace kSmallestPairs {

class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        vector<pair<int, int>> res;
        if (k >= n1 * n2) {
            for (int i = 0; i < n1; ++i) {
                for (int j = 0; j < n2; ++j) {
                    res.push_back(make_pair(nums1[i], nums2[j]));
                }
            }
            
            sort(res.begin(), res.end(),[](const pair<int,int>&a, const pair<int,int>&b){
                return a.first + a.second < b.first + b.second;
            });
        } else if (n1 > 0 && n2 > 0 && k > 0) {
            int l = min(nums1[0], nums2[0]);
            int h = max(nums1[n1 - 1], nums2[n2 - 1]);
            vector<int> lastBound;
            while (l <= h) {
                int cnt = 0;
                int m = (l + h) / 2;
                vector<int> bound;
                int j = n2 - 1;
                for (int i = 0; i < n1; ++i) {
                    while (j >= 0 && nums2[j] + nums1[i] > m) { --j; }
                    cnt += j + 1;
                    bound.push_back(j);
                }
                if (cnt >= k) {
                    lastBound.swap(bound);
                }
                if (cnt < k) {
                    l = m + 1;
                } else if (cnt > k) {
                    h = m - 1;
                } else {
                    break;
                }
            }
            for (int i = 0; i < n1; ++i) {
                for (int j = 0; j <= lastBound[i]; ++j) {
                    res.push_back(make_pair(nums1[i], nums2[j]));
                }
            }
            sort(res.begin(), res.end(),[](const pair<int,int>&a, const pair<int,int>&b){
                return a.first + a.second < b.first + b.second;
            });
            res.resize(k);
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> nums1{0,0,0,0,0};
    vector<int> nums2{-3,22,35,56,76};
    int k = 22;
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = kSmallestPairs::Solution().kSmallestPairs(nums1, nums2, k);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
