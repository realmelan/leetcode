// maximalSquare.cpp
// leetcode
//
// Created by  Song Ding on 11/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maximalSquare {
/*
// TODO: copy problem statement here
 221. Maximal Square
 Medium

 1740

 41

 Favorite

 Share
 Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

 Example:

 Input:

 1 0 1 0 0
 1 0 1 1 1
 1 1 1 1 1
 1 0 0 1 0

 Output: 4
 */

class Solution {
public:
    /**
     * let dp[i][j] = max length of squares whose bottom right corner is at i,j
     * then dp[i][j]=min(dp[i-1][j-1], dp[i][j-1],dp[i-1][j])+1 if matrix[i][j]=1
     */
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size(), m = matrix[0].size(), res = 0;
        vector<vector<int>> dp(n, vector<int>(m,0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == 0 || j == 0) {
                    dp[i][j] = matrix[i][j] - '0';
                } else if (matrix[i][j] == '1') {
                    dp[i][j] = min(dp[i-1][j-1], min(dp[i][j-1],dp[i-1][j])) + 1;
                }
                res = max(res, dp[i][j]);
            }
        }
        return res*res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<char>> matrix;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{
            {'1','0','1','0','0'},
            {'1','0','1','1','1'},
            {'1','1','1','1','1'},
            {'1','0','0','1','0'},
        }}
    };

    vector< int > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maximalSquare::Solution().maximalSquare(dp.matrix);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
