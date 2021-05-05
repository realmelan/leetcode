// findLongestWord.cpp
// leetcode
//
// Created by  Song Ding on 10/23/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findLongestWord {
/*
// TODO: copy problem statement here
 524. Longest Word in Dictionary through Deleting
 Medium

 390

 196

 Favorite

 Share
 Given a string and a string dictionary, find the longest string in the dictionary that can be formed by deleting some characters of the given string. If there are more than one possible results, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.

 Example 1:
 Input:
 s = "abpcplea", d = ["ale","apple","monkey","plea"]

 Output:
 "apple"
 Example 2:
 Input:
 s = "abpcplea", d = ["a","b","c"]

 Output:
 "a"
 Note:
 All the strings in the input will only contain lower-case letters.
 The size of the dictionary won't exceed 1,000.
 The length of all the strings in the input won't exceed 1,000.
 */

class Solution {
public:
    /**
     * before create trie, remove word that contains character not in s.
     * create a trie using word list, and match s against the trie in such a way:
     * after matching current node:
     *  check whether current node marks end of a word, if so, update res if needed;
     *  for each next node, move position of s till character at position matches the node
     */
    string findLongestWord(string s, vector<string>& d) {
        return "";
    }
    /**
     * prepare s to get the position list of each unique character.
     * match s against each word in d:
     *  for each char in word:
     *   use binary search to find next position in s and update current position
     *
     * O(nlogm), where m = s.size();
     */
    string findLongestWord2(string s, vector<string>& d) {
        int n = d.size();
        vector<vector<int>> p(26);
        for (int i = 0; i < s.size(); ++i) {
            p[s[i]-'a'].push_back(i);
        }
        string res;
        for (auto& w : d) {
            int cp = 0;
            int i = 0;
            for (; i < w.size(); ++i) {
                if (p[w[i]-'a'].empty()) {
                    break;
                }
                auto it = lower_bound(p[w[i]-'a'].begin(), p[w[i]-'a'].end(), cp);
                if (it == p[w[i]-'a'].end()) {
                    continue;
                }
                cp = *it;
            }
            if (i >= w.size() && (w.size() > res.size() || (w.size() == res.size() && w < res))) {
                res = w;
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
        string s;
        vector<string> d;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"abpcplea",{"ale","apple","monkey","plea"}},
        {"abpcplea",{"a","b","c"}},
    };

    vector< string > answers {
        "apple",
        "a",
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findLongestWord::Solution().findLongestWord2(dp.s, dp.d);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
