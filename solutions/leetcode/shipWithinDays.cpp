// shipWithinDays.cpp
// leetcode
//
// Created by  Song Ding on 5/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace shipWithinDays {
/*
// TODO: copy problem statement here
 1011. Capacity To Ship Packages Within D Days
 Medium
 
 230
 
 9
 
 Favorite
 
 Share
 A conveyor belt has packages that must be shipped from one port to another within D days.
 
 The i-th package on the conveyor belt has a weight of weights[i].  Each day, we load the ship with packages on the conveyor belt (in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.
 
 Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within D days.
 
 
 
 Example 1:
 
 Input: weights = [1,2,3,4,5,6,7,8,9,10], D = 5
 Output: 15
 Explanation:
 A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
 1st day: 1, 2, 3, 4, 5
 2nd day: 6, 7
 3rd day: 8
 4th day: 9
 5th day: 10
 
 Note that the cargo must be shipped in the order given, so using a ship of capacity 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.
 Example 2:
 
 Input: weights = [3,2,2,4,1,4], D = 3
 Output: 6
 Explanation:
 A ship capacity of 6 is the minimum to ship all the packages in 3 days like this:
 1st day: 3, 2
 2nd day: 2, 4
 3rd day: 1, 4
 Example 3:
 
 Input: weights = [1,2,3,1,1], D = 4
 Output: 3
 Explanation:
 1st day: 1
 2nd day: 2
 3rd day: 3
 4th day: 1, 1
 
 
 Note:
 
 1 <= D <= weights.length <= 50000
 1 <= weights[i] <= 500
 */

class Solution {
public:
    /**
     * the lower bound should be max(max(weights), sum(weights)/D).
     * upper bound can be (max(weights) * n + D - 1) / D.
     *
     * Then use binary search to find out.
     */
    int shipWithinDays(vector<int>& weights, int D) {
        int n = weights.size();
        int maxw = 0;
        int sumw = 0;
        for (auto w : weights) {
            maxw = max(maxw, w);
            sumw += w;
        }
        
        int l = max(maxw, (sumw / D - 1));
        int r = (maxw * n + D - 1) / D;
        while (l < r) {
            int m = (l + r) / 2;
            int t = testShip(weights, m);
            if (t <= D) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }

private:
    int testShip(vector<int>& weights, int m) {
        int res = 1;
        int n = weights.size();
        int t = m;
        for (int i = 0; i < n; ++i) {
            if (weights[i] > t) {
                ++res;
                t = m;
            }
            t -= weights[i];
        }
        return res;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> weights;
        int D;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3,4,5,6,7,8,9,10}, 5},
        {{3,2,2,4,1,4}, 3},
        {{1,2,3,1,1}, 4},
        {{1,2,3,4,5,6,7,8,9,10}, 1},
        {{1,2,3,1,1},4}
        
    };

    vector< int > answers {
        15,
        6,
        3,
        55,
        3
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = shipWithinDays::Solution().shipWithinDays(dp.weights, dp.D);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
