// minCut.cpp
// leetcode
//
// Created by  Song Ding on 4/4/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

/**
 132. Palindrome Partitioning II
 Hard

 725

 25

 Favorite

 Share
 Given a string s, partition s such that every substring of the partition is a palindrome.

 Return the minimum cuts needed for a palindrome partitioning of s.

 Example:

 Input: "aab"
 Output: 1
 Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
 
 */

namespace minCut {

class Solution {
public:
    /**
     *  Step 1, compute a table t[i][j] to tell
     *      whether string s[1..j] is palindrome.
     *      This step takes O(n^2)
     *
     *  Step 2: DFS with memo to find the minimum cut
     *      needed.
     */
    int minCut(string s) {
        int n = s.size();
        int res = 0;
        if (n > 0) {
            vector<vector<bool>> t(n);
            clock_t start = clock();
            prepare_table(s, t);
            cout << clock() - start << endl;
            
            vector<vector<int>> memo(n);
            for (auto& v : memo) {
                v.resize(n, -1);
            }
            //res = dfs(0, n - 1, t, memo);
            vector<int> d(n, n);
            d[0] = 0;
            for (int i = 1; i < n; ++i) {
                if (t[0][i]) {
                    d[i] = 0;
                } else {
                    for (int j = 1; j <= i; ++j) {
                        if (t[j][i] && d[i] > 1 + d[j - 1]) {
                            d[i] = 1 + d[j - 1];
                        }
                    }
                }
            }
            res = d[n - 1];
        }
        return res;
    }
    
    int minCut2(string s) {
        int n = s.size();
        int res = 0;
        if (n > 0) {
            vector<vector<bool>> t(n);
            for (auto& v : t) {
                v.resize(n, false);
            }
            vector<int> cut(n);
            for (int i = 0; i < n; ++i) {
                cut[i] = i;
            }
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j <= i; ++j) {
                    if (s[j] == s[i] && (j+1 >= i-1 || t[j+1][i-1])) {
                        t[j][i] = true;
                        cut[i] = min(cut[i], j > 0 ? (1 + cut[j - 1]) : 0);
                    }
                }
            }
            res = cut[n - 1];
        }
        return res;
    }
    
    int minCut3(string s) {
        int n = s.size();
        if (n > 0) {
            vector<int> cut(n);
            for (int i = 0; i < n; ++i) {
                cut[i] = i;
            }
            for (int i = 0; i < n; ++i) {
                for (int j = 0; i - j >= 0 && i + j < n && s[i-j]==s[i+j]; ++j) {
                    cut[i+j] = min(cut[i+j], j < i ? 1 + cut[i-j-1] : 0);
                }
                for (int j = 1; i-j+1>=0 && i+j < n && s[i-j+1] == s[i+j]; ++j) {
                    cut[i+j] = min(cut[i+j], j <= i ? 1 + cut[i-j] : 0);
                }
            }
            return cut[n - 1];
        }
        return 0;
    }

private:
    void prepare_table(const string& s, vector<vector<bool>>& t) {
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            t[i].resize(n, false);
            t[i][i] = true;
            if (i + 1 < n) {
                t[i][i + 1] = (s[i] == s[i + 1]);
            }
        }
        for (int i = 3; i <= n; ++i) {
            for (int j = 0; j <= n - i; ++j) {
                int k = j + i - 1;
                if (s[j] == s[k]) {
                    t[j][k] = t[j + 1][k - 1];
                }
            }
        }
    }
    int dfs(int i, int j, const vector<vector<bool>>& t, vector<vector<int>>& memo) {
        if (memo[i][j] != -1) {
            return memo[i][j];
        } else if (t[i][j]) {
            memo[i][j] = 0;
            return 0;
        }
        
        int res = j - i;
        for (int k = i; k < j; ++k) {
            int r1 = dfs(i, k, t, memo);
            int r2 = dfs(k + 1, j, t, memo);
            if (res > r1 + r2 + 1) {
                res = r1 + r2 + 1;
            }
        }
        memo[i][j] = res;
        return res;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string s{"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaBBaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
    //string s{"aab"};
    //string s("ababa");
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = minCut::Solution().minCut3(s);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
