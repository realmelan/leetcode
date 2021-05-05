// shortestPalindrome.cpp
// leetcode
//
// Created by  Song Ding on 8/19/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace shortestPalindrome {
/*
// TODO: copy problem statement here
 214. Shortest Palindrome
 Hard
 
 716
 
 87
 
 Favorite
 
 Share
 Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
 
 Example 1:
 
 Input: "aacecaaa"
 Output: "aaacecaaa"
 Example 2:
 
 Input: "abcd"
 Output: "dcbabcd"
 */

class Solution {
public:
    /**
     * reverse s and append it to original input s.
     * Note, we want to find the longest prefix of s that is a palindrome.
     * then after reversing s, the longest prefix palindrome is at the end of
     * the reversed string, and it matches the prefix of s too.
     *
     * Build a table of longest proper prefix that is also a suffix.
     */
    string shortestPalindrome(string s) {
        int n = s.size();
        string t = s + "#";
        t.insert(t.end(), s.rbegin(), s.rend());
        vector<int> lps_table = build_lps(t);
        int k = lps_table[n*2];
        
        string res(s.rbegin(), s.rend());
        res.resize(n - k);
        res.append(s);
        return res;
    }
    vector<int> build_lps(string s) {
        int n = s.size();
        vector<int> res(n, 0);
        res[0] = 0;
        int i = 0;
        int k = 1;
        while (k < n) {
            if (s[i] == s[k]) {
                ++i;
                res[k] = i;
                ++k;
            } else { // s[i] != s[k]
                if (i > 0) {
                    // move i back to next possible position and continue comparison
                    // i might become 0.
                    i = res[i-1];
                } else { // i=0 && s[i] != s[k]
                    // this happens after i becomes 0 and still s[i] != s[k]
                    res[k] = 0;
                    ++k;
                }
            }
        }
        return res;
    }
    void kmp_search(const std::string& text, const std::string& pattern) {
        int nt = text.size();
        int np = pattern.size();
        vector<int> lps = build_lps(pattern);
        int i = 0;
        int j = 0;
        while (i < nt) {
            if (text[i] == pattern[j]) {
                ++i;
                ++j;
            }
            if (j == np) { // pattern found
                cout << "pattern found at " << i-j+1 << endl;
                j = lps[j-1];
            } else if (i < nt && pattern[j] != text[i]) { // update j when there is a mismatch.
                if (j > 0) {
                    j = lps[j-1];
                } else {
                    ++i;
                }
            }
        }
    }
    /**
     * reverse s and append it to s to get a new string ns, find all suffix trees of
     * ns and sort it using prefix doubling.
     *
     * Keep valid suffix tree of s and reversed s, but remove all the other suffix trees.
     * Use Kasai algorithm to find longest common prefix of the leftover suffix tree array.
     *
     * For each index in the suffix tree array, if lcp(suf[i], suf[i+1]) = length(suf[i])
     * and (index of suf[i], index of suf[i+1]) matches a palindrome, then a candidate is found.
     */
    string shortestPalindrome_TLE(string s) {
        struct st {
            int p;
            int rk1;
            int rk2;
        };
        
        int n = s.size();
        int nn = n * 2;
        string ns(nn, 'a');
        for (int i = 0; i < n; ++i) {
            ns[i] = s[i];
            ns[nn-i-1] = s[i];
        }
        
        n = nn;
        vector<int> rank(n, 0);
        vector<st> sufs;
        for (int i = 0; i < n; ++i) {
            sufs.push_back({i, -1, -1});
            rank[i] = ns[i] - 'a';
        }
        for (int k = 1; k < n; k<<=1) {
            for (int i = 0; i < n; ++i) {
                sufs[i].p = i;
                sufs[i].rk1 = rank[i];
                sufs[i].rk2 = i + k < n ? rank[i+k] : -1;
            }
            sort(sufs.begin(), sufs.end(), [](const st&a, const st& b){
                return a.rk1 != b.rk1 ? a.rk1 < b.rk1 : a.rk2 < b.rk2;
            });
            
            for (int i = 0; i < n; ++i) {
                rank[sufs[i].p] = i;
                // if two consecutive suf tree has same rk1 and rk2
                // then rank[p1] = rank[p2];
                if (i > 0 && sufs[i].rk1 == sufs[i-1].rk1 && sufs[i].rk2 == sufs[i-1].rk2) {
                    rank[sufs[i].p] = rank[sufs[i-1].p];
                }
            }
        }
        
        vector<int> suftab(n, 0);
        for (int i = 0; i < n; ++i) {
            suftab[i] = sufs[i].p;
        }
        vector<int> sufinv(n, 0);
        for (int i = 0; i < n; ++i) {
            sufinv[suftab[i]] = i;
        }
        
        // now use Kasai algorithm to find LCP
        vector<int> lcp(n, 0);
        int h = 0;
        for (int i = 0; i < n; ++i) {
            if (sufinv[i] > 0) {
                int k = suftab[sufinv[i]-1];
                while (ns[i+h] == ns[k+h]) {
                    ++h;
                }
                lcp[sufinv[i]] = h;
                if (h > 0) {
                    --h;
                }
            }
        }
        
        int rlen = n - 1;
        int ri = 0;
        // loop through suffix tree and see whether a palindrom can be constructed
        int thr = (n-2) / 4;
        for (int i = 0; i < n-1; ++i) {
            if (suftab[i] < n-1 - thr) {
                continue;
            }
            
            // find next valid suffix starting index
            int cnt = 2;
            int p1 = n - suftab[i];
            int p2 = p1 - 1;
            int j = i+1;
            int len = lcp[j]; // length of common prefix
            while (j < n && cnt > 0) {
                len = min(len, lcp[j]);
                if (len < p1) {
                    break;
                } else if (suftab[j] == p1 && p1 <= thr) {
                    if ((n/2 - p1)*2 < rlen) {
                        ri = p1;
                        rlen = (n/2 - p1)*2;
                    }
                    --cnt;
                } else if (suftab[j] == p2 && p2 <= thr) {
                    if ((n/2 - 1 - p2)*2+1 < rlen) {
                        ri = p2;
                        rlen = (n/2-1 - p2)*2+1;
                    }
                    --cnt;
                }
                
                ++j;
            }
        }
        
        string res(s);
        int toadd = rlen - n / 2;
        for (int i = toadd; i >= 1; --i) {
            res.insert(res.begin(), s[n/2-i]);
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
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"babbbabbaba"},
        {"abbacd"},
        {"aabba"},
        {"aacecaaa"},
        {"aaacecaaa"},
        {"abcd"},
        {"a"},
        {""},
        {"gabqtbypdwjjelvgohmvzpyfqayobkyyhoizaqhtqkzodcosufbpgurxsbjtrkombfbl"},
    };

    vector< string > answers {
        "ababbabbbabbaba"
        "dcabbacd",
        "abbaabba",
        "aaacecaaa",
        "aaacecaaa",
        "dcbabcd",
        "a",
        "",
        "lbfbmokrtjbsxrugpbfusocdozkqthqaziohyykboyaqfypzvmhogvlejjwdpybtqbagabqtbypdwjjelvgohmvzpyfqayobkyyhoizaqhtqkzodcosufbpgurxsbjtrkombfbl"
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = shortestPalindrome::Solution().shortestPalindrome(dp.s);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
