// findSubstringInWraproundString.cpp
// leetcode
//
// Created by  Song Ding on 10/27/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findSubstringInWraproundString {
/*
// TODO: copy problem statement here
 467. Unique Substrings in Wraparound String
 Medium

 431

 70

 Favorite

 Share
 Consider the string s to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so s will look like this: "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".

 Now we have another string p. Your job is to find out how many unique non-empty substrings of p are present in s. In particular, your input is the string p and you need to output the number of different non-empty substrings of p in the string s.

 Note: p consists of only lowercase English letters and the size of p might be over 10000.

 Example 1:
 Input: "a"
 Output: 1

 Explanation: Only the substring "a" of string "a" is in the string s.
 Example 2:
 Input: "cac"
 Output: 2
 Explanation: There are two substrings "a", "c" of string "cac" in the string s.
 Example 3:
 Input: "zab"
 Output: 6
 Explanation: There are six substrings "z", "a", "b", "za", "ab", "zab" of string "zab" in the string s.
 */

class Solution {
public:
    /**
     * use a map to record maximum length of all substrings starting with each character.
     * find all consecutive substrings and update the map of the maximum length for each character.
     */
    int findSubstringInWraproundString(string p) {
        vector<int> ml(26, 0);
        p.push_back('$');
        int n = p.size();
        int start = p[0]-'a';
        int len = 1;
        for (int i = 1; i < n; ++i) {
            int cur = p[i] - 'a';
            if ((start + len)%26 == cur) {
                ++len;
            } else {
                ml[start] = max(ml[start], len--);
                for (int j=(start+1)%26; j != start && len > 0; j=(j+1)%26, --len) {
                    ml[j] = max(ml[j], len);
                }
                start = cur;
                len = 1;
            }
        }
        
        return accumulate(ml.begin(), ml.end(), 0);
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string p;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"a"},
        {"aca"},
        {"zab"},
    };

    vector< int > answers {
        1,
        2,
        6,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findSubstringInWraproundString::Solution().findSubstringInWraproundString(dp.p);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
