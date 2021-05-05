// findLUSlength.cpp
// leetcode
//
// Created by  Song Ding on 10/23/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findLUSlength {
/*
// TODO: copy problem statement here
 522. Longest Uncommon Subsequence II
 Medium

 124

 512

 Favorite

 Share
 Given a list of strings, you need to find the longest uncommon subsequence among them. The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this subsequence should not be any subsequence of the other strings.

 A subsequence is a sequence that can be derived from one sequence by deleting some characters without changing the order of the remaining elements. Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.

 The input will be a list of strings, and the output needs to be the length of the longest uncommon subsequence. If the longest uncommon subsequence doesn't exist, return -1.

 Example 1:
 Input: "aba", "cdc", "eae"
 Output: 3
 Note:

 All the given strings' lengths will not exceed 10.
 The length of the given list will be in the range of [2, 50].
 */

class Solution {
public:
    /**
     * sort all strings by length into ascending order
     * the LUS must be one of the string itself, not a subsequence.
     * starting from the longest string:
     *  if current word has no duplication, and is not a subsequence of longer strings, then it is LUS
     *  else move the next strng
     */
    int findLUSlength(vector<string>& strs) {
        int n = strs.size();
        sort(strs.begin(), strs.end(), [](const string&a, const string& b){
            return a.size() != b.size() ? a.size() < b.size() : a < b;
        });
        unordered_set<string> longer;
        for (int i = strs.size()-1; i >= 0; --i) {
            string& cur = strs[i];
            if ((i < n-1 && cur == strs[i+1])
                || (i > 0 && cur == strs[i-1])) {
                longer.insert(cur);
                continue;
            }
            // check if it is a subsequence of longer strings
            auto it = longer.begin();
            while (it != longer.end()) {
                if (isSubseq(cur, *it)) {
                    break;
                }
                ++it;
            }
            if (it == longer.end()) {
                return cur.size();
            } else {
                longer.insert(cur);
            }
        }
        return -1;
    }

private:
    bool isSubseq(const string& a, const string& b) {
        int na = a.size(), nb = b.size();
        int i = 0, j = 0;
        while (j < nb) {
            if (a[i] == b[j]) {
                ++i;
            }
            ++j;
        }
        return i == na;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<string> strs;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{"aba", "cdc", "eae"}},
    };

    vector< int > answers {
        3,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findLUSlength::Solution().findLUSlength(dp.strs);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
