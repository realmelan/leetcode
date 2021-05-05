// findSubstring.cpp
// leetcode
//
// Created by  Song Ding on 4/10/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findSubstring {

class Solution {
public:
    /**
     Keep track of words for substring (i, j), using stride of wl(word length).
     
     To find all possible positions, have to loop from starting position of [0 to wl-1]
     
     */
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int n = s.size();
        int nw = words.size();
        if (n <= 0 || nw <= 0) return res;
        
        int wn = words[0].size();
        int tn = wn * nw;
        
        // first of all, use hash map to index words
        int index = 0;
        unordered_map<string, int> wordIdx;
        vector<int> wordTarget;
        for (const auto& w : words) {
            auto it =wordIdx.find(w);
            if (it == wordIdx.end()) {
                wordIdx[w] = index++;
                wordTarget.resize(index);
            }
            ++wordTarget[wordIdx[w]];
        }
        
        vector<int> swordIdx(n);
        for (int i = 0; i < n; ++i) {
            string t(s.substr(i, wn));
            auto it = wordIdx.find(t);
            if (it == wordIdx.end()) {
                swordIdx[i] = -1;
            } else {
                swordIdx[i] = it->second;
            }
        }
        
        for (int k = 0; k < wn; ++k) {
            int i = k;
            int j = k;
            
            int uncovered = wordIdx.size();
            vector<int> swordTarget(index, 0);
            while (i < n) {
                while (uncovered > 0 && i < n) {
                    int wi = swordIdx[i];
                    if (wi != -1) {
                        ++swordTarget[wi];
                        if (swordTarget[wi] == wordTarget[wi]) {
                            --uncovered;
                        }
                    }
                    i += wn;
                }
                
                while (uncovered == 0 && j < i) {
                    int wi = swordIdx[j];
                    if (wi != -1) {
                        if (swordTarget[wi] == wordTarget[wi]) {
                            ++uncovered;
                        }
                        if (i - j == tn) {
                            res.push_back(j);
                        }
                        
                        --swordTarget[wi];
                    }
                    j += wn;
                }
            }
        } // end for
        return res;
    }
    /**
     Use tow pointer i, j to test whether substring s[j+1..i]
     contains exactly same (multi-)set of characters as the word set.
     
     If such a substring is found, test whether it contains all words.
     */
    vector<int> findSubstring2(string s, vector<string>& words) {
        vector<int> res;
        int n = s.size();
        int nw = words.size();
        if (n <= 0 || nw <= 0) return res;
        
        int wn = words[0].size();
        int tn = wn * nw;
        map<string, int> wordCnt;
        vector<int> cht(256, 0);
        for (auto& w : words) {
            ++wordCnt[w];
            for (auto c : w) {
                ++cht[c];
            }
        }
        
        int i = 0;
        int j = 0;
        while (i < n) {
            if (cht[s[i]] > 0) {
                --tn;
            }
            --cht[s[i]];
            ++i;
            
            while (tn == 0) {
                // test whether it contains all words
                if (i - j == wn * nw) {
                    map<string, int> t(wordCnt);
                    for (int k = j; k < i; k += wn) {
                        string w(s.substr(k, wn));
                        --t[w];
                    }
                    
                    bool matched = true;
                    for (const auto&p : t) {
                        if (p.second != 0) {
                            matched = false;
                            break;
                        }
                    }
                    
                    if (matched) {
                        res.push_back(j);
                    }
                }
                
                if (cht[s[j]] == 0) {
                    ++tn;
                }
                ++cht[s[j]];
                ++j;
            } // end while
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string s = "aaa";
    vector<string> words {
        "a", "a"
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = findSubstring::Solution().findSubstring(s, words);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
