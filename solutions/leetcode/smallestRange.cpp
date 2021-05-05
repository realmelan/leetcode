//
//  smallestRange.cpp
//  leetcode
//
//  Created by  Song Ding on 1/27/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace smallestRange {
    class Solution {
    public:
        /**
         The smallest range must start at a point in one list and end
         at a point in another list.
         
         Starting from the min of min values from all lists, and loop
         through all lists to find the first range. Now skip the starting
         point and use the second min value
         */
        vector<int> smallestRange(vector<vector<int>>& nums) {
            vector<int> res;
            int k = nums.size();
            if (k <= 0) {
                return res;
            }
            if (k == 1) {
                const vector<int>& v = nums[0];
                res.push_back(v[0]);
                res.push_back(v[0]);
                return res;
            }
            
            vector<pair<int, int>> elems;
            for (int i = 0; i < k; ++i) {
                const vector<int>& v = nums[i];
                for (int j = 0; j < v.size(); ++j) {
                    elems.push_back(make_pair(v[j], i));
                }
            }
            sort(elems.begin(), elems.end(), [](const pair<int,int>& a, const pair<int,int>& b){
                if (a.first < b.first) {
                    return true;
                } else if (a.first > b.first) {
                    return false;
                } else {
                    return a.second < b.second;
                }
            });
            
            int n = elems.size();
            int minStart = 0;
            int minEnd = 0;
            
            int start = 0;
            int startIdx = 0;
            int end = 0;
            int endIdx = 0;
            map<int, int> covered;
            minStart = elems[0].first;
            covered.insert(make_pair(elems[0].second, 1));
            for (int i = 1; i < n; ++i) {
                int elem = elems[i].first;
                int listIdx = elems[i].second;
                ++covered[listIdx];
                if (covered.size() == k) {
                    end = minEnd = elem;
                    endIdx = i;
                    break;
                }
            }
            while (true) {
                // remove current minStart
                int listIdx = elems[startIdx].second;
                ++startIdx;
                start = elems[startIdx].first;
                --covered[listIdx];
                if (covered[listIdx] == 0) {
                    covered.erase(listIdx);
                }
                if (covered.size() == k) {
                    if (end - start < minEnd - minStart) {
                        minStart = start;
                        minEnd = end;
                    }
                    continue;
                }
                int i = endIdx + 1;
                for (; i < n; ++i) {
                    int elem = elems[i].first;
                    int listIdx = elems[i].second;
                    ++covered[listIdx];
                    if (covered.size() == k) {
                        end = elem;
                        endIdx = i;
                        if (end - start < minEnd - minStart) {
                            minStart = start;
                            minEnd = end;
                        }
                        break;
                    }
                }
                if (i >= n) {
                    break;
                }
                
            }
            
            res.push_back(minStart);
            res.push_back(minEnd);
            return res;
        }
        
        /**
         use sliding window, left = starting element, and right = element that meets conditions.
         */
        vector<int> smallestRange2(vector<vector<int>>& nums) {
            vector<vector<int>> elems;
            for (int i = 0; i < nums.size(); ++i) {
                for (auto v : nums[i]) {
                    elems.push_back({v, i});
                }
            }
            sort(elems.begin(), elems.end());
            // m counts the # of elements covered for each list
            unordered_map<int, int> m;
            int cnt = 0, k = nums.size();
            int left = 0;
            int resl = 0, resr = 0, minr = INT_MAX;
            for (int i = 0; i < elems.size(); ++i) {
                if (m[elems[i][1]]++ == 0) {
                    ++cnt;
                }
                while (cnt == k && left <= i) {
                    if (elems[i][0] - elems[left][0] < minr) {
                        minr = elems[i][0] - elems[left][0];
                        resl = elems[left][0];
                        resr = elems[i][0];
                    }
                    if (m[elems[left++][1]]-- == 1) {
                        --cnt;
                    }
                }
            }
            return {resl, resr};
        }
    };
}
/*

int main() {
    vector<vector<int>> nums{
        {1}
        //{4,10,15,24,26},{0,9,12,20},{5,18,22,30}
        //{10,10},{11,11}
    };
    vector<int> res = smallestRange::Solution().smallestRange2(nums);
    printVector(res);
    return 0;
}
 //*/
