// randomPickWithBlacklist.cpp
// leetcode
//
// Created by  Song Ding on 11/13/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace randomPickWithBlacklist {

class Solution {
public:
    Solution(int N, vector<int> blacklist) {
        _N = N;
        bl.insert(blacklist.begin(), blacklist.end());
        for (int i = 0; i < N; ++i) {
            if (bl.find(i) == bl.end()) {
                nums.insert(i);
            }
        }
    }
    
    int pick() {
        int n = nums.size();
        int r = n * rand() / RAND_MAX;
        auto it = nums.begin();
        std::advance(it, r);
        int res = *it;
        nums.erase(it);
        
        if (nums.empty()) {
            for (int i = 0; i < _N; ++i) {
                if (bl.find(i) == bl.end()) {
                    nums.insert(i);
                }
            }
        }
        return res;
        
    }

private:
    set<int> nums; // exceed memory.
    int _N;
    unordered_set<int> bl;
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int N = 1;
    vector<int> blacklist {
        
    };
    randomPickWithBlacklist::Solution sln(N, blacklist);

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    cout << sln.pick() << ", " << sln.pick() << ", " << sln.pick() << endl;
    cout << clock() - tstart << endl;
    return 0;
}
//*/
