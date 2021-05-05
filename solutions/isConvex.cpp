// isConvex.cpp
// leetcode
//
// Created by  Song Ding on 10/26/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace isConvex {
/*
// TODO: copy problem statement here
 469. Convex Polygon

 Given a list of points that form a polygon when joined sequentially, find if this polygon is convex (Convex polygon definition).

 Note:

 There are at least 3 and at most 10,000 points.
 Coordinates are in the range -10,000 to 10,000.
 You may assume the polygon formed by given points is always a simple polygon (Simple polygon definition). In other words, we ensure that exactly two edges intersect at each vertex, and that edges otherwise don\'t intersect each other.
 Example 1:

 [[0,0],[0,1],[1,1],[1,0]]

 Answer: True

 Explanation:
 Example 2:

 [[0,0],[0,10],[10,10],[10,0],[5,5]]

 Answer: False
 */

class Solution {
public:
    /**
     * for any edge of the polygon, all nodes are at one side of the line(except the two vertices)
     * that are on the line.
     * Computation cost is O(n^2).
     */
    bool isConvex(vector<vector<int>>& points) {
        int n = points.size();
        for (int i = 0; i < n; ++i) {
            vector<int>& p = points[i];
            vector<int>& q = points[(i+1)%n];
            // construct line: ay+bx+c=0;
            int a = p[0]-q[0];
            int b = q[1]-p[1];
            int c = p[1]*q[0]-p[0]*q[1];
            
            // test all
            int j = (i+2)%n;
            bool sign = (a * points[j][1] + b * points[j][0] + c) > 0;
            for (j = (j+1)%n; j != i; j=(j+1)%n) {
                bool sj = (a * points[j][1] + b * points[j][0] + c) > 0;
                if (sj != sign) {
                    return false;
                }
            }
        }
        return true;
    }
    
    /**
     * O(n) solution:
     * say the vertices clockwise starting at A,B,C,D,E,...
     * then slope(AB)-slope(AC) is negative, same for slope(BC)-slope(BD),
     * ... for slope(LA)-slope(LB).
     * if vertices are counterclockwise, then the diff would be positive.
     */
    bool isConvex2(vector<vector<int>>& points) {
        int n = points.size(), pre = 0, cur = 0;
        for (int i = 0; i < n; ++i) {
            int dx1 = points[(i+1)%n][0] - points[i][0];
            int dy1 = points[(i+1)%n][1] - points[i][1];
            int dx2 = points[(i+2)%n][0] - points[i][0];
            int dy2 = points[(i+2)%n][1] - points[i][1];
            cur = dx1*dy2 - dx2*dy1;
            if (cur != 0) {
                if (cur * pre < 0) {
                    return false;
                }
                pre = cur;
            }
        }
        return true;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> points;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{0,0},{0,1},{1,1},{1,0}}},
        {{{0,0},{0,10},{10,10},{10,0},{5,5}}},
    };

    vector< bool > answers {
        true,
        false,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = isConvex::Solution().isConvex2(dp.points);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
