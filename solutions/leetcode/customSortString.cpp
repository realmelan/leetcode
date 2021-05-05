// customSortString.cpp
// leetcode
//
// Created by  Song Ding on 5/31/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace customSortString {
/*
// TODO: copy problem statement here
 791. Custom Sort String
 Medium
 
 373
 
 126
 
 Favorite
 
 Share
 S and T are strings composed of lowercase letters. In S, no letter occurs more than once.
 
 S was sorted in some custom order previously. We want to permute the characters of T so that they match the order that S was sorted. More specifically, if x occurs before y in S, then x should occur before y in the returned string.
 
 Return any permutation of T (as a string) that satisfies this property.
 
 Example :
 Input:
 S = "cba"
 T = "abcd"
 Output: "cbad"
 Explanation:
 "a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a".
 Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.
 
 
 Note:
 
 S has length at most 26, and no character is repeated in S.
 T has length at most 200.
 S and T consist of lowercase letters only.
 */

class Solution {
public:
    /**
     *
     */
    string customSortString(string S, string T) {
        vector<int> count(26, 0);
        for (auto c : T) {
            ++count[c-'a'];
        }
        
        string res;
        for (auto c : S) {
            for (int i = 0; i < count[c-'a']; ++i) {
                res.push_back(c);
            }
            count[c-'a'] = 0;
        }
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < count[i]; ++j) {
                res.push_back('a' + i);
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string S;
        string T;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"cba", "abcd"}
    };

    vector< string > answers {
        "cbad"
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = customSortString::Solution().customSortString(dp.S, dp.T);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
