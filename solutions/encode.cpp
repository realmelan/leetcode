// encode.cpp
// leetcode
//
// Created by  Song Ding on 11/6/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace encode {
/*
// TODO: copy problem statement here
 471. Encode String with Shortest Length

 Given a non-empty string, encode the string such that its encoded length is the shortest.

 The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.

 Note:

 k will be a positive integer and encoded string will not be empty or have extra space.
 You may assume that the input string contains only lowercase English letters. The string\'s length is at most 160.
 If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them is fine.
 Example 1:

 Input: "aaa"
 Output: "aaa"
 Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.
 Example 2:

 Input: "aaaaa"
 Output: "5[a]"
 Explanation: "5[a]" is shorter than "aaaaa" by 1 character.
 Example 3:

 Input: "aaaaaaaaaa"
 Output: "10[a]"
 Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".
 Example 4:

 Input: "aabcaabcd"
 Output: "2[aabc]d"
 Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".
 Example 5:

 Input: "abbbabbbcabbbabbbc"
 Output: "2[2[abbb]c]"
 Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".
 */

class Solution {
public:
    /**
     * let dp[i][j] = shortest encoded string for s[i..j]
     * then dp[i][j] = min(dp[i][k]+dp[k+1][j] for all k, s[i..j])
     * however the above doesn't think about the k[...] case, that is s[i..j]
     * might be able to encoded into k[pattern].
     *
     * How to can we find this pattern?
     * idx = (t+t).find(t, 1)
     * if idx == t.size(): then there is no such pattern which after k repeation would compose s
     * else then the patten is of length idx, and there are t.size()/idx such patterns.
     * This can be verified that after the first 2 patterns, the following has to be k-2 patterns.
     */
    string encode(string s) {
        int n = s.size();
        vector<vector<string>> dp(n, vector<string>(n));
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i <= n-len; ++i) {
                int j = i + len - 1;
                dp[i][j] = s.substr(i, len);
                for (int k = i; k < j; ++k) {
                    if (dp[i][j].size() > dp[i][k].size() + dp[k+1][j].size()) {
                        dp[i][j] = dp[i][k] + dp[k+1][j];
                    }
                }
                // find the k[pattern] for s[i..j]
                const string& t = s.substr(i, len);
                size_t idx = (t+t).find(t, 1);
                if (idx < t.size()) {
                    ostringstream oss;
                    oss << t.size()/idx << "[" << dp[i][i+idx-1] << "]";
                    if (dp[i][j].size() > oss.str().size()) {
                        dp[i][j] = oss.str();
                    }
                }
            }
        }
        return dp[0][n-1];
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string s;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"aaa"},
        {"aaaa"},
        {"aaaaa"},
        {"aaaaaaaaaa"},
        {"aabcaabcd"},
        {"abbbabbbcabbbabbbc"},
    };

    vector< string > answers {
        "aaa",
        "aaaa",
        "5[a]",
        "10[a]",
        "2[aabc]d",
        "2[2[abbb]c]",
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = encode::Solution().encode(dp.s);
        cout << clock() - tstart << endl;
        cout << res.size() << ":" << res << endl;
    }
    
    for(auto& s : answers) {
        cout << s.size() << ":" << s << endl;
    }
    return 0;
}
//*/
