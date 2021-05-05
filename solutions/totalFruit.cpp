// totalFruit.cpp
// leetcode
//
// Created by  Song Ding on 10/4/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace totalFruit {

class Solution {
public:
    /**
     * This is to find the longest subarray of just two elements.
     */
    int totalFruit(vector<int>& tree) {
        int n = tree.size();
        if (n <= 2) {
            return n;
        }
        
        int res = 0;
        int ia = 0;
        int ta = tree[0];
        int ca = 0;
        while (ia < n && tree[ia] == ta) {
            ++ia;
            ++ca;
        }
        if (ia >= n) {
            return ca;
        }
        int tb = tree[ia];
        int ib = ia;
        int cb = 1;
        --ia;
        int i = ib + 1;
        while (i < n) {
            if (tree[i] == ta) {
                ia = i;
                ++ca;
            } else if (tree[i] == tb) {
                ++cb;
                ib = i;
            } else {
                if (res < ca + cb) {
                    res = ca + cb;
                }
                
                if (ia == i - 1) {
                    tb = tree[i];
                    cb = 1;
                    ca = ia - ib;
                    ib = i;
                } else {
                    ta = tree[i];
                    ca = 1;
                    cb = ib - ia;
                    ia = i;
                }
            }
            ++i;
        }
        if (res < ca + cb) {
            res = ca + cb;
        }
        return res;
        
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> trees {3,3,3,1,2,1,1,2,3,3,4};

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = totalFruit::Solution().totalFruit(trees);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
