// minAreaFreeRect.cpp
// leetcode
//
// Created by  Song Ding on 6/9/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minAreaFreeRect {
/*
// TODO: copy problem statement here
 963. Minimum Area Rectangle II
 Medium
 
 55
 
 106
 
 Favorite
 
 Share
 Given a set of points in the xy-plane, determine the minimum area of any rectangle formed from these points, with sides not necessarily parallel to the x and y axes.
 
 If there isn't any rectangle, return 0.
 
 
 
 Example 1:
 
 
 
 Input: [[1,2],[2,1],[1,0],[0,1]]
 Output: 2.00000
 Explanation: The minimum area rectangle occurs at [1,2],[2,1],[1,0],[0,1], with an area of 2.
 Example 2:
 
 
 
 Input: [[0,1],[2,1],[1,1],[1,0],[2,0]]
 Output: 1.00000
 Explanation: The minimum area rectangle occurs at [1,0],[1,1],[2,1],[2,0], with an area of 1.
 Example 3:
 
 
 
 Input: [[0,3],[1,2],[3,1],[1,3],[2,1]]
 Output: 0
 Explanation: There is no possible rectangle to form from these points.
 Example 4:
 
 
 
 Input: [[3,1],[1,1],[0,1],[2,1],[3,3],[3,2],[0,2],[2,3]]
 Output: 2.00000
 Explanation: The minimum area rectangle occurs at [2,1],[2,3],[3,3],[3,1], with an area of 2.
 
 
 Note:
 
 1 <= points.length <= 50
 0 <= points[i][0] <= 40000
 0 <= points[i][1] <= 40000
 All points are distinct.
 Answers within 10^-5 of the actual value will be accepted as correct.
 */

class Solution {
public:
   /**
    * method 3:
    *  all any two points (a,b), compute the distance, group these pair based on distance.
    *  within each group, any two pairs that share a mid point will form a rectangle.
    *
    */
    double minAreaFreeRect(vector<vector<int>>& points) {
        unordered_map<long, vector<vector<int>>> groups;
        int n = points.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                long d = distSquare(points[i], points[j]);
                groups[d].push_back({i,j});
            }
        }
        
        double res = INT_MAX;
        for (const auto& gp : groups) {
            const auto& members = gp.second;
            // group by mid point
            unordered_map<vector<int>, vector<vector<int>>, vhash> mpg;
            for (const auto& p : members) {
                vector<int> mp(2);
                mp[0] = points[p[0]][0]+points[p[1]][0];
                mp[1] = points[p[0]][1]+points[p[1]][1];
                mpg[mp].push_back(p);
            }
            
            for (const auto& p : mpg) {
                const auto& g = p.second;
                int gn = g.size();
                for (int i = 0; i < gn; ++i) {
                    for (int j = i+1; j < gn; ++j) {
                        res = min(res, area(points[g[i][0]], points[g[i][1]], points[g[j][0]]));
                    }
                }
            }
        }
        if (res == INT_MAX) {
            res = 0;
        }
        return res;
    }
private:
    /**
     * brutal force:
     * as there are at most 50 points, randomly pick 3 points(a,b,c) and compute
     * the other point d.
     *
     * for any two points a, b, use them as a pair at opposite corner, let m = (a+b)/2.
     * then ab divides all other points into two groups, one above ab, the other below.
     * only need to check one part; this would significantly cut computation, but still
     * is N^3.
     * ps: one group can be ordered based on distance to the mid point m.
     * only fixed
     *
     *
     * method 3:
     *  all any two points (a,b), compute the distance, group these pair based on distance.
     *  within each group, any two pairs that share a mid point will form a rectangle.
     *
     */
    double minAreaFreeRectBF(vector<vector<int>>& points) {
        unordered_set<vector<int>, vhash> all;
        for (const auto& p : points) {
            all.insert(p);
        }
        
        double res = INT_MAX;
        int n = points.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                for (int k = j+1; k < n; ++k) {
                    vector<vector<int>> positions {
                        {i,j,k}, {i,k,j},{j,k,i}
                    };
                    for (const auto& pos : positions) {
                        vector<int> d = the4thPoint(points[pos[0]], points[pos[1]], points[pos[2]]);
                        if (d.size() && all.find(d) != all.end()) {
                            res = min(res, area(points[pos[0]], points[pos[1]], points[pos[2]]));
                        }
                    }
                }
            }
        }
        if (res == INT_MAX) {
            return 0;
        }
        return res;
    }

private:
    struct vhash {
        size_t operator()(const vector<int>& p) const {
            return (size_t)p[0] * 80000 + p[1];
        }
    };
    // return the other point d, if point a, b, c and d can form a rectangle
    // most likely a, b, c can NOT form a 90 angle
    // if not, return an empty vector.
    vector<int> the4thPoint(const vector<int>& a, const vector<int>& b, const vector<int>& c) {
        vector<int> d;
        //TODO: check whether abc forms a 90 degree angle
        if ((a[0]-c[0]) * (b[0]-c[0]) + (a[1]-c[1]) * (b[1]-c[1]) == 0) {
            d.push_back(a[0]+b[0]-c[0]);
            d.push_back(a[1]+b[1]-c[1]);
        }
        return d;
    }
    long distSquare(const vector<int>& a, const vector<int>& b) {
        return ((long)a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1]) * (a[1]-b[1]);
    }
    double area(const vector<int>& a, const vector<int>& b, const vector<int>& c) {
        double side1 = ((double)a[0]-c[0])*(a[0]-c[0]) + (a[1]-c[1]) * (a[1] - c[1]);
        double side2 = ((double)b[0]-c[0])*(b[0]-c[0]) + (b[1]-c[1]) * (b[1] - c[1]);
        return sqrt(side1 * side2);
    }
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
        {{{1,2},{2,1},{1,0},{0,1}}},
        {{{0,1},{2,1},{1,1},{1,0},{2,0}}},
        {{{0,3},{1,2},{3,1},{1,3},{2,1}}},
        {{{3,1},{1,1},{0,1},{2,1},{3,3},{3,2},{0,2},{2,3}}}
    };

    vector< double > answers {
        2.00000,
        1,00000,
        0,
        2.00000
        
    };
    
    cout << sizeof(size_t) << endl;

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minAreaFreeRect::Solution().minAreaFreeRect(dp.points);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
