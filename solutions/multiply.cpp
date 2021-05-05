// multiply.cpp
// leetcode
//
// Created by  Song Ding on 10/31/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace multiply {
/*
// TODO: copy problem statement here
 311. Sparse Matrix Multiplication

 Given two sparse matrices A and B, return the result of AB.

 You may assume that A\'s column number is equal to B\'s row number.

 Example:

 A = [
   [ 1, 0, 0],
   [-1, 0, 3]
 ]

 B = [
   [ 7, 0, 0 ],
   [ 0, 0, 0 ],
   [ 0, 0, 1 ]
 ]


      |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
 AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                   | 0 0 1 |
 */

class Solution {
public:
    /**
     * find out positions in A and B that are non zero, and multiply them and add the result to the result matrix.
     */
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        int na = A.size(), ma = A[0].size(), nb = B.size(), mb = B[0].size();
        vector<vector<int>> res(na, vector<int>(mb, 0));
        // A: row -> col -> value
        // B: col -> row -> value
        unordered_map<int, unordered_map<int, int>> ap, bp;
        for (int i = 0; i < na; ++i) {
            for (int j = 0; j < ma; ++j) {
                if (A[i][j]) {
                    ap[i][j] = A[i][j];
                }
            }
        }
        for (int i = 0; i < nb; ++i) {
            for (int j = 0; j < mb; ++j) {
                if (B[i][j]) {
                    bp[j][i] = B[i][j];
                }
            }
        }
        
        for (auto& apr : ap) {
            int ar = apr.first;
            for (auto& apv : apr.second) {
                int ac = apv.first;
                int av = apv.second;
                for (auto& bpv : bp[ac]) {
                    res[ar][bpv.first] += av * bpv.second;
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
        vector<vector<int>> A;
        vector<vector<int>> B;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {
            {{
                { 1, 0, 0},
                {-1, 0, 3},
            }},
            {{
                { 7, 0, 0 },
                { 0, 0, 0 },
                { 0, 0, 1 },
            }},
        },
    };

    vector< vector<vector<int>> > answers {
        {
            {7,0,0},
            {-7,0,3},
        }
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = multiply::Solution().multiply(dp.A, dp.B);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
