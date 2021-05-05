// maximalRectangle.cpp
// leetcode
//
// Created by  Song Ding on 3/18/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maximalRectangle {

class Solution {
public:
    // https://leetcode.com/problems/maximal-rectangle/discuss/29054/Share-my-DP-solution
    // for each position (i,j), extends up (i,j) to (i1,j) such that (i1-1,j)=0
    // Now, compute max rectangle that contains (i1,j)->(i,j).
    // To get the left most bounday of this rectangle, lmax, and right boundary rmin,
    // lmax = max( extends from point (k,j)(i1<=k<=i) leftward until meeting '0')
    // rmin = min( extends from point (k,j)(i1<=k<=i) rightward until metting '0')
    int maximalRectangle2(vector<vector<char> > &matrix) {
        int m = matrix.size(), n = m ? matrix[0].size() : 0;
        vector<int> left(n, 0), right(n, n), height(n, 0);
        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    ++height[j];
                } else {
                    height[j] = 0;
                }
            }
            int curLeft = 0;
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    left[j] = max(left[j], curLeft);
                } else {
                    left[j] = 0;
                    curLeft = j+1;
                }
            }
            int curRight = n;
            for (int j = n-1; j >= 0; --j) {
                if (matrix[i][j] == '1') {
                    right[j] = min(right[j], curRight);
                } else {
                    right[j] = n;
                    curRight = j;
                }
            }
            for (int j = 0; j < n; ++j) {
                res = max(res, (right[j]-left[j]) * height[j]);
            }
        }
        return res;
    }
    int maximalRectangle3(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = m ? matrix[0].size() : 0;
        // x,y=> a list of rectangles with bottom right position at x-1,y-1
        // these rectangles don't have same width or same height, ordering by
        // increasing width
        vector<vector<vector<vector<int>>>> dp(m+1, vector<vector<vector<int>>>(n+1));
        int res = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (matrix[i-1][j-1] == '1') {
                    int maxH = dp[i-1][j].size() ? (dp[i-1][j].back())[1] + 1 : 1;
                    bool used = false;
                    for (auto& v : dp[i][j-1]) {
                        if (v[1] < maxH) {
                            dp[i][j].emplace_back(std::initializer_list<int>({v[0]+1, v[1]}));
                            res = max(res, (v[0]+1) * v[1]);
                        } else {
                            dp[i][j].emplace_back(std::initializer_list<int>({v[0]+1, maxH}));
                            res = max(res, (v[0]+1) * maxH);
                            used = true;
                            break;
                        }
                    }
                    if (!used) {
                        dp[i][j].emplace_back(std::initializer_list<int>({1, maxH}));
                        res = max(res, maxH);
                    }
                }
            }
        }
        return res;
    }
    /**
     if a column contains a 0, then the matrix is divided into two parts:
     left and right, that are two sub problems.
     However, on this column, there might be 1's, but we only need to consider
     the rectangle that contains the 1's on this column.
     */
    int maximalRectangle(vector<vector<char>>& matrix) {
        int row = matrix.size();
        if (row <= 0) {
            return 0;
        }
        int column = matrix[0].size();
        if (column <= 0) {
            return 0;
        }
        return dnc(matrix, 0, row - 1, 0, column - 1);
    }
private:
    int dnc(vector<vector<char>>& m, int r1, int r2, int c1, int c2) {
        int maxzero = 0;
        int zc = -1;
        for (int c = c1; c <= c2; ++c) {
            int s = r2 - r1 + 1;
            for (int r = r1; r <= r2; ++r) {
                s -= m[r][c] - '0';
            }
            if (s > maxzero) {
                maxzero = s;
                zc = c;
            }
        }
        if (maxzero == 0) {
            return (r2 - r1 + 1) * (c2 - c1 + 1);
        }
        
        int left = 0;
        if (zc > c1) {
            left = dnc(m, r1, r2, c1, zc - 1);
        }
        int right = 0;
        if (zc < c2) {
            right = dnc(m, r1, r2, zc + 1, c2);
        }
        
        int re = r1;
        int res = 0;
        while (true) {
            int rs = re;
            while (rs <= r2 && m[rs][zc] == '0') { ++rs; }
            if (rs > r2) {
                break;
            }
            re = rs + 1;
            while (re <= r2 && m[re][zc] == '1') { ++re; }
            
            // find max rectangle from rs to re
            // this is DP.
            vector<int> leftWidth(re, INT_MAX);
            vector<int> rightWidth(re, INT_MAX);
            for (int r = rs; r < re; ++r) {
                int left = 0;
                for (int c = zc - 1; c >= c1 && m[r][c] == '1'; --c) {
                    ++left;
                }
                int right = 0;
                for (int c = zc + 1; c <= c2 && m[r][c] == '1'; ++c ) {
                    ++right;
                }
                leftWidth[r] = left;
                rightWidth[r] = right;
                
                if (1 + left + right > res) {
                    res = 1 + left + right;
                }
            }
            vector<int> recLeft(leftWidth);
            vector<int> recRight(rightWidth);
            for (int h = 2; h <= re - rs; ++h) {
                vector<int> cRecLeft(re, INT_MAX);
                vector<int> cRecRight(re, INT_MAX);
                for (int r = rs + h - 1; r < re; ++r) {
                    cRecLeft[r] = min(leftWidth[r], recLeft[r - 1]);
                    cRecRight[r] = min(rightWidth[r], recRight[r - 1]);
                    int ones = 1 + cRecLeft[r] + cRecRight[r];
                    if (ones * h > res) {
                        res = ones * h;
                    }
                }
                recLeft.swap(cRecLeft);
                recRight.swap(cRecRight);
            }
        }
        
        res = max(res, max(left, right));
        return res;
    }
private:
};

};

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<char>> matrix {
        //{'1','0','1','1','0','1'},{'1','1','1','1','1','1'},{'0','1','1','0','1','1'},{'1','1','1','0','1','0'},{'0','1','1','1','1','1'},{'1','1','0','1','1','1'}
        {'0','1','1'},{'1','1','0'},{'1','1','1'}
    };
    // TODO: add return type and paramters.
    clock_t start = clock();
    int res = maximalRectangle::Solution().maximalRectangle2(matrix);
    //cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
