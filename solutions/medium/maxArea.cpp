// maxArea.cpp
// leetcode
//
// Created by  Song Ding on 6/18/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxArea {
/*
// TODO: copy problem statement here
 11. Container With Most Water
 Medium
 
 3364
 
 445
 
 Favorite
 
 Share
 Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.
 
 Note: You may not slant the container and n is at least 2.
 
 
 
 
 
 The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
 
 
 
 Example:
 
 Input: [1,8,6,2,5,4,8,3,7]
 Output: 49
 */

class Solution {
public:
    /**
     * https://leetcode.com/problems/container-with-most-water/discuss/6100/Simple-and-clear-proofexplanation
     */
    int maxArea3(vector<int>& height) {
        int n = height.size();
        int res = 0;
        int i = 0, j = n-1;
        while (i < j) {
            res = max(res, (j-i)*min(height[i],height[j]));
            if (height[i] < height[j]) {
                ++i;
            } else {
                --j;
            }
        }
        return res;
    }
    /**
     * Find a list of increasing heights from left and right, then for each height of
     * of the left queue, find max water using each height of the right queue.
     *
     */
    int maxArea2(vector<int>& height) {
        int n = height.size();
        vector<int> leftq, rightq;
        for (int i = 0; i < n; ++i) {
            if (leftq.empty() || height[leftq.back()] < height[i]) {
                leftq.push_back(i);
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            if (rightq.empty() || height[rightq.back()] < height[i]) {
                rightq.push_back(i);
            }
        }
        
        int res = 0;
        int i = 0, j = 0;
        while (i < leftq.size() && j < rightq.size() && leftq[i] < rightq[j]) {
            res = max(res, (rightq[j]-leftq[i]) * min(height[leftq[i]], height[rightq[j]]));
            if (height[leftq[i]] < height[rightq[j]]) {
                ++i;
            } else {
                ++j;
            }
        }
        if (i >= leftq.size()) {
            while (j < rightq.size()) {
                res = max(res, (rightq[j]-leftq.back()) * min(height[leftq.back()], height[rightq[j]]));
                ++j;
            }
        } else {
            while (i < leftq.size()) {
                res = max(res, (rightq.back()-leftq[i]) * min(height[leftq[i]], height[rightq.back()]));
                ++i;
            }
        }
        return res;
    }
    /**
     * Find a list of increasing heights from left and right, then for each height of
     * of the left queue, find max water using each height of the right queue.
     *
     */
    int maxArea(vector<int>& height) {
        int n = height.size();
        vector<vector<int>> leftq, rightq;
        for (int i = 0; i < n; ++i) {
            if (leftq.empty() || leftq.back()[1] < height[i]) {
                leftq.push_back({i, height[i]});
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            if (rightq.empty() || rightq.back()[1] < height[i]) {
                rightq.push_back({i, height[i]});
            }
        }
        
        int res = 0;
        int ln = leftq.size();
        int rn = rightq.size();
        int j = 0;
        for (int i = 0; i < ln; ++i) {
            int lx = leftq[i][0];
            int lh = leftq[i][1];
            while (j < rn && rightq[j][0] <= lx) {
                ++j;
            }
            for (int k = j; k < rn; ++k) {
                int rx = rightq[k][0];
                int rh = rightq[k][1];
                res = max(res, min(lh, rh) * (rx - lx));
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
        vector<int> height;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,8,6,2,5,4,8,3,7}}
    };

    vector< int > answers {
        49
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxArea::Solution().maxArea3(dp.height);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
