// numRabbits.cpp
// leetcode
//
// Created by  Song Ding on 9/5/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numRabbits {

class Solution {
public:
    /**
     * answers of same number can be in one color group. However,
     * there are cases where more answers than group count, then
     * the answers have to be divided into multiple group.
     */
    int numRabbits(vector<int>& answers) {
        vector<int> counts(1000, 0);
        for (int i : answers) {
            ++counts[i];
        }
        
        int res = 0;
        for (int i = 0; i < 1000; ++i) {
            res += (counts[i] + i) / (i + 1) * (i + 1);
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> answers {
        10,10,10
    };
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = numRabbits::Solution().numRabbits(answers);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
