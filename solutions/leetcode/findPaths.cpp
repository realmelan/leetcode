//
//  findPaths.cpp
//  leetcode
//
//  Created by  Song Ding on 1/1/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace findPaths {
    class Solution {
    public:
        /**
         DP:
         using a map to record below info:
         for each cell(i, j), how many paths are there for N steps to
         get out of boundary.
         
         start from each boundary cell, iterating from 1 step
         to N steps.
         Note: since step N is only related step N - 1, so keep two
         matrix would be ok.
         */
        int findPaths(int m, int n, int N, int i, int j) {
            if (m <= 0 || n <= 0 || N <= 0) {
                return 0;
            }
            vector<vector<unsigned long>> step1(m);
            for (auto& v : step1) {
                v.resize(n, 0);
            }
            vector<vector<unsigned long>> step2(m);
            for (auto& v : step2) {
                v.resize(n, 0);
            }
            for (int i = 0; i < n; ++i) {
                step1[0][i] += 1;
                step1[m - 1][i] += 1;
            }
            for (int i = 0; i < m; ++i) {
                step1[i][0] += 1;
                step1[i][n - 1] += 1;
            }
            
            long res = step1[i][j];
            for (int k = 2; k <= N; ++k) {
                for (auto& v: step2) {
                    v.clear();
                    v.resize(n, 0);
                }
                
                for (int r = 0; r < m; ++r) {
                    for (int c = 0; c < n; ++c) {
                        if (r - 1 >= 0) {
                            step2[r - 1][c] += step1[r][c];
                            step2[r - 1][c] %= 1000000007;
                        }
                        if (r + 1 < m) {
                            step2[r + 1][c] += step1[r][c];
                            step2[r + 1][c] %= 1000000007;
                        }
                        if (c - 1 >= 0) {
                            step2[r][c - 1] += step1[r][c];
                            step2[r][c - 1] %= 1000000007;
                        }
                        if (c + 1 < n) {
                            step2[r][c + 1] += step1[r][c];
                            step2[r][c + 1] %= 1000000007;
                        }
                    }
                }
                
                step1.swap(step2);
                res += step1[i][j];
            }
            const unsigned long p = pow(10, 9) + 7;
            cout << res << endl;
            return static_cast<int>(res % p);
        }
        int findPaths2(int m, int n, int N, int i, int j) {
            uint dp[51][50][50] = {};
            for (auto Ni = 1; Ni <= N; ++Ni)
                for (auto mi = 0; mi < m; ++mi)
                    for (auto ni = 0; ni < n; ++ni)
                        dp[Ni][mi][ni] = ((mi == 0 ? 1 : dp[Ni - 1][mi - 1][ni]) + (mi == m - 1? 1 : dp[Ni - 1][mi + 1][ni])
                                          + (ni == 0 ? 1 : dp[Ni - 1][mi][ni - 1]) + (ni == n - 1 ? 1 : dp[Ni - 1][mi][ni + 1])) % 1000000007;
            return dp[N][i][j];
        }
    };
}
/*
int main() {
    int m = 36, n = 5;
    int N = 50;
    int i = 15, j = 3;
    cout << findPaths::Solution().findPaths(m, n, N, i, j) << endl;
    cout << findPaths::Solution().findPaths2(m, n, N, i, j) << endl;
    return 0;
}
*/
