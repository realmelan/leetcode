// findAndReplacePattern.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findAndReplacePattern {
/*
// TODO: copy problem statement here
 890. Find and Replace Pattern
 Medium
 
 352
 
 33
 
 Favorite
 
 Share
 You have a list of words and a pattern, and you want to know which words in words matches the pattern.
 
 A word matches the pattern if there exists a permutation of letters p so that after replacing every letter x in the pattern with p(x), we get the desired word.
 
 (Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter.)
 
 Return a list of the words in words that match the given pattern.
 
 You may return the answer in any order.
 
 
 
 Example 1:
 
 Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
 Output: ["mee","aqq"]
 Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}.
 "ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation,
 since a and b map to the same letter.
 
 
 Note:
 
 1 <= words.length <= 50
 1 <= pattern.length = words[i].length <= 20
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> res;
        int n = pattern.size();
        for (auto w : words) {
            bool bad = false;
            vector<char> p1(26, '#');
            vector<char> p2(26, '#');
            for (int i = 0; i < n; ++i) {
                char wc = w[i];
                char pc = pattern[i];
                if ((p1[wc-'a'] != '#' && p1[wc-'a'] != pc)
                    || (p2[pc-'a'] != '#' && p2[pc-'a'] != wc)) {
                    bad = true;
                    break;
                }
                p1[wc-'a'] = pc;
                p2[pc-'a'] = wc;
            }
            if (!bad) {
                res.push_back(w);
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
        vector<string> words;
        string pattern;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{"abc","deq","mee","aqq","dkd","ccc"},"abb"}
    };

    vector< vector<string> > answers {
        {"mee","aqq"}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findAndReplacePattern::Solution().findAndReplacePattern(dp.words, dp.pattern);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
