// WordDictionary.cpp
// leetcode
//
// Created by  Song Ding on 5/13/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace WordDictionary {

class WordDictionary {

    struct TrieNode {
        TrieNode* children[26];
        bool end;
        TrieNode() {
            end = false;
            cout << sizeof(children) << endl;
            memset(children, 0, sizeof(children));
        }
        
        void add(const string& word, int d) {
            if (d >= word.size()) {
                end = true;
                return;
            }
            int id = word[d] - 'a';
            TrieNode* c = children[id];
            if (c == NULL) {
                c = children[id] = new TrieNode();
            }
            c->add(word, d + 1);
        }
        
        bool search(const string& word, int d) {
            if (d == word.size()) {
                return end;
            }
            
            char wc = word[d];
            if (wc == '.') {
                for (auto* p : children) {
                    if (p && p->search(word, d + 1)) {
                        return true;
                    }
                }
                return false;
            } else {
                int id = word[d] - 'a';
                TrieNode* c = children[id];
                if (c != NULL) {
                    return c->search(word, d + 1);
                }
                return false;
            }
        }
    };
public:
    /** Initialize your data structure here. */
    /**
     * Use trie
     *
     */
    WordDictionary() {
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        root.add(word, 0);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter.*/
    bool search(string word) {
        return root.search(word, 0);
    }
private:
    TrieNode root;
};

}

/*/
int main() {
    // TODO: prepare parameters here
    WordDictionary::WordDictionary wd;
    wd.addWord("bad");
    wd.addWord("dad");
    wd.addWord("mad");

    // TODO: add return type and paramters.
    clock_t start = clock();
    cout << wd.search("pad") << endl;
    cout << wd.search("bad") << endl;
    cout << wd.search(".ad") << endl;
    cout << wd.search("..d") << endl;
    cout << clock() - start << endl;
    return 0;
}
//*/
