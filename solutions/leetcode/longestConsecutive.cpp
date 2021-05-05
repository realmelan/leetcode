//
//  longestConsecutive.cpp
//  leetcode
//
//  Created by  Song Ding on 2/5/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//
/*
 Problem:
 128. Longest Consecutive Sequence
 Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
 
 For example,
 Given [100, 4, 200, 1, 3, 2],
 The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
 
 Your algorithm should run in O(n) complexity.
 */

#include "common.h"
using namespace std;

namespace longestConsecutive {
    class Solution {
    public:
        
        int longestConsecutive(vector<int>& nums) {
            unordered_set<int> ns(nums.begin(), nums.end());
            int res = 0;
            
            while (ns.size()) {
                int cur = *ns.begin();
                ns.erase(cur);
                // increase head
                int right = cur;
                while (ns.find(right+1) != ns.end()) {
                    ++right;
                    ns.erase(right);
                }
                int left = cur;
                while (ns.find(left-1) != ns.end()) {
                    --left;
                    ns.erase(left);
                }
                res = max(res, right - left+1);
            }
            return res;
        }
        /**
         Bucket sort, since number of digits of a integer is at most 12,
         bucket sort is O(n).
         */
        int longestConsecutive2(vector<int>& nums) {
            int n = nums.size();
            if (n <= 1) {
                return n;
            }
            // first decide how many iterations are needed.
            vector<vector<long>> buckets(10);
            long min = nums[0];
            long max = nums[0];
            for (auto i : nums) {
                if (max < i) {
                    max = i;
                }
                if (min > i) {
                    min = i;
                }
            }
            
            if (min < 0) {
                for (auto i : nums) {
                    long t = i;
                    t -= min;
                    buckets[t % 10].push_back(t);
                }
                max -= min;
            } else {
                for (auto i : nums) {
                    long t = i;
                    buckets[t % 10].push_back(t);
                }
            }
            
            int mr = 1;
            while (max / 10) {
                max /= 10;
                ++mr;
            }
            
            long b = 1;
            for (int r = 1; r < mr; ++r) {
                b *= 10;
                vector<vector<long>> nbuckets(10);
                for (const auto& v : buckets) {
                    for (auto i : v) {
                        nbuckets[(i / b) % 10].push_back(i);
                    }
                }
                buckets.swap(nbuckets);
            }
            
            // count consecutive numbers
            vector<long> sorted;
            for (const auto& v : buckets) {
                if (v.empty()) {
                    continue;
                }
                long last = v[0];
                sorted.push_back(last);
                for (auto i : v) {
                    if (i != last) {
                        sorted.push_back(i);
                    }
                    last = i;
                }
            }
            long last = sorted[0] - 1;
            int res = 0;
            int c = 0;
            for (auto i : sorted) {
                if (i == last + 1) {
                    ++c;
                } else {
                    if (c > res) {
                        res = c;
                    }
                    c = 1;
                }
                last = i;
            }
            if (c > res) {
                res = c;
            }
            return res;
        }
    };
}

/*

int main() {
    vector<int> nums{100, 4, 200, 1, 3, 2};
    cout << longestConsecutive::Solution().longestConsecutive(nums) << endl;
    return 0;
}
// */
