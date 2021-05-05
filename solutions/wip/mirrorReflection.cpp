// mirrorReflection.cpp
// leetcode
//
// Created by  Song Ding on 5/21/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace mirrorReflection {
/*
// TODO: copy problem statement here
 858. Mirror Reflection
 Medium
 
 128
 
 214
 
 Favorite
 
 Share
 There is a special square room with mirrors on each of the four walls.  Except for the southwest corner, there are receptors on each of the remaining corners, numbered 0, 1, and 2.
 
 The square room has walls of length p, and a laser ray from the southwest corner first meets the east wall at a distance q from the 0th receptor.
 
 Return the number of the receptor that the ray meets first.  (It is guaranteed that the ray will meet a receptor eventually.)
 
 
 
 Example 1:
 
 Input: p = 2, q = 1
 Output: 2
 Explanation: The ray meets receptor 2 the first time it gets reflected back to the left wall.
 
 
 
 Note:
 
 1 <= p <= 1000
 0 <= q <= p
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    int mirrorReflection(int p, int q) {
        return 0;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int p;
        int q;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {2,1}
    };

    vector< int > answers {
        2
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = mirrorReflection::Solution().mirrorReflection(dp.p, dp.q);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
