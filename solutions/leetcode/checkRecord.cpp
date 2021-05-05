// checkRecord.cpp
// leetcode
//
// Created by  Song Ding on 11/1/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace checkRecord {

class Solution {
public:
    /**
     * Let r(i, 1, 'A') = # of rewardable records when the i-th record is 'A'
     *     r(i, 0, 'P') = # of rewardable records when the i-th record is 'P'.
     *     r(i, 0, 'L') = # of rewardable records when the i-th record is 'L'.
     *
     * The second index indicate whether the rewardable record has 'A' or not.
     *
     * Then:
     *  r(i, 1, 'A') = r(i-1, 0, 'P') + r(i-1, 0, 'L')
     *  r(i, 1, 'L') = r(i-1, 1, 'A') + r(i-1, 1, 'P') + r(i-2, 1, 'A') + r(i-2, 1, 'P')
     *  r(i, 1, 'P') = r(i-1, 1, 'A') + r(i-1, 1, 'L') + r(i-1, 1, 'P')
     *  r(i, 0, 'L') = r(i-1, 0, 'P') + r(i-2, 0, 'L')
     *  r(i, 0, 'P') = r(i-1, 0, 'P') + r(i-1, 0, 'P')
     *
     * Initial values:
     *  r(1, 1, 'A') = 1
     *  r(1, 0, 'L') = 1
     *  r(1, 0, 'P') = 1
     *  r(2, 1, 'A') = 2
     *  r(2, 1, 'L') = 1
     *  r(2, 1, 'P') = 1
     *  r(2, 0, 'L') = 2
     *  r(2, 0, 'P') = 2
     *
     */
    int checkRecord(int n) {
        vector<vector<vector<long>>> res(2, vector<vector<long>>(2));
        for (auto& v : res) {
            for (auto& vv : v) {
                vv.resize(3, 0);
            }
        }
        // for n = 1
        res[1][0][0] = 0;
        res[1][0][1] = 1;
        res[1][0][2] = 1;
        res[1][1][0] = 1;
        res[1][1][1] = 0;
        res[1][1][2] = 0;
        
        // for n = 2;
        res[0][0][0] = 0;
        res[0][0][1] = 2;
        res[0][0][2] = 2;
        res[0][1][0] = 2;
        res[0][1][1] = 1;
        res[0][1][2] = 1;
        
        if (n == 1) {
            return 3;
        }
        
        for (int k = 3; k <= n; ++k) {
            vector<vector<long>> next(2);
            for (auto& v : next) {
                v.resize(3, 0);
            }
            next[1][0] = (res[0][0][1] + res[0][0][2]) % mod;
            next[1][1] = (res[0][1][0] + res[0][1][2] + res[1][1][0] + res[1][1][2]) % mod;
            next[1][2] = (res[0][1][0] + res[0][1][1] + res[0][1][2]) % mod;
            next[0][1] = (res[0][0][2] + res[1][0][2]) % mod;
            next[0][2] = (res[0][0][1] + res[0][0][2]) % mod;
            
            res[1].swap(res[0]);
            res[0].swap(next);
        }
        long sum = 0;
        for (const auto& v : res[0]) {
            for (auto i : v) {
                sum += i;
            }
        }
        return sum % mod;
    }

private:
    static const int mod = 1000000007;
    int charToId(char c) {
        switch (c) {
            case 'A' : return 0;
            case 'L' : return 1;
            case 'P' : return 2;
        }
        return 2;
    }
    
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int n = 2;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = checkRecord::Solution().checkRecord(n);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
