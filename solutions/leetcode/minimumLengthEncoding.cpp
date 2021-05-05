// minimumLengthEncoding.cpp
// leetcode
//
// Created by  Song Ding on 5/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minimumLengthEncoding {
/*
 820. Short Encoding of Words
 Medium
 
 147
 
 40
 
 Favorite
 
 Share
 Given a list of words, we may encode it by writing a reference string S and a list of indexes A.
 
 For example, if the list of words is ["time", "me", "bell"], we can write it as S = "time#bell#" and indexes = [0, 2, 5].
 
 Then for each index, we will recover the word by reading from the reference string from that index until we reach a "#" character.
 
 What is the length of the shortest reference string S possible that encodes the given words?
 
 Example:
 
 Input: words = ["time", "me", "bell"]
 Output: 10
 Explanation: S = "time#bell#" and indexes = [0, 2, 5].
 
 
 Note:
 
 1 <= words.length <= 2000.
 1 <= words[i].length <= 7.
 Each word has only lowercase letters.
 */

class Solution {
public:
    /**
     * If a word is a suffix of another word, then it can be indexed using existing
     * word.
     * Apparently, words that are shorter might be indexed by longer words. But not
     * vice versa.
     */
    int minimumLengthEncoding(vector<string>& words) {
        sort(words.begin(), words.end(),[](const string&a, const string&b){
            return a.length() > b.length();
        });
        
        unordered_set<string> indexed;
        int res = 0;
        for (const auto& w : words) {
            if (indexed.find(w) == indexed.end()) {
                // generate all words that are indexed.
                string tobeIndex;
                for (int i = w.size() - 1; i >= 0; --i) {
                    indexed.insert(w.substr(i));
                }
                res += w.size() + 1;
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
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{"time", "me", "bell"}}
    };

    vector< int > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minimumLengthEncoding::Solution().minimumLengthEncoding(dp.words);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
