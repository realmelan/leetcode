// minMutation.cpp
// leetcode
//
// Created by  Song Ding on 10/3/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minMutation {
/**
 433. Minimum Genetic Mutation
 Medium

 307

 37

 Favorite

 Share
 A gene string can be represented by an 8-character long string, with choices from "A", "C", "G", "T".

 Suppose we need to investigate about a mutation (mutation from "start" to "end"), where ONE mutation is defined as ONE single character changed in the gene string.

 For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

 Also, there is a given gene "bank", which records all the valid gene mutations. A gene must be in the bank to make it a valid gene string.

 Now, given 3 things - start, end, bank, your task is to determine what is the minimum number of mutations needed to mutate from "start" to "end". If there is no such a mutation, return -1.

 Note:

 Starting point is assumed to be valid, so it might not be included in the bank.
 If multiple mutations are needed, all mutations during in the sequence must be valid.
 You may assume start and end string is not the same.
  

 Example 1:

 start: "AACCGGTT"
 end:   "AACCGGTA"
 bank: ["AACCGGTA"]

 return: 1
  

 Example 2:

 start: "AACCGGTT"
 end:   "AAACGGTA"
 bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

 return: 2
  

 Example 3:

 start: "AAAAACCC"
 end:   "AACCCCCC"
 bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

 return: 3
 */

class Solution {
public:
    /**
     * BFS:
     * starting from start, and check every mutation and only keep the ones that are in the bank.
     * or we can transform string into integer, as there are only 8 positions and 4 characters at a position.
     */
    int minMutation2(string start, string end, vector<string>& bank) {
        unordered_map<char, int> gi;
        gi['A'] = 1;
        gi['C'] = 2;
        gi['G'] = 4;
        gi['T'] = 8;
        unordered_set<int> bset;
        for (auto b : bank) {
            bset.insert(gtoi(b, gi));
        }
        
        int res = 0;
        int target = gtoi(end, gi);
        if (!bset.count(target)) {
            return -1;
        }
        unordered_set<int> visited{gtoi(start, gi)};
        unordered_set<int> cur{gtoi(start, gi)};
        while (cur.size()) {
            ++res;
            unordered_set<int> next;
            for (auto s : cur) {
                for (int i = 0; i < 8; ++i) {
                    for (auto& p : gi) {
                        int t = s;
                        t &= ~(15 << (i*4));
                        t |= (p.second << (i*4));
                        if (t != s && bset.count(t) && !visited.count(t)) {
                            if (t == target) {
                                return res;
                            }
                            next.insert(t);
                            visited.insert(t);
                        }
                    }
                }
            }
            cur.swap(next);
        }
        return -1;
    }
    int gtoi(const string& a, unordered_map<char, int>& gi) {
        int t = 0;
        for (auto c : a) {
            t <<= 4;
            t |= gi[c];
        }
        return t;
    }
    /**
     * breadth first search
     */
    int minMutation(string start, string end, vector<string>& bank) {
        const vector<char> alpha{'A','C','G','T'};
        unordered_set<string> genes(bank.begin(), bank.end());
        if (genes.find(end) == genes.end()) {
            return -1;
        }
        
        int res = 0;
        unordered_set<string> cur{start};
        unordered_set<string> used;
        while (true) {
            ++res;
            unordered_set<string> next;
            for (auto c : cur) {
                for (int i = 0; i < 8; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        string nc(c);
                        if (nc[i] != alpha[j]) {
                            nc[i] = alpha[j];
                            if (nc == end) {
                                return res;
                            }
                            if (used.find(nc) == used.end()
                                && cur.find(nc) == cur.end()
                                && genes.find(nc) != genes.end()) {
                                next.insert(nc);
                            }
                        }
                    }
                }
            }
            used.insert(cur.begin(), cur.end());
            if (next.empty()) {
                return -1;
            } else {
                cur.swap(next);
            }
        }
        return res;
    }
    
    int minMutation3(string start, string end, vector<string>& bank) {
        const vector<char> cs{'A', 'C', 'G', 'T'};
        unordered_set<string> isGene(begin(bank), std::end(bank));
        if (!isGene.count(end)) {
            return -1;
        }
        int res = 0;
        unordered_set<string> visited{start};
        vector<string> cur{start};
        while (cur.size()) {
            ++res;
            vector<string> next;
            for (const auto& s : cur) {
                string w(s);
                for (int i = 0; i < 8; ++i) {
                    for (char c : cs) {
                        w[i] = c;
                        if (w == end) {
                            return res;
                        }
                        if (isGene.count(w) && !visited.count(w)) {
                            visited.insert(w);
                            next.push_back(w);
                        }
                    }
                    w[i] = s[i];
                }
            }
            cur.swap(next);
        }
        return -1;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    struct d {
        string start;
        string end;
        vector<string> bank;
    };
    vector<struct d> p {
        {"AACCGGTT","AACCGGTA",{"AACCGGTA"}},
        
    };
    vector< int > answers {
        1,
        
    };
    // TODO: add return type and paramters.
    for (auto& dp : p) {
        clock_t tstart = clock();
        auto res = minMutation::Solution().minMutation3(dp.start, dp.end, dp.bank);
        cout << clock() - tstart << endl;
        cout << res << endl << endl;
    }
    return 0;
}
//*/
