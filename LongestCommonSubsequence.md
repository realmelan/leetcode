Longest Common Subsequence

# lenght of LCS
```c++
int lcs(string s1, string s2) {
    int n1 = s1.size(), n2 = s2.size();
    vector<vector<int>> dp(n1+1, vector<int>(n2+1));
    for (int i = 0; i <= n1; ++i) {
        for (int j = 0; j <= n2; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (s1[i-1] == s2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[n1][n2];
}
```

# LCS string itself
```c++
int lcs_string(string s1, string s2) {
    int n1 = s1.size(), n2 = s2.size();
    vector<vector<int>> dp(n1+1, vector<int>(n2+1));
    for (int i = 0; i <= n1; ++i) {
        for (int j = 0; j <= n2; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (s1[i-1] == s2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    string res;
    int i = n1, j = n2;
    while (i && j) {
        if (s1[i-1] == s2[j-1]) {
            res.push_back(s1[i-1]);
            --i;
            --j;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            --j;
        } else {
            --i;
        }
    }
    reverse(begin(res), end(res));
    return res;
}
```

# REF:
* https://www.geeksforgeeks.org/printing-longest-common-subsequence/?ref=rp

# Problems:
* https://leetcode.com/problems/shortest-common-supersequence/
