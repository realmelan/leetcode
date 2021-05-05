// findLonelyPixel.cpp
// leetcode
//
// Created by  Song Ding on 10/23/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findLonelyPixel {
/*
// TODO: copy problem statement here
 531. Lonely Pixel I

 Given a picture consisting of black and white pixels, find the number of black lonely pixels.

 The picture is represented by a 2D char array consisting of \'B\' and \'W\', which means black and white pixels respectively.

 A black lonely pixel is character \'B\' that located at a specific position where the same row and same column don\'t have any other black pixels.

 Example:

 Input:
 [[\'W\', \'W\', \'B\'],
  [\'W\', \'B\', \'W\'],
  [\'B\', \'W\', \'W\']]

 Output: 3
 Explanation: All the three \'B\'s are black lonely pixels.
 Note:

 The range of width and height of the input 2D array is [1,500].
 */

class Solution {
public:
    /**
     * Use a map to recrod candidate pixels and remove/add when scanning each row.
     * use a vector to record the # of B's after scanning each line:
     *  if current column has only 1 B, then if current row has only 1 B then it is a candidate
     *  else remove candiate from candidate map based on the column.
     */
    int findLonelyPixel(vector<vector<char>>& picture) {
        int n = picture.size();
        int m = picture[0].size();
        unordered_map<int,int> cand;
        vector<int> bcnt(m, 0);
        for (int i = 0; i < n; ++i) {
            int bj = -1;
            for (int j = 0; j < m; ++j) {
                if (picture[i][j] == 'B') {
                    ++bcnt[j];
                    if (bj == -1) {
                        bj = j;
                    } else {
                        bj = m;
                    }
                }
            }
            if (bj >= 0 && bj < m) {
                cand[bj] = i;
            }
        }
        int res = 0;
        for (auto p : cand) {
            if (bcnt[p.first] == 1) {
                ++res;
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
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{
            {'W', 'W', 'B'},
            {'W', 'B', 'W'},
            {'B', 'W', 'W'}
        }}
    };

    vector< int > answers {
        3,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findLonelyPixel::Solution().findLonelyPixel(dp.picture);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
