// canIWin.cpp
// leetcode
//
// Created by  Song Ding on 6/21/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace canIWin {
/*
// TODO: copy problem statement here
 464. Can I Win
 Medium
 
 618
 
 105
 
 Favorite
 
 Share
 In the "100 game," two players take turns adding, to a running total, any integer from 1..10. The player who first causes the running total to reach or exceed 100 wins.
 
 What if we change the game so that players cannot re-use integers?
 
 For example, two players might take turns drawing from a common pool of numbers of 1..15 without replacement until they reach a total >= 100.
 
 Given an integer maxChoosableInteger and another integer desiredTotal, determine if the first player to move can force a win, assuming both players play optimally.
 
 You can always assume that maxChoosableInteger will not be larger than 20 and desiredTotal will not be larger than 300.
 
 Example
 
 Input:
 maxChoosableInteger = 10
 desiredTotal = 11
 
 Output:
 false
 
 Explanation:
 No matter which integer the first player choose, the first player will lose.
 The first player can choose an integer from 1 up to 10.
 If the first player choose 1, the second player can only choose integers from 2 up to 10.
 The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
 Same with other integers chosen by the first player, the second player will always win.
 */

class Solution {
public:
    /**
     * check https://leetcode.com/problems/can-i-win/discuss/230432/C%2B%2B-12-ms-98-solution-with-detailed-explanation
     */
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        int m = maxChoosableInteger;
        int t = desiredTotal;
        if (t <= m) {
            return true;
        }
        if (t > m*(m+1)/2) {
            return false;
        }
        
        bitset<21> used(0);
        unordered_map<bitset<21>, bool> memo;
        return !recur(used, m, 0, t, memo);
        
    }
    bool recur(bitset<21>& used, int m, int c, int t, unordered_map<bitset<21>, bool>& memo) {
        auto it = memo.find(used);
        if (it != memo.end()) {
            return it->second;
        }
        if (c >= t) {
            memo[used] = true;
            return true;
        }
        bool res = true;
        for (int i = 1; i <= m; ++i) {
            if (!used.test(i)) {
                used.flip(i);
                if (recur(used, m, c+i, t, memo)) {
                    used.flip(i);
                    res = false;
                    break;
                }
                used.flip(i);
            }
        }
        memo[used] = res;
        return res;
    }
    /**
     * DFS + Memoization.
     */
    bool canIWin2(int maxChoosableInteger, int desiredTotal) {
        bitset<21> bm(0);
        int sum = 0;
        for (int i = 1; i <= maxChoosableInteger; ++i) {
            sum += i;
            bm.flip(i);
        }
        if (sum < desiredTotal) {
            return false;
        }
        
        // TODO: total doesn't have to be in key, as the bitmap and the desiredTotal
        // together decides total
        unordered_map<bitset<21>, bool> memo;
        for (int i = maxChoosableInteger; i > 0; --i) {
            if (i >= desiredTotal) {
                return true;
            }
            bm.flip(i);
            if (!recur2(bm, desiredTotal - i, memo)) {
                bm.flip(i);
                return true;
            }
            bm.flip(i);
        }
        return false;
    }

private:
    bool recur2(bitset<21>& bm, int total, unordered_map<bitset<21>, bool>& memo) {
        auto it = memo.find(bm);
        if (it != memo.end()) {
            return it->second;
        }
        
        bool res = false;
        int n = bm.size();
        for (int i = n - 1; i > 0; --i) {
            if (bm.test(i)) {
                if (i >= total) {
                    res = true;
                    break;
                }
                bm.flip(i);
                if (!recur2(bm, total - i, memo)) {
                    bm.flip(i);
                    res = true;
                    break;
                }
                bm.flip(i);
            }
        }
        memo[bm] = res;
        return res;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int maxChoosableInteger;
        int desiredTotal;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {10, 11},
        {10, 10},
        {20, 300},
        {10, 40},
        {5, 50}
    };

    vector< bool > answers {
        false,
        true,
        false,
        false,
        false
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = canIWin::Solution().canIWin(dp.maxChoosableInteger, dp.desiredTotal);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
