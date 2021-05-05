// numSubmatrixSumTarget.cpp
// leetcode
//
// Created by  Song Ding on 9/19/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numSubmatrixSumTarget {
/*
// TODO: copy problem statement here
 1074. Number of Submatrices That Sum to Target
 Hard
 
 148
 
 5
 
 Favorite
 
 Share
 Given a matrix, and a target, return the number of non-empty submatrices that sum to target.
 
 A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.
 
 Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.
 
 
 
 Example 1:
 
 Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
 Output: 4
 Explanation: The four 1x1 submatrices that only contain 0.
 Example 2:
 
 Input: matrix = [[1,-1],[-1,1]], target = 0
 Output: 5
 Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.
 
 
 Note:
 
 1 <= matrix.length <= 300
 1 <= matrix[0].length <= 300
 -1000 <= matrix[i] <= 1000
 -10^8 <= target <= 10^8
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        return numSubmatrixSumTarget1(matrix, target);
    }
    
    int numSubmatrixSumTarget1(vector<vector<int>>& matrix, int target) {
        int row = matrix.size();
        int col = matrix[0].size();
        int res = 0;
        vector<vector<int>> sums;
        for (int r = 0; r < row; ++r) {
            vector<int> rsum(col+1, 0);
            for (int c = 1; c <= col; ++c) {
                rsum[c] = rsum[c-1]+matrix[r][c-1];
            }
            sums.push_back(vector<int>(col+1, 0));
            for (int i = 0; i <= r; ++i) {
                unordered_map<int, int> sumCnt;
                sumCnt[0] = 1;
                for (int c = 1; c <= col; ++c) {
                    sums[i][c] += rsum[c];
                    res += sumCnt[sums[i][c]-target];
                    ++sumCnt[sums[i][c]];
                }
            }
        }
        return res;
    }
    int numSubmatrixSumTarget2(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size(), res = 0;
        for (int i = 0; i < m; ++i) {
            vector<int> cols(n+1, 0);
            for (int j = i; j < m; ++j) {
                unordered_map<int,int> cnt;
                cnt[0] = 1;
                int sum = 0;
                for (int k = 0; k < n; ++k) {
                    sum += matrix[j][k];
                    cols[k+1] += sum;
                    res += cnt[cols[k+1]-target];
                    ++cnt[cols[k+1]];
                }
            }
        }
        return res;
    }

private:
};

}

//*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> matrix;
        int target;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{{{0,1,0},{1,1,1},{0,1,0}}, 0},
        {{{1,-1},{-1,1}}, 0},
        {{{0,1,0,0,1},{0,0,1,1,1},{1,1,1,0,1},{1,1,0,1,1},{0,1,1,0,0}},1},
    };

    vector< int > answers {
        4,
        5,
        47
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = numSubmatrixSumTarget::Solution().numSubmatrixSumTarget2(dp.matrix, dp.target);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
