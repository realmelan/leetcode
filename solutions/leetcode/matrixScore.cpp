// matrixScore.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace matrixScore {
/*
// TODO: copy problem statement here
 861. Score After Flipping Matrix
 Medium
 
 254
 
 64
 
 Favorite
 
 Share
 We have a two dimensional matrix A where each value is 0 or 1.
 
 A move consists of choosing any row or column, and toggling each value in that row or column: changing all 0s to 1s, and all 1s to 0s.
 
 After making any number of moves, every row of this matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.
 
 Return the highest possible score.
 
 
 
 Example 1:
 
 Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
 Output: 39
 Explanation:
 Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].
 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
 
 
 Note:
 
 1 <= A.length <= 20
 1 <= A[0].length <= 20
 A[i][j] is 0 or 1.
 */

class Solution {
public:
    /**
     * First of all, turn column 1 into all 1's, because the most significant bit
     * alone is larger than the rest bits.
     *
     * then check the next column and see whether there are more 1's than 0's.
     * if not, flip the column.
     *
     *
     */
    int matrixScore(vector<vector<int>>& A) {
        int n = A.size();
        int nb = A[0].size();
        int res = 0;
        
        for (int i = 0; i < n; ++i) {
            if (A[i][0] == 0) {
                for (int j = 0; j < nb; ++j) {
                    A[i][j] = 1 - A[i][j];
                }
            }
        }
        
        int base = 1 << nb;
        for (int i = 0; i < nb; ++i) {
            base >>= 1;
            int bit1 = 0;
            for (int j = 0; j < n; ++j) {
                bit1 += A[j][i];
            }
            
            res += base * max(n-bit1, bit1);
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
        vector<vector<int>> A;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{0,0,1,1},{1,0,1,0},{1,1,0,0}}}
    };

    vector< int > answers {
        39
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = matrixScore::Solution().matrixScore(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
