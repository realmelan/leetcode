// mincostTickets.cpp
// leetcode
//
// Created by  Song Ding on 5/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace mincostTickets {
/*
// TODO: copy problem statement here
 983. Minimum Cost For Tickets
 Medium
 
 422
 
 8
 
 Favorite
 
 Share
 In a country popular for train travel, you have planned some train travelling one year in advance.  The days of the year that you will travel is given as an array days.  Each day is an integer from 1 to 365.
 
 Train tickets are sold in 3 different ways:
 
 a 1-day pass is sold for costs[0] dollars;
 a 7-day pass is sold for costs[1] dollars;
 a 30-day pass is sold for costs[2] dollars.
 The passes allow that many days of consecutive travel.  For example, if we get a 7-day pass on day 2, then we can travel for 7 days: day 2, 3, 4, 5, 6, 7, and 8.
 
 Return the minimum number of dollars you need to travel every day in the given list of days.
 
 
 
 Example 1:
 
 Input: days = [1,4,6,7,8,20], costs = [2,7,15]
 Output: 11
 Explanation:
 For example, here is one way to buy passes that lets you travel your travel plan:
 On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
 On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
 On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
 In total you spent $11 and covered all the days of your travel.
 Example 2:
 
 Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
 Output: 17
 Explanation:
 For example, here is one way to buy passes that lets you travel your travel plan:
 On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2, ..., 30.
 On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
 In total you spent $17 and covered all the days of your travel.
 
 
 Note:
 
 1 <= days.length <= 365
 1 <= days[i] <= 365
 days is in strictly increasing order.
 costs.length == 3
 1 <= costs[i] <= 1000
 */

class Solution {
public:
    /**
     * DP:
     * let sp(i,j) = min cost till day i with day i on a j-day pass.
     * then j has values {2,7,15}.
     *
     * then sp(i,j) = max(sp(k, kj)) + costs[j] for the largest day k not covered
     * by j-day pass from i.
     */
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        vector<int> cover{1,7,30};
        int n = days.size();
        vector<int> minCost;
        minCost.push_back(min(costs[0], min(costs[1], costs[2])));
        for (int i = 1; i < n; ++i) {
            int k = i - 1;
            int mc = INT_MAX;
            for (int j = 0; j < 3; ++j) {
                int c = cover[j];
                while (k >= 0 && (days[i] - days[k] + 1) <= c) {
                    --k;
                }
                if (k < 0) {
                    mc = min(mc, costs[j]);
                } else {
                    mc = min(mc, costs[j] + minCost[k]);
                }
            }
            minCost.push_back(mc);
        }
        return minCost[n-1];
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> days;
        vector<int> costs;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,4,6,7,8,20},{2,7,15}},
        {{1,2,3,4,5,6,7,8,9,10,30,31},{2,7,15}}
    };

    vector< int > answers {
        11,
        17
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = mincostTickets::Solution().mincostTickets(dp.days, dp.costs);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
