// findBlackPixel.cpp
// leetcode
//
// Created by  Song Ding on 10/23/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findBlackPixel {
/*
// TODO: copy problem statement here
 533. Lonely Pixel II

 Given a picture consisting of black and white pixels, and a positive integer N, find the number of black pixels located at some specific row R and column C that align with all the following rules:

 Row R and column C both contain exactly N black pixels.
 For all rows that have a black pixel at column C, they should be exactly the same as row R
 The picture is represented by a 2D char array consisting of \'B\' and \'W\', which means black and white pixels respectively.

 Example:

 Input:
 [[\'W\', \'B\', \'W\', \'B\', \'B\', \'W\'],
  [\'W\', \'B\', \'W\', \'B\', \'B\', \'W\'],
  [\'W\', \'B\', \'W\', \'B\', \'B\', \'W\'],
  [\'W\', \'W\', \'B\', \'W\', \'B\', \'W\']]

 N = 3
 Output: 6
 Explanation: All the bold \'B\' are the black pixels we need (all \'B\'s at column 1 and 3).
         0    1    2    3    4    5         column index
 0    [[\'W\', \'B\', \'W\', \'B\', \'B\', \'W\'],
 1     [\'W\', \'B\', \'W\', \'B\', \'B\', \'W\'],
 2     [\'W\', \'B\', \'W\', \'B\', \'B\', \'W\'],
 3     [\'W\', \'W\', \'B\', \'W\', \'B\', \'W\']]
 row index

 Take \'B\' at row R = 0 and column C = 1 as an example:
 Rule 1, row R = 0 and column C = 1 both have exactly N = 3 black pixels.
 Rule 2, the rows have black pixel at column C = 1 are row 0, row 1 and row 2. They are exactly the same as row R = 0.

 Note:

 The range of width and height of the input 2D array is [1,200].
 */

class Solution {
public:
    /**
     * count # of B's in each column.
     * group rows and for each row group, check the # of B in the row and see whether it matches the # of row in that group.
     *   for each B pixel in the row, check whether the column has exact # of B's as the row count, if so add row count to final result
     *
     */
    int findBlackPixel(vector<vector<char>>& picture, int N) {
        int n = picture.size();
        int m = picture[0].size();
        vector<int> bcnt(m, 0), rcnt(n, 0);
        unordered_map<string, int> rg;
        for (int i = 0; i < n; ++i) {
            string row;
            int cnt = 0;
            for (int j = 0; j < m; ++j) {
                row.push_back(picture[i][j]);
                if (picture[i][j] == 'B') {
                    ++bcnt[j];
                    ++cnt;
                }
            }
            if (cnt == N) {
                ++rg[row];
            }
        }
        int res = 0;
        for (auto& p : rg) {
            if (p.second != N) {
                continue;
            }
            for (int i = 0; i < m; ++i) {
                if (p.first[i] == 'B' && bcnt[i] == N) {
                    res += N;
                }
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<char>> picture;
        int N;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{'W', 'B', 'W', 'B', 'B', 'W'},
            {'W', 'B', 'W', 'B', 'B', 'W'},
            {'W', 'B', 'W', 'B', 'B', 'W'},
            {'W', 'W', 'B', 'W', 'B', 'W'}}, 3},
    };

    vector< int > answers {
        6,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findBlackPixel::Solution().findBlackPixel(dp.picture, dp.N);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
