//
//  minimumJumps.cpp
//  leetcode
//
//  Created by Song Ding on 2/23/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
#include <numeric>
using namespace std;

namespace minimumJumps {
/*
// TODO: copy problem statement here
 1654. Minimum Jumps to Reach Home
 Medium

 200

 58

 Add to List

 Share
 A certain bug's home is on the x-axis at position x. Help them get there from position 0.

 The bug jumps according to the following rules:

 It can jump exactly a positions forward (to the right).
 It can jump exactly b positions backward (to the left).
 It cannot jump backward twice in a row.
 It cannot jump to any forbidden positions.
 The bug may jump forward beyond its home, but it cannot jump to positions numbered with negative integers.

 Given an array of integers forbidden, where forbidden[i] means that the bug cannot jump to the position forbidden[i], and integers a, b, and x, return the minimum number of jumps needed for the bug to reach its home. If there is no possible sequence of jumps that lands the bug on position x, return -1.

  

 Example 1:

 Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
 Output: 3
 Explanation: 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.
 Example 2:

 Input: forbidden = [8,3,16,6,12,20], a = 15, b = 13, x = 11
 Output: -1
 Example 3:

 Input: forbidden = [1,6,2,14,5,17,4], a = 16, b = 9, x = 7
 Output: 2
 Explanation: One jump forward (0 -> 16) then one jump backward (16 -> 7) will get the bug home.
  

 Constraints:

 1 <= forbidden.length <= 1000
 1 <= a, b, forbidden[i] <= 2000
 0 <= x <= 2000
 All the elements in forbidden are distinct.
 Position x is not forbidden.
*/
class Solution {
public:
    // TODO: copy function signature here
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        return minimumJumps_dfs(forbidden, a, b, x);
    }
    int minimumJumps_bfs(vector<int>& forbidden, int a, int b, int x) {
        if (x == 0) {
            return 0;
        }
        int g = gcd(a, b);
        if (x%g) {
            return -1;
        }
        int mx = max(x,* max_element(begin(forbidden),end(forbidden))) + a + b;
        unordered_set<int> forwardVisited(begin(forbidden), end(forbidden));
        unordered_set<int> backwardVisited(begin(forbidden), end(forbidden));
        // pair.first => position
        // pair.second => direction resulting in position(0=>backward, 1=>forward)
        queue<pair<int,int>> q;
        q.push({0,0});
        int res = 0;
        while (q.size()) {
            ++res;
            int qn = q.size();
            while (qn--) {
                auto [p, d] = q.front();
                q.pop();
                if (p+a == x || (d && (p-b == x))) {
                    return res;
                }
                if (p+a <= mx && !forwardVisited.count(p+a)) {
                    q.push({p+a,1});
                    forwardVisited.insert(p+a);
                }
                if (d && p-b > 0 && !backwardVisited.count(p-b)) {
                    q.push({p-b,0});
                    backwardVisited.insert(p-b);
                }
            }
        }
        return -1;
    }
    int minimumJumps_dfs(vector<int>& forbidden, int a, int b, int x) {
        if (x == 0) {
            return 0;
        }
        int g = gcd(a, b);
        if (x%g) {
            return -1;
        }
        int mx = x;
        vector<bool> f(2001,false);
        for (auto i : forbidden) {
            f[i] = true;
            mx = max(mx, i);
        }
        mx += a + b;
        unordered_map<int,int> memo;
        int res = dfs(0, false, mx, a, b, x, f, memo);
        return res == INT_MAX ? -1 : res;
    }
    int dfs(int p, bool forward, int mx, int a, int b, int x, vector<bool>& f, unordered_map<int,int>& memo) {
        if (p == x) {
            return 0;
        } else if (memo.count(p)) {
            return memo[p];
        }
        int res = INT_MAX, t = INT_MAX;
        if (p+a<=mx && (p+a>2000 || !f[p+a]) && (t=dfs(p+a, true, mx, a, b, x, f, memo)) != INT_MAX) {
            res = 1+t;
        }
        if (forward && p-b>0 && (p-b>2000 || !f[p-b]) && (t=dfs(p-b, false, mx, a, b, x, f, memo)) != INT_MAX) {
            res = min(res, 1+t);
        }
        return memo[p] = res;
    }
    int minimumJumps_TLE(vector<int>& forbidden, int a, int b, int x) {
           int g = gcd(a,b);
           if (x%g) {
               return -1;
           }
           vector<bool> f(2001,false);
           for (auto i : forbidden) {
               f[i] = true;
           }
           int t = x;
           while (t%a) {
               t += b;
           }
           int m = t/a, n = (t-x)/b;
        int ad = b/g, bd = a/g;
           // now use dfs to check whether m+n is possible.
           // 0 => unset
           // 1 => valid
           // -1 => invalid
        // they may be blocked for the same reason.
        while (m>=n) {
            vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
            dp[0][0] = 1;
            if (dfs(0, m, n, a, b, f, dp) == 1) {
                return m+n;
            }
            m += ad;
            n += bd;
        }
           
           return -1;
       }
    int gcd(int a, int b) {
        if (a<b) {
            swap(a,b);
        }
        while (b) {
            int t = a%b;
            a = b;
            b = t;
        }
        return a;
    }
       int dfs(int p, int m, int n, int a, int b, const vector<bool>& f, vector<vector<int>>& dp) {
           if (n == 0) {
               while (m) {
                   p += a;
                   if (p<=2000 && f[p]) {
                       return -1;
                   }
                   --m;
               }
               return 1;
           }
           if (dp[m][n]) {
               return dp[m][n];
           }
           int res = -1;
           for (int i = 1; i <= m-n+1 && i <= m; ++i) {
               p += a;
               if (p<=2000 && f[p]) {
                   break;
               }
               
               if (p-b<=0 || (p-b<=2000 && f[p-b])) {
                   continue;
               }
               if (dfs(p-b, m-i,n-1, a, b, f, dp) == 1) {
                   res = 1;
                   break;
               }
           }
           return dp[m][n] = res;
       }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> forbidden;
        int a;
        int b;
        int x;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{8,3,16,6,12,20},15,13,11},
        {{18,13,3,9,8,14},3,8,6},
        {{1401,832,1344,173,1529,1905,1732,277,1490,650,1577,1886,185,1728,1827,1924,1723,1034,1839,1722,1673,1198,1667,538,911,1221,1201,1313,251,752,40,1378,1515,1789,1580,1422,907,1536,294,1677,1807,1419,1893,654,1176,812,1094,1942,876,777,1850,1382,760,347,112,1510,1278,1607,1491,429,1902,1891,647,1560,1569,196,539,836,290,1348,479,90,1922,111,1411,1286,1362,36,293,1349,667,430,96,1038,793,1339,792,1512,822,269,1535,1052,233,1835,1603,577,936,1684,1402,1739,865,1664,295,977,1265,535,1803,713,1298,1537,135,1370,748,448,254,1798,66,1915,439,883,1606,796},19,18,1540},
    };
    // TODO: provide expected results here
    vector<int> answers {
        -1,
        -1,
        120
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minimumJumps::Solution().minimumJumps(dp.forbidden, dp.a, dp.b, dp.x);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
