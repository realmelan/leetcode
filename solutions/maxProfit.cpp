// maxProfit.cpp
// leetcode
//
// Created by  Song Ding on 10/3/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxProfit {
/*
// TODO: copy problem statement here
 309. Best Time to Buy and Sell Stock with Cooldown
 Medium

 1596

 59

 Favorite

 Share
 Say you have an array for which the ith element is the price of a given stock on day i.

 Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

 You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
 After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
 Example:

 Input: [1,2,3,0,2]
 Output: 3
 Explanation: transactions = [buy, sell, cooldown, buy, sell]
 */

class Solution {
public:
    /**
     * let sp[i] = maximum value of (profit - price of stock bought)
     * nsp[i] = maximum profit without stock at hand
     * then nsp[i] = max(nsp[i-1], sp[i-1]+price[i])
     * sp[i] = max(sp[i-1], nsp[i-2]-price[i])
     */
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }
        
        vector<int> sp(n, 0), nsp(n, 0);
        sp[0] = -prices[0];
        sp[1] = max(sp[0], -prices[1]);
        nsp[0] = 0;
        nsp[1] = max(nsp[0], sp[0]+prices[1]);
        for (int i = 2; i < n; ++i) {
            sp[i] = max(sp[i-1], nsp[i-2]-prices[i]);
            nsp[i] = max(nsp[i-1], sp[i-1]+prices[i]);
        }
        return nsp[n-1];
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> prices;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3,0,2}},
    };

    vector< int > answers {
        3,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxProfit::Solution().maxProfit(dp.prices);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
