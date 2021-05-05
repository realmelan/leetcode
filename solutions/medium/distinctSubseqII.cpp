// distinctSubseqII.cpp
// leetcode
//
// Created by  Song Ding on 9/8/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace distinctSubseqII {
/*
// TODO: copy problem statement here
 940. Distinct Subsequences II
 Hard
 
 222
 
 10
 
 Favorite
 
 Share
 Given a string S, count the number of distinct, non-empty subsequences of S .
 
 Since the result may be large, return the answer modulo 10^9 + 7.
 
 
 
 Example 1:
 
 Input: "abc"
 Output: 7
 Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac", "bc", and "abc".
 Example 2:
 
 Input: "aba"
 Output: 6
 Explanation: The 6 distinct subsequences are "a", "b", "ab", "ba", "aa" and "aba".
 Example 3:
 
 Input: "aaa"
 Output: 3
 Explanation: The 3 distinct subsequences are "a", "aa" and "aaa".
 
 
 
 
 Note:
 
 S contains only lowercase letters.
 1 <= S.length <= 2000
 */

class Solution {
public:
    /**
     * let chcnt[c] = # of unique subseq as of current position.
     * For current character c, seq ending at c = sum of previous seq + 1
     * but all subseq = sum of previous seq * 2 + 1 - sum of previous subseq ending at c.
     */
    int distinctSubseqII(string S) {
        int n = S.size();
        vector<long> chcnt(26, 0);
        chcnt[S[0]-'a'] = 1;
        long res = 1;
        for (int i = 1; i < n; ++i) {
            long t = res;
            res <<= 1;
            res = (res + 1000000007 - chcnt[S[i]-'a'] + 1) % 1000000007;
            if (res < 0) {
                cout << "negative" << endl;
            }
            chcnt[S[i]-'a'] = t+1;
        }
        return res % 1000000007;
    }
    /**
     * let sqcnt[i][ch] = # of distinct subsqence for substring S[0,i] ending
     * with character ch.
     *
     * for sqcnt[i][ch] = sqcnt[i-1][ch] if ch != S[i];
     *  else sqcnt[i][ch] = SUM(sqcnt[i-1][a...z]) + 1.
     */
    int distinctSubseqII_endchar(string S) {
        int n = S.size();
        vector<vector<int>> res (n, vector<int>(26,0));
        res[0][S[0]-'a'] = 1;
        for (int i = 1; i < n; ++i) {
            long sum = 0;
            for (int j = 0; j < 26; ++j) {
                res[i][j] = res[i-1][j];
                sum += res[i-1][j];
            }
            res[i][S[i]-'a'] = (sum + 1) % 1000000007;
            
        }
        long total = 0;
        for (auto r : res[n-1]) {
            total += r;
        }
        return total % 1000000007;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string S;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
 
        {"abc"},
        {"aba"},
        {"aaa"},
        {"pcrdhwdxmqdznbenhwjsenjhvulyve"},
        {"zchmliaqdgvwncfatcfivphddpzjkgyygueikthqzyeeiebczqbqhdytkoawkehkbizdmcnilcjjlpoeoqqoqpswtqdpvszfaksn"}
    };

    vector< int > answers {
        7,
        6,
        3,
        836817663,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = distinctSubseqII::Solution().distinctSubseqII(dp.S);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
