// isSelfCrossing.cpp
// leetcode
//
// Created by  Song Ding on 3/25/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

/**
 335. Self Crossing
 Hard

 96

 286

 Favorite

 Share
 You are given an array x of n positive numbers. You start at point (0,0) and moves x[0] metres to the north, then x[1] metres to the west, x[2] metres to the south, x[3] metres to the east and so on. In other words, after each move your direction changes counter-clockwise.

 Write a one-pass algorithm with O(1) extra space to determine, if your path crosses itself, or not.

  

 Example 1:

 ┌───┐
 │           │
 └───┼──>
        │

 Input: [2,1,1,2]
 Output: true
 Example 2:

 ┌──────┐
 │                     │
 │
 │
 └────────────>

 Input: [1,2,3,4]
 Output: false
 Example 3:

 ┌───┐
 │           │
 └───┼>

 Input: [1,1,1,1]
 Output: true
 */
namespace isSelfCrossing {

class Solution {
public:
    /**
     * only when it is contracting that it is  possible self-crossing, that is x5 <= x3:
     * here x5 is the previous move, and x4 is previous move to x5, ...
     * there are 2 scenarios that contracting leads to self-crossing:
     * 1, x5 <= x3 && x4 <= x2, in this case, xx(current move) has to be larger than x4
     * 2, when x4 > x2, , when xx >= x4, it will self-crossing; when xx < x4, it is possible that
     * it will self-cross, that is, when xx crosses then line by x1 (x5 >= x3-x1 && xx > x4-x2)
     * graph for scenario 1:
     __________
     |                |
     |                |
     |         |      |
     |_____|      |
            |
     * scenario 2:
     __________________
     |                              |
     |                              |
     |                              |
     |        ____________ |
     |             |
     |             |
     |_______|
     * in both graphs, the bottom edge is x5, left most vertical edge is x4, top most edge is x3,
     * right most vertical edge is x2, the mid vertical edge is xx, and the other horizontal edge
     * is x1(graph 2).
     */
    bool isSelfCrossing4(vector<int>& x) {
        int n = x.size();
        if (n <= 3) {
            return false;
        }
        int x1 = 0, x2 = 0, x3 = x[0], x4 = x[1], x5 = x[2];
        for (int i = 3; i < n; ++i) {
            int xx = x[i];
            if (x5 <= x3 && (xx >= x4 || (x4 > x2 && xx >= x4-x2 && x5 >= x3-x1))) {
                return true;
            }
            x1 = x2;
            x2 = x3;
            x3 = x4;
            x4 = x5;
            x5 = xx;
        }
        return false;
    }
    
    bool isSelfCrossing3(vector<int>& x) {
        int n = x.size();
        if (n <= 3) {
            return false;
        }
        int x1 = 0, x2 = 0, x3 = x[0], x4 = x[1], x5 = x[2];
        for (int i = 3; i < n; ++i) {
            int xx = x[i];
            // expand->contract
            if ((x4 > x2 && ((x5 <= x3 && x5 >= x3-x1 && xx >= x4-x2)
                ||(x5 <= x3-x1 && xx >= x4)))
            ||(x4 <= x2 && (x5 >= x3))) { // contract->contract
                return true;
            }
            x1 = x2;
            x2 = x3;
            x3 = x4;
            x4 = x5;
            x5 = xx;
        }
        return false;
    }
    /**
     * https://leetcode.com/problems/self-crossing/discuss/79133/C%2B%2B-simple-solution
     * check 1st reply
     *
     The graph either ends as one enlarging spiral or
     ends as a two spiral, one enlarging spiral followed
     by one contracting spiral.
     
     To not self cross, either ends as an enlarging spiral
     or, ends in the contracting spiral, not crossing.
     
     in enlarging spiral, x[i] > x[i - 2], while in contracting
     spiral, x[i] < x[i - 2].
     */
    bool isSelfCrossing(vector<int>& x) {
        x.insert(x.begin(), 4, 0);
        int n = x.size();
        int i = 4;
        // enlarging spiral
        for (; i < n && x[i] > x[i - 2]; ++i);
        if (i >= n) {
            return false;
        }
        
        // adjust x[i - 1]
        if (x[i] >= x[i - 2] - x[i - 4]) {
            x[i - 1] -= x[i - 3];
        }
        
        // contracting spiral
        for (++i; i < n && x[i] < x[i - 2]; ++i);
        return i < n;
    }
    /**
     This use extra memory to store all vertical lines
     and horizontal lines.
     */
    bool isSelfCrossing2(vector<int>& x) {
        int n = x.size();
        
        if (n >= 4) {
            multimap<int, vector<int>> vs;
            multimap<int, vector<int>> hs;
            int px = 0;
            int py = 0;
            
            int i = 0;
            vector<int> xsign{0, -1, 0, 1};
            vector<int> ysign{1, 0, -1, 0};
            while(i < n) {
                int npx = px + xsign[i%4] * x[i];
                int npy = py + ysign[i%4] * x[i];
                ++i;
                // check whether there is cross
                if (npx == px) {
                    // a vertical line
                    int yhigh = max(npy, py);
                    int ylow = min(npy, py);
                    
                    auto it = vs.equal_range(npx);
                    for (auto yit = it.first; yit != it.second; ++yit) {
                        if ((ylow <= (yit->second)[0] && (yit->second)[0] <= yhigh)
                            || (ylow <= (yit->second)[1] && (yit->second)[1] <= yhigh)) {
                            return true;
                        }
                    }
                    
                    auto y1 = hs.lower_bound(ylow);
                    auto y2 = hs.upper_bound(yhigh);
                    while (y1 != y2) {
                        if (y1->first != py && (y1->second)[0] <= px && px <= (y1->second)[1]) {
                            return true;
                        }
                        ++y1;
                    }
                    vs.insert(make_pair(px, vector<int>{ylow, yhigh}));
                } else {
                    // a horizontal line
                    int xhigh = max(npx, px);
                    int xlow = min(npx, px);
                    
                    auto it = hs.equal_range(npy);
                    for (auto xit = it.first; xit != it.second; ++xit) {
                        if ((xlow <= (xit->second)[0] && (xit->second)[0] <= xhigh)
                            || (xlow <= (xit->second)[1] && (xit->second)[1] <= xhigh)) {
                            return true;
                        }
                    }
                    
                    auto x1 = vs.lower_bound(xlow);
                    auto x2 = vs.upper_bound(xhigh);
                    while (x1 != x2) {
                        if (x1->first != px && (x1->second)[0] <= py && py <= (x1->second)[1]) {
                            return true;
                        }
                        ++x1;
                    }
                    hs.insert(make_pair(py, vector<int>{xlow, xhigh}));
                }
                
                px = npx;
                py = npy;
            }
        }
        return false;
    }

private:
};

}

/*/
int main() {
    struct d {
        vector<int> x;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3,4}},
        {{1,1,1,1}},
        {{2,1,1,2}},
        {{1,1,2,1,1}},
        {{1,1,2,2,1,1}},
        {{3,3,4,2,2}},
        {{3,3,3,2,1,1}},
    };

    vector< bool > answers {
        false,
        true,
        true,
        true,
        true,
        false,
        false,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = isSelfCrossing::Solution().isSelfCrossing4(dp.x);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
