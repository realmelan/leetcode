// smallestRepunitDivByK.cpp
// leetcode
//
// Created by  Song Ding on 4/25/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace smallestRepunitDivByK {

class Solution {
public:
    int smallestRepunitDivByK(int K) {
        int lastMod = 1;
        int lastSumOfMods = 1;
        unordered_set<long> visited {K+1};
        int res = 1;
        while (lastSumOfMods % K != 0) {
            ++res;
            lastMod *= 10;
            lastMod %= K;
            lastSumOfMods += lastMod;
            lastSumOfMods %= K;
            
            if (lastSumOfMods == 0) {
                return res;
            }
            
            long cid = id(lastMod, lastSumOfMods, K);
            if (visited.find(cid) != visited.end()) {
                return -1;
            } else {
                visited.insert(cid);
            }
        }
        return res;
    }

private:
    long id(int lastMod, int lastSumOfMods, int K) {
        return (long)lastMod * K + lastSumOfMods;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> K {
        1,
        2,
        3,
        49991
    };

    vector< int  > answers {
        1,
        -1,
        3,
        4999
    };
    int i = 3;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = smallestRepunitDivByK::Solution().smallestRepunitDivByK(K[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
