//
//  hasAllCodes.cpp
//  leetcode
//
//  Created by Song Ding on 3/14/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace hasAllCodes {
/*
// TODO: copy problem statement here

*/
class Solution {
public:
    // TODO: copy function signature here
    bool hasAllCodes(string s, int k) {
        int n = s.size();
        if (n-k+1 < 1<<k) {
            return false;
        }
        int mask = (1<<k) - 1;
        bitset<1<<20> bs(string(1<<k,'1'));
        int cur = 0, i = 0;
        for (; i < k-1; ++i) {
            cur <<= 1;
            cur += s[i] - '0';
        }
        for (i = k-1; i < n; ++i) {
            cur <<= 1;
            cur &= mask;
            cur += s[i] - '0';
            bs.reset(cur);
            
        }
        return bs.none();
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        string s;
        int k;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        //{"00110110",2},
        {"00000000010011101",4},
    };
    // TODO: provide expected results here
    vector<bool> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = hasAllCodes::Solution().hasAllCodes(dp.s, dp.k);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
