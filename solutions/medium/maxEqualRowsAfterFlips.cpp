// maxEqualRowsAfterFlips.cpp
// leetcode
//
// Created by  Song Ding on 6/11/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxEqualRowsAfterFlips {
/*
// TODO: copy problem statement here
 1072. Flip Columns For Maximum Number of Equal Rows
 Medium
 
 80
 
 7
 
 Favorite
 
 Share
 Given a matrix consisting of 0s and 1s, we may choose any number of columns in the matrix and flip every cell in that column.  Flipping a cell changes the value of that cell from 0 to 1 or from 1 to 0.
 
 Return the maximum number of rows that have all values equal after some number of flips.
 
 
 
 Example 1:
 
 Input: [[0,1],[1,1]]
 Output: 1
 Explanation: After flipping no values, 1 row has all values equal.
 Example 2:
 
 Input: [[0,1],[1,0]]
 Output: 2
 Explanation: After flipping values in the first column, both rows have equal values.
 Example 3:
 
 Input: [[0,0,0],[0,0,1],[1,1,0]]
 Output: 2
 Explanation: After flipping values in the first two columns, the last two rows have equal values.
 
 
 Note:
 
 1 <= matrix.length <= 300
 1 <= matrix[i].length <= 300
 All matrix[i].length's are equal
 matrix[i][j] is 0 or 1
 */

class Solution {
public:
    /**
     * for each row, find columns to flip to transform it to all 0's or 1's.
     * count the flip using a map.
     */
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int r = matrix.size();
        int c = matrix[0].size();
        
        unordered_map<vector<int>, int, vhash> count;
        for (int i = 0; i < r; ++i) {
            if (matrix[i][0] == 1) {
                for (int j = 0; j < c; ++j) {
                    matrix[i][j] = 1 - matrix[i][j];
                }
            }
        }
        for (const auto& v : matrix) {
            ++count[v];
        }
        
    
        int res = 0;
        for (const auto& p : count) {
            res = max(res, p.second);
        }
        return res;
    }

private:
    struct vhash {
        size_t operator()(const vector<int>& v) const {
            static std::hash<string> h;
            string s;
            s.reserve(v.size());
            for (auto i : v) {
                s.push_back(i + '0');
            }
            return h(s);
        }
    };
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> matrix;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{0,1},{1,1}}},
        {{{0,1},{1,0}}},
        {{{0,0,0},{0,0,1},{1,1,0}}}
    };

    vector< int > answers {
        1,
        2,
        2
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxEqualRowsAfterFlips::Solution().maxEqualRowsAfterFlips(dp.matrix);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
