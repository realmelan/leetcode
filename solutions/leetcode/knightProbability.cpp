//
//  knightProbability.cpp
//  leetcode
//
//  Created by  Song Ding on 11/22/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace knightProbability {
    class Solution {
    public:
        /**
         Recursive would timeout. However, bookkeeping may help
         reduce cost.
         */
        double knightProbability(int N, int K, int r, int c) {
            if (N <= 0) {
                return 0;
            } else if (K < 1) {
                if (r >= 0 && r < N && c >= 0 && c < N) {
                    return 1;
                } else {
                    return 0;
                }
            }
            
            static const int moves[][2] = {
                {-2,-1},{-2,1},{-1,2},{-1,-2},
                {2,1},{2,-1},{1,-2},{1,2}
            };
            vector<vector<double>> current(N);
            for (auto& v : current) {
                v.resize(N, 1);
            }
            
            for (int k = 0; k < K; ++k) {
                vector<vector<double>> next(N);
                for (auto& v : next) {
                    v.resize(N, 0);
                }
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        for (int m = 0; m < 8; ++m) {
                            int rn = i - moves[m][0];
                            int cn = j - moves[m][1];
                            if ((rn >= 0 && rn < N)
                                && (cn >= 0 && cn < N)) {
                                next[rn][cn] += current[i][j];
                            }
                        }
                    }
                }
                current.swap(next);
            }
            double res = current[r][c];
            for (int k = 0; k < K; ++k) {
                res /= 8;
            }
            return res;
        }
    };
}
/*
int main() {
    cout << knightProbability::Solution().knightProbability(8, 30, 6, 4) << endl;
    return 0;
}
 */
