// findMaxForm.cpp
// leetcode
//
// Created by  Song Ding on 10/26/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findMaxForm {
/*
// TODO: copy problem statement here
 474. Ones and Zeroes
 Medium

 663

 160

 Favorite

 Share
 In the computer world, use restricted resource you have to generate maximum benefit is what we always want to pursue.

 For now, suppose you are a dominator of m 0s and n 1s respectively. On the other hand, there is an array with strings consisting of only 0s and 1s.

 Now your task is to find the maximum number of strings that you can form with given m 0s and n 1s. Each 0 and 1 can be used at most once.

 Note:

 The given numbers of 0s and 1s will both not exceed 100
 The size of given string array won't exceed 600.
  

 Example 1:

 Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
 Output: 4

 Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are “10,”0001”,”1”,”0”
  

 Example 2:

 Input: Array = {"10", "0", "1"}, m = 1, n = 1
 Output: 2

 Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".
 */

class Solution {
public:
    /**
     * DP: let dp[i][j] = # of strings i 0 and j 1 can form up to current strings
     */
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for (auto& s : strs) {
            int zeros = 0;
            int ones = 0;
            for (auto c : s) {
                if (c == '0') {
                    ++zeros;
                } else {
                    ++ones;
                }
            }
            for (int i = m; i >= zeros; --i) {
                for (int j = n; j >= ones; --j) {
                    dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones]+1);
                }
            }
        }
        return dp[m][n];
    }
    /**
     * DFS:
     */
    int findMaxForm_dfs(vector<string>& strs, int m, int n) {
        sort(strs.begin(), strs.end(), [](const string& a, const string& b){
            return a.size() < b.size();
        });
        vector<vector<int>> cs;
        for (auto& s : strs) {
            if (s.size() <= m+n) {
                cs.push_back({0,0});
                for (auto c : s) {
                    ++cs.back()[c-'0'];
                }
            }
        }
        int sn = cs.size();
        vector<vector<vector<int>>> dp(m+1, vector<vector<int>>(n+1, vector<int>(sn+1, -1)));
        return dfs(m, n, 0, cs, dp);
        
    }
    int dfs(int m, int n, int k, const vector<vector<int>>& cs, vector<vector<vector<int>>>& dp) {
        if ((m == 0 && n == 0) || k >= cs.size() || (m <= cs[k][0] && n <= cs[k][1] && m+n < cs[k][0]+cs[k][1])) {
            return 0;
        }
        if (dp[m][n][k] >= 0) {
            return dp[m][n][k];
        }
        dp[m][n][k] = dfs(m, n, k+1, cs, dp);
        if (cover(m, n, cs[k])) {
            dp[m][n][k] = max(dp[m][n][k], dfs(m-cs[k][0], n-cs[k][1], k+1, cs, dp)+1);
        }
        return dp[m][n][k];
    }
    /**
     * DP:
     * let dp[i][j][k] = max # of strings m 0's and n 1's  can form for strings[k..sn]
     * then dp[i][j][k] = max(dp[i][j][k+1], dp[i-cs[k][0]][j-cs[k][1][k+1]+1).
     * here cs[k][0] = # of 0's in strs[k], cs[k][1]=# of 1's in strs[k];
     */
    int findMaxForm_dp(vector<string>& strs, int m, int n) {
        sort(strs.begin(), strs.end(), [](const string& a, const string& b){
            return a.size() < b.size();
        });
        vector<vector<int>> cs;
        for (auto& s : strs) {
            if (s.size() <= m+n) {
                cs.push_back({0,0});
                for (auto c : s) {
                    ++cs.back()[c-'0'];
                }
            }
        }
        
        int sn = cs.size();
        vector<vector<vector<int>>> dp(m+1, vector<vector<int>>(n+1, vector<int>(sn+1, 0)));
        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j <= n; ++j) {
                for (int k = sn-1; k >= 0; --k) {
                    dp[i][j][k] = dp[i][j][k+1];
                    if (cover(i, j, cs[k])) {
                        dp[i][j][k] = max(dp[i][j][k], dp[i-cs[k][0]][j-cs[k][1]][k+1]+1);
                    }
                }
            }
        }
        return dp[m][n][0];
    }

private:
    bool cover(int m, int n, const vector<int>& cnt) {
        return m >= cnt[0] && n >= cnt[1];
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<string> strs;
        int m;
        int n;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{"10", "0001", "111001", "1", "0"}, 5, 3},
        {{"10", "0", "1"}, 1, 1},
    };

    vector< int > answers {
        4,
        2,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findMaxForm::Solution().findMaxForm(dp.strs, dp.m, dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
