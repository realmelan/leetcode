// camelMatch.cpp
// leetcode
//
// Created by  Song Ding on 5/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace camelMatch {
/*
// TODO: copy problem statement here
 1023. Camelcase Matching
 Medium
 
 53
 
 50
 
 Favorite
 
 Share
 A query word matches a given pattern if we can insert lowercase letters to the pattern word so that it equals the query. (We may insert each character at any position, and may insert 0 characters.)
 
 Given a list of queries, and a pattern, return an answer list of booleans, where answer[i] is true if and only if queries[i] matches the pattern.
 
 
 
 Example 1:
 
 Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
 Output: [true,false,true,true,false]
 Explanation:
 "FooBar" can be generated like this "F" + "oo" + "B" + "ar".
 "FootBall" can be generated like this "F" + "oot" + "B" + "all".
 "FrameBuffer" can be generated like this "F" + "rame" + "B" + "uffer".
 Example 2:
 
 Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBa"
 Output: [true,false,true,false,false]
 Explanation:
 "FooBar" can be generated like this "Fo" + "o" + "Ba" + "r".
 "FootBall" can be generated like this "Fo" + "ot" + "Ba" + "ll".
 Example 3:
 
 Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBaT"
 Output: [false,true,false,false,false]
 Explanation:
 "FooBarTest" can be generated like this "Fo" + "o" + "Ba" + "r" + "T" + "est".
 
 
 Note:
 
 1 <= queries.length <= 100
 1 <= queries[i].length <= 100
 1 <= pattern.length <= 100
 All strings consists only of lower and upper case English letters.
 */

class Solution {
public:
    /**
     * prepare pattern to a list of lowercase strings and a list of capital case letter
     * that separate the lowercase strings. Note, some lowercase strings may be empty.
     */
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        vector<bool> res;
        vector<string> lcs;
        string uc;
        
        string t;
        for (auto c : pattern) {
            if (c >= 'A' && c <= 'Z') {
                lcs.push_back(t);
                t.clear();
                uc.push_back(c);
            } else {
                t.push_back(c);
            }
        }
        lcs.push_back(t);
        int ucn = uc.size();
        
        for (auto q : queries) {
            int n = q.size();
            int j = 0;
            int k = 0;
            bool bad = false;
            for (int i = 0; i < n; ++i) {
                if (q[i] >= 'A' && q[i] <= 'Z') {
                    if (j >= ucn || q[i] != uc[j]) {
                        bad = true;
                        break;
                    } else {
                        if (k < lcs[j].size()) {
                            bad = true;
                            break;
                        }
                    }
                    ++j;
                    k = 0; // reset k for a new lowercase part.
                } else {
                    // deal with lower case
                    if (k < lcs[j].size() && q[i] == lcs[j][k]) {
                        ++k;
                    }
                }
            }
            
            res.push_back((!bad && j == ucn && k == lcs[j].size()));
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
        vector<string> queries;
        string pattern;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"},"FB"},
        {{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"},"FoBa"},
        {{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"},"FoBaT"}
    };

    vector< vector<bool> > answers {
        {true,false,true,true,false},
        {true,false,true,false,false},
        {false,true,false,false,false}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = camelMatch::Solution().camelMatch(dp.queries, dp.pattern);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
