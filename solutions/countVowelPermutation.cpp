// countVowelPermutation.cpp
// leetcode
//
// Created by  Song Ding on 10/10/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace countVowelPermutation {
/*
// TODO: copy problem statement here
 1220. Count Vowels Permutation
 Hard

 54

 17

 Favorite

 Share
 Given an integer n, your task is to count how many strings of length n can be formed under the following rules:

 Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
 Each vowel 'a' may only be followed by an 'e'.
 Each vowel 'e' may only be followed by an 'a' or an 'i'.
 Each vowel 'i' may not be followed by another 'i'.
 Each vowel 'o' may only be followed by an 'i' or a 'u'.
 Each vowel 'u' may only be followed by an 'a'.
 Since the answer may be too large, return it modulo 10^9 + 7.

  

 Example 1:

 Input: n = 1
 Output: 5
 Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
 Example 2:

 Input: n = 2
 Output: 10
 Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".
 Example 3:

 Input: n = 5
 Output: 68
  

 Constraints:

 1 <= n <= 2 * 10^4
 */

class Solution {
public:
    /**
     * let dp[i][c] = # of permutations of strings of length i, ending at character c.
     * then dp[i+1][ch1] = SUM(dp[i][ch]) for each ch that are suitable to appending ch1.
     */
    int countVowelPermutation(int n) {
        vector<long> dp(26, 0);
        static vector<char> vowels {'a', 'e', 'i', 'o', 'u'};
        for (auto ch : vowels) {
            dp[ch-'a'] = 1;
        }
        for (int i = 2; i <= n; ++i) {
            vector<long> next(26, 0);
            next['e'-'a'] += dp['a'-'a'];
            next['a'-'a'] += dp['e'-'a'];
            next['i'-'a'] += dp['e'-'a'];
            next['a'-'a'] += dp['i'-'a'];
            next['e'-'a'] += dp['i'-'a'];
            next['o'-'a'] += dp['i'-'a'];
            next['u'-'a'] += dp['i'-'a'];
            next['i'-'a'] += dp['o'-'a'];
            next['u'-'a'] += dp['o'-'a'];
            next['a'-'a'] += dp['u'-'a'];
            
            for (char ch : vowels) {
                next[ch-'a'] %= 1000000007;
            }
            
            dp.swap(next);
        }
        long res = 0;
        for (auto cnt : dp) {
            res += cnt;
            res %= 1000000007;
        }
        return res;
    }

private:
};

}

//*/
int main() {
    // TODO: define parameter type here
    struct d {
        int n;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {1},
        {2},
        {5},
    };

    vector< int > answers {
        5,
        10,
        68
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = countVowelPermutation::Solution().countVowelPermutation(dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
