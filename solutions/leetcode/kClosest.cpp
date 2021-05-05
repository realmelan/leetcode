// kClosest.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace kClosest {
/*
// TODO: copy problem statement here
 973. K Closest Points to Origin
 Medium
 
 399
 
 42
 
 Favorite
 
 Share
 We have a list of points on the plane.  Find the K closest points to the origin (0, 0).
 
 (Here, the distance between two points on a plane is the Euclidean distance.)
 
 You may return the answer in any order.  The answer is guaranteed to be unique (except for the order that it is in.)
 
 
 
 Example 1:
 
 Input: points = [[1,3],[-2,2]], K = 1
 Output: [[-2,2]]
 Explanation:
 The distance between (1, 3) and the origin is sqrt(10).
 The distance between (-2, 2) and the origin is sqrt(8).
 Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
 We only want the closest K = 1 points from the origin, so the answer is just [[-2,2]].
 Example 2:
 
 Input: points = [[3,3],[5,-1],[-2,4]], K = 2
 Output: [[3,3],[-2,4]]
 (The answer [[-2,4],[3,3]] would also be accepted.)
 
 
 Note:
 
 1 <= K <= points.length <= 10000
 -10000 < points[i][0] < 10000
 -10000 < points[i][1] < 10000
 */

class Solution {
public:
    /**
     * priority queue
     */
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        int n = points.size();
        if (K >= n) {
            return points;
        }
        
        priority_queue<vector<int>, vector<vector<int>>, SmallestDistanceFirst> pq;
        for (const auto& p : points) {
            pq.push(p);
        }
        vector<vector<int>> res;
        for (int i = 0; i < K; ++i) {
            res.push_back(pq.top());
            pq.pop();
        }
        return res;
    }

private:
    struct SmallestDistanceFirst {
        bool operator()(const vector<int>& a, const vector<int>& b) {
            int da = a[0]*a[0] + a[1]*a[1];
            int db = b[0]*b[0] + b[1]*b[1];
            return db < da;
        }
    };
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> points;
        int K;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{1,3},{-2,2}},1},
        {{{3,3},{5,-1},{-2,4}},2}
    };

    vector< vector<vector<int>> > answers {
        {{-2,2}},
        {{3,3},{-2,4}}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = kClosest::Solution().kClosest(dp.points, dp.K);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
