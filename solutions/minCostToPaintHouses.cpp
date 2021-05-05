//
//  minCostToPaintHouses.cpp
//  leetcode
//
//  Created by Song Ding on 11/12/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minCostToPaintHouses {
/*
// TODO: copy problem statement here
 1473. Paint House III
 Hard

 284

 14

 Add to List

 Share
 There is a row of m houses in a small city, each house must be painted with one of the n colors (labeled from 1 to n), some houses that has been painted last summer should not be painted again.

 A neighborhood is a maximal group of continuous houses that are painted with the same color. (For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods  [{1}, {2,2}, {3,3}, {2}, {1,1}]).

 Given an array houses, an m * n matrix cost and an integer target where:

 houses[i]: is the color of the house i, 0 if the house is not painted yet.
 cost[i][j]: is the cost of paint the house i with the color j+1.
 Return the minimum cost of painting all the remaining houses in such a way that there are exactly target neighborhoods, if not possible return -1.

  

 Example 1:

 Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
 Output: 9
 Explanation: Paint houses of this way [1,2,2,1,1]
 This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
 Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.
 Example 2:

 Input: houses = [0,2,1,2,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
 Output: 11
 Explanation: Some houses are already painted, Paint the houses of this way [2,2,1,2,2]
 This array contains target = 3 neighborhoods, [{2,2}, {1}, {2,2}].
 Cost of paint the first and last house (10 + 1) = 11.
 Example 3:

 Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[1,10],[10,1],[1,10]], m = 5, n = 2, target = 5
 Output: 5
 Example 4:

 Input: houses = [3,1,2,3], cost = [[1,1,1],[1,1,1],[1,1,1],[1,1,1]], m = 4, n = 3, target = 3
 Output: -1
 Explanation: Houses are already painted with a total of 4 neighborhoods [{3},{1},{2},{3}] different of target = 3.
  

 Constraints:

 m == houses.length == cost.length
 n == cost[i].length
 1 <= m <= 100
 1 <= n <= 20
 1 <= target <= m
 0 <= houses[i] <= n
 1 <= cost[i][j] <= 10^4
*/
class Solution {
public:
    // TODO: copy function signature here
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        if (n == 1 && target > 1) {
            return -1;
        }
        
        int res = INT_MAX;
        dfs(m-1, target, -1, 0, res, houses, cost);
        return res == INT_MAX ? -1 : res;
    }
    void dfs(int hi, int tc, int last, int curCost, int& res, vector<int>& houses, vector<vector<int>>& cost) {
        if (tc < 0) {
            return;
        } else if (hi < 0) {
            if (tc == 0) {
                res = min(res, curCost);
            }
        } else if (houses[hi]) {
            dfs(hi-1, tc-((houses[hi]!=last)?1:0), houses[hi], curCost, res, houses, cost);
        } else {
            for (int i = 1; i <= cost[hi].size(); ++i) {
                if (curCost+cost[hi][i-1]>100) {
                    cout << "hold on" << endl;
                }
                dfs(hi-1, tc-((i!=last)?1:0), i, curCost+cost[hi][i-1], res, houses, cost);
                
            }
        }
    }
    int minCost3(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        constexpr int IMPOSSIBLE = 10000000;
        vector<vector<vector<int>>> dp(target+1, vector<vector<int>>(m, vector<int>(n+1, INT_MAX)));
        int res = dfs(target, m-1, 0, houses, cost, dp);
        return res >= IMPOSSIBLE ? -1 : res;
    }
    int dfs(int nb, int hi, int lastColor, vector<int>& houses, vector<vector<int>>& cost, vector<vector<vector<int>>>& dp) {
        constexpr int IMPOSSIBLE = 10000000;
        if (hi < 0) {
            if (nb == 0) {
                return 0;
            } else {
                return IMPOSSIBLE;
            }
        } else if (nb < 0 || nb - hi > 1) {
            return IMPOSSIBLE;
        }
        
        if (dp[nb][hi][lastColor] != INT_MAX) {
            return dp[nb][hi][lastColor];
        }
        
        int res = IMPOSSIBLE;
        if (houses[hi] != 0) {
           res = dfs(nb - (lastColor != houses[hi]), hi-1, houses[hi], houses, cost, dp);
        } else {
            for (int i = 1; i <= cost[hi].size(); ++i) {
                res = min(res, dfs(nb-(i != lastColor), hi-1, i, houses, cost, dp) + cost[hi][i-1]);
            }
        }
        return (dp[nb][hi][lastColor] = res);
    }
    int minCost2(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
           constexpr int IMPOSSIBLE = 10000000;
           vector<vector<vector<int>>> dp(target+1, vector<vector<int>>(m, vector<int>(n+1, INT_MAX)));
           for (int i = 1; i <= n; ++i) {
               dp[target][m-1][i] = dfs2(target, m-1, i, houses, cost, dp);
           }
           int res = *min_element(begin(dp[target][m-1]), end(dp[target][m-1]));
           return res >= IMPOSSIBLE ? -1 : res;
       }
       int dfs2(int nbi, int hi, int ci, vector<int>& houses, vector<vector<int>>& cost, vector<vector<vector<int>>>& dp) {
           constexpr int IMPOSSIBLE = 10000000;
           if (nbi == 0 && hi < 0) {
               return 0;
           } else if (nbi == 0 || hi < 0 || nbi - hi > 1) {
               return IMPOSSIBLE;
           }
           
           if (dp[nbi][hi][ci] != INT_MAX) {
               return dp[nbi][hi][ci];
           }
           
           int res = IMPOSSIBLE;
           if (houses[hi] == ci) {
               for (int i = 1; i <= cost[hi].size(); ++i) {
                   if (i != ci) {
                       res = min(res, dfs2(nbi-1, hi-1, i, houses, cost, dp));
                   } else {
                       res = min(res, dfs2(nbi, hi-1, ci, houses, cost, dp));
                   }
               }
           } else if (houses[hi] == 0) {
               for (int i = 1; i <= cost[hi].size(); ++i) {
                   if (i != ci) {
                       res = min(res, dfs2(nbi-1, hi-1, i, houses, cost, dp) + cost[hi][ci-1]);
                   } else {
                       res = min(res, dfs2(nbi, hi-1, ci, houses, cost, dp) + cost[hi][ci-1]);
                   }
               }
           }
           return (dp[nbi][hi][ci] = res);
       }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> houses;
        vector<vector<int>> cost;
        int m;
        int n;
        int target;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{0,0,0,0,0}, {{1,10},{10,1},{10,1},{1,10},{5,1}}, 5, 2, 3},
        {{0,2,1,2,0},{{1,10},{10,1},{10,1},{1,10},{5,1}},5,2,3},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minCostToPaintHouses::Solution().minCost(dp.houses, dp.cost, dp.m, dp.n, dp.target);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
