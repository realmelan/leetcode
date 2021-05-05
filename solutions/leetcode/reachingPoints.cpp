// reachingPoints.cpp
// leetcode
//
// Created by  Song Ding on 1/7/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace reachingPoints {

class Solution {
public:
    /**
     * This looks like finding LCM of tx and ty.
     * Let's start from (tx, ty) and there is only one way
     * of getting to the previous state (sx, sy): the larger of the
     * two minus the smaller.
     */
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        int x = tx;
        int y = ty;
        while (true) {
            if (x < sx || y < sy) {
                return false;
            }
            if (((x - sx) % y == 0 && y == sy)
                || ((y - sy) % x == 0 && x == sx)) {
                return true;
            }
            
            
            if (x > y) {
                x %= y;
            } else {
                y %= x;
            }
           
        }
        return true;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here

    vector< vector<int>  > xy {
        {1,1,3,5},
        {1,1,2,2},
        {1,1,1,1},
        {1,1,1000000000,1},
        {9,9,9,18},
        {10,1,17,17},
        {9,10,9,19}
    };
    vector<bool> answers {
        true,
        false,
        true
    };
    int i = 1;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = reachingPoints::Solution().reachingPoints(xy[i][0], xy[i][1], xy[i][2], xy[i][3]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
