//
//  isPrintable.cpp
//  leetcode
//
//  Created by Song Ding on 3/9/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace isPrintable {
/*
// TODO: copy problem statement here
 1591. Strange Printer II My SubmissionsBack to Contest
 User Accepted: 210
 User Tried: 396
 Total Accepted: 212
 Total Submissions: 631
 Difficulty: Hard
 There is a strange printer with the following two special requirements:

 On each turn, the printer will print a solid rectangular pattern of a single color on the grid. This will cover up the existing colors in the rectangle.
 Once the printer has used a color for the above operation, the same color cannot be used again.
 You are given a m x n matrix targetGrid, where targetGrid[row][col] is the color in the position (row, col) of the grid.

 Return true if it is possible to print the matrix targetGrid, otherwise, return false.

  

 Example 1:



 Input: targetGrid = [[1,1,1,1],[1,2,2,1],[1,2,2,1],[1,1,1,1]]
 Output: true
 Example 2:



 Input: targetGrid = [[1,1,1,1],[1,1,3,3],[1,1,3,4],[5,5,1,4]]
 Output: true
 Example 3:

 Input: targetGrid = [[1,2,1],[2,1,2],[1,2,1]]
 Output: false
 Explanation: It is impossible to form targetGrid because it is not allowed to print the same color in different turns.
 Example 4:

 Input: targetGrid = [[1,1,1],[3,1,3]]
 Output: false
  

 Constraints:

 m == targetGrid.length
 n == targetGrid[i].length
 1 <= m, n <= 60
 1 <= targetGrid[row][col] <= 60
*/
class Solution {
public:
    // TODO: copy function signature here
    // if a cell(Ca) has 4 lines of neighbors(left,right,up,down)
    // if a color(Cb) appears in at least 2 directions, then
    // there is a happen-before relation between Ca and Cb
    // all these relations should form a DAG
    // we can use topological sort to verify that that there is no circle.
    bool isPrintable(vector<vector<int>>& tg) {
        int m = tg.size(), n = tg[0].size();
        vector<vector<int>> before(61);
        unordered_set<int> colors;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int c = tg[i][j];
                colors.insert(c);
                vector<set<int>> neigh(4);
                for (int k = i-1; k >= 0; --k) {
                    neigh[0].insert(tg[k][j]);
                }
                for (int k = i+1; k < m; ++k) {
                    neigh[1].insert(tg[k][j]);
                }
                for (int k = j-1; k >= 0; --k) {
                    neigh[2].insert(tg[i][k]);
                }
                for (int k = j+1; k < n; ++k) {
                    neigh[3].insert(tg[i][k]);
                }
                // check whether a color appears in at least two
                for (int ni = 0; ni < 3; ++ni) {
                    for (int nj = ni+1; nj < 4; ++nj) {
                        set_intersection(begin(neigh[ni]), end(neigh[ni]), begin(neigh[nj]), end(neigh[nj]), back_inserter(before[c]));
                    }
                }
            }
        }
        // do topological sort
        vector<vector<int>> conns(61);
        vector<int> in(61,0);
        queue<int> q;
        for (auto c : colors) {
            unordered_set<int> t(begin(before[c]), end(before[c]));
            t.erase(c);
            for (auto j : t) {
                conns[j].push_back(c);
            }
            in[c] = t.size();
            if (!in[c]) {
                q.push(c);
            }
        }
        while (q.size()) {
            int c = q.front();
            q.pop();
            colors.erase(c);
            for (auto nc : conns[c]) {
                if (--in[nc] == 0) {
                    q.push(nc);
                }
            }
        }
        return colors.empty();
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> tg;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{{1,2,1},{2,1,2},{1,2,1}}},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = isPrintable::Solution().isPrintable(dp.tg);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
