// isScramble.cpp
// leetcode
//
// Created by  Song Ding on 11/7/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace isScramble {

class Solution {
public:
    bool isScramble(string s1, string s2) {
        unordered_map<string, bool> memo;
        return recur(s1, s2, memo);
    }

private:
    bool recur(string s1, string s2, unordered_map<string, bool>& memo) {
        int n = s1.size();
        if (n == 1) {
            return s1 == s2;
        } else if (n == 2) {
            return (s1[0] == s2[0] && s1[1] == s2[1])
            || (s1[0] == s2[1] && s1[1] == s2[0]);
        } else {
            string key1 = s1 + s2;
            string key2 = s2 + s1;
            auto it = memo.find(key1);
            if (it != memo.end()) {
                return it->second;
            }
            
            // first count characters
            int count[26] = {0};
            for (int i = 0; i < n; ++i) {
                ++count[s1[i] - 'a'];
                --count[s2[i] - 'a'];
            }
            for (auto i : count) {
                if (i != 0) {
                    memo[key1] = memo[key2] = false;
                    return false;
                }
            }
            
            for (int i = 1; i < n; ++i) {
                string s1p1 = s1.substr(0, i);
                string s1p2 = s1.substr(i);
                string s2p1 = s2.substr(0, i);
                string s2p2 = s2.substr(i);
                if (recur(s1p1, s2p1, memo) && recur(s1p2, s2p2, memo)) {
                    memo[key1] = true;
                    memo[key2] = true;
                    return true;
                }
                
                s2p1 = s2.substr(0, n - i);
                s2p2 = s2.substr(n - i);
                if (recur(s1p1, s2p2, memo) && recur(s1p2, s2p1, memo)) {
                    memo[key1] = true;
                    memo[key2] = true;
                    return true;
                }
            }
            
            memo[key1] = false;
            memo[key2] = false;
            return false;
        }
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<string> s1 {
        "great",
        "great",
        "abcde"
        
    };
    vector<string> s2 {
        "rgeat",
        "rgtae",
        "caebd"
    };

    vector<  bool > answers {
        true,
        true,
        false
    };
    int i = 2;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = isScramble::Solution().isScramble(s1[i], s2[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
