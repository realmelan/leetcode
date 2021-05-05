// spellchecker.cpp
// leetcode
//
// Created by  Song Ding on 6/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace spellchecker {
/*
// TODO: copy problem statement here
 966. Vowel Spellchecker
 Medium
 
 59
 
 125
 
 Favorite
 
 Share
 Given a wordlist, we want to implement a spellchecker that converts a query word into a correct word.
 
 For a given query word, the spell checker handles two categories of spelling mistakes:
 
 Capitalization: If the query matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the case in the wordlist.
 Example: wordlist = ["yellow"], query = "YellOw": correct = "yellow"
 Example: wordlist = ["Yellow"], query = "yellow": correct = "Yellow"
 Example: wordlist = ["yellow"], query = "yellow": correct = "yellow"
 Vowel Errors: If after replacing the vowels ('a', 'e', 'i', 'o', 'u') of the query word with any vowel individually, it matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the match in the wordlist.
 Example: wordlist = ["YellOw"], query = "yollow": correct = "YellOw"
 Example: wordlist = ["YellOw"], query = "yeellow": correct = "" (no match)
 Example: wordlist = ["YellOw"], query = "yllw": correct = "" (no match)
 In addition, the spell checker operates under the following precedence rules:
 
 When the query exactly matches a word in the wordlist (case-sensitive), you should return the same word back.
 When the query matches a word up to capitlization, you should return the first such match in the wordlist.
 When the query matches a word up to vowel errors, you should return the first such match in the wordlist.
 If the query has no matches in the wordlist, you should return the empty string.
 Given some queries, return a list of words answer, where answer[i] is the correct word for query = queries[i].
 
 
 
 Example 1:
 
 Input: wordlist = ["KiTe","kite","hare","Hare"], queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
 Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
 
 
 Note:
 
 1 <= wordlist.length <= 5000
 1 <= queries.length <= 5000
 1 <= wordlist[i].length <= 7
 1 <= queries[i].length <= 7
 All strings in wordlist and queries consist only of english letters.
 */

class Solution {
public:
    /**
     * build 3 dictionary for each kind of match, in decreasing priority
     *  1, exact match
     *  2, change to lower case
     *  3, change to lower case, and replace vowel with *.
     */
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_map<string, int> exact;
        unordered_map<string, int> cap;
        unordered_map<string, int> vowel;
        
        vector<char> vowels {
            'a', 'e', 'i', 'o', 'u'
        };
        vector<bool> isVowel(26, false);
        for (char v : vowels) {
            isVowel[v - 'a'] = true;
        }
        
        int n = wordlist.size();
        for (int i = 0; i < n; ++i) {
            string w(wordlist[i]);
            exact.insert(make_pair(w, i));
            
            string vw;
            for (char& c : w) {
                if (c >= 'A' && c <= 'Z') {
                    c = c - 'A' + 'a';
                }
                
                if (isVowel[c - 'a']) {
                    vw.push_back('*');
                } else {
                    vw.push_back(c);
                }
            }
            cap.insert(make_pair(w, i));
            
            vowel.insert(make_pair(vw, i));
        }
        
        vector<string> res;
        for (auto q : queries) {
            auto it = exact.find(q);
            if (it != exact.end()) {
                res.push_back(q);
                continue;
            }
            
            string vq;
            for (char& c : q) {
                if (c >= 'A' && c <= 'Z') {
                    c = c - 'A' + 'a';
                }
                
                if (isVowel[c - 'a']) {
                    vq.push_back('*');
                } else {
                    vq.push_back(c);
                }
            }
            
            it = cap.find(q);
            if (it != cap.end()) {
                res.push_back(wordlist[it->second]);
                continue;
            }
            
            it = vowel.find(vq);
            if (it != cap.end()) {
                res.push_back(wordlist[it->second]);
            } else {
                res.push_back("");
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
        vector<string> wordlist;
        vector<string> queries;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{"KiTe","kite","hare","Hare"},{"kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"}}
    };

    vector< vector<string> > answers {
        {"kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = spellchecker::Solution().spellchecker(dp.wordlist, dp.queries);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
