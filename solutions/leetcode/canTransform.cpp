// canTransform.cpp
// leetcode
//
// Created by  Song Ding on 9/5/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace canTransform {

class Solution {
public:
    /**
     * Relative order of L/R will not change. Also, 'R' can only move
     * rightward, and 'L' can only move leftward.
     *
     * Two conditions must be met:
     *    1, after stripping 'X', the leftover strings should be equal
     *    2, 'X' on left side of 'L' should only decrease, and 'X' on left
     *        side of 'R' should only increase.
     */
    bool canTransform(string start, string end) {
        if (start.size() != end.size()) {
            return false;
        }
        
        string sstrip;
        string estrip;
        int xcount = 0;
        vector<int> xstart;
        for (char c : start) {
            if (c != 'X') {
                xstart.push_back(xcount);
                sstrip.push_back(c);
            } else {
                ++xcount;
            }
        }
        xstart.push_back(xcount);
        
        xcount = 0;
        vector<int> xend;
        for (char c : end) {
            if (c != 'X') {
                xend.push_back(xcount);
                estrip.push_back(c);
            } else {
                ++xcount;
            }
        }
        xend.push_back(xcount);
        if (estrip != sstrip) {
            return false;
        }
        
        for (int i = 0; i < estrip.size(); ++i) {
            if (estrip[i] == 'L' && xstart[i] < xend[i]) {
                return false;
            } else if (estrip[i] == 'R' && xstart[i] > xend[i]) {
                return false;
            }
        }
        return true;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string start = "XXRXXLXXXX";
    
    string end = "XXXXRXXLXX";

    // TODO: add return type and paramters.
    clock_t start_clock = clock();
    auto res = canTransform::Solution().canTransform(start, end);
    cout << clock() - start_clock << endl;
    cout << res << endl;
    return 0;
}
//*/
