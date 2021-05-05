// maxUncrossedLines.cpp
// leetcode
//
// Created by  Song Ding on 5/21/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxUncrossedLines {
/*
// TODO: copy problem statement here
 1035. Uncrossed Lines
 Medium
 
 132
 
 5
 
 Favorite
 
 Share
 We write the integers of A and B (in the order they are given) on two separate horizontal lines.
 
 Now, we may draw connecting lines: a straight line connecting two numbers A[i] and B[j] such that:
 
 A[i] == B[j];
 The line we draw does not intersect any other connecting (non-horizontal) line.
 Note that a connecting lines cannot intersect even at the endpoints: each number can only belong to one connecting line.
 
 Return the maximum number of connecting lines we can draw in this way.
 
 
 
 Example 1:
 
 
 Input: A = [1,4,2], B = [1,2,4]
 Output: 2
 Explanation: We can draw 2 uncrossed lines as in the diagram.
 We cannot draw 3 uncrossed lines, because the line from A[1]=4 to B[2]=4 will intersect the line from A[2]=2 to B[1]=2.
 Example 2:
 
 Input: A = [2,5,1,2,5], B = [10,5,2,1,5,2]
 Output: 3
 Example 3:
 
 Input: A = [1,3,7,1,7,5], B = [1,9,2,5,1]
 Output: 2
 
 
 Note:
 
 1 <= A.length <= 500
 1 <= B.length <= 500
 1 <= A[i], B[i] <= 2000
 */

class Solution {
public:
    /**
     * DP:
     * let mul(i,j) = max # of uncrossed lines for A[0..i] and B[0..j]
     * then mul(i,j) = max(mul(i-1,j), mul(i, j-1), mul(i-1,j-1)+1 if A[i]==B[j]).
     */
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        int na = A.size();
        int nb = B.size();
        int cnt = 0;
        vector<vector<int>> res(na);
        for (int i = 0; i < na; ++i) {
            res[i].resize(nb);
            if (B[0] == A[i]) {
                cnt = 1;
            }
            res[i][0] = cnt;
        }
        cnt = 0;
        for (int i = 0; i < nb; ++i) {
            if (A[0] == B[i]) {
                cnt = 1;
            }
            res[0][i] = cnt;
        }
        for (int i = 1; i < na; ++i) {
            for (int j = 1; j < nb; ++j) {
                res[i][j] = max(res[i-1][j], res[i][j-1]);
                if (A[i] == B[j]) {
                    res[i][j] = max(res[i][j], res[i-1][j-1]+1);
                }
            }
        }
        return res[na-1][nb-1];
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
        {{1,4,2},{1,2,4}},
        {{2,5,1,2,5},{10,5,2,1,5,2}},
        {{1,3,7,1,7,5},{1,9,2,5,1}}
    };

    vector< int > answers {
        2,
        3,
        2
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxUncrossedLines::Solution().maxUncrossedLines(dp.A, dp.B);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
