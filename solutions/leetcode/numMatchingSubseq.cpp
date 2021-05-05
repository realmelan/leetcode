// numMatchingSubseq.cpp
// leetcode
//
// Created by  Song Ding on 10/7/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numMatchingSubseq {

class Solution {
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        vector<vector<int>> sv(26);
        for (int i = 0; i < S.size(); ++i){
            sv[S[i] - 'a'].push_back(i);
        }
        
        int res = 0;
        for (const auto& w : words) {
            int si = -1;
            int i = 0;
            for (; i < w.size(); ++i) {
                const auto& sc = sv[w[i] - 'a'];
                auto it = upper_bound(sc.begin(), sc.end(), si);
                if (it == sc.end()) {
                    break;
                }
                si = *it;
            }
            if (i >= w.size()) {
                ++res;
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string S = "abcde";
    vector<string> words {
        "a", "bb", "acd", "ace"
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = numMatchingSubseq::Solution().numMatchingSubseq(S, words);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
