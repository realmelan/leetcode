// calculateMinimumHP.cpp
// leetcode
//
// Created by  Song Ding on 12/13/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;
/*
 174. Dungeon Game
 Hard

 830

 19

 Favorite

 Share
 The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

 The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

 Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

 In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

  

 Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

 For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

 -2 (K)    -3    3
 -5    -10    1
 10    30    -5 (P)
  

 Note:

 The knight's health has no upper bound.
 Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.
 */

namespace calculateMinimumHP {

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        return calculateMinimumHP_reverse(dungeon);
    }
    
    /**
     * let dp[i][j] = minimum HP for cell (i,j), then after reach the right cell HP becomes
     * dp[i][j]+dungeon[i][j] = dp[i][j+1], so to reach (i,j+1), dp[i][j] = dp[i+1][j]-dungeon[i][].
     * same for the cell downside.
     */
    int calculateMinimumHP_reverse(vector<vector<int>>& dungeon) {
        int n = dungeon.size();
        int m = dungeon[0].size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, INT_MAX));
        dp[n][m-1] = 1; // cell down the princess cell
        dp[n-1][m] = 1; // cell on the right of pricess cell
        for (int i = n-1; i >= 0; --i) {
            for (int j = m-1; j>=0; --j) {
                int need = min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j];
                dp[i][j] = need <= 0 ? 1 : need;
            }
        }
        return dp[0][0];
    }
    /**
     * For each point in the grid, maintain all possible of pairs(current hp, max min hp).
     * For point (i, j), there are two ways to reach (i, j), from (i-1,j) downward or
     * from (i,j-1) rightward. Then for all possible pairs from these two points, update
     * current hp, and if current hp is smaller than max min hp, update max min hp.
     *
     * during merging these pairs, some pairs may not possibly be optimal, thus can be removed.
     * For example, there are two pairs (chp1, mmhp1), (chp2, mmhp2). if chp1 < chp2 and
     * mmhp1 < mmhp2, then (chp1, mmhp1) is not optimal.
     */
    int calculateMinimumHP_slow(vector<vector<int>>& dungeon) {
        int r = dungeon.size();
        if (r <= 0) {
            return 1;
        }
        int c = dungeon[0].size();
        if (c <= 0) {
            return 1;
        }
        
        vector<vector<map<int,int>>> res(r);
        res[0].resize(c);
        int cur_hp = 0;
        int min_hp = 0;
        for (int i = 0; i < c; ++i) {
            cur_hp += dungeon[0][i];
            if (cur_hp < min_hp) {
                min_hp = cur_hp;
            }
            res[0][i].insert(make_pair(cur_hp, min_hp));
        }
        
        cur_hp = dungeon[0][0];
        min_hp = cur_hp;
        for (int i = 1; i < r; ++i) {
            res[i].resize(c);
            cur_hp += dungeon[i][0];
            if (cur_hp < min_hp) {
                min_hp = cur_hp;
            }
            res[i][0].insert(make_pair(cur_hp, min_hp));
        }
        
        for (int i = 1; i < r; ++i) {
            for (int j = 1; j < c; ++j) {
                int cv = dungeon[i][j];
                
                map<int,int> tres1;
                const auto& up = res[i-1][j];
                for (auto p : up) {
                    int chp = p.first + cv;
                    int mmhp = p.second;
                    if (chp < mmhp) {
                        mmhp = chp;
                    }
                    
                    // check whether pair(chp, mmhp) is ok to add to tres
                    add(tres1, chp, mmhp);
                }
                
                map<int,int> tres2;
                const auto& left = res[i][j-1];
                for (auto p : left) {
                    int chp = p.first + cv;
                    int mmhp = p.second;
                    if (chp < mmhp) {
                        mmhp = chp;
                    }
                    
                    // check whether pair(chp, mmhp) is ok to add to tres
                    add(tres2, chp, mmhp);
                }
                
                // merge tres1 and tres2
                merge(tres1, tres2, res[i][j]);
            }
        }
        
        int mmhp = INT_MIN;
        for (auto& p : res[r-1][c-1]) {
            if (mmhp < p.second) {
                mmhp = p.second;
            }
        }
        if (mmhp < 0) {
            return -mmhp + 1;
        }
        return 1;
    }

private:
    void add(map<int,int>& res, int chp, int mmhp) {
        auto it = res.lower_bound(chp);
        while (it != res.end()) {
            if (it->second >= mmhp) {
                return;
            }
            ++it;
        }
        res[chp] = mmhp;
    }
    void merge(const map<int,int>& tres1, const map<int,int>& tres2, map<int,int>& tres) {
        auto it1 = tres1.rbegin();
        auto it2 = tres2.rbegin();
        while (it1 != tres1.rend() && it2 != tres2.rend()) {
            if (it1->first > it2->first) {
                add(tres, it1->first, it1->second);
                ++it1;
            } else {
                add(tres, it2->first, it2->second);
                ++it2;
            }
        }
        while (it1 != tres1.rend()) {
            add(tres, it1->first, it1->second);
            ++it1;
        }
        while (it2 != tres2.rend()) {
            add(tres, it2->first, it2->second);
            ++it2;
        }
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<vector<int>> > dungeon {
        {{-2,-3,3},{-5,-10,1},{10,30,-5}}
    };

    vector<  int > answers {
        7
    };
    int i = 0;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = calculateMinimumHP::Solution().calculateMinimumHP(dungeon[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
