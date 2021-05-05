// largestOverlap.cpp
// leetcode
//
// Created by  Song Ding on 6/18/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace largestOverlap {
/*
// TODO: copy problem statement here
 835. Image Overlap
 Medium
 
 190
 
 274
 
 Favorite
 
 Share
 Two images A and B are given, represented as binary, square matrices of the same size.  (A binary matrix has only 0s and 1s as values.)
 
 We translate one image however we choose (sliding it left, right, up, or down any number of units), and place it on top of the other image.  After, the overlap of this translation is the number of positions that have a 1 in both images.
 
 (Note also that a translation does not include any kind of rotation.)
 
 What is the largest possible overlap?
 
 Example 1:
 
 Input: A = [[1,1,0],
 [0,1,0],
 [0,1,0]]
 B = [[0,0,0],
 [0,1,1],
 [0,0,1]]
 Output: 3
 Explanation: We slide A to right by 1 unit and down by 1 unit.
 Notes:
 
 1 <= A.length = A[0].length = B.length = B[0].length <= 30
 0 <= A[i][j], B[i][j] <= 1
 */

class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();
        int res = 0;
        for (int ik = 1-n; ik <= n-1; ++ik) {
            int i1 = max(ik, 0);
            int i2 = max(-ik, 0);
            for (int jk = 1-n; jk <= n-1; ++jk) {
                int j1 = max(jk, 0);
                int j2 = max(-jk, 0);
                int t = 0;
                for (int i = 0; i < n && i1+i < n && i2+i < n; ++i) {
                    for (int j = 0; j < n && j1+j < n && j2+j < n; ++j) {
                        t += (img1[i1+i][j1+j] & img2[i2+i][j2+j]);
                    }
                }
                res = max(res, t);
            }
        }
        return res;
    }
    /**
     * Brutal force, as each relative position change would require comparison of
     *  all overlapped cells.
     *
     * However, some pruning can be used to bypass some overlaps, whose max overlap
     * is no larger than current known max overlap.
     *
     * To know the overlap upper bound of each relative psoition, # of cells having value
     * 1 be computed for rectangles starting from each corner, for both images.
     */
    int largestOverlap2(vector<vector<int>>& A, vector<vector<int>>& B) {
        int n = A.size();
        vector<vector<vector<int>>> asums(4), bsums(4);
        
        vector<vector<int>> sps{{0,0},{0,n-1},{n-1,0},{n-1,n-1}};
        vector<vector<int>> dirs{{1,1},{1,-1},{-1,1},{-1,-1}};
        // compute sums for a & b
        for (int k = 0; k < 4; ++k) {
            const auto& sp = sps[k];
            const auto& dir = dirs[k];
            asums[k].resize(n);
            bsums[k].resize(n);
            for (int i = sp[0]; i >=0 && i < n; i += dir[0]) {
                if (i != sp[0]) {
                    asums[k][i] = asums[k][i-dir[0]];
                    bsums[k][i] = asums[k][i-dir[0]];
                } else {
                    asums[k][i].resize(n, 0);
                    bsums[k][i].resize(n, 0);
                }
                int ta = 0, tb = 0;
                for (int j = sp[1]; j >= 0 && j < n; j += dir[1]) {
                    ta += A[i][j];
                    tb += B[i][j];
                    asums[k][i][j] += ta;
                    bsums[k][i][j] += tb;
                }
            }
        }
        int upper = INT_MAX;
        int t = 0;
        for (const auto& v : A) {
            for (auto i : v) {
                t += i;
            }
        }
        upper = min(upper, t);
        t = 0;
        for (const auto& v : B) {
            for (auto i : v) {
                t += i;
            }
        }
        upper = min(upper, t);
        
        int res = 0;
        // compute overlap
        // fix A, and move the position of the first cell(0,0)
        for (int mi = 1-n; mi < n && res < upper; ++mi) {
            for (int mj = 1-n; mj < n && res < upper; ++mj) {
                // TODO: determin asi based on ai aj, bi bj
                int as = 0;
                int asi = 0, asj = 0;
                int bsi = 0, bsj = 0;
                
                // compute ai aj and bi bj
                int ai = max(0, mi);
                int bi = max(0, -mi);
                
                int aj = max(0, mj);
                int bj = max(0, -mj);
                
                // TOOD: figure out!
                if (mi < 0) {
                    if (mj <= 0) {
                        as = 0;
                        bsi = bi;
                        bsj = bj;
                        asi = n - 1 - bsi;
                        asj = n - 1 - bsj;
                    } else {
                        as = 1;
                        asi = ai;
                        bsj = bj;
                        asj = n - 1 - bsj;
                        bsi = n - 1 - asi;
                    }
                } else {
                    if (mj <= 0) {
                        as = 2;
                        asi = ai;
                        bsj = bj;
                        bsi = n - 1 - asi;
                        asj = n - 1 - bsj;
                    } else {
                        as = 3;
                        asi = ai;
                        asj = aj;
                        bsi = n - 1 - asi;
                        bsj = n - 1 - asj;
                    }
                }
                
                int bs = 3 - as;
                int up = min(asums[as][asi][asj], bsums[bs][bsi][bsj]);
                if (up <= res) {
                    continue;
                }
                
                int over = 0;
                for (; ai < n && bi < n; ++ai, ++bi) {
                    for (int ajj = aj, bjj = bj ; ajj < n && bjj < n; ++ajj, ++bjj) {
                        if (A[ai][ajj] && B[bi][bjj]) {
                            ++over;
                        }
                    }
                }
                
                res = max(res, over);
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
        {{{1,1,0}, {0,1,0}, {0,1,0}}, {{0,0,0}, {0,1,1}, {0,0,1}}},
        {{{1}},{{1}}},
        {{{1,0},{0,0}}, {{0,1},{1,0}}},
        {{{0,0,0,0,0},{0,1,0,0,0},{0,0,1,0,0},{0,0,0,0,1},{0,1,0,0,1}}, {{1,0,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{0,1,1,1,1},{1,0,1,1,1}}}
    };

    vector< int > answers {
        3,
        1,
        1,
        5
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = largestOverlap::Solution().largestOverlap(dp.A, dp.B);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
