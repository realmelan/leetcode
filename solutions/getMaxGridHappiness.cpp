//
//  getMaxGridHappiness.cpp
//  leetcode
//
//  Created by Song Ding on 2/22/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace getMaxGridHappiness {
/*
// TODO: copy problem statement here
 1659. Maximize Grid Happiness
 Hard

 116

 38

 Add to List

 Share
 You are given four integers, m, n, introvertsCount, and extrovertsCount. You have an m x n grid, and there are two types of people: introverts and extroverts. There are introvertsCount introverts and extrovertsCount extroverts.

 You should decide how many people you want to live in the grid and assign each of them one grid cell. Note that you do not have to have all the people living in the grid.

 The happiness of each person is calculated as follows:

 Introverts start with 120 happiness and lose 30 happiness for each neighbor (introvert or extrovert).
 Extroverts start with 40 happiness and gain 20 happiness for each neighbor (introvert or extrovert).
 Neighbors live in the directly adjacent cells north, east, south, and west of a person's cell.

 The grid happiness is the sum of each person's happiness. Return the maximum possible grid happiness.

  

 Example 1:


 Input: m = 2, n = 3, introvertsCount = 1, extrovertsCount = 2
 Output: 240
 Explanation: Assume the grid is 1-indexed with coordinates (row, column).
 We can put the introvert in cell (1,1) and put the extroverts in cells (1,3) and (2,3).
 - Introvert at (1,1) happiness: 120 (starting happiness) - (0 * 30) (0 neighbors) = 120
 - Extrovert at (1,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
 - Extrovert at (2,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
 The grid happiness is 120 + 60 + 60 = 240.
 The above figure shows the grid in this example with each person's happiness. The introvert stays in the light green cell while the extroverts live on the light purple cells.
 Example 2:

 Input: m = 3, n = 1, introvertsCount = 2, extrovertsCount = 1
 Output: 260
 Explanation: Place the two introverts in (1,1) and (3,1) and the extrovert at (2,1).
 - Introvert at (1,1) happiness: 120 (starting happiness) - (1 * 30) (1 neighbor) = 90
 - Extrovert at (2,1) happiness: 40 (starting happiness) + (2 * 20) (2 neighbors) = 80
 - Introvert at (3,1) happiness: 120 (starting happiness) - (1 * 30) (1 neighbor) = 90
 The grid happiness is 90 + 80 + 90 = 260.
 Example 3:

 Input: m = 2, n = 2, introvertsCount = 4, extrovertsCount = 0
 Output: 240
  

 Constraints:

 1 <= m, n <= 5
 0 <= introvertsCount, extrovertsCount <= min(m * n, 6)
*/
class Solution {
public:
    // TODO: copy function signature here
    // intuition 1: add as much as extroverts as possible on one side, and if anything left, add introverts
    // brutal force DP, for each cell position, try set it to empty/introvert/extrovert
    // but we still need to know # of introverts/extroverts left, and how the
    // previouse n positions are set(empty/introvert/extrovert), as only the left and up
    // positions have impact on current position.
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
        int dp[25][7][7][32][32] = {0};
        return dfs(0, m, n, introvertsCount, extrovertsCount, 0, 0, dp);
    }
    int dfs(int p, int m, int n, int iCount, int eCount, int imask, int emask, int dp[25][7][7][32][32]) {
        if (p>=m*n) {
            return 0;
        } else if (dp[p][iCount][eCount][imask][emask]) {
            return dp[p][iCount][eCount][imask][emask]-1;
        }
        int x = p/n, y = p%n;
        
        int nimask = (imask << 1) & ((1<<n)-1);
        int nemask = (emask << 1) & ((1<<n)-1);
        // empty for current cell
        int res = dfs(p+1, m, n, iCount, eCount, nimask, nemask, dp);
        
        if (iCount) {
            res = max(res, 120 + point(x, y, -30, n, imask, emask) + dfs(p+1, m, n, iCount-1, eCount, nimask+1, nemask, dp));
        }
        if (eCount) {
            res = max(res, 40 + point(x, y, 20, n, imask, emask) + dfs(p+1, m, n, iCount, eCount-1, nimask, nemask+1, dp));
        }
        dp[p][iCount][eCount][imask][emask] = res+1;
        return res;
    }
    int point(int x, int y, int my, int n, int imask, int emask) {
        int res = 0;
        // has an upper neighbor
        if (x > 0 && imask & (1<<(n-1))) {
            res -= 30;
            res += my;
        }
        // has a left neighbor
        if (y > 0 && imask & 1) {
            res -= 30;
            res += my;
        }
        if (x > 0 && emask & (1<<(n-1))) {
            res += 20;
            res += my;
        }
        if (y > 0&& emask & 1) {
            res += 20;
            res += my;
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
        int m;
        int n;
        int introvertsCount;
        int extrovertsCount;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        //{2,3,1,2},
        {3,1,2,1},
        {3,3,3,1},
    };
    // TODO: provide expected results here
    vector<int> answers {
        240,
        260,
        400
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = getMaxGridHappiness::Solution().getMaxGridHappiness(dp.m, dp.n, dp.introvertsCount, dp.extrovertsCount);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
