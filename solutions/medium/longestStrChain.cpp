// longestStrChain.cpp
// leetcode
//
// Created by  Song Ding on 6/9/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace longestStrChain {
/*
// TODO: copy problem statement here
 1048. Longest String Chain
 Medium
 
 77
 
 7
 
 Favorite
 
 Share
 Given a list of words, each word consists of English lowercase letters.
 
 Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter anywhere in word1 to make it equal to word2.  For example, "abc" is a predecessor of "abac".
 
 A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1, where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.
 
 Return the longest possible length of a word chain with words chosen from the given list of words.
 
 
 
 Example 1:
 
 Input: ["a","b","ba","bca","bda","bdca"]
 Output: 4
 Explanation: one of the longest word chain is "a","ba","bda","bdca".
 
 
 Note:
 
 1 <= words.length <= 1000
 1 <= words[i].length <= 16
 words[i] only consists of English lowercase letters.
 */

class Solution {
public:
    /**
     * DP:
     *  let ls[i] = largest length of str chain ending at words[i].
     *  then ls[i] = max(length of str chain for each predecessor(words[i]) + 1).
     *
     *  a hash map can be kept to save all longest str chain ending at words[0..i]
     */
    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(),[](const string& a, const string&b){
            return a.size() < b.size();
        });
        int res = 1;
        int n = words.size();
        // string to length
        unordered_map<string, int> memo;
        memo[words[0]] = 1;
        for (int i = 1; i < n; ++i) {
            int nw = words[i].size();
            int wlc = 1;
            string pre;
            for (int j = 0; j < nw; ++j) {
                // remove j
                string p(pre);
                p.append(words[i].substr(j+1));
                
                auto it = memo.find(p);
                if (it != memo.end()) {
                    wlc = max(wlc, it->second + 1);
                }
                
                pre.push_back(words[i][j]);
            }
            memo[words[i]] = wlc;
            res = max(res, wlc);
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
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{{"a","b","ba","bca","bda","bdca"}},
        {{"ksqvsyq","ks","kss","czvh","zczpzvdhx","zczpzvh","zczpzvhx","zcpzvh","zczvh","gr","grukmj","ksqvsq","gruj","kssq","ksqsq","grukkmj","grukj","zczpzfvdhx","gru"}}
    };

    vector< int > answers {
        4,
        7
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = longestStrChain::Solution().longestStrChain(dp.words);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
