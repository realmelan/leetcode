//
//  getMinDistSum.cpp
//  leetcode
//
//  Created by Song Ding on 9/16/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace getMinDistSum {
/*
// TODO: copy problem statement here
 1515. Best Position for a Service Centre
 Hard

 80

 123

 Add to List

 Share
 A delivery company wants to build a new service centre in a new city. The company knows the positions of all the customers in this city on a 2D-Map and wants to build the new centre in a position such that the sum of the euclidean distances to all customers is minimum.

 Given an array positions where positions[i] = [xi, yi] is the position of the ith customer on the map, return the minimum sum of the euclidean distances to all customers.

 In other words, you need to choose the position of the service centre [xcentre, ycentre] such that the following formula is minimized:


 Answers within 10^-5 of the actual value will be accepted.

  

 Example 1:


 Input: positions = [[0,1],[1,0],[1,2],[2,1]]
 Output: 4.00000
 Explanation: As shown, you can see that choosing [xcentre, ycentre] = [1, 1] will make the distance to each customer = 1, the sum of all distances is 4 which is the minimum possible we can achieve.
 Example 2:


 Input: positions = [[1,1],[3,3]]
 Output: 2.82843
 Explanation: The minimum possible sum of distances = sqrt(2) + sqrt(2) = 2.82843
 Example 3:

 Input: positions = [[1,1]]
 Output: 0.00000
 Example 4:

 Input: positions = [[1,1],[0,0],[2,0]]
 Output: 2.73205
 Explanation: At the first glance, you may think that locating the centre at [1, 0] will achieve the minimum sum, but locating it at [1, 0] will make the sum of distances = 3.
 Try to locate the centre at [1.0, 0.5773502711] you will see that the sum of distances is 2.73205.
 Be careful with the precision!
 Example 5:

 Input: positions = [[0,1],[3,2],[4,5],[7,6],[8,9],[11,1],[2,12]]
 Output: 32.94036
 Explanation: You can use [4.3460852395, 4.9813795505] as the position of the centre.
  

 Constraints:

 1 <= positions.length <= 50
 positions[i].length == 2
 0 <= positions[i][0], positions[i][1] <= 100
*/
class Solution {
public:
    double getMinDistSum3(vector<vector<int>>& positions) {
        double step = 1e-6;
        double l = -100, r = 200, res = 0;
        while (r-l > step) {
            double m = (l+r)/2;
            res = minDistance2(m, positions);
            double md2 = minDistance2(m+step, positions);
            if (res < md2) {
                r = m;
            } else  {
                l = m+step;
            }
        }
        return res;
    }
    double minDistance2(double x, vector<vector<int>>& positions) {
        double step = 1e-6;
        double l = -100, r = 200, res = 0;
        int cnt = 0;
        while (r-l > step) {
            ++cnt;
            double m = (l+r)/2;
            res = distance(x, m, positions);
            double md2 = distance(x, m+step, positions);
            if (res < md2) {
                r = m;
            } else {
                l = m+step;
            }
        }
        return res;
    }
    // Binary search:
    // find the x value whose min distance to all positions is smallest using mountain array peak binary search
    //    when determine the min distance for x, also use mountain array peak binary search
    //
    double getMinDistSum2(vector<vector<int>>& positions) {
        double step = 1e-9;
        double l = -100, r = 200, res = 0;
        while (r-l > step) {
            double m = l + (r-l)/3;
            double m2 = r - (r-l)/3;
            res = minDistance(m, positions);
            double md2 = minDistance(m2, positions);
            if (res < md2) {
                r = m2;
            } else if (res > md2) {
                l = m;
            } else {
                l = m;
                r = m2;
            }
        }
        return res;
    }
    double minDistance(double x, vector<vector<int>>& positions) {
        double step = 1e-9;
        double l = -100, r = 200, res = 0;
        int cnt = 0;
        while (r-l > step) {
            ++cnt;
            double m = l + (r-l)/3;
            double m2 = r - (r-l)/3;
            res = distance(x, m, positions);
            double md2 = distance(x, m2, positions);
            if (res < md2) {
                r = m2;
            } else if (res > md2) {
                l = m;
            } else {
                l = m;
                r = m2;
            }
        }
        return res;
    }
    double distance(double x, double y, vector<vector<int>>& positions) {
        double res = 0;
        for (auto& p : positions) {
            res += hypot(x-p[0], y-p[1]);
        }
        return res;
    }
    // TODO: copy function signature here
    // starting from Mannhattan distance center
    // do BFS search and only follow the directions which reduce
    // euclidean distance
    double getMinDistSum(vector<vector<int>>& positions) {
        int n = positions.size();
        vector<int> xs, ys;
        for (auto& p : positions) {
            xs.push_back(p[0]);
            ys.push_back(p[1]);
        }
        //sort(begin(xs), end(xs));
        //sort(begin(ys), end(ys));
        nth_element(begin(xs), begin(xs)+n/2, end(xs));
        double mx = xs[n/2];
        nth_element(begin(ys), begin(ys)+n/2, end(ys));
        double my = ys[n/2];
        double res = distance(mx, my, positions);
        static const vector<int> dirs{1,0,-1,0,1};
        double step = 1;
        // x,y, distance
        vector<tuple<double,double,double>> q;
        q.emplace_back(mx, my, res);
        unordered_map<double, unordered_set<double>> v;
        while (step > 1e-6) {
            vector<tuple<double,double,double>> nq;
            unordered_map<double, unordered_set<double>> nv;
            for (int j = 0; j < q.size(); ++j) {
                auto [x, y, d] = q[j];
                for (int i = 0; i < 4; ++i) {
                    double nx = x + dirs[i]*step;
                    double ny = y + dirs[i+1]*step;
                    double nd = distance(nx, ny, positions);
                    if (nd <= d && !v[nx].count(ny)) {
                        v[nx].insert(ny);
                        q.emplace_back(nx, ny, nd);
                        if (nd <= res) {
                            if (nd < res) {
                                nq.clear();
                                nv.clear();
                            }
                            nq.emplace_back(nx, ny, nd);
                            nv[nx].insert(ny);
                            res = nd;
                        }
                    }
                }
            }
            q.swap(nq);
            v.swap(nv);
            step /= 2;
        }
        return res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> positions;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        //{{{0,1},{1,0},{1,2},{2,1}}},
        //{{{1,1},{3,3}}},
        //{{{1,1}}},
        //{{{1,1},{0,0},{2,0}}},
        {{{0,1},{3,2},{4,5},{7,6},{8,9},{11,1},{2,12}}},
    };
    // TODO: provide expected results here
    vector<double> answers {
        4,
        2.82843,
        0,
        2.73205,
        32.94036,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = getMinDistSum::Solution().getMinDistSum3(dp.positions);
        cout << setprecision(16) << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
