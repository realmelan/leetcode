// minFlipsMonoIncr.cpp
// leetcode
//
// Created by  Song Ding on 5/21/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minFlipsMonoIncr {
/*
// TODO: copy problem statement here
 926. Flip String to Monotone Increasing
 Medium
 
 299
 
 13
 
 Favorite
 
 Share
 A string of '0's and '1's is monotone increasing if it consists of some number of '0's (possibly 0), followed by some number of '1's (also possibly 0.)
 
 We are given a string S of '0's and '1's, and we may flip any '0' to a '1' or a '1' to a '0'.
 
 Return the minimum number of flips to make S monotone increasing.
 
 
 
 Example 1:
 
 Input: "00110"
 Output: 1
 Explanation: We flip the last digit to get 00111.
 Example 2:
 
 Input: "010110"
 Output: 2
 Explanation: We flip to get 011111, or alternatively 000111.
 Example 3:
 
 Input: "00011000"
 Output: 2
 Explanation: We flip to get 00000000.
 
 
 Note:
 
 1 <= S.length <= 20000
 S only consists of '0' and '1' characters.
 */

class Solution {
public:
    /**
     * For each position i, let zero[i] = # of flips to make S[0..i] all 0;
     * let one[i] = # of flips to make S[i..n] all 1.
     *
     * Loop through all positions and find min(zero[i] + one[i+1]).
     */
    int minFlipsMonoIncr(string S) {
        int n = S.size();
        vector<int> zero(n), one(n);
        int cnt0 = 0;
        int cnt1 = 0;
        for (int i = 0; i < n; ++i) {
            if (S[i] == '1') {
                ++cnt1;
            }
            zero[i] = cnt1;
            
            if (S[n-1-i] == '0') {
                ++cnt0;
            }
            one[n-1-i] = cnt0;
        }
        
        int res = min(zero[n-1], one[0]);
        for (int i = 0; i < n - 1; ++i) {
            res = min(res, zero[i] + one[i+1]);
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string S;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"00110"},
        {"010110"},
        {"00011000"}
    };

    vector< int > answers {
        1,
        2,
        2
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minFlipsMonoIncr::Solution().minFlipsMonoIncr(dp.S);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
