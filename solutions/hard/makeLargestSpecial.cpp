// makeLargestSpecial.cpp
// leetcode
//
// Created by  Song Ding on 9/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace makeLargestSpecial {
/*
// TODO: copy problem statement here
 761. Special Binary String
 Hard
 
 195
 
 75
 
 Favorite
 
 Share
 Special binary strings are binary strings with the following two properties:
 
 The number of 0's is equal to the number of 1's.
 Every prefix of the binary string has at least as many 1's as 0's.
 Given a special string S, a move consists of choosing two consecutive, non-empty, special substrings of S, and swapping them. (Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.)
 
 At the end of any number of moves, what is the lexicographically largest resulting string possible?
 
 Example 1:
 Input: S = "11011000"
 Output: "11100100"
 Explanation:
 The strings "10" [occuring at S[1]] and "1100" [at S[3]] are swapped.
 This is the lexicographically largest string possible after some number of swaps.
 Note:
 
 S has length at most 50.
 S is guaranteed to be a special binary string as defined above.
 */

class Solution {
public:
    /**
     * Suppose S = ABCD, A,B,C,D are all special string which
     * themselves are not divisible.
     * then
     *  1, it is not possible to swap suffix of B with prefix of C.
     *  2, it is possible to swap ABCD into any order.
     * so, it is wise to reorder ABCD into a decreasing order.
     *
     * Also, before reorder ABCD, they themselves should be made
     * largest possible, which means recursive call.
     *
     * If S is the smallest special string unit, then S = 1ABCD0,
     * or 1S0, any way do a recursive call on the inner S.
     *
     */
    string makeLargestSpecial(string S) {
        unordered_map<string, string> memo;
        return recur(S, memo);
    }

private:
    string recur(const string& s, unordered_map<string, string>& memo) {
        if (s.size() <= 2) {
            return s;
        }
        auto it = memo.find(s);
        if (it != memo.end()) {
            return it->second;
        }
        
        // find whether S is divisible.
        vector<string> subs;
        int n = s.size();
        int cnt = 0;
        int last = -1;
        int i = 0;
        while (i < n) {
            if (s[i] == '1') {
                ++cnt;
            } else {
                if (--cnt == 0 && (last != -1 || i != n - 1)) {
                    // find a special string component
                    subs.push_back(recur(s.substr(last+1, i-last), memo));
                    last = i;
                }
            }
            ++i;
        }
        
        string res;
        if (subs.size()) {
            sort(subs.begin(), subs.end(), [](const string&a, const string& b){
                return a > b;
            });
            for (auto& sub : subs) {
                res.append(sub);
            }
        } else {
            // single S
            res = "1" + recur(s.substr(1, n-2), memo) + "0";
        }
        memo[s] = res;
        return res;
    }
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
        {"101100"},
        {"11011000"},
        {"11011001110000"},
    };

    vector< string > answers {
        "110010",
        "11100100",
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = makeLargestSpecial::Solution().makeLargestSpecial(dp.S);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
