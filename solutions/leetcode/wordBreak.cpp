// wordBreak.cpp
// leetcode
//
// Created by  Song Ding on 12/12/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace wordBreak {

class Solution {
public:
    /**
     * DP:
     *  let S(i) = all possible strings for s[0..i].
     *  for S(i+1), test all possible suffices(s(k..i+1) that is in the dict, then
     *  S(i+1) = S(k-1) + s(k..i+1).
     *
     * To fasten processing, we can build a suffix table for all words in dict.
     */
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string, int> suffixCnt;
        unordered_set<string> dict;
        int maxLen = 0;
        for (const auto& w : wordDict) {
            dict.insert(w);
            string suffix;
            for (int i = w.size() - 1; i >= 0; --i) {
                suffix.insert(suffix.begin(), w[i]);
                ++suffixCnt[suffix];
            }
            if (maxLen < w.size()) {
                maxLen = w.size();
            }
        }
        
        int n = s.size();
        vector<set<int>> divideIndex;
        for (int k = 1; k <= n; ++k) {
            set<int> kindex;
            string suffix;
            for (int i = k - 1; i >= 0 && i + maxLen >= k; --i) {
                suffix.insert(suffix.begin(), s[i]);
                if (suffixCnt[suffix] == 0) {
                    break;
                }
                
                if (dict.count(suffix) && (i == 0 || divideIndex[i-1].size())) {
                    kindex.insert(i);
                }
            }
            divideIndex.push_back(kindex);
        }
        // now dump strings based on divideIndex
        
        vector<string> res;
        generate(s, divideIndex, n-1, "", res);
        return res;
    }
    
    
    /**
     * DP:
     *  let S(i) = all possible strings for s[0..i].
     *  for S(i+1), test all possible suffices(s(k..i+1) that is in the dict, then
     *  S(i+1) = S(k-1) + s(k..i+1).
     *
     * To fasten processing, we can build a suffix table for all words in dict.
     */
    vector<string> wordBreakNotworking(string s, vector<string>& wordDict) {
        unordered_map<string, int> suffixCnt;
        unordered_set<string> dict;
        unordered_set<char> charmap;
        for (const auto& w : wordDict) {
            dict.insert(w);
            string suffix;
            for (int i = w.size() - 1; i >= 0; --i) {
                suffix.insert(suffix.begin(), w[i]);
                ++suffixCnt[suffix];
                charmap.insert(w[i]);
            }
        }
        for (char c : s) {
            if (!charmap.count(c)) {
                return {};
            }
        }
        
        int n = s.size();
        vector<vector<string>> res; // length is index
        res.push_back({""});
        for (int k = 1; k <= n; ++k) {
            vector<string> kres;
            string suffix;
            for (int i = k - 1; i >= 0; --i) {
                suffix.insert(suffix.begin(), s[i]);
                if (suffixCnt[suffix] == 0) {
                    break;
                }
                
                if (dict.count(suffix) && res[i].size()) {
                    for (const auto& r : res[i]) {
                        if (r.size()) {
                            kres.push_back(r + " " + suffix);
                        } else {
                            kres.push_back(suffix);
                        }
                    }
                }
            }
            res.push_back(kres);
        }
        
        return res[n];
    }

private:
    void generate(string s, vector<set<int>>& divideIndex, int i, string tres, vector<string>& res) {
        if (divideIndex[i].empty()) {
            return;
        }
        
        const auto& index = divideIndex[i];
        for (auto j : index) {
            string t(s.substr(j, i - j + 1));
            t.append(" ").append(tres);
            if (j == 0) {
                t.resize(t.size() - 1);
                res.push_back(t);
            } else {
                generate(s, divideIndex, j - 1, t, res);
            }
        }
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< string > s {
        "catsanddog",
        "pineapplepenapple",
        "catsandog",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        
         "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    };
    vector< vector<string> > wordDict {
        {"cat", "cats", "and", "sand", "dog"},
        {"apple", "pen", "applepen", "pine", "pineapple"},
        {"cats", "dog", "sand", "and", "cat"},
        {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"},
        {"aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa","ba"},
        {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"}
    };

    vector< vector<string>  > answers {
        {"cats and dog", "cat sand dog"},
        {"pine apple pen apple", "pineapple pen apple", "pine applepen apple"},
        {},
        {}
    };
    int i = 4;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = wordBreak::Solution().wordBreak2(s[i], wordDict[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
