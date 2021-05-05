//
//  spiralOrder.cpp
//  leetcode
//
//  Created by  Song Ding on 1/11/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace spiralOrder {
    class Solution {
    public:
        /**
         The matrix can be seen as circles of numbers.
         Reading each circle is the same.
         */
        vector<int> spiralOrder(vector<vector<int>>& matrix) {
            vector<int> res;
            int row = matrix.size();
            if (row <= 0) {
                return res;
            }
            int column = matrix[0].size();
            if (column <= 0) {
                return res;
            }
            
            int rc = row, cc = column;
            int rs = 0, cs = 0; // step of 2
            while (rc > 1 && cc > 1) {
                // start from (rs, cs)
                int i = rs;
                int j = cs;
                
                // move right
                for (; j < column - cs; ++j) {
                    res.push_back(matrix[i][j]);
                }
                --j;

                // move down
                for (++i; i < row - rs; ++i) {
                    res.push_back(matrix[i][j]);
                }
                --i;
                
                // move left
                for (--j; j >= cs; --j) {
                    res.push_back(matrix[i][j]);
                }
                ++j;
                
                // move up
                for (--i; i > rs; --i) {
                    res.push_back(matrix[i][j]);
                }
                
                rc -= 2;
                cc -= 2;
                ++rs;
                ++cs;
            }
            if (rc == 1) {
                for (int j = cs; j < column - cs; ++j) {
                    res.push_back(matrix[rs][j]);
                }
            }
            if (cc == 1) {
                for (int i = rs; i < row - rs; ++i) {
                    res.push_back(matrix[i][cs]);
                }
            }
            return res;
        }
    };
}

/*
int main() {
    vector<vector<int>> matrix{
        {1,2,3,3,4},
        {4,5,6,5,6},
        {7,8,9,9,0}
    };
    vector<int> res = spiralOrder::Solution().spiralOrder(matrix);
    for (auto i : res) {
        cout << i << ",";
    }
    cout << endl;
}
 */
