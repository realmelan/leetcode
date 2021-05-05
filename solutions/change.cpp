// change.cpp
// leetcode
//
// Created by  Song Ding on 10/4/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace change {
/**
 518. Coin Change 2
 Medium

 991

 40

 Favorite

 Share
 You are given coins of different denominations and a total amount of money. Write a function to compute the number of combinations that make up that amount. You may assume that you have infinite number of each kind of coin.

  

 Example 1:

 Input: amount = 5, coins = [1, 2, 5]
 Output: 4
 Explanation: there are four ways to make up the amount:
 5=5
 5=2+2+1
 5=2+1+1+1
 5=1+1+1+1+1
 Example 2:

 Input: amount = 3, coins = [2]
 Output: 0
 Explanation: the amount of 3 cannot be made up just with coins of 2.
 Example 3:

 Input: amount = 10, coins = [10]
 Output: 1
  

 Note:

 You can assume that

 0 <= amount <= 5000
 1 <= coin <= 5000
 the number of coins is less than 500
 the answer is guaranteed to fit into signed 32-bit integer
 */

class Solution {
public:
    /**
     * let dp[i] = # of ways for i using coins from first to current
     * then dp[i] += dp[i-coin]
     */
    int change2(int amount, vector<int>& coins) {
        vector<int> dp(1+amount, 0);
        dp[0] = 1;
        for (int coin : coins) {
            for (int i = coin; i <= amount; ++i) {
                dp[i] += dp[i-coin]; // dp[i-coin] includes ways that use coin.
            }
        }
        return dp[amount];
    }
    /**
     * sort the coins based on value in descending order.
     * change(N, C{1,n}) = change(N - C[n], C{1,n}) + change(N, C{1,n-1});
     */
    int change(int amount, vector<int>& coins) {
        unordered_map<int, int> memo;
        sort(coins.begin(), coins.end(), std::greater<int>());
        return recur(amount, coins, 0, memo);
    }

private:
    int recur(int amount, vector<int>& coins, int i, unordered_map<int, int>& memo) {
        if (amount == 0) {
            return 1;
        }
        
        int id = amount * 1000 + i;
        auto it = memo.find(id);
        if (it != memo.end()) {
            return it->second;
        }
        
        int res = 0;
        while (i < coins.size() && coins[i] > amount) {
            ++i;
        }
        if (i >= coins.size()) {
            res = 0;
        } else {
            res = recur(amount - coins[i], coins, i, memo)
                + recur(amount, coins, i + 1, memo);
        }
        
        memo.insert(make_pair(id, res));
        return res;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int amount = 100;
    vector<int> coins {10,5,2,1};

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = change::Solution().change2(amount, coins);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
