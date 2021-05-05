// MagicDictionary.cpp
// leetcode
//
// Created by  Song Ding on 11/15/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace MagicDictionary {
/*
// TODO: copy problem statement here
 676. Implement Magic Dictionary
 Medium

 430

 107

 Favorite

 Share
 Implement a magic directory with buildDict, and search methods.

 For the method buildDict, you'll be given a list of non-repetitive words to build a dictionary.

 For the method search, you'll be given a word, and judge whether if you modify exactly one character into another character in this word, the modified word is in the dictionary you just built.

 Example 1:
 Input: buildDict(["hello", "leetcode"]), Output: Null
 Input: search("hello"), Output: False
 Input: search("hhllo"), Output: True
 Input: search("hell"), Output: False
 Input: search("leetcoded"), Output: False
 Note:
 You may assume that all the inputs are consist of lowercase letters a-z.
 For contest purpose, the test data is rather small by now. You could think about highly efficient algorithm after the contest.
 Please remember to RESET your class variables declared in class MagicDictionary, as static/class variables are persisted across multiple test cases. Please see here for more details.
 */

class MagicDictionary {
public:
    /**
     * //TODO: explain algorithm here
     */
    /** Initialize your data structure here. */
    MagicDictionary() {
        
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        for (auto& word : dict) {
            for (int i = 0; i < word.size(); ++i) {
                string t(word);
                t[i] = '*';
                if (m.find(t) != m.end()) {
                    m[t] = "";
                } else {
                    m[t] = word;
                }
            }
        }
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        for (int i = 0; i < word.size(); ++i) {
            string t(word);
            t[i] = '*';
            auto it = m.find(t);
            if (it != m.end() && it->second != word) {
                return true;
            }
        }
        return false;
    }

private:
    unordered_map<string, string> m;
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<string> dict;
        string word;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {}
    };

    vector< int > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto md = MagicDictionary::MagicDictionary();
        md.buildDict(dp.dict);
        auto res = md.search(dp.word);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
