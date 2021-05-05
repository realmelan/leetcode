// maxSatisfied.cpp
// leetcode
//
// Created by  Song Ding on 6/11/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxSatisfied {
/*
// TODO: copy problem statement here
 1052. Grumpy Bookstore Owner
 Medium
 
 82
 
 8
 
 Favorite
 
 Share
 Today, the bookstore owner has a store open for customers.length minutes.  Every minute, some number of customers (customers[i]) enter the store, and all those customers leave after the end of that minute.
 
 On some minutes, the bookstore owner is grumpy.  If the bookstore owner is grumpy on the i-th minute, grumpy[i] = 1, otherwise grumpy[i] = 0.  When the bookstore owner is grumpy, the customers of that minute are not satisfied, otherwise they are satisfied.
 
 The bookstore owner knows a secret technique to keep themselves not grumpy for X minutes straight, but can only use it once.
 
 Return the maximum number of customers that can be satisfied throughout the day.
 
 
 
 Example 1:
 
 Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], X = 3
 Output: 16
 Explanation: The bookstore owner keeps themselves not grumpy for the last 3 minutes.
 The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 + 5 = 16.
 
 
 Note:
 
 1 <= X <= customers.length == grumpy.length <= 20000
 0 <= customers[i] <= 1000
 0 <= grumpy[i] <= 1
 */

class Solution {
public:
    /**
     * find the start minutes of X that would cover most lost customers.
     */
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        int res = 0;
        int n = customers.size();
        int msave = 0;
        int save = 0;
        vector<int> gm;
        int gi = 0;
        for (int i = 0; i < n; ++i) {
            if (grumpy[i]) {
                gm.push_back(i);
                while (i - gm[gi] >= X) {
                    msave = max(msave, save);
                    save -= customers[gm[gi]];
                    ++gi;
                }
                save += customers[i];
            } else {
                res += customers[i];
            }
        }
        
        msave = max(msave, save);
        return res + msave;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> customers;
        vector<int> grumpy;
        int X;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,0,1,2,1,1,7,5},{0,1,0,1,0,1,0,1},3},
        {{22,609,498,467,957,156,897,839,136,382,43,395,910,662,496,472,582,573,355,849,174,77,900,751,487,530,566,350,15,351,793,166,698,583,858,895,907,942,2,512,895,30,270,585,838,271,905,476,217,536},
            {1,0,1,1,0,0,0,1,0,1,1,0,0,1,1,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,0,1,0,1,1,0,0,0,0,0},
            26}
    };

    vector< int > answers {
        16,
        22176
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxSatisfied::Solution().maxSatisfied(dp.customers, dp.grumpy, dp.X);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
