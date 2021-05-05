// flipLights.cpp
// leetcode
//
// Created by  Song Ding on 10/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace flipLights {
/*
// TODO: copy problem statement here
 672. Bulb Switcher II
 Medium

 106

 751

 Favorite

 Share
 There is a room with n lights which are turned on initially and 4 buttons on the wall. After performing exactly m unknown operations towards buttons, you need to return how many different kinds of status of the n lights could be.

 Suppose n lights are labeled as number [1, 2, 3 ..., n], function of these 4 buttons are given below:

 Flip all the lights.
 Flip lights with even numbers.
 Flip lights with odd numbers.
 Flip lights with (3k + 1) numbers, k = 0, 1, 2, ...
  

 Example 1:

 Input: n = 1, m = 1.
 Output: 2
 Explanation: Status can be: [on], [off]
  

 Example 2:

 Input: n = 2, m = 1.
 Output: 3
 Explanation: Status can be: [on, off], [off, on], [off, off]
  

 Example 3:

 Input: n = 3, m = 1.
 Output: 4
 Explanation: Status can be: [off, on, off], [on, off, on], [off, off, off], [off, on, on].
  

 Note: n and m both fit in range [0, 1000].
 */

class Solution {
public:
    /**
     * we only need to determine the first 3 bulbs, all other bulbs
     * can be deduced from the state the first 3 bulbs.
     * if m >= 3, we can get all possbile 8 states.
     */
    int flipLights(int n, int m) {
        if (n == 0) {
            return 0;
        } else if (n == 1) {
            if (m == 0) {
                return 1;
            } else {
                return 2;
            }
        } else if (n == 2) {
            if (m == 0) {
                return 1;
            } else if (m == 1) {
                return 3;
            } else {
                return 4;
            }
        } else {
            // TODO: understand logic here?
            vector<int> firstThree{1, 3, 4}; // # of states for operations without flip-all.
            if (m == 0) {
                return 1;
            } else if (m >= 3) {
                return 4 + 4;
            } else {
                // the 2nd one means for all states obtained in m-1 operation, do a flip all?
                return firstThree[m] + firstThree[m - 1];
            }
        }
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int n;
        int m;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {}
    };

    vector< int > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = flipLights::Solution().flipLights(dp.n, dp.m);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
