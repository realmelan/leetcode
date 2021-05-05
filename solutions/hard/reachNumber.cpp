// reachNumber.cpp
// leetcode
//
// Created by  Song Ding on 9/26/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace reachNumber {
/*
// TODO: copy problem statement here
 754. Reach a Number
 Easy

 333

 279

 Favorite

 Share
 You are standing at position 0 on an infinite number line. There is a goal at position target.

 On each move, you can either go left or right. During the n-th move (starting from 1), you take n steps.

 Return the minimum number of steps required to reach the destination.

 Example 1:
 Input: target = 3
 Output: 2
 Explanation:
 On the first move we step from 0 to 1.
 On the second step we step from 1 to 3.
 Example 2:
 Input: target = 2
 Output: 3
 Explanation:
 On the first move we step from 0 to 1.
 On the second move we step  from 1 to -1.
 On the third move we step from -1 to 2.
 Note:
 target will be a non-zero integer in the range [-10^9, 10^9].
 */

class Solution {
public:
    /**
     * go right until surpassing target. Now suppose we are k past target, then we can change
     * one of the moves from going right to going left, which would reduce our total distance
     * by 2 * that move. Apparently the gap has to be an even number for us to do change.
     */
    int reachNumber(int target) {
        if (target < 0) {
            target = -target;
        }

        int curMax = 0;
        int steps = 0;
        while (true) {
            ++steps;
            curMax += steps;
            // check whether target is covered and the diff is even
            if (target % 2 == curMax % 2 && curMax >= target) {
                break;
            }
        }
        return steps;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int target;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {3},
        {2},
    };

    vector< int > answers {
        2,
        3
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = reachNumber::Solution().reachNumber(dp.target);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
