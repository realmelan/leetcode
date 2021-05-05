// escapeGhosts.cpp
// leetcode
//
// Created by  Song Ding on 5/27/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace escapeGhosts {
/*
// TODO: copy problem statement here
 789. Escape The Ghosts
 Medium
 
 120
 
 252
 
 Favorite
 
 Share
 You are playing a simplified Pacman game. You start at the point (0, 0), and your destination is (target[0], target[1]). There are several ghosts on the map, the i-th ghost starts at (ghosts[i][0], ghosts[i][1]).
 
 Each turn, you and all ghosts simultaneously *may* move in one of 4 cardinal directions: north, east, west, or south, going from the previous point to a new point 1 unit of distance away.
 
 You escape if and only if you can reach the target before any ghost reaches you (for any given moves the ghosts may take.)  If you reach any square (including the target) at the same time as a ghost, it doesn't count as an escape.
 
 Return True if and only if it is possible to escape.
 
 Example 1:
 Input:
 ghosts = [[1, 0], [0, 3]]
 target = [0, 1]
 Output: true
 Explanation:
 You can directly reach the destination (0, 1) at time 1, while the ghosts located at (1, 0) or (0, 3) have no way to catch up with you.
 Example 2:
 Input:
 ghosts = [[1, 0]]
 target = [2, 0]
 Output: false
 Explanation:
 You need to reach the destination (2, 0), but the ghost at (1, 0) lies between you and the destination.
 Example 3:
 Input:
 ghosts = [[2, 0]]
 target = [1, 0]
 Output: false
 Explanation:
 The ghost can reach the target at the same time as you.
 Note:
 
 All points have coordinates with absolute value <= 10000.
 The number of ghosts will not exceed 100.
 */

class Solution {
public:
    /**
     * rational strategy for pacman: always moves towards target.
     *
     * Now, suppose a ghost catches pacman at a position p(x, y), then
     * distance(g,p) <= distance(p, {0,0}),
     * then distance(g, target) <= distance({0,0}, target).
     *
     * so, if pacman has nearest position to target, then it can escape.
     *
     */
    bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
        int td = dist(target, {0,0});
        for (const auto& g : ghosts) {
            if (dist(target, g) < td) {
                return false;
            }
        }
        return true;
    }
    /**
     * BFS
     * expand pacman and ghosts one step at a time.
     * At each step, remove positions that appear in ghosts occupation.
     *
     *
     * if distance(pacman, target) >= distance(ghosts, target), pacman loses.
     *
     * Note, ghosts may choose not to move.
     */
    bool escapeGhosts2(vector<vector<int>>& ghosts, vector<int>& target) {
        if (target == vector<int>{0,0}) {
            return true;
        }
        unordered_set<vector<int>, hash> pcur{{0,0}}, gvisited;
        int mingd = INT_MAX;
        for (const auto& v : ghosts) {
            int gd = dist(target, v);
            if (gd <= dist(target, {0,0})) {
                return false;
            }
            mingd = min(mingd, gd);
            gvisited.insert(v);
        }
        const vector<vector<int>> gchange{
            {0,1},{0,-1},{1,0},{-1,0}
        };
        vector<vector<int>> pchange;
        int xpch = 1;
        if (target[0] < 0) {
            xpch = -1;
        }
        pchange.push_back({xpch, 0});
        int ypch = 1;
        if (target[1] < 0) {
            ypch = -1;
        }
        pchange.push_back({0,ypch});
        
        unordered_set<vector<int>, hash> gcur(gvisited);
        while (pcur.size()) {
            unordered_set<vector<int>, hash> gnew;
            if (--mingd == 0) {
                return false;
            }
            for (const auto& v : gcur) {
                for (const auto& ch : gchange) {
                    vector<int> nv = move(v, ch);
                    if (gvisited.find(nv) != gvisited.end()) {
                        gnew.insert(nv);
                        gvisited.insert(nv);
                    }
                }
            }
            
            unordered_set<vector<int>, hash> pnew;
            for (const auto& v : pcur) {
                for (const auto& ch : pchange) {
                    vector<int> nv = move(v, ch);
                    if (nv == target) {
                        return true;
                    }
                    if (gvisited.find(nv) == gvisited.end() && dist(target, nv) < mingd) {
                        pnew.insert(nv);
                    }
                }
            }
            pcur.swap(pnew);
            gcur.swap(gnew);
        }
        return false;
        
    }

private:
    int dist(const vector<int>& p1, const vector<int>& p2) {
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
    }
    vector<int> move(const vector<int>& cur, const vector<int>& change) {
        return {cur[0]+change[0], cur[1]+change[1]};
    }
    struct hash {
        size_t operator()(const vector<int>& v) const {
            return v[0] * 10001 + v[1];
        }
    };
    
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> ghosts;
        vector<int> target;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{1, 0}, {0, 3}},{0, 1}},
        {{{1, 0}},{2, 0}},
        {{{2, 0}},{1, 0}},
        {{{-1,0},{0,1},{-1,0},{0,1},{-1,0}},{0,0}},
        {{{546,547},{1728,885},{66,67},{-331,-330},{1637,976},{1501,1112},{1414,1199},{2057,556},{1722,891},{1709,904},{151,152},{1492,1121},{-989,-988},{1473,1140},{-585,-584},{1491,1122},{4219,-1606},{4016,-1403},{2398,215},{420,421},{1126,1127},{2337,276},{711,712},{3895,-1282},{-1527,-1526},{1008,1009},{-1134,-1133},{2857,-244},{3413,-800},{687,688},{1840,773},{-949,-948},{874,875},{4165,-1552},{-450,-449},{384,385},{2731,-118},{441,442},{1980,633},{63,64},{1993,620},{3207,-594},{2259,354},{1931,682},{200,201},{-1265,-1264},{3877,-1264},{-173,-172},{4092,-1479},{1851,762},{1509,1104},{2107,506},{3698,-1085},{-424,-423},{-787,-786},{-712,-711},{3465,-852},{2210,403},{3799,-1186},{3111,-498},{2832,-219},{1476,1137},{-525,-524},{2326,287},{2446,167},{1838,775},{-248,-247},{505,506},{-362,-361},{1567,1046},{4288,-1675},{1081,1082},{1799,814},{143,144},{-1153,-1152},{3205,-592},{92,93},{-1669,-1668},{3675,-1062},{1273,1274},{-1230,-1229},{1555,1058},{1648,965},{2735,-122},{340,341},{-608,-607},{2547,66},{3573,-960},{1107,1108},{-1640,-1639},{-764,-763},{1771,842},{3384,-771},{-53,-52},{3021,-408},{-1114,-1113},{-309,-308},{1653,960},{3639,-1026},{2820,-207}},{1306,-1689}}
    };

    vector< bool > answers {
        true,
        false,
        false
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = escapeGhosts::Solution().escapeGhosts(dp.ghosts, dp.target);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
