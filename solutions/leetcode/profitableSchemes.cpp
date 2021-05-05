// profitableSchemes.cpp
// leetcode
//
// Created by  Song Ding on 10/30/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace profitableSchemes {

class Solution {
public:
    /**
     * total # of schemes, s(i) = s(G - g[i], P - p[i], g(0, i -1), p(0, i -1)) + s(G, P, g(0, i-1), p(0, i-1))
     */
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        int n = group.size();
        vector<vector<vector<int>>> memo(G + 1);
        for (auto & v : memo) {
            v.resize(P + 1, vector<int>(n, -1));
        }
        
        return recur(G, P, n, group, profit, memo);
        
    }

private:
    int recur(int G, int P, int i, vector<int>& group, vector<int>& profit, vector<vector<vector<int>>>& memo) {
        if (P < 0) {
            P = 0;
        }
        if (memo[G][P][i - 1] >= 0) {
            return memo[G][P][i - 1];
        }
        
        if (i == 1) {
            int res = 0;
            if (group[0] <= G) {
                if (P <= 0) {
                    res = 2;
                } else if (profit[0] >= P) {
                    res = 1;
                } else {
                    res = 0;
                }
            } else {
                if (P <= 0) {
                    res = 1;
                } else {
                    res = 0;
                }
            }
            memo[G][P][i - 1] = res;
            return res;
        } else {
            long res = 0;
            if (G >= group[i - 1]) {
                res += recur(G - group[i - 1], P - profit[i - 1], i - 1, group, profit, memo);
            }
            res += recur(G, P, i - 1, group, profit, memo);
            res %= 1000000007;
            memo[G][P][i - 1] = res;
            return res;
        }
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> G {
        5,
        10,
        1
    };
    vector<int> P  {
        3,
        5,
        1
    };
    vector<vector<int>> group {
        {2,2},
        {2,3,5},
        {1,1,1,1,2,2,1,2,1,1}
        
    };
    vector<vector<int>> profit {
        {2,3},
        {6,7,8},
        {0,1,0,0,1,1,1,0,2,2}
    };
    
    int i = 2;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = profitableSchemes::Solution().profitableSchemes(G[i], P[i], group[i], profit[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
