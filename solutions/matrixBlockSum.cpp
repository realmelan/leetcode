//
//  matrixBlockSum.cpp
//  leetcode
//
//  Created by Song Ding on 7/15/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace matrixBlockSum {
/*
// TODO: copy problem statement here
 1314. Matrix Block Sum
 Medium

 354

 69

 Add to List

 Share
 Given a m * n matrix mat and an integer K, return a matrix answer where each answer[i][j] is the sum of all elements mat[r][c] for i - K <= r <= i + K, j - K <= c <= j + K, and (r, c) is a valid position in the matrix.
  

 Example 1:

 Input: mat = [[1,2,3],[4,5,6],[7,8,9]], K = 1
 Output: [[12,21,16],[27,45,33],[24,39,28]]
 Example 2:

 Input: mat = [[1,2,3],[4,5,6],[7,8,9]], K = 2
 Output: [[45,45,45],[45,45,45],[45,45,45]]
  

 Constraints:

 m == mat.length
 n == mat[i].length
 1 <= m, n, K <= 100
 1 <= mat[i][j] <= 100
*/
class Solution {
public:
    // TODO: copy function signature here
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int K) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));
        vector<vector<int>> t(ans);
        for (int i = 0; i < m; ++i) {
            int c = 0;
            for (int j = 0; j < n; ++j) {
                c += mat[i][j];
                c -= (j-K-1 >= 0 ? mat[i][j-K-1] : 0);
                t[i][j] += c;
            }
        }
        for (int i = 0; i < m; ++i) {
            int c = 0;
            for (int j = n-1; j >= 0; --j) {
                t[i][j] += c;
                c += mat[i][j];
                c -= (j+K < n ? mat[i][j+K] : 0);
            }
        }
        for (int j = 0; j < n; ++j) {
            int c = 0;
            for (int i = 0; i < m; ++i) {
                c += t[i][j];
                c -= (i-K-1 >= 0 ? t[i-K-1][j] : 0);
                ans[i][j] += c;
            }
        }
        for (int j = 0; j < n; ++j) {
            int c = 0;
            for (int i = m-1; i >= 0; --i) {
                ans[i][j] += c;
                c += t[i][j];
                c -= (i+K < m ? t[i+K][j] : 0);
            }
        }
        return ans;
    }
    vector<vector<int>> matrixBlockSum2(vector<vector<int>>& mat, int K) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));
        vector<vector<int>> t(ans);
        for (int i = 0; i < m; ++i) {
            int c = 0;
            for (int j = 0; j < n; ++j) {
                 c += mat[i][j];
                t[i][j] = (i>=1 ? t[i-1][j] : 0) + c;
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int left = max(0, j-K);
                int right = min(n-1, j+K);
                int up = max(0, i-K);
                int down = min(m-1, i+K);
                
                ans[i][j] = t[down][right];
                if (left-1 >= 0) {
                    ans[i][j] -= t[down][left-1];
                }
                if (up-1 >= 0) {
                    ans[i][j] -= t[up-1][right];
                }
                if (left - 1 >= 0 && up-1 >= 0) {
                    ans[i][j] += t[up-1][left-1];
                }
            }
        }
        
        return ans;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> mat;
        int K;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{{1,2,3},{4,5,6},{7,8,9}},1},
        {{{1,2,3},{4,5,6},{7,8,9}},2},
    };
    // TODO: provide expected results here
    vector<vector<vector<int>>> answers {
        {{12,21,16},{27,45,33},{24,39,28}},
        {{45,45,45},{45,45,45},{45,45,45}}
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = matrixBlockSum::Solution().matrixBlockSum2(dp.mat, dp.K);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
