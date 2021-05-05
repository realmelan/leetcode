// minDominoRotations.cpp
// leetcode
//
// Created by  Song Ding on 5/19/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minDominoRotations {
/*
// TODO: copy problem statement here
 1007. Minimum Domino Rotations For Equal Row
 Medium
 
 48
 
 54
 
 Favorite
 
 Share
 In a row of dominoes, A[i] and B[i] represent the top and bottom halves of the i-th domino.  (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)
 
 We may rotate the i-th domino, so that A[i] and B[i] swap values.
 
 Return the minimum number of rotations so that all the values in A are the same, or all the values in B are the same.
 
 If it cannot be done, return -1.
 
 
 
 Example 1:
 
 
 
 Input: A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
 Output: 2
 Explanation:
 The first figure represents the dominoes as given by A and B: before we do any rotations.
 If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.
 Example 2:
 
 Input: A = [3,5,1,2,3], B = [3,6,3,3,4]
 Output: -1
 Explanation:
 In this case, it is not possible to rotate the dominoes to make one row of values equal.
 
 
 Note:
 
 1 <= A[i], B[i] <= 6
 2 <= A.length == B.length <= 20000
 */

class Solution {
public:
    /**
     * The value has to be either A[0] or B[0]
     */
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        int n = A.size();
        int t = A[0];
        int b = B[0];
        vector<int> a1v;
        vector<int> b1v;
        for (int i = 0; i < n; ++i) {
            if (A[i] == t && B[i] == t) {
                a1v.push_back(3);
            } else if (A[i] == t) {
                a1v.push_back(1);
            } else if (B[i] == t) {
                a1v.push_back(2);
            } else {
                a1v.push_back(0);
            }
            
            if (A[i] == b && B[i] == b) {
                b1v.push_back(3);
            } else if (A[i] == b) {
                b1v.push_back(2);
            } else if (B[i] == b) {
                b1v.push_back(1);
            } else {
                b1v.push_back(0);
            }
        }
        
        int a1t = 0, a1b = 0;
        int i = 0;
        for (; i < n; ++i) {
            if (!a1v[i]) {
                break;
            }
            switch (a1v[i]) {
                case 1:
                    ++a1t;
                    break;
                case 2:
                    ++a1b;
                    break;
                case 3:
                    ++a1t;
                    ++a1b;
                    break;
            }
        }
        int res1 = -1;
        if (i == n) {
            res1 = min(n - a1t, n - a1b);
        }
        
        int b1t = 0, b1b = 0;
        for (i = 0; i < n; ++i) {
            if (!b1v[i]) {
                break;
            }
            switch (b1v[i]) {
                case 1:
                    ++b1t;
                    break;
                case 2:
                    ++b1b;
                    break;
                case 3:
                    ++b1t;
                    ++b1b;
                    break;
            }
        }
        int res2 = -1;
        if (i == n) {
            res2 = min(n - b1t, n - b1b);
        }
        
        if (res1 == -1) {
            return res2;
        } else if (res2 == -1) {
            return res1;
        } else {
            return min(res1, res2);
        }
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> A;
        vector<int> B;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{2,1,2,4,2,2},{5,2,6,2,3,2}},
        {{3,5,1,2,3},{3,6,3,3,4}},
        {{1,2,2,1,2,1,2,1,2},{1,2,1,1,1,1,2,1,2}}
    };

    vector< int > answers {
        2,
        -1,
        -1
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minDominoRotations::Solution().minDominoRotations(dp.A, dp.B);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
