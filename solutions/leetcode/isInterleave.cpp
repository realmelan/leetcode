// isInterleave.cpp
// leetcode
//
// Created by  Song Ding on 12/6/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace isInterleave {

class Solution {
public:
    /**
     * for each position, k,  in s3, keep all possible pairs (i, j)
     * that string s1[0..i] and s2[0..j] can interleave s3[0,..i+j]
     * then for position i, check all possible pairs for position i - 1,
     * which would add most 1 possibility.
     */
    bool isInterleave(string s1, string s2, string s3) {
        int sn1 = s1.size();
        int sn2 = s2.size();
        int sn3 = s3.size();
        if (sn1 + sn2 != sn3) {
            return false;
        }
        
        int cnt[26] = {0};
        for (char c : s1 + s2) {
            ++cnt[c - 'a'];
        }
        int cnt2[26] = {0};
        for (char c : s3) {
            --cnt[c - 'a'];
        }
        for (int i = 0; i < 26; ++i) {
            if (cnt[i]) {
                return false;
            }
        }
        
        set<vector<int>> res;
        if (sn1 > 0 && s1[0] == s3[0]) {
            res.insert({0, -1});
        }
        if (sn2 > 0 && s2[0] == s3[0]) {
            res.insert({-1, 0});
        }
        for (int k = 1; k < sn3; ++k) {
            set<vector<int>> next;
            for (const auto& p : res) {
                int i = p[0] + 1;
                int j = p[1] + 1;
                if (i < sn1 && s1[i] == s3[k]) {
                    next.insert({i, j - 1});
                }
                if (j < sn2 && s2[j] == s3[k]) {
                    next.insert({i - 1, j});
                }
            }
            if (next.empty()) {
                return false;
            }
            res.swap(next);
        }
        return true;
        
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<string>> p{
        {"aabcc","dbbca","aadbbcbcac"},
        {"aabcc","dbbca","aadbbbaccc"},
        {"cbcccbabbccbbcccbbbcabbbabcababbbbbbaccaccbabbaacbaabbbc",
            "abcbbcaababccacbaaaccbabaabbaaabcbababbcccbbabbbcbbb", "abcbcccbacbbbbccbcbcacacbbbbacabbbabbcacbcaabcbaaacbcbbbabbbaacacbbaaaabccbcbaabbbaaabbcccbcbabababbbcbbbcbb"},
        {"aaaaaaaaaaaa","aaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaa"}
    };
    

    vector< bool > answers {
        true,
        false
    };
    int i = 3;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = isInterleave::Solution().isInterleave(p[i][0], p[i][1], p[i][2]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
