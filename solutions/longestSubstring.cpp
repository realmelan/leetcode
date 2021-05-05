// longestSubstring.cpp
// leetcode
//
// Created by  Song Ding on 10/29/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace longestSubstring {
/*
// TODO: copy problem statement here
 395. Longest Substring with At Least K Repeating Characters
 Medium

 917

 83

 Favorite

 Share
 Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

 Example 1:

 Input:
 s = "aaabb", k = 3

 Output:
 3

 The longest substring is "aaa", as 'a' is repeated 3 times.
 Example 2:

 Input:
 s = "ababbc", k = 2

 Output:
 5

 The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 */

class Solution {
public:
    /**
     * recursion:
     * find all characters whose number < k, and these characters divide s into substring set.
     * if there is no such character, then s is the longest substring;
     * otherwise, recursively find target substrings in the substring set.
     */
    int longestSubstring(string s, int k) {
        return 0;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string s;
        int k;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {}
    };

    vector< int > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = longestSubstring::Solution().longestSubstring(dp.s, dp.k);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
