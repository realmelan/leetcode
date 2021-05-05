// flipgame.cpp
// leetcode
//
// Created by  Song Ding on 6/15/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace flipgame {

class Solution {
public:
    /**
     * remove all cards that have same number on front and back.
     * find the smallest number among the left cards.
     */
    int flipgame(vector<int>& fronts, vector<int>& backs) {
        int n = fronts.size();
        unordered_set<int> dups;
        for (int i = 0; i < n; ++i) {
            if (fronts[i] == backs[i]) {
                dups.insert(fronts[i]);
            }
        }
        int min = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (dups.find(fronts[i]) == dups.end()) {
                if (fronts[i] < min) {
                    min = fronts[i];
                }
            }
            if (dups.find(backs[i]) == dups.end()) {
                if (backs[i] < min) {
                    min = backs[i];
                }
            }
        }
        if (min == INT_MAX) {
            return 0;
        }
        return min;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> fronts {1,2,4,4,7};
    vector<int> backs {1,3,4,1,3};

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = flipgame::Solution().flipgame(fronts, backs);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
