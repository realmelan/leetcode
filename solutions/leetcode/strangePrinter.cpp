//
//  strangePrinter.cpp
//  leetcode
//
//  Created by  Song Ding on 3/5/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace strangePrinter {
class Solution {
public:
    /**
     let dp[i][j] = # of turns to print s[i][j],
     then dp[i][j] = 1+dp[i+1][j] (the slowest)
     or if there is s[k] = s[i], then dp[i][j] = dp[i+1][k-1] + dp[k][j], which means
     the first half doesn't have to print s[i], as it can be printed by the seond half.
     */
        int strangePrinter(string s) {
            int n = s.size();
            if (n <= 1) {
                return n;
            }
            string t;
            char last = s[0];
            t.push_back(last);
            for (auto c : s) {
                if (last != c) {
                    t.push_back(c);
                }
                last = c;
            }
            n = t.size();
            vector<vector<int>> dp(n, vector<int>(n, 0));
            for (int i = 0; i < n; ++i) {
                dp[i][i] = 1;
            }
            for (int l = 2; l <= n; ++l) {
                for (int i = 0; i <= n-l; ++i) {
                    int j = i+l-1;
                    dp[i][j] = 1 + dp[i+1][j];
                    for (int k = i+1; k < j; ++k) {
                        if (t[k+1] == t[i]) {
                            int res = dp[i+1][k] + dp[k+1][j];
                            dp[i][j] = min(dp[i][j], res);
                        }
                    }
                }
            }
            return dp[0][n-1];
        }
        /**
         First of all, compress the given string by reducing same characters
         in a sub array into one character, say aaabbb to ab. This will not
         change the final result.
         
         Now, string from the first position, and see whether there are other
         positions that have the same character. Loop through all combinations
         of (0, j), where j is a postion which has the same character as the 0th.
         Recursively do this for substrings.
         
         single characters shall be removed first.
         */
        int strangePrinter_dfs(string s) {
            int n = s.size();
            if (n <= 1) {
                return n;
            }
            
            string t;
            char last = s[0];
            t.push_back(last);
            for (auto c : s) {
                if (last != c) {
                    t.push_back(c);
                }
                last = c;
            }
            
            map<string, int> memo;
            return dfs(t, memo);
        }
    private:
        int dfs(string s, map<string, int>& memo) {
            auto it = memo.find(s);
            if (it != memo.end()) {
                return it->second;
            }
            
            int n = s.size();
            if (n <= 1) {
                return n;
            }
            
            char f = s[0];
            int res = 1 + dfs(s.substr(1), memo);
            for (int i = 2; i < n; ++i) {
                if (s[i] == f) {
                    int t = 1 + dfs(s.substr(1, i - 1), memo);
                    if (i < n - 1) {
                        t += dfs(s.substr(i + 1), memo);
                    }
                    
                    if (t < res) {
                        res = t;
                    }
                }
            }
            memo.insert(make_pair(s, res));
            return res;
        }
    };
}

/*
int main() {
    //string s = "aba";
    string s = "baacdddaaddaaaaccbddbcabdaabdbbcdcbbbacbddcabcaaa";
    cout << strangePrinter::Solution().strangePrinter(s) << endl;
    return 0;
}
 //*/
