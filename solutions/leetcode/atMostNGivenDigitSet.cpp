// atMostNGivenDigitSet.cpp
// leetcode
//
// Created by  Song Ding on 12/9/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace atMostNGivenDigitSet {

class Solution {
public:
    /**
     * From the last k digits of N, say K, count # of numbers that have k digits
     * but smaller than K.
     * result would be sum of these #'s.
     */
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        int n = D.size();
        // prepare dict
        vector<int> lt(10);
        set<int> dgts;
        for (int i = 0; i < n; ++i) {
            int d = D[i][0] - '0';
            dgts.insert(d);
            for (int j = d + 1; j < 10; ++j) {
                ++lt[j];
            }
        }
        
        vector<int> nd;
        vector<int> permCnt;
        int res = -1;
        int t = N;
        int c = 1;
        while (t) {
            res += c;
            int d = t % 10;
            nd.push_back(d);
            permCnt.push_back(c);
            t /= 10;
            c *= n;
        }
        
        int i = nd.size() - 1;
        for (; i > 0; --i) {
            int c = lt[nd[i]];
            int d = nd[i];
            res += c * permCnt[i];
            if (dgts.find(d) == dgts.end()) {
                break;
            }
        }
        
        if (i == 0) {
            res += lt[nd[0]];
            if (dgts.find(nd[0]) != dgts.end()) {
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
    vector< vector<string> > D {
        {"1","3","5","7"},
        {"1","4","9"},
        {"1"},
        {"3","4","8"}
    };
    vector<int> N {
        100,
        1000000000,
        1000,
        4
    };

    vector<  int > answers {
        20,
        29523,
        3,
        2
    };
    int i = 0;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = atMostNGivenDigitSet::Solution().atMostNGivenDigitSet(D[i], N[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
