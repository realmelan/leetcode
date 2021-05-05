// getMaxRepetitions.cpp
// leetcode
//
// Created by  Song Ding on 11/26/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace getMaxRepetitions {

class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int sn1 = s1.size();
        int sn2 = s2.size();
        
        int cnt1[26] = {0};
        for (char c : s1) {
            ++cnt1[c - 'a'];
        }
        
        int cnt2[26] = {0};
        for (char c : s2) {
            ++cnt2[c - 'a'];
        }
        
        for (int i = 0; i < 26; ++i) {
            if (cnt1[i] * n1 < cnt2[i] * n2) {
                return 0;
            }
        }
        
        int t1 = 0; // # of whole s1
        int t2 = 0; // # of whole s2
        int i = 0; // index of s1
        int j = 0; // index of s2
        vector<int> res;
        
        while (true) {
            while (s1[i] != s2[j]) {
                ++i;
                if (i >= sn1) {
                    ++t1;
                    i = 0;
                }
            }
            if (t1 >= n1) {
                return t2 / n2;
            }
            // add to dictionary
            
            
            ++i;
            if (i >= sn1) {
                ++t1;
                i = 0;
            }
            ++j;
            if (j >= sn2) {
                ++t2;
                j = 0;
            }
            
            if (i == 0) {
                res.push_back(t2);
            }
            
            if (i == 0 && j == 0 && t2 > 0) {
                break;
            }
        }
        
        int r = n1 / t1 * t2;
        if (n1 % t1) {
            int l = n1 % t1;
            r += res[l - 1];
        }
        return r / n2;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<string> s1 {
        "acb",
        "musicforever",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "aaa"
    };
    vector<int> n1 {
        4,
        10,
        1000000,
        3
        
    };
    
    vector<string> s2 {
        "ab",
        "lovelive",
        "a",
        "aa"
        
    };
    vector<int> n2 {
        2,
        100000,
        1,
        1
    };

    vector< int  > answers {
    };
    int i = 2;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = getMaxRepetitions::Solution().getMaxRepetitions(s1[i], n1[i], s2[i], n2[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
