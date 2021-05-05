//
//  numSquares.cpp
//  leetcode
//
//  Created by  Song Ding on 11/29/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace numSquares {
    class Solution {
    public:
        int numSquares(int n) {
            return numSquares_recur(n);
        }
        int numSquares_recur(int n) {
            vector<int> dp(n+1, 0);
            vector<int> sq;
            for (int i = 1; i*i <= n; ++i) {
                sq.push_back(i*i);
                dp[i*i] = 1;
            }
            dp[0] = 0;
            return recur(n, sq, dp);
        }
        int recur(int n, vector<int>& sq, vector<int>& dp) {
            if (dp[n]) {
                return dp[n];
            }
            int t = n;
            for (int j = sqrt(n)-1; j >= 0; --j) {
                if (sq[j] <= n) {
                    t = min(t, recur(n-sq[j], sq, dp)+1);
                }
            }
            dp[n] = t;
            return dp[n];
        }
        int numSquares_dp3(int n) {
            vector<int> sq;
            vector<int> dp(n+1, INT_MAX);
            for (int i = 1; i*i <= n; ++i) {
                sq.push_back(i*i);
                dp[i*i] = 1;
            }
            for (int i = 1; i < n; ++i) {
                for (int j = 0; j < sq.size() && i + sq[j] <= n; ++j) {
                    dp[i+sq[j]] = min(dp[i+sq[j]], 1+dp[i]);
                }
            }
            return dp[n];
        }
        int numSquares_dp2(int n) {
            if (n <= 0)
            {
                return 0;
            }
            
            // cntPerfectSquares[i] = the least number of perfect square numbers
            // which sum to i. Note that cntPerfectSquares[0] is 0.
            vector<int> cntPerfectSquares(n + 1, INT_MAX);
            cntPerfectSquares[0] = 0;
            for (int i = 1; i <= n; i++)
            {
                // For each i, it must be the sum of some number (i - j*j) and
                // a perfect square number (j*j).
                for (int j = 1; j*j <= i; j++)
                {
                    cntPerfectSquares[i] =
                        min(cntPerfectSquares[i], cntPerfectSquares[i - j*j] + 1);
                }
            }
            
            return cntPerfectSquares.back();
        }
        int numSquares_dp1(int n) {
            if (n <= 0)
            {
                return 0;
            }
            
            // cntPerfectSquares[i] = the least number of perfect square numbers
            // which sum to i. Since cntPerfectSquares is a static vector, if
            // cntPerfectSquares.size() > n, we have already calculated the result
            // during previous function calls and we can just return the result now.
            static vector<int> cntPerfectSquares({0});
            
            // While cntPerfectSquares.size() <= n, we need to incrementally
            // calculate the next result until we get the result for n.
            while (cntPerfectSquares.size() <= n)
            {
                int m = cntPerfectSquares.size();
                int cntSquares = INT_MAX;
                for (int i = 1; i*i <= m; i++)
                {
                    cntSquares = min(cntSquares, cntPerfectSquares[m - i*i] + 1);
                }
                
                cntPerfectSquares.push_back(cntSquares);
            }
            
            return cntPerfectSquares[n];
        }
        int numSquares_dfs(int n) {
            int m = (int)sqrt(n);
            int res = recur(n, m, n);
            return res;
        }
    private:
        int recur(int n, int m, int s) {
            int q = m * m;
            if (q > n) {
                int ns = (int)sqrt(n);
                return recur(n, ns, s);
            } else {
                int c = n;
                for (int i = m; i > 1; --i) {
                    int q = i * i;
                    if (n >= q * s) {
                        break;
                    } else if (n == q) {
                        c = 1;
                        break;
                    } else if (n > q) {
                        int l = c;
                        if (l > s) {
                            l = s;
                        }
                        int t = recur(n - q, i, l - 1);
                        if (c > t + 1) {
                            c = t + 1;
                        }
                    }
                }
                
                return c;
            }
            
        }
    };
    
    int stringToInteger(string input) {
        return stoi(input);
    }
}
/*
int main() {
    string line;
    while (getline(cin, line)) {
        int n = numSquares::stringToInteger(line);
        
        clock_t tstart = clock();
        int ret = numSquares::Solution().numSquares(n);
        cout << clock() - tstart << endl;
        string out = to_string(ret);
        cout << out << endl;
    }
    return 0;
}
// */
