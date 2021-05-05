// brokenCalc.cpp
// leetcode
//
// Created by  Song Ding on 5/3/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace brokenCalc {

class Solution {
public:
    /**
     Intuition:
     Considering how to change Y to X
     Opertation 1: Y = Y / 2 if Y is even
     Opertation 2: Y = Y + 1
     
     
     Explanation:
     Obviously,
     If Y <= X, we won't do Y / 2 anymore.
     We will increase Y until it equals to X
     
     So before that, while Y > X, we'll keep reducing Y, until it's smaller than X.
     If Y is odd, we can do only Y = Y + 1
     If Y is even, if we plus 1 to Y, then Y is odd, we need to plus another 1.
     And because (Y + 1 + 1) / 2 = (Y / 2) + 1, 3 operations are more than 2.
     We always choose Y / 2 if Y is even.
     
     
     Why it's right
     Actually, what we do is:
     If Y is even, Y = Y / 2
     If Y is odd, Y = (Y + 1) / 2
     
     We reduce Y with least possible operations, until it's smaller than X.
     
     And we know that, we won't do Y + 1 twice in a row.
     Becasue we will always end with an operation Y / 2.
     
     2N times Y + 1 and once Y / 2 needs 2N + 1 operations.
     Once Y / 2 first and N times Y + 1 will end up with same result, but needs only N + 1 operations.
     */
    int brokenCalc(int X, int Y) {
        int steps = 0;
        while (Y > X) {
            
            if (Y % 2) {
                Y = (Y + 1) / 2;
                steps += 2;
            }else {
                Y /= 2;
                ++steps;
            }
        }
        return steps + X - Y;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> p {
        {2,3},
        {5,8},
        {3,10},
        {1024,1},
        {3,8},
        {2,2},
        {1,1000000000},
        {2,1000000000},
        {1000000000,2},
        {9411921,9411923}
    };

    vector<  int > answers {
        2,2,3,1023,3,0,39,38
    };
    int i = 9;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = brokenCalc::Solution().brokenCalc(p[i][0], p[i][1]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
