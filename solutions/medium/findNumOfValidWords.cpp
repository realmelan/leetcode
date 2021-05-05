// findNumOfValidWords.cpp
// leetcode
//
// Created by  Song Ding on 9/18/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findNumOfValidWords {
/*
// TODO: copy problem statement here
 1178. Number of Valid Words for Each Puzzle
 Hard
 
 96
 
 8
 
 Favorite
 
 Share
 With respect to a given puzzle string, a word is valid if both the following conditions are satisfied:
 word contains the first letter of puzzle.
 For each letter in word, that letter is in puzzle.
 For example, if the puzzle is "abcdefg", then valid words are "faced", "cabbage", and "baggage"; while invalid words are "beefed" (doesn't include "a") and "based" (includes "s" which isn't in the puzzle).
 Return an array answer, where answer[i] is the number of words in the given word list words that are valid with respect to the puzzle puzzles[i].
 
 
 Example :
 
 Input:
 words = ["aaaa","asas","able","ability","actt","actor","access"],
 puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
 Output: [1,1,3,2,4,0]
 Explanation:
 1 valid word for "aboveyz" : "aaaa"
 1 valid word for "abrodyz" : "aaaa"
 3 valid words for "abslute" : "aaaa", "asas", "able"
 2 valid words for "absoryz" : "aaaa", "asas"
 4 valid words for "actresz" : "aaaa", "asas", "actt", "access"
 There're no valid words for "gaswxyz" cause none of the words in the list contains letter 'g'.
 
 
 Constraints:
 
 1 <= words.length <= 10^5
 4 <= words[i].length <= 50
 1 <= puzzles.length <= 10^4
 puzzles[i].length == 7
 words[i][j], puzzles[i][j] are English lowercase letters.
 Each puzzles[i] doesn't contain repeated characters.
 */

class Solution {
public:
    /**
     * Build a trie from words based on each word's unique characters, at most 7 layer.
     * the first layer has a->z, second layer starting from first layer's character +1.
     * say a node represent 'm', then its children start from "n".
     * ignore a word having >7 unique characters,
     *
     * Then check each puzzle against the trie, and only add count when the first character of
     * puzzle is met in the trie. Since a word may have skip any character in puzzle (except the
     * first character, which is a must), at each layer of trie, match would starts at any
     * character.
     */
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        TrieNode trie;
        for (const auto& w : words) {
            add(w, trie);
        }
        
        // now match
        vector<int> res;
        for (const auto& p : puzzles) {
            res.push_back(match(p, trie));
        }
        return res;
    }

private:
    struct TrieNode {
        int cnt; // # of word that stop at this node
        char val; // which character this represents, and also determines the start index of child.
        vector<TrieNode*> child;
        
        TrieNode() : cnt(0), child(26) {}
        ~TrieNode() {
            release();
        }
        
        void add(set<char>& cs) {
            if (cs.empty()) {
                return;
            }
            char c = *(cs.begin());
            TrieNode* next = child[c-'a'];
            if (next == NULL) {
                next = child[c-'a'] = new TrieNode();
            }
            next->val = c;
            cs.erase(cs.begin());
            if (cs.empty()) {
                ++next->cnt;
            } else {
                next->add(cs);
            }
        }
        int match(set<char> cs, char fc) {
            int res = 0;
            set<char> nextCs(cs);
            for (auto it = cs.begin(); it != cs.end(); ++it) {
                nextCs.erase(nextCs.begin());
                TrieNode* next = child[*it-'a'];
                if (next) {
                    char nfc = fc;
                    if (fc == *it) {
                        nfc = 0;
                    }
                    if (nfc == 0) {
                        res += next->cnt;
                    }
                    res += next->match(nextCs, nfc);
                }
            }
            return res;
        }
        void release() {
            for (auto*& p : child) {
                if (p) {
                    p->release();
                }
                delete p;
                p = NULL;
            }
        }
    };
    void add(const string& word, TrieNode& root) {
        set<char> cs;
        for (auto c : word) {
            cs.insert(c);
        }
        if (cs.size() > 7) {
            return;
        }
        root.add(cs);
    }
    int match(const string& puzzle, TrieNode& root) {
        set<char> cs;
        for (auto c : puzzle) {
            cs.insert(c);
        }
        return root.match(cs, puzzle[0]);
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<string> words;
        vector<string> puzzles;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{"aaaa","asas","able","ability","actt","actor","access"},{"aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"}},
        {{"kkaz","kaaz","aazk","aaaz","abcdefghijklmnopqrstuvwxyz","kkka","kkkz","aaaa","kkkk","zzzz"},{"kazxyuv"}},
    };

    vector< vector<int> > answers {
        {1,1,3,2,4,0},
        {6},
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findNumOfValidWords::Solution().findNumOfValidWords(dp.words, dp.puzzles);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
