// shortestPalindrome.cpp
// leetcode
//
// Created by  Song Ding on 3/26/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace shortestPalindrome {

class Solution {
public:
    string shortestPalindrome(string s) {
        //*
        int n = s.size();
        string t = s + "#";
        t.insert(t.end(), s.rbegin(), s.rend());
        cout << t << endl;
        vector<int> lps_table = build_lps(t);
        cout << lps_table <<endl;
        int k = lps_table[n*2];
        cout << k << endl;
        
        string res(s.rbegin(), s.rend());
        res.resize(n - k);
        cout << res << endl;
        res.append(s);
        return res;
        //*/
        return "";
    }
    
    vector<int> longestProperSuffix(string w) {
        int n = w.size();
        vector<int> t(n, 0);
        int i = 0;
        int k = 1;
        while (k < n) {
            if (w[i] == w[k]) {
                ++i;
                t[k] = i;
                //cout << "t[" << k << "]=" << t[k] << endl;
                ++k;
            } else {
                i = t[i - 1];
                while (i > 0 && w[i] != w[k]) {
                    i = t[i - 1];
                }
                if (w[i] == w[k]) {
                    ++i;
                }
                t[k] = i;
                ++k;
            }
        }
        return t;
    }
    
    int kmp_search(string s, string w, const vector<int>& t) {
        int ns = s.size();
        int ws = w.size();
        
        int k = 0;
        int i = 0;
        while (k <= ns && i <= ws) {
            if (s[k] == w[i]) {
                ++k;
                ++i;
                
                if (i == ws) {
                    return k - ws;
                }
            } else {
                i = t[i];
                if (i < 0) {
                    ++i;
                    ++k;
                }
            }
        }
        
        return 0;
    }
    vector<int> build_kmp_table(string s) {
        int n = s.size();
        vector<int> res(n, 0);
        res[0] = -1;
        int i = 0;
        int k = 1;
        while (k < n) {
            if (s[i] == s[k]) {
                res[k] = i;
                ++i;
                ++k;
            } else {
                res[k] = i;
                while (i >= 0 && s[i] != s[k]) {
                    i = res[i];
                }
                ++k;
                ++i;
            }
        }
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
            } else {
                res[k] = 0;
                while (i > 0 && s[i] != s[k]) {
                    i = res[i-1];
                }
                if (i > 0) {
                    res[k] = ++i;
                }
                ++k;
            }
        }
        return res;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string w{
        //"AAABCDAAAABCDE"
        "aacecaaa"
        //"abcd"
        //"abbacd"
    };
    //auto t = shortestPalindrome::Solution().build_kmp_table(w);
    //cout << t << endl;
    
    //auto sret = shortestPalindrome::Solution().kmp_search("ABC ABCDAB ABCDABCDABDE", w, t);
    //cout << sret << endl;
    
    //auto lsref = shortestPalindrome::Solution().longestProperSuffix(w);
    //cout << lsref << endl;
    //return 0;
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = shortestPalindrome::Solution().shortestPalindrome(w);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
