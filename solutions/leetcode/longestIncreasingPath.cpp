// longestIncreasingPath.cpp
// leetcode
//
// Created by  Song Ding on 10/21/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace longestIncreasingPath {

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int r = matrix.size();
        if (r <= 0) {
            return 0;
        }
        int c = matrix[0].size();
        if (c <= 0) {
            return 0;
        }
        
        int res = 0;
        unordered_map<int, int> memo;
        for (int ri = 0; ri < r; ++ri) {
            for (int ci = 0; ci < c; ++ci) {
                int v = matrix[ri][ci];
                if ((ri - 1 < 0 || v >= matrix[ri - 1][ci])
                    && (ri + 1 >= r || v >= matrix[ri + 1][ci])
                    && (ci - 1 < 0 || v >= matrix[ri][ci - 1])
                    && (ci + 1 >= c || v >= matrix[ri][ci + 1])) {
                    int t = recur(matrix, ri, ci, memo);
                    if (t > res) {
                        res = t;
                    }
                    memo[ri * c + ci] = res;
                }
            }
        }
        return res;
    }

private:
    int recur(vector<vector<int>>& matrix, int i, int j, unordered_map<int, int>& memo) {
        int r = matrix.size();
        int c = matrix[0].size();
        int id = i * c + j;
        auto it = memo.find(id);
        if (it != memo.end()) {
            return it->second;
        }
        
        int res = 1;
        int v = matrix[i][j];
        if (i - 1 >= 0 && v > matrix[i - 1][j]) {
            int t = recur(matrix, i - 1, j, memo) + 1;
            if (t > res) {
                res = t;
            }
        }
        if (i + 1 < r && v > matrix[i + 1][j]) {
            int t = recur(matrix, i + 1, j, memo) + 1;
            if (t > res) {
                res = t;
            }
        }
        if (j - 1 >= 0 && v > matrix[i][j - 1]) {
            int t = recur(matrix, i, j - 1, memo) + 1;
            if (t > res) {
                res = t;
            }
        }
        if (j + 1 < c && v > matrix[i][j + 1]) {
            int t = recur(matrix, i, j + 1, memo) + 1;
            if (t > res) {
                res = t;
            }
        }
        
        memo[id] = res;
        return res;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> matrix {
        //{9,9,4},{6,6,8},{2,1,1}
        //{3,4,5},{3,2,6},{2,2,1}
        {7,7,5},{2,4,6},{8,2,0}
    };

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = longestIncreasingPath::Solution().longestIncreasingPath(matrix);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
