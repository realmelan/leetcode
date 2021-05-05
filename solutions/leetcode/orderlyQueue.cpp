// orderlyQueue.cpp
// leetcode
//
// Created by  Song Ding on 10/11/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace orderlyQueue {

class Solution {
public:
    /**
     * If K >= 2, then it is possible to rearrange the position of
     * consecutive two letters, so that the smaller is before the larger.
     * This way, the whole string can be sorted.
     *
     * If K = 1, then we can only rotate S to see which position gives
     * the smallest string
     */
    string orderlyQueue(string S, int K) {
        string res;
        vector<vector<int>> count(26);
        for (int i = 0; i < S.size(); ++i) {
            count[S[i] - 'a'].push_back(i);
        }
        
        if (K == 1) {
            int i = 0;
            for (; i < 26; ++i) {
                if (count[i].size()) {
                    break;
                }
            }
            
            int idx = count[i].front();
            res.append(S.substr(idx)).append(S.substr(0, idx));
            for (int j = 1; j < count[i].size(); ++j) {
                idx = count[i][j];
                string t(S.substr(idx) + S.substr(0, idx));
                if (t < res) {
                    res = t;
                }
            }
        } else {
            for (int i = 0; i < 26; ++i) {
                if (count[i].size()) {
                    res.append(count[i].size(), 'a' + i);
                }
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
    string S = "baaca";
    int K = 2;
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = orderlyQueue::Solution().orderlyQueue(S, K);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
