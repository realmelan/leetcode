// findMinMoves.cpp
// leetcode
//
// Created by  Song Ding on 11/8/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findMinMoves {
/*
// TODO: copy problem statement here
 517. Super Washing Machines
 Hard

 235

 123

 Favorite

 Share
 You have n super washing machines on a line. Initially, each washing machine has some dresses or is empty.

 For each move, you could choose any m (1 ≤ m ≤ n) washing machines, and pass one dress of each washing machine to one of its adjacent washing machines at the same time .

 Given an integer array representing the number of dresses in each washing machine from left to right on the line, you should find the minimum number of moves to make all the washing machines have the same number of dresses. If it is not possible to do it, return -1.

 Example1

 Input: [1,0,5]

 Output: 3

 Explanation:
 1st move:    1     0 <-- 5    =>    1     1     4
 2nd move:    1 <-- 1 <-- 4    =>    2     1     3
 3rd move:    2     1 <-- 3    =>    2     2     2
 Example2

 Input: [0,3,0]

 Output: 2

 Explanation:
 1st move:    0 <-- 3     0    =>    1     2     0
 2nd move:    1     2 --> 0    =>    1     1     1
 Example3

 Input: [0,2,0]

 Output: -1

 Explanation:
 It's impossible to make all the three washing machines have the same number of dresses.
 Note:
 The range of n is [1, 10000].
 The range of dresses number in a super washing machine is [0, 1e5].
 */

class Solution {
public:
    /**
     * this equals to finding out the machines that would do the most handout(to both directions).
     */
    int findMinMoves(vector<int>& machines) {
        int n = machines.size();
        int sum = accumulate(machines.begin(), machines.end(), 0);
        if (sum % n) {
            return -1;
        }
        int avg = sum / n;
        int cnt = 0;
        int res = 0;
        for (int i = 0; i < n; ++i) {
            // cnt < 0 => need to bring dress from the right
            // cnt > 0 => need to send dress to the right
            cnt += machines[i] - avg;
            res = max(res, max(abs(cnt), machines[i]-avg));
        }
        return res;
    }
    int findMinMoves2(vector<int>& machines) {
        int n = machines.size();
        int sum = accumulate(machines.begin(), machines.end(), 0);
        if (sum % n) {
            return -1;
        }
        int avg = sum / n;
        int cnt = 0;
        vector<int> moves(n, 0);
        for (int i = 0; i < n-1; ++i) {
            cnt += machines[i] - avg;
            if (cnt < 0) {
                moves[i+1] -= cnt;
            } else {
                moves[i] += cnt;
            }
        }
        return *max_element(moves.begin(), moves.end());
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> machines;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,0,5}},
        {{0,3,0}},
        {{0,2,0}},
    };

    vector< int > answers {
        3,
        2,
        -1
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findMinMoves::Solution().findMinMoves2(dp.machines);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
