// stoneGame.cpp
// leetcode
//
// Created by  Song Ding on 5/31/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace stoneGame {
/*
// TODO: copy problem statement here
 877. Stone Game
 Medium
 
 290
 
 532
 
 Favorite
 
 Share
 Alex and Lee play a game with piles of stones.  There are an even number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].
 
 The objective of the game is to end with the most stones.  The total number of stones is odd, so there are no ties.
 
 Alex and Lee take turns, with Alex starting first.  Each turn, a player takes the entire pile of stones from either the beginning or the end of the row.  This continues until there are no more piles left, at which point the person with the most stones wins.
 
 Assuming Alex and Lee play optimally, return True if and only if Alex wins the game.
 
 
 
 Example 1:
 
 Input: [5,3,4,5]
 Output: true
 Explanation:
 Alex starts first, and can only take the first 5 or the last 5.
 Say he takes the first 5, so that the row becomes [3, 4, 5].
 If Lee takes 3, then the board is [4, 5], and Alex takes 5 to win with 10 points.
 If Lee takes the last 5, then the board is [3, 4], and Alex takes 4 to win with 9 points.
 This demonstrated that taking the first 5 was a winning move for Alex, so we return true.
 
 
 Note:
 
 2 <= piles.length <= 500
 piles.length is even.
 1 <= piles[i] <= 500
 sum(piles) is odd.
 */

class Solution {
public:
    /**
     * DP:
     * let mp(i, k) = max value the 1st player can get given k piles starting at the i-th pile.
     * then mp(i,k) = max(p[i]+sum(i+1,k-1)-mp(i+1,k-1), p[i+k-1]+sum(i,k-1)-mp[i,k-1]).
     *
     */
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        int ssum = piles[0];
        vector<int> mp(piles);
        for (int k = 2; k <= n; ++k) {
            vector<int> next;
            ssum += piles[k-1];
            
            int s = ssum;
            next.push_back(s - min(mp[1], mp[0]));
            for (int i = 1; i <= n - k; ++i) {
                s -= piles[i-1];
                s += piles[i+k-1];
                next.push_back(s - min(mp[i+1], mp[i]));
            }
            mp.swap(next);
        }
        return mp[0] > (ssum>>1);
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> piles;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{5,3,4,5}}
    };

    vector< bool > answers {
        true
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = stoneGame::Solution().stoneGame(dp.piles);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
