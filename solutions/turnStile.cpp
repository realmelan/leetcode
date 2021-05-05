//
//  turnStile.cpp
//  leetcode
//
//  Created by Song Ding on 11/10/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace turnStile {
/*
// TODO: copy problem statement here
 Imagine a small Amazon Go store that has exactly one turnstile. It can be used by customers either as an entrance or an exit. Sometimes multiple customers want to pass through the turnstile and their directions can be different. The ith customer comes to the turnstile at time[i] and wants to either exit the store if direction [i] = 1 or enter the store if direction[i] = 0. Customers form 2 queues, one to exit and one to enter. They are ordered by the time when they came to the turnstile and, if the times are equal, by their indices.

 If one customer wants to enter the store and another customer wants to exit at the same moment, there are three cases:

 If in the previous second the turnstile was not used (maybe it was used before, but not at the previous second), then the customer who wants to exit goes first.
 If in the previous second the turnstile was used as an exit, then the customer who wants to leave goes first.
 If in the previous second the turnstile was used as an entrance, then the customer who wants to enter goes first.
 Passing through the turnstile takes 1 second.

 Write an algorithm to find the time for each customer when they will pass through the turnstile.

 Input

 The function/method consists of three arguments:

 numcustomers, an integer representing the number of customers (n);
 arrTime, a list of integers where the value at indexi is the time in seconds when the ith customer will come to the turnstile;
 direction, a list of integers where the value at indexi is the direction of the ith customer.

 Output

 Return a list of integers where the value at index i is the time when the ith customer will pass the turnstile.

 Constraints

 1 <= numCustomers <= 10^5
 0 <= arrTime[i] <= arrTime[i + 1] <= 10^9
 0 <= i <= numCustomers - 2
 0 <= direction[i] <= 1
 0 <= j <= numCustomers - 1

 Examples

 Example 1:

 Input:
 numCustomers = 4
 arrTime = [0, 0, 1,5]
 direction = [0, 1, 1, 0]
 Output:
 [2,0,1,5]

 Explanation:
 At time 0, customer 0 and 1 want to pass through the turnstile. Customer 0 wants to enter the store and customer 1 wants to leave the store. The turnstile was not used in the previous second, so the priority is on the side of the customer 1
 At time 1, customers 0 and 2 want to pass through the turnstile. Customer 2 wants to leave the store and at the previous second the turnstile was used as an exit, so the customer 2 passes through the turnstile.
 At time 2, customer 0 passes through the turnstile.
 At time 5, customer 3 passes through the turnstile.

 Example 2

 Input:
 numCustomers = 5
 arrTime = [0,1,1,3,3]
 direction = [0, 1, 0, 0, 1]
 Output: [0, 2, 1, 4, 3]

 Explanation:

 At time 0, customer 0 passes through the turnstile (enters).
 At time 1, customers 1 (exit) and 2 (enter) want to pass through the turnstile, and customer 2 passes through the turnstile because their direction is equal to the direction at the previous second.
 At time 2. customer 1 passes through the turnstile (exit).
 At time 3, customers 3 (enter) and 4 (exit) want to pass through the turnstile. Customer 4 passes through the turnstile because at the previous second the turnstile was used to exit.
 At time 4, customer 3 passes through the turnstile.
*/
class Solution {
public:
    // TODO: copy function signature here
    vector<int> turnStile(vector<int>& arrTime, vector<int>& direction) {
        int n = arrTime.size();
        int enter = 0, leave = 0;
        while (leave < n && direction[leave] != 1) {
            ++leave;
        }
        while (enter < n && direction[enter] != 0) {
            ++enter;
        }
        
        vector<int> res(n);
        int t = -1;
        int dir = 1;
        while (leave < n && enter < n) {
            // enter
            if ((arrTime[enter] <= t  && dir == 0)
                || (t < arrTime[enter] && arrTime[enter] < arrTime[leave])) {
                res[enter] = max(t, arrTime[enter]);
                t = res[enter] + 1;
                dir = 0;
                ++enter;
                while (enter < n && direction[enter] != 0) {
                    ++enter;
                }
            } else {
                res[leave] = max(t, arrTime[leave]);
                t = res[leave]+1;
                dir = 1;
                // move leave
                ++leave;
                while (leave < n && direction[leave] != 1) {
                    ++leave;
                }
            }
        }
        while (leave < n) {
            if (direction[leave] == 1) {
                res[leave] = max(t, arrTime[leave]);
                t = res[leave] + 1;
            }
            ++leave;
        }
        while (enter < n) {
            if (direction[enter] == 0) {
                res[enter] = max(t, arrTime[enter]);
                t = res[enter] + 1;
            }
            ++enter;
        }
        return res;
    }
    
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> arrTime;
        vector<int> direction;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{0, 0, 1,5},{0,1,1,0}},
        {{0,1,1,3,3},{0, 1, 0, 0, 1}},
    };
    // TODO: provide expected results here
    vector<vector<int>> answers {
        {2,0,1,5},
        {0, 2, 1, 4, 3},
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = turnStile::Solution().turnStile(dp.arrTime, dp.direction);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
