// maxPoints.cpp
// leetcode
//
// Created by  Song Ding on 6/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxPoints {
/*
// TODO: copy problem statement here
 149. Max Points on a Line
 Hard
 
 466
 
 1288
 
 Favorite
 
 Share
 Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
 
 Example 1:
 
 Input: [[1,1],[2,2],[3,3]]
 Output: 3
 Explanation:
 ^
 |
 |        o
 |     o
 |  o
 +------------->
 0  1  2  3  4
 Example 2:
 
 Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
 Output: 4
 Explanation:
 ^
 |
 |  o
 |     o        o
 |        o
 |  o        o
 +------------------->
 0  1  2  3  4  5  6
 NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
 */

class Solution {
public:
    static long mcd(long m, long n) {
        if (m < n) {
            swap(m, n);
        }
        while (m % n) {
            int t = m % n;
            m = n;
            n = t;
        }
        return n;
    }
    struct line {
        long a;
        long b;
        long c;
        line(int xa, int ya, int xb, int yb) {
            // line can be expressed as: ay = bx + c
            a = xb - xa;
            b = yb - ya;
            c = (long)xb * ya - (long)xa * yb;
            if (b == 0) {
                a = 1;
                c = ya;
                return;
            }
            
            // what if a, b, c have common divisor?
            int sign = 1;
            if (b < 0) {
                sign = -1;
                b *= -1;
            }
            long mcd1 = mcd(a, b);
            b *= sign;
            sign = 1;
            
            if (c == 0) {
                a /= mcd1;
                b /= mcd1;
                return;
            }
            
            sign = 1;
            if (c < 0) {
                c *= -1;
                sign = -1;
            }
            long mcd2 = mcd(a, c);
            c *= sign;
            sign = 1;
            
            long t = mcd(mcd1, mcd2);
            
            a /= t;
            b /= t;
            c /= t;
        }
        line(const line& l) {
            a = l.a;
            b = l.b;
            c = l.c;
        }
        line& operator=(const line& l) {
            a = l.a;
            b = l.b;
            c = l.c;
            return *this;
        }
        bool operator==(const struct line& l) const {
            return a == l.a && b == l.b && c == l.c;
        }
    };
    
    struct LineHash {
        size_t operator()(const line& l) const {
            static hash<string> sh;
            std::ostringstream oss;
            oss << l.a << "," << l.b << "," << l.c;
            return sh(oss.str());
        }
    };
    /**
     * group points by x coordinate, and then for loop through
     * the groups, find all possible lines resulting from the new
     * group:
     *   if a point in group[i] is on an existing line, increase
     *     the point count for that line
     *   else: add a new line and set # of points to 2.
     *
     * To make checking quicker, then each group would be a hash set.
     *
     * cost = O(N^3)
     */
    int maxPoints(vector<vector<int>>& points) {
        map<int, unordered_map<int,int>> groups;
        for (auto& p : points) {
            ++groups[p[0]][p[1]];
        }
        int res = 0;
        // create initial lines
        unordered_map<struct line, int, LineHash> lines;
        
        for (auto it = groups.begin(); it != groups.end(); ++it) {
            // check whether points are on existing lines
            int x = it->first;
            auto& ys = it->second;
            int cnt = 0;
            for (auto& y : ys) {
                cnt += y.second;
            }
            res = max(res, cnt);
            
            for (auto& p : lines) {
                long y = computeY(p.first, x);
                if (y < INT_MAX && ys.find(y) != ys.end()) {
                    p.second += ys[y];
                }
            }
            
            // create new lines from ys
            // TODO: how to deal with multiple y (same y value)
            for (auto y : ys) {
                for (auto git = groups.begin(); git != it; ++git) {
                    for (auto ya : git->second) {
                        line l(git->first, ya.first, x, y.first);
                        if (lines.find(l) == lines.end()) {
                            lines.insert(make_pair(l, ya.second + y.second));
                        }
                    }
                }
            }
        }
        
        for (const auto& p : lines) {
            res = max(res, p.second);
        }
        return res;
    }
    
    long computeY(const struct line& l, int x) {
        long t = (long)x * l.b + l.c;
        if (t % l.a == 0) {
            return t/l.a;
        } else {
            return INT_MAX;
        }
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
        //{{{1,1},{2,2},{3,3}}},
        //{{{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}}},
        //{{{0,0},{1,65536},{65536,0}}},
        //{{{0,0},{0,0}}},
        {{{2,3},{3,3},{-5,3}}}
    };

    vector< int > answers {
        3,
        4,
        2,
        2,
        3
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxPoints::Solution().maxPoints(dp.points);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
