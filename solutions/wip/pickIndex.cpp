// pickIndex.cpp
// leetcode
//
// Created by  Song Ding on 6/9/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace pickIndex {
/*
// TODO: copy problem statement here
 528. Random Pick with Weight
 Medium
 
 256
 
 463
 
 Favorite
 
 Share
 Given an array w of positive integers, where w[i] describes the weight of index i, write a function pickIndex which randomly picks an index in proportion to its weight.
 
 Note:
 
 1 <= w.length <= 10000
 1 <= w[i] <= 10^5
 pickIndex will be called at most 10000 times.
 Example 1:
 
 Input:
 ["Solution","pickIndex"]
 [[[1]],[]]
 Output: [null,0]
 Example 2:
 
 Input:
 ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
 [[[1,3]],[],[],[],[],[]]
 Output: [null,0,1,1,1,0]
 Explanation of Input Syntax:
 
 The input is two lists: the subroutines called and their arguments. Solution's constructor has one argument, the array w. pickIndex has no arguments. Arguments are always wrapped with a list, even if there aren't any.
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    Solution(vector<int>& w) {
        
    }
    
    int pickIndex() {
        return 0;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {}
    };

    vector<  > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = pickIndex::Solution().pickIndex(dp.);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
