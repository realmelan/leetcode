// asteroidCollision.cpp
// leetcode
//
// Created by  Song Ding on 10/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace asteroidCollision {
/*
// TODO: copy problem statement here
 735. Asteroid Collision
 Medium

 567

 70

 Favorite

 Share
 We are given an array asteroids of integers representing asteroids in a row.

 For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

 Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

 Example 1:
 Input:
 asteroids = [5, 10, -5]
 Output: [5, 10]
 Explanation:
 The 10 and -5 collide resulting in 10.  The 5 and 10 never collide.
 Example 2:
 Input:
 asteroids = [8, -8]
 Output: []
 Explanation:
 The 8 and -8 collide exploding each other.
 Example 3:
 Input:
 asteroids = [10, 2, -5]
 Output: [10]
 Explanation:
 The 2 and -5 collide resulting in -5.  The 10 and -5 collide resulting in 10.
 Example 4:
 Input:
 asteroids = [-2, -1, 1, 2]
 Output: [-2, -1, 1, 2]
 Explanation:
 The -2 and -1 are moving left, while the 1 and 2 are moving right.
 Asteroids moving the same direction never meet, so no asteroids will meet each other.
 Note:

 The length of asteroids will be at most 10000.
 Each asteroid will be a non-zero integer in the range [-1000, 1000]..
 */

class Solution {
public:
    /**
     *
     */
    vector<int> asteroidCollision(vector<int>& asteroids) {
        int n = asteroids.size();
        vector<int> res{asteroids[0]};
        for (int i = 1; i < n; ++i) {
            if (asteroids[i] == 0) {
                continue;
            }
            if (asteroids[i] > 0) {
                res.push_back(asteroids[i]);
            } else {
                // check res from back to forth, and update
                int t = asteroids[i];
                while (res.size() && t < 0 && res.back() > 0) {
                    int b = res.back();
                    if (t + b <= 0) {
                        res.pop_back();
                    }
                    if (t + b >= 0) {
                        t = 0;
                    }
                }
                if (t) {
                    res.push_back(asteroids[i]);
                }
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> asteroids;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{5, 10, -5}},
        {{8, -8}},
        {{10, 2, -5}},
        {{-2, -1, 1, 2}},
    };

    vector< vector<int> > answers {
        {5, 10},
        {},
        {10},
        {-2, -1, 1, 2},
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = asteroidCollision::Solution().asteroidCollision(dp.asteroids);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
