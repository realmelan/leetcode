// palindromPairs.cpp
// leetcode
//
// Created by  Song Ding on 3/24/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

/**
 336. Palindrome Pairs
 Hard

 949

 128

 Favorite

 Share
 Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

 Example 1:

 Input: ["abcd","dcba","lls","s","sssll"]
 Output: [[0,1],[1,0],[3,2],[2,4]]
 Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
 Example 2:

 Input: ["bat","tab","cat"]
 Output: [[0,1],[1,0]]
 Explanation: The palindromes are ["battab","tabbat"]

 */
namespace palindromePairs {

class Solution {
public:
    /**
     * another solution:
     * https://leetcode.com/problems/palindrome-pairs/discuss/79210/The-Easy-to-unserstand-JAVA-Solution
     *
     * However, looks like mine looks very good!
     * the central idea is, dividing pairing groups based on the last character recursively,
     * and in pairing groups, an empty string in one group matches a palindrome string in the other group.
     * for non empy strings in the 2 groups, further divide them based on the last character.
     */
    vector<vector<int>> palindromePairs(vector<string>& words) {
        int n = words.size();
        vector<int> w1, w2;
        for (int i = 0; i < n; ++i) {
            w1.push_back(i);
            w2.push_back(i);
        }
        set<vector<int>> res;
        find(words, w1, w2, 0, res);
        return vector<vector<int>>(res.begin(), res.end());
    }
private:
    void find(vector<string>& words, vector<int>& w1, vector<int>& w2, int idx, set<vector<int>>& res) {
        vector<vector<int>> headSet(26), tailSet(26);
        set<int> fpwords, spwords;
        set<int> fempty, sempty;
        for (int i = 0; i < w1.size(); ++i) {
            const string& w = words[w1[i]].substr(idx);
            if (w.empty()) {
                fempty.insert(w1[i]);
            } else if (isPalindrome(w, 0, w.length() - 1)) {
                fpwords.insert(w1[i]);
            }
        }
        for (int i = 0; i < w2.size(); ++i) {
            const string& hw = words[w2[i]];
            const string& w = hw.substr(0, hw.length() - idx);
            if (w.empty()) {
                sempty.insert(w2[i]);
            } else if (isPalindrome(w, 0, w.length() - 1)) {
                spwords.insert(w2[i]);
            }
        }
        
        for (int i = 0; i < w1.size(); ++i) {
            const string& w = words[w1[i]].substr(idx);
            if (!w.empty()) {
                headSet[w[0] - 'a'].push_back(w1[i]);
            }
        }
        for (int i = 0; i < w2.size(); ++i) {
            const string& hw = words[w2[i]];
            const string& w = hw.substr(0, hw.length() - idx);
            if (!w.empty()) {
                tailSet[w[w.length() - 1] - 'a'].push_back(w2[i]);
            }
        }
        for (auto i : fpwords) {
            for (auto j : sempty) {
                if (i != j) {
                    res.insert(vector<int>{i, j});
                }
            }
        }
        
        
        for (auto i : fempty) {
            for (auto j : spwords) {
                if (i != j) {
                    res.insert(vector<int>{i, j});
                }
            }
            for (auto j : sempty) {
                if (i != j) {
                    res.insert(vector<int>{i, j});
                }
            }
        }
        
        for (int i = 0; i < 26; ++i) {
            if (headSet[i].size() && tailSet[i].size()) {
                find(words, headSet[i], tailSet[i], idx + 1, res);
            }
        }
        
    }
    bool isPalindrome(const string& w, int l, int r) {
        int i = l;
        int j = r;
        while (i < j && w[i] == w[j]) {
            ++i;
            --j;
        }
        return i >= j;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<string> words {
        "abcd", "dcba", "lls", "s", "sssll"
    };
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = palindromePairs::Solution().palindromePairs(words);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
