//
//  getMoneyAmount.cpp
//  leetcode
//
//  Created by  Song Ding on 12/11/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace getMoneyAmount {
    class Solution {
    public:
        /**
         Instintion: using half-half search might not be that efficient
         in terms of pay.
         apparent 2:1 division for n of 10 would be better.
         Question: how to find this rate for every step.
         
         We can start from array length of 1, and then up to n.
         For each length, loop through all possible first layer divisions
         to find which first layer division gives minimal pay.
         This is DP.
         */
        int getMoneyAmount(int n) {
            // each vector<int> element is for a fixed length, of 0, 1, ...
            vector<vector<int>> res(n + 1);
            res[1].resize(n + 1, 0);
            res[2].resize(n, 0);
            for (int i = 1; i < n; ++i) {
                res[2][i] = i;
            }
            res[3].resize(n - 1, 0);
            for (int i = 1; i < n - 1; ++i) {
                res[3][i] = i + 1;
            }
            for (int i = 4; i <= n; ++i) {
                res[i].resize(n + 2 - i, 0);
                for (int j = 1; j < n + 2 - i; ++j) {
                    int t = res[1][j] + res[i - 1][j + 1];
                    for (int d = 2; d < i; ++d) {
                        if (res[d][j] + res[i - d][j + d] > t) {
                            t = res[d][j] + res[i - d][j + d];
                        }
                    } // end loop of possible division of sub array of length i
                    res[i][j] = t;
                } // end loop of starting index of length i
            } // end loop of sub array of length i;
            return res[n][1];
        }
    };
}
/*
int main() {
    cout << getMoneyAmount::Solution().getMoneyAmount(10) << endl;
    return 0;
}
 //*/
