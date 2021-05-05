//
//  wordAbbreviation.cpp
//  leetcode
//
//  Created by Song Ding on 4/8/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace wordAbbreviation {
/*
// TODO: copy problem statement here
 [LeetCode] 527. Word Abbreviation
  

 Given an array of n distinct non-empty strings, you need to generate minimal possible abbreviations for every word following rules below.

 Begin with the first character and then the number of characters abbreviated, which followed by the last character.
 If there are any conflict, that is more than one words share the same abbreviation, a longer prefix is used instead of only the first character until making the map from word to abbreviation become unique. In other words, a final abbreviation cannot map to more than one original words.
 If the abbreviation doesn't make the word shorter, then keep it as original.
 Example:

 Input: ["like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion"]
 Output: ["l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"]
  

 Note:

 Both n and the length of each word will not exceed 400.
 The length of each word is greater than 1.
 The words consist of lowercase English letters only.
 The return answers should be in the same order as the original array.
*/
class Solution {
public:
    // TODO: copy function signature here
    vector<string> wordsAbbreviation(vector<string>& dict) {
        unordered_map<string,string> w2a;
        dfs(dict, 1, w2a);
        vector<string> res;
        for (auto& w : dict) {
            res.push_back(w2a[w]);
        }
        return res;
    }
    void dfs(vector<string>& wl, int prelen, unordered_map<string,string>& res) {
        int n = wl.size();
        unordered_map<string, vector<string>> groups;
        for (int i = 0; i < n; ++i) {
            if (wl[i].size()-prelen <= 2) {
                res[wl[i]] = wl[i];
            } else {
                groups[abbr(wl[i], prelen)].push_back(wl[i]);
            }
        }
        for (auto& p : groups) {
            if (p.second.size() == 1) {
                res[p.second[0]] = p.first;
            } else {
                dfs(p.second, prelen+1, res);
            }
        }
    }
    string abbr(const string& w, int prelen) {
        return w.substr(0, prelen) + to_string(w.size()-1-prelen) + w.substr(w.size()-1);
    }
    vector<string> wordsAbbreviation_trie_wrong(vector<string>& dict) {
        Trie root;
        for (auto& w : dict) {
            add(w, &root);
        }
        vector<string> res;
        for (auto& w : dict) {
            int p = prefix(w, &root);
            if (w.size()-p<=2) {
                res.push_back(w);
            } else {
                string t(w.substr(0,p));
                t.append(to_string(w.size()-1-p)).append(1, w.back());
                res.push_back(t);
            }
        }
        return res;
    }


private:
    struct Trie {
        int cnt;
        vector<Trie*> child;
        Trie() : cnt(0), child(26, nullptr) {}
    };
    void add(const string& w, Trie* root) {
        Trie* node = root;
        int i = 0;
        while (i < w.size()) {
            ++node->cnt;
            if (!node->child[w[i]-'a']) {
                node->child[w[i]-'a'] = new Trie;
            }
            node = node->child[w[i]-'a'];
            ++i;
        }
    }
    int prefix(const string& w, Trie* root) {
        Trie* node = root;
        int i = 0;
        while (i < w.size() && node->cnt > 1) {
            node = node->child[w[i]-'a'];
            ++i;
        }
        return i;
    }
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<string> dict;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{"like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion"}},
    };
    // TODO: provide expected results here
    vector<vector<string>> answers {
        {"l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"},
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = wordAbbreviation::Solution().wordsAbbreviation(dp.dict);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
