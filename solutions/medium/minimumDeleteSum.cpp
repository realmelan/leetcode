// minimumDeleteSum.cpp
// leetcode
//
// Created by  Song Ding on 6/20/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minimumDeleteSum {
/**
 712. Minimum ASCII Delete Sum for Two Strings
 Medium
 
 560
 
 37
 
 Favorite
 
 Share
 Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.
 
 Example 1:
 Input: s1 = "sea", s2 = "eat"
 Output: 231
 Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
 Deleting "t" from "eat" adds 116 to the sum.
 At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
 Example 2:
 Input: s1 = "delete", s2 = "leet"
 Output: 403
 Explanation: Deleting "dee" from "delete" to turn the string into "let",
 adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
 At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
 If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
 Note:
 
 0 < s1.length, s2.length <= 1000.
 All elements of each string will have an ASCII value in [97, 122].
 */

class Solution {
public:
    /**
     * a variation of longest common sequence.
     * Here, the maximum value common sequence is wanted.
     *
     * Let mc(i,j) = maximum value of common sequence of s1[0:i]
     * and s2[0:j], then
     * mc(i,j) = s1[i] + mc(i-1,j-1) if s1[i] == s2[j]
     * or mc(i-1,j) or mc(i,j-1).
     *
     */
    int minimumDeleteSum(string s1, string s2) {
        int n1 = s1.size();
        int n2 = s2.size();
        int sum = 0;
        for (auto c : s1) {
            sum += c;
        }
        for (auto c : s2) {
            sum += c;
        }
        
        if (n1 == 0 || n2 == 0) {
            return sum;
        }
        
        vector<int> res(n2, 0);
        int t = 0;
        for (int j = 0; j < n2; ++j) {
            if (s1[0] == s2[j]) {
                t = s1[0];
            }
            res[j] = t;
        }
        for (int i = 1; i < n1; ++i) {
            vector<int> next(n2, 0);
            next[0] = res[0];
            if (s2[0] == s1[i] && next[0] < s2[0]) {
                next[0] = s2[0];
            }
            for (int j = 1; j < n2; ++j) {
                next[j] = next[j - 1];
                if (s1[i] == s2[j] && next[j] < res[j - 1] + s1[i]) {
                    next[j] = res[j - 1] + s1[i];
                }
                if (next[j] < res[j]) {
                    next[j] = res[j];
                }
            }
            res.swap(next);
        }
        
        return sum - 2 * res[n2 - 1];
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string s1;
        string s2;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{"sea", "eat"},
        //{"delete", "leet"},
        {"a", "at"}
    };
    
    vector< int > answers {
        231,
        403,
        116
    };
    
    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minimumDeleteSum::Solution().minimumDeleteSum(dp.s1, dp.s2);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
