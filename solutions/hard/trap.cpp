// trap.cpp
// leetcode
//
// Created by  Song Ding on 9/4/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace trap {
/*
// TODO: copy problem statement here
 42. Trapping Rain Water
 Hard
 
 4259
 
 78
 
 Favorite
 
 Share
 Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.
 
 
 The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!
 
 Example:
 
 Input: [0,1,0,2,1,0,1,3,2,1,2,1]
 Output: 6
 */

class Solution {
public:
    // for each position, find the highest bars at left and right end.
    int trap3(vector<int>& height) {
        int n = height.size();
        vector<int> lp(n), rp(n);
        lp[0] = 0;
        for (int i = 1; i < n; ++i) {
            lp[i] = lp[i-1];
            if (height[i] > height[lp[i]]) {
                lp[i] = i;
            }
        }
        rp[n-1] = n-1;
        for (int i = n-2; i >= 0; --i) {
            rp[i] = rp[i+1];
            if (height[i] > height[rp[i]]) {
                rp[i] = i;
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += min(height[lp[i]], height[rp[i]]) - height[i];
        }
        return res;
    }
    
    /**
     * use two pointers l and r, and find the lower of the two, which determines the level of the water at the lower side.
     * iteratively move the pointers toward the middle, which updating the level of water.
     * https://leetcode.com/problems/trapping-rain-water/discuss/153992/Java-O(n)-time-and-O(1)-space-(with-explanations).
     */
    int trap2(vector<int>& height) {
        int n = height.size(), res = 0, l = 0, r = n - 1, level = 0;
        while (l < r) {
            if (height[l] < height[r]) {
                level = max(level, height[l]);
                res += level - height[l];
                ++l;
            } else {
                level = max(level, height[r]);
                res += level - height[r];
                --r;
            }
        }
        return res;
    }
    /**
     * For each point, find the highest points on both side, and the
     * lower of two highest points decides the final height of water.
     */
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2) {
            return 0;
        }
        map<int, pair<int,int>> leftPeaks, rightPeaks;
        leftPeaks[0] = make_pair(-1,0);
        rightPeaks[n - 1] = make_pair(n, 0);
        
        for (int i = 1; i < n; ++i) {
            leftPeaks[i] = leftPeaks[i - 1];
            if (height[i - 1] > leftPeaks[i].second) {
                leftPeaks[i] = make_pair(i - 1, height[i - 1]);
            }
        }
        for (int i = n - 2; i >= 0; --i) {
            rightPeaks[i] = rightPeaks[i + 1];
            if (height[i + 1] > rightPeaks[i].second) {
                rightPeaks[i] = make_pair(i + 1, height[i + 1]);
            }
        }
        
        int res = 0;
        for (int i = 1; i < n - 1; ++i) {
            int ph = leftPeaks[i].second;
            if (ph > rightPeaks[i].second) {
                ph = rightPeaks[i].second;
            }
            if (height[i] < ph) {
                res += ph - height[i];
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
        {{0,1,0,2,1,0,1,3,2,1,2,1}},
    };

    vector< int > answers {
        6,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = trap::Solution().trap3(dp.height);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
