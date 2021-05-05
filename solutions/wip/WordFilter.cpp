// WordFilter.cpp
// leetcode
//
// Created by  Song Ding on 4/12/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace WordFilter {

class WordFilter {
public:
    WordFilter(vector<string> words) {
        int n = words.size();
        for (int i = 0; i < n; ++i) {
            string w(words[i]);
            ptree.add(w, i, 0);
            
            reverse(w.begin(), w.end());
            stree.add(w, i, 0);
        }
    }
    
    int f(string prefix, string suffix) {
        set<int> pw;
        ptree.get(prefix, 0, pw);
        string r(suffix);
        reverse(r.begin(), r.end());
        set<int> sw;
        stree.get(r, 0, sw);
        
        vector<int> common;
        set_intersection(pw.begin(), pw.end(), sw.begin(), sw.end(), std::back_inserter(common));
        if (common.size()) {
            return common.back();
        } else {
            return -1;
        }
    }

private:
    struct Node {
        set<int> weights;
        Node* children[26];
        
        Node() {
            memset(children,  0, sizeof(children));
        }
        ~Node() {
            for (int i = 0; i < 26; ++i) {
                delete children[i];
            }
        }
        void add(const string& w, int i, int level) {
            weights.insert(i);
            int n = w.size();
            if (level < n) {
                char c = w[level];
                Node* child = children[c - 'a'];
                if (child == NULL) {
                    children[c - 'a'] = new Node();
                    child = children[c - 'a'];
                }
                child->add(w, i, level + 1);
            }
        }
        void get(const string& w, int level, set<int>& res) {
            int n = w.size();
            if (level == n) {
                res.insert(weights.begin(), weights.end());
            } else {
                char c = w[level];
                Node* child = children[c - 'a'];
                if (child != NULL) {
                    child->get(w, level + 1, res);
                }
            }
        }
    };
    
    Node ptree;
    Node stree;
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<string> words{
        "cabaabaaaa","ccbcababac","bacaabccba","bcbbcbacaa","abcaccbcaa","accabaccaa","cabcbbbcca","ababccabcb","caccbbcbab","bccbacbcba"
    };
    // TODO: add return type and paramters.
    vector<vector<string>> params {
        {"bccbacbcba","a"},{"ab","abcaccbcaa"},{"a","aa"},{"cabaaba","abaaaa"},{"cacc","accbbcbab"},{"ccbcab","bac"},{"bac","cba"},{"ac","accabaccaa"},{"bcbb","aa"},{"ccbca","cbcababac"}
    };
    clock_t start = clock();
    WordFilter::WordFilter wf(words);
    for (const auto& v : params) {
        cout << wf.f(v[0], v[1]) << endl;
    }
    cout << clock() - start << endl;
    return 0;
}
//*/
