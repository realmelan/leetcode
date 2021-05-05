// numPermsDISequence.cpp
// leetcode
//
// Created by  Song Ding on 10/17/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

/**
 903. Valid Permutations for DI Sequence
 Hard
 
 198
 
 25
 
 Favorite
 
 Share
 We are given S, a length n string of characters from the set {'D', 'I'}. (These letters stand for "decreasing" and "increasing".)
 
 A valid permutation is a permutation P[0], P[1], ..., P[n] of integers {0, 1, ..., n}, such that for all i:
 
 If S[i] == 'D', then P[i] > P[i+1], and;
 If S[i] == 'I', then P[i] < P[i+1].
 How many valid permutations are there?  Since the answer may be large, return your answer modulo 10^9 + 7.
 
 
 
 Example 1:
 
 Input: "DID"
 Output: 5
 Explanation:
 The 5 valid permutations of (0, 1, 2, 3) are:
 (1, 0, 3, 2)
 (2, 0, 3, 1)
 (2, 1, 3, 0)
 (3, 0, 2, 1)
 (3, 1, 2, 0)
 
 
 Note:
 
 1 <= S.length <= 200
 S consists only of characters from the set {'D', 'I'}.
 */

namespace numPermsDISequence {

class Solution {
public:
    // https://leetcode.com/problems/valid-permutations-for-di-sequence/discuss/196939/Easy-to-understand-solution-with-detailed-explanation
    int numPermsDISequence(string S) {
            constexpr int M = 1e9+7;
            int n = S.size();
            /*if(S[i-1] == 'D')
       dp[i][j] = dp[i-1][j] + dp[i-1][j+1] + ... + dp[i-1][i-1]

    if(S[i-1] == 'I')
       dp[i][j] = dp[i-1][0] + dp[i-1][1] + ... + dp[i-1][j-1]
            */
            vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
            dp[0][0] = 1;
            for (int i = 1; i <= n; ++i) {
                if (S[i-1] == 'D') {
                    for (int j = i-1; j >= 0; --j) {
                        dp[i][j] = (dp[i][j+1] + dp[i-1][j])%M;
                    }
                } else {
                    for (int j = 1; j <= i; ++j) {
                        dp[i][j] = (dp[i][j-1] + dp[i-1][j-1])%M;
                    }
                }
            }
            int res = 0;
            for (auto i : dp[n]) {
                res = (res + i)%M;
            }
            return res;
        }
    /**
     * Let dp[i][j] denote the number of permutations of length i + 1,
     * and the i+1 th digit is the j+1 th smallest among digits other than
     * the first i digits of the permutation.
     *
     * Now to come up dp[i+1][j] with dp[i][j] if S[i] = I:
     *  for dp[i][k] where k < j, then for each sequence in dp[i][k],
     *  pick a digit in digits in permutation[i+1,n] that is the j+1'th smallest.
     *  then this is only possible when k < j. Otherwise if k >= j, and because
     *  S[i]=I, then next digit must be at least j-th smallest among the others.
     *
     *
     * https://leetcode.com/problems/valid-permutations-for-di-sequence/discuss/168278/C%2B%2BJavaPython-DP-Solution-O(N2)
     */
    int numPermsDISequence3(string S) {
        int mod = 1000000007;
        int n = S.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 1;
        }
        
        int cur = 0;
        for (int i = 0; i < n; ++i) {
            if (S[i] == 'I') {
                cur = 0;
                for (int j = 0; j < n - i; ++j) {
                    dp[i + 1][j] = cur = (cur + dp[i][j]) % mod;
                }
            } else {
                cur = 0;
                for (int j = n - i - 1; j >= 0; --j) {
                    dp[i + 1][j] = cur = (cur + dp[i][j + 1]) % mod;
                }
            }
        }
        
        return dp[n][0];
    }
    
    /**
     * Suppose we have results for i, now we want to calculate results for i+1 sequence.
     * That is, we need to add a value that is larger than any one in i sequence.
     * So, adding a(i+1) would introduce an I to the DI sequence except to the front, which
     * would prepend a D to the DI sequence.
     * So, for a i+1 DI sequence, look for all appearance of I and the front D.
     *
     */
    int numPermsDISequence2(string S) {
        unordered_map<string, long> memo;
        memo["II"] = 1;
        memo["DD"] = 1;
        memo["DI"] = 2;
        memo["ID"] = 2;
        return recur(S, memo) % 1000000007;
    }

private:
    long recur(string S, unordered_map<string, long>& memo) {
        int n = S.size();
        if (n <= 1) {
            return 1;
        }
        
        auto it = memo.find(S);
        if (it != memo.end()) {
            return it->second;
        }
        
        long res = 0;
        
        set<char> cnt;
        for (char c : S) {
            cnt.insert(c);
        }
        if (cnt.size() == 1) {
            res = 1;
            memo.insert(make_pair(S, res));
            return res;
        }
       
        if (S[0] == 'D') {
            res += recur(S.substr(1), memo);
        }
        for (int i = 0; i < n - 1; ++i) {
            if (S[i] == 'I' && S[i + 1] == 'D') {
                string s1 = S.substr(0, i) + "I";
                if (i+2 < n) {
                    s1 += S.substr(i+2);
                }
                res += recur(s1, memo);
                string s2 = S.substr(0, i) + "D";
                if (i+2 < n) {
                    s2 += S.substr(i+2);
                }
                res += recur(s2, memo);
            }
        }
        if (S[n - 1] == 'I') {
            res += recur(S.substr(0, n - 1), memo);
        }
        res %= 1000000007;
        memo.insert(make_pair(S, res));
        return res;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string S = "IIDIIDDIDDDDIIDDIDIDIDDDDIDDDIIIIDDIDDDDIDIIDDIDID";
    S = "DID";

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = numPermsDISequence::Solution().numPermsDISequence(S);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
