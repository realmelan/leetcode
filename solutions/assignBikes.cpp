//
//  assignBikes.cpp
//  leetcode
//
//  Created by Song Ding on 4/8/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace assignBikes {
/*
// TODO: copy problem statement here
 1160 · Campus Bikes
 算法
 Medium
 Accepted Rate
 43%

 DescriptionSolutionNotesDiscussLeaderboard
 Description
 On a campus represented as a 2D grid, there are
 N
 N workers and
 M
 M bikes, with
 N
 ≤
 M
 N≤M. Each worker and bike is a 2D coordinate on this grid.

 Our goal is to assign a bike to each worker. Among the available bikes and workers, we choose the (worker, bike) pair with the shortest Manhattan distance between each other, and assign the bike to that worker. (If there are multiple (worker, bike) pairs with the same shortest Manhattan distance, we choose the pair with the smallest worker index; if there are multiple ways to do that, we choose the pair with the smallest bike index). We repeat this process until there are no available workers.

 The Manhattan distance between two points
 p
 1
 p
 ​1
 ​​  and
 p
 2
 p
 ​2
 ​​  is
 M
 a
 n
 h
 a
 t
 t
 a
 n
 (
 p
 1
 ,
 p
 2
 )
 =
 ∣
 p
 1
 .
 x
 −
 p
 2
 .
 x
 ∣
 +
 ∣
 p
 1
 .
 y
 −
 p
 2
 .
 y
 ∣
 Manhattan(p
 ​1
 ​​ ,p
 ​2
 ​​ )=∣p
 ​1
 ​​ .x−p
 ​2
 ​​ .x∣+∣p
 ​1
 ​​ .y−p
 ​2
 ​​ .y∣.

 Return a vector
 a
 n
 s
 ans of length
 N
 N, where
 a
 n
 s
 i
 ans
 ​i
 ​​  is the index (0-indexed) of the bike that the
 i
 i-th worker is assigned to.

 0
 ≤
 w
 o
 r
 k
 e
 r
 s
 [
 i
 ]
 [
 j
 ]
 ,
 b
 i
 k
 e
 s
 [
 i
 ]
 [
 j
 ]
 <
 1
 0
 0
 0
 0≤workers[i][j],bikes[i][j]<1000
 All worker and bike locations are distinct.
 1
 ≤
 w
 o
 r
 k
 e
 r
 s
 .
 l
 e
 n
 g
 t
 h
 ≤
 b
 i
 k
 e
 s
 .
 l
 e
 n
 g
 t
 h
 ≤
 1
 0
 0
 0
 1≤workers.length≤bikes.length≤1000
 Example
 Example 1

 Input:
 [[0,0],[2,1]]
 [[1,2],[3,3]]
 Output: [1,0]
 Explanation:
 Worker 1 grabs Bike 0 as they are closest (without ties), and Worker 0 is assigned Bike 1. So the output is [1, 0].
 图片

 Example 2

 Input:
 [[0,0],[1,1],[2,0]]
 [[1,0],[2,2],[2,1]]
 Output: [0,2,1]
 Explanation:
 Worker 0 grabs Bike 0 at first. Worker 1 and Worker 2 share the same distance to Bike 2, thus Worker 1 is assigned to Bike 2, and Worker 2 will take Bike 1. So the output is [0,2,1].
 图片
*/
class Solution {
public:
    // TODO: copy function signature here
    vector<int> assignBikes(vector<vector<int>> &workers, vector<vector<int>> &bikes) {
        // write your code here
        int nw = workers.size(), nb = bikes.size();
        vector<priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>>> q(nw);
        for (int i = 0; i < nw; ++i) {
          for (int j = 0; j < nb; ++j) {
            q[i].push({dist(workers[i], bikes[j]), j});
          }
        }
        int cnt = 0;
        vector<bool> bused(nb, false);
        vector<int> res(nw, -1);
        while (cnt < nw) {
          int mdist = 2000, mwi = -1, mbi = -1;
          for (int i = 0; i < nw; ++i) {
            if (res[i]<0) {
              while (q[i].size() && bused[q[i].top()[1]]) {
                q[i].pop();
              }
              if (q[i].top()[0] < mdist) {
                  mdist = q[i].top()[0];
                mwi = i;
                mbi = q[i].top()[1];
              }
            }
          }
          ++cnt;
          res[mwi] = mbi;
          bused[mbi] = true;
        }
        return res;
    }
    int dist(vector<int>&a, vector<int>& b) {
      return abs(a[0]-b[0]) + abs(a[1]-b[1]);
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> workers;
        vector<vector<int>> bikes;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{{0,0},{1,1},{2,0}},{{1,0},{2,2},{2,1}}},
    };
    // TODO: provide expected results here
    vector<vector<int>> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = assignBikes::Solution().assignBikes(dp.workers, dp.bikes);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
