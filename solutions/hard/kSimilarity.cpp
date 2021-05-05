// kSimilarity.cpp
// leetcode
//
// Created by  Song Ding on 8/29/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace kSimilarity {
/*
// TODO: copy problem statement here
 854. K-Similar Strings
 Hard
 
 190
 
 21
 
 Favorite
 
 Share
 Strings A and B are K-similar (for some non-negative integer K) if we can swap the positions of two letters in A exactly K times so that the resulting string equals B.
 
 Given two anagrams A and B, return the smallest K for which A and B are K-similar.
 
 Example 1:
 
 Input: A = "ab", B = "ba"
 Output: 1
 Example 2:
 
 Input: A = "abc", B = "bca"
 Output: 2
 Example 3:
 
 Input: A = "abac", B = "baca"
 Output: 2
 Example 4:
 
 Input: A = "aabc", B = "abca"
 Output: 2
 Note:
 
 1 <= A.length == B.length <= 20
 A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}
 */

class Solution {
public:
    /**
     *
     */
    int kSimilarity(string A, string B) {
        int n = A.size();
        int res = 0;
        unordered_map<string, int> pc;
        for (int i = 0; i < n; ++i) {
            if (A[i] == B[i]) {
                continue;
            }
            string p;
            p.push_back(B[i]);
            p.push_back(A[i]);
            if (pc.find(p) != pc.end()) {
                if (--pc[p] <= 0) {
                    pc.erase(p);
                }
                ++res;
            } else {
                reverse(p.begin(), p.end());
                ++pc[p];
            }
        }
        
        // order matters
        string a;
        string b;
        for (int i = 0; i < n; ++i) {
            string p;
            p.push_back(A[i]);
            p.push_back(B[i]);
            if (--pc[p] >= 0) {
                a.push_back(A[i]);
                b.push_back(B[i]);
            }
        }
        if (a.empty()) {
            return res;
        }
        
        // TODO: how to deal process pair(a,b)
        int hres = INT_MAX;
        n = a.size();
        for (int i = 1; i < n; ++i) {
            if (a[i] == b[0]) {
                a[i] = a[0];
                int t = 1 + kSimilarity(a.substr(1), b.substr(1));
                a[i] = b[0];
                hres = min(hres, t);
            }
        }
        return res + hres;
    }
    int lp_cnt(string A, string B) {
        vector<int> cnt1(6, 0);
        vector<int> minf1(6, 0);
        vector<int> cnt2(6, 0);
        vector<int> minf2(6, 0);
        int n = A.size();
        for (int i = 0; i < n; ++i) {
            ++cnt1[A[i]-'a'];
            minf1[B[i]-'a'] = min(minf1[B[i]-'a'], --cnt1[B[i]-'a']);
            
            ++cnt2[B[i]-'a'];
            minf2[A[i]-'a'] = min(minf2[A[i]-'a'], --cnt2[A[i]-'a']);
        }
        
        int res1 = 0;
        for (auto i : minf1) {
            res1 -= i;
        }
        int res2 = 0;
        for (auto i : minf2) {
            res2 -= i;
        }
        return max(res1, res2);
    }
    /**
     * count maximum times that a letter moves forward.
     */
    int kSimilarity_wrong(string A, string B) {
        vector<int> cnt1(6, 0);
        vector<int> minf1(6, 0);
        vector<int> cnt2(6, 0);
        vector<int> minf2(6, 0);
        int n = A.size();
        for (int i = 0; i < n; ++i) {
            ++cnt1[A[i]-'a'];
            minf1[B[i]-'a'] = min(minf1[B[i]-'a'], --cnt1[B[i]-'a']);
            
            ++cnt2[B[i]-'a'];
            minf2[A[i]-'a'] = min(minf2[A[i]-'a'], --cnt2[A[i]-'a']);
        }
        
        int res1 = 0;
        for (auto i : minf1) {
            res1 -= i;
        }
        int res2 = 0;
        for (auto i : minf2) {
            res2 -= i;
        }
        return max(res1, res2);
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string A;
        string B;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"ab","ba"},
        {"abc","bca"},
        {"abac","baca"},
        {"aabc","abca"},
        {"bccaba","abacbc"},
        {"decba","eadcb"},
        {"abccaacceecdeea","bcaacceeccdeaae"},
        
    };

    vector< int > answers {
        1,
        2,
        2,
        2,
        3,
        4,
        9
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = kSimilarity::Solution().kSimilarity(dp.A, dp.B);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
