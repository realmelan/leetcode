//
//  outerTrees.cpp
//  leetcode
//
//  Created by  Song Ding on 3/6/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;
/**
 587. Erect the Fence
 Hard

 152

 159

 Favorite

 Share
 There are some trees, where each tree is represented by (x,y) coordinate in a two-dimensional garden. Your job is to fence the entire garden using the minimum length of rope as it is expensive. The garden is well fenced only if all the trees are enclosed. Your task is to help find the coordinates of trees which are exactly located on the fence perimeter.

  

 Example 1:

 Input: [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
 Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
 Explanation:

 Example 2:

 Input: [[1,2],[2,2],[4,2]]
 Output: [[1,2],[2,2],[4,2]]
 Explanation:

 Even you only have trees in a line, you need to use rope to enclose them.
  

 Note:

 All trees should be enclosed together. You cannot cut the rope to enclose trees that will separate them in more than one group.
 All input integers will range from 0 to 100.
 The garden has at least one tree.
 All coordinates are distinct.
 Input points have NO order. No order required for output.
 input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
 */

namespace outerTrees {
    /**
     * Definition for a point.
     * struct Point {
     *     int x;
     *     int y;
     *     Point() : x(0), y(0) {}
     *     Point(int a, int b) : x(a), y(b) {}
     * };
     */
    class Solution {
    public:
        /**
         gift wrapping algorithm to detech all points forming the convex hull.
         */
        vector<Point> outerTrees(vector<Point>& points) {
            int n = points.size();
            vector<Point> res;
            int lm = 0;
            for (int i = 0; i < n; ++i) {
                if (points[i].x < points[lm].x) {
                    lm = i;
                }
            }
            
            res.push_back(points[lm]);
            int cur = lm;
            while (true) {
                Point& start = points[cur];
                int nextId = 0;
                int dist = pointDist(start, points[nextId]);
                vector<int> other;
                for (int i = 1; i < n; ++i) {
                    if (i == cur) {
                        continue;
                    }
                    int cross = crossProduct(start, points[nextId], points[i]);
                    int nd = pointDist(start, points[i]);
                    if (nextId == cur || cross > 0) {
                        nextId = i;
                        other.clear();
                        dist = nd;
                    } else if (cross == 0 && nd > dist) {
                        other.push_back(nextId);
                        nextId = i;
                        dist = nd;
                    }
                }
                for (auto i : other) {
                    res.push_back(points[i]);
                }
                if (nextId == lm) {
                    break;
                }
                res.push_back(points[nextId]);
            }
            return res;
        }
        int crossProduct(Point& a, Point& b, Point& c) {
            return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
        }
        int pointDist(Point& a, Point& b) {
            return (a.x - b.x) * (a.x - b.x) + (a.y-b.y)*(a.y-b.y);
        }
        /**
         First, find two points, with the smallest and largest
         x coordinates, say x(left) and y(right). The line between x and y divides
         all the other points into two groups: up part and down.
         
         For the up part, find a point which is farthest from line (x,y)
         say, p, then p will not be enclosed by other polygons. Now, points
         inside triangle pxy should be ignored, and for the points outside
         pxy, another two groups are found: ones outside px, and ones outside py.
         recursively do the same for the two parts.
         
         the points outside px can be viewed as on the up side of px, same for py.
         
         Same for the down part, except when dividing points, check points below px,py.
         */
        vector<Point> outerTrees2(vector<Point>& points) {
            vector<Point> res;
            int n = points.size();
            if (n <= 3) {
                res.insert(res.begin(), points.begin(), points.end());
                return res;
            }
            Point left(INT_MAX, 0), right(INT_MIN, 0);
            for (const auto& p : points) {
                if (p.x < left.x) {
                    left = p;
                }
                if (p.x > right.x) {
                    right = p;
                }
            }
            
            if (left.x == right.x) {
                res.insert(res.begin(), points.begin(), points.end());
                return res;
            }
            
            // divide points into two groups
            res.push_back(left);
            res.push_back(right);
            vector<Point> up, down, online;
            for (const auto& p : points) {
                if ((p.x != left.x || p.y != left.y)
                    && (p.x != right.x || p.y != right.y)) {
                    double d = dist(left, right, p);
                    if (d > 0) {
                        up.push_back(p);
                    } else if (d < 0) {
                        down.push_back(p);
                    } else {
                        online.push_back(p);
                    }
                }
            }
            
            if (up.size()) {
                find(left, right, up, 1, res);
            }
            if (down.size()) {
                find(left, right, down, -1, res);
            }
            
            if (up.empty() || down.empty()) {
                res.insert(res.end(), online.begin(), online.end());
            }
            return res;
            
        }
    private:
        void find(Point x, Point y, vector<Point>& points, int upflag, vector<Point>& res) {
            if (points.size() == 1) {
                res.push_back(points.back());
                return;
            }
            
            double md = 0;
            Point mdp;
            for (const auto& p : points) {
                double d = dist(x, y, p);
                if (abs(d) > md) {
                    md = abs(d);
                    mdp = p;
                }
            }
            res.push_back(mdp);
            
            vector<Point> px, py, pxline, pyline;
            for (const auto& p : points) {
                if (p.x == mdp.x && p.y == mdp.y) {
                    continue;
                }
                double dpx = dist(x, mdp, p);
                double dpy = dist(mdp, y, p);
                
                if (dpx == 0) {
                    pxline.push_back(p);
                } else if (dpx * upflag > 0) {
                    px.push_back(p);
                }
                
                if (dpy == 0) {
                    pyline.push_back(p);
                } else if (dpy * upflag > 0) {
                    py.push_back(p);
                }
            }
            
            if (px.size()) {
                find(x, mdp, px, upflag, res);
            } else {
                res.insert(res.end(), pxline.begin(), pxline.end());
            }
            if (py.size()) {
                find(mdp, y, py, upflag, res);
            } else {
                res.insert(res.end(), pyline.begin(), pyline.end());
            }
        }
        double dist(Point l, Point r, Point p) {
            double a = (r.x - l.x) * p.y - (r.y - l.y) * p.x + l.x * r.y - r.x * l.y;
            double b = sqrt((double)((r.y - l.y) * (r.y - l.y) + (r.x - l.x) * (r.x - l.x)));
            return a / b;
        }
    };
}
/*
int main() {
    vector<Point> points {
        //{1,1},{2,2},{2,0},{2,4},{3,3},{4,2}
        //{1,2},{2,2},{4,2}
        {3,3},{2,4},{2,2},{7,4},{3,4}
    };
    vector<Point> res = outerTrees::Solution().outerTrees2(points);
    printVector(res);
}
// */
