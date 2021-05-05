//
//  probabilityOfHeads.cpp
//  leetcode
//
//  Created by Song Ding on 9/11/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace probabilityOfHeads {
/*
// TODO: copy problem statement here
 LeetCode 1230. Toss Strange Coins
  
 You have some coins.  The i-th coin has a probability prob[i] of facing heads when tossed.

 Return the probability that the number of coins facing heads equals target if you toss every coin exactly once.

 Example 1:

 Input: prob = [0.4], target = 1
 Output: 0.40000
 Example 2:

 Input: prob = [0.5,0.5,0.5,0.5,0.5], target = 0
 Output: 0.03125
 Constraints:

 1 <= prob.length <= 1000
 0 <= prob[i] <= 1
 0 <= target <= prob.length
 Answers will be accepted as correct if they are within 10^-5 of the correct answer.
*/
class Solution {
public:
    // TODO: copy function signature here
    double probabilityOfHeads(vector<double>& prob, int target) {
        vector<double> fhp(1,1); // 0 facing head at prob of 1
        for (auto p : prob) {
            fhp.push_back(0);
            for (int i = max(target, (int)fhp.size()); i >= 0; --i) {
                fhp[i] = p * fhp[i-1] + (1-p) * fhp[i];
            }
        }
        return fhp[target];
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<double> prob;
        int target;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{0.4}, 1},
        {{0.5,0.5,0.5,0.5,0.5}, 0},
    };
    // TODO: provide expected results here
    vector<double> answers {
        0.4,
        0.03125,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = probabilityOfHeads::Solution().probabilityOfHeads(dp.prob, dp.target);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
