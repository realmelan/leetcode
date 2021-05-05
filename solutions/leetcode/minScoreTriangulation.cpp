// minScoreTriangulation.cpp
// leetcode
//
// Created by  Song Ding on 6/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minScoreTriangulation {
/*
// TODO: copy problem statement here
 1039. Minimum Score Triangulation of Polygon
 Medium
 
 146
 
 18
 
 Favorite
 
 Share
 Given N, consider a convex N-sided polygon with vertices labelled A[0], A[i], ..., A[N-1] in clockwise order.
 
 Suppose you triangulate the polygon into N-2 triangles.  For each triangle, the value of that triangle is the product of the labels of the vertices, and the total score of the triangulation is the sum of these values over all N-2 triangles in the triangulation.
 
 Return the smallest possible total score that you can achieve with some triangulation of the polygon.
 
 
 
 Example 1:
 
 Input: [1,2,3]
 Output: 6
 Explanation: The polygon is already triangulated, and the score of the only triangle is 6.
 Example 2:
 
 
 
 Input: [3,7,4,5]
 Output: 144
 Explanation: There are two triangulations, with possible scores: 3*7*5 + 4*5*7 = 245, or 3*4*5 + 3*4*7 = 144.  The minimum score is 144.
 Example 3:
 
 Input: [1,3,1,4,1,5]
 Output: 13
 Explanation: The minimum score triangulation has score 1*1*3 + 1*1*4 + 1*1*5 + 1*1*1 = 13.
 
 
 Note:
 
 3 <= A.length <= 50
 1 <= A[i] <= 100
 */

class Solution {
public:
    /**
     * let ms(i,j) = min score for A[i] to A[j], with A[i] A[j] connected.
     * then ms(i,j) = min(ms(i,k)+ms(k,j)+A[i]*A[j]*A[k] for i < k < j)
     *
     */
    int minScoreTriangulation(vector<int>& A) {
        int n = A.size();
        vector<vector<int>> ms(n);
        for (auto& v : ms) {
            v.resize(n, 0);
        }
        for (int l = 3; l <= n; ++l) {
            for (int i = 0; i + l - 1 < n; ++i) {
                int j = i + l - 1;
                ms[i][j] = INT_MAX;
                for (int k = i+1; k < j; ++k) {
                    ms[i][j] = min(ms[i][j], ms[i][k]+ms[k][j]+A[i]*A[j]*A[k]);
                }
            }
        }
        return ms[0][n-1];
    }
    /**
     * let s(i,j,k) = score for triangle(i,j,k)
     * let ms(i,l,j) = min score of vertices, i to i+l-1, and j is not in [i,i+l-1]
     * then ms(i,l,j) = min(s(i,i+l-2,j) + ms(i,l-1,i+l-1), ms(i,k,j)+ms(i+k,l-k,j) for any k in [1,l-1])
     */
    int minScoreTriangulation2(vector<int>& A) {
        int n = A.size();
        // layer 1: vertex id
        // layer 2: # of consecutive vertices
        // layer 3: the other vertex outside of [i, i+l-1]
        vector<vector<vector<int>>> ms(n);
        // l = 2 (2 consecutive vertices)
        for (int i = 0; i < n; ++i) {
            ms[i].resize(n);
            for (int j = (i+2)%n; j != i; ++j,j%=n) {
                ms[i][2].resize(n, 0);
                ms[i][2][j] = score(i,(i+1)%n,j, A);
            }
        }
        for (int l = 3; l < n; ++l) {
            for (int i = 0; i < n; ++i) { //start node
                ms[i][l].resize(n, 0);
                for (int j = (i+l)%n; j != i; ++j,j%=n) {
                    ms[i][l][j] = score(i,(i+l-1)%n,j, A) + ms[i][l-1][(i+l-1)%n];
                    for (int k = 2; k < l; ++k) {
                        ms[i][l][j] = min(ms[i][l][j], ms[i][k][j]+ms[(i+k-1)%n][l-k+1][j]);
                    }
                }
            }
        }
        return ms[0][n-1][n-1];
    }

private:
    int score(int i, int j, int k, const vector<int>& A) {
        return A[i]*A[j]*A[k];
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> A;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3}},
        {{3,7,4,5}},
        {{1,3,1,4,1,5}}
        
    };

    vector< int > answers {
        6,
        144,
        13
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minScoreTriangulation::Solution().minScoreTriangulation(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
