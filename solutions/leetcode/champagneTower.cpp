// champagneTower.cpp
// leetcode
//
// Created by  Song Ding on 5/29/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace champagneTower {

class Solution {
public:
    /**
     * For the target cup, recursively find the height of the upper
     * cups which might flow to it:
     * h(i, j) = [h(i-1, j-1) - 1] + [h(i-1, j) - 1]
     * which means only if h(i-1,j-1) > 1, add its contribution.
     */
    double champagneTower(int poured, int query_row, int query_glass) {
        unordered_map<int, double> memo;
        double res = h(poured, query_row, query_glass, memo);
        if (res > 1) {
            res = 1;
        }
        return res;
    }

private:
    double h(int n, int i, int j, unordered_map<int, double>& memo) {
        if (i == 0) {
            return n;
        }
        
        int id = i * 100 + j;
        auto it = memo.find(id);
        if (it != memo.end()) {
            return it->second;
        }
        
        double r = 0;
        if (j - 1 >= 0) {
            double t = h(n, i - 1, j - 1, memo);
            if (t > 1) {
                r += ((double)t - 1) / 2;
            }
        }
        
        if (j != i) {
            double t = h(n, i - 1, j, memo);
            if (t > 1) {
                r += ((double)t - 1) / 2;
            }
        }
        memo.insert(make_pair(id, r));
        return r;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    //int poured = 100, query_glass = 85, query_row = 39;
    //int poured = 8, query_glass = 0, query_row = 3;
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = champagneTower::Solution().champagneTower(poured, query_row, query_glass);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
