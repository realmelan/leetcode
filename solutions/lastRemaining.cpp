// lastRemaining.cpp
// leetcode
//
// Created by  Song Ding on 10/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace lastRemaining {
/*
// TODO: copy problem statement here
 390. Elimination Game
 Medium

 272

 241

 Favorite

 Share
 There is a list of sorted integers from 1 to n. Starting from left to right, remove the first number and every other number afterward until you reach the end of the list.

 Repeat the previous step again, but this time from right to left, remove the right most number and every other number from the remaining numbers.

 We keep repeating the steps again, alternating left to right and right to left, until a single number remains.

 Find the last number that remains starting with a list of length n.

 Example:

 Input:
 n = 9,
 1 2 3 4 5 6 7 8 9
 2 4 6 8
 2 6
 6

 Output:
 6
 */

class Solution {
public:
    /**
     * Recursive
     * after one round of removal, the new numbers can be 2*(1,2,3...)
     * if the n/2 is odd, then after 2nd removal, the new numbers are 4*(1,2,3,4...)
     * if the n/2 is even, then the leftover numbers are [2,6,10...], when add 2, it becomes [4,8,12...]=4*(1,2,3...)
     */
    int lastRemaining(int n) {
        if (n <= 2) {
            return n;
        } else if (n == 3) {
            return 2;
        } else if ((n/2) % 2) {
            int t = lastRemaining(n/4);
            return t*4;
        } else {
            int t = lastRemaining(n/4);
            return t*4-2;
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
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {9},
    };

    vector< int > answers {
        6,
        
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = lastRemaining::Solution().lastRemaining(dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
