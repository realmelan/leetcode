// decodeAtIndex.cpp
// leetcode
//
// Created by  Song Ding on 9/20/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace decodeAtIndex {

class Solution {
public:
    /**
     * get the total length, then recursively
     * reduce K and S.
     *
     */
    string decodeAtIndex(string S, int K) {
        long ul = 1;
        long total = 1;
        stack<pair<long,char>> ulv;
        ulv.push(make_pair(1, S[0]));
        
        int n = S.size();
        int i = 1;
        while (i < n) {
            if (S[i] >= 'a' && S[i] <= 'z') {
                if (S[i-1] >= '0' && S[i-1] <= '9') {
                    ul = total;
                }
                ++ul;
                ulv.push(make_pair(ul, S[i]));
                ++total;
            } else {
                total *= S[i] - '0';
            }
            ++i;
        }
        
        int k = K;
        return charAtIndex(S, ulv, k);
    }

private:
    string charAtIndex(string S, stack<pair<long,char>>& ulv, int k) {
        string res;
        while (ulv.top().first > k) {
            ulv.pop();
        }
        long ul = ulv.top().first;
        if (k == ul) {
            res.push_back(ulv.top().second);
            return res;
        }
        
        k = k % ul;
        if (k == 0) {
            k = ul;
        }
        return charAtIndex(S, ulv, k);
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string S = "leet2code3";
    int K = 6;

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = decodeAtIndex::Solution().decodeAtIndex(S, K);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
