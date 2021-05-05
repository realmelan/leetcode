// findCircleNum.cpp
// leetcode
//
// Created by  Song Ding on 10/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findCircleNum {
/*
// TODO: copy problem statement here
 547. Friend Circles
 Medium

 1283

 104

 Favorite

 Share
 There are N students in a class. Some of them are friends, while some are not. Their friendship is transitive in nature. For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C. And we defined a friend circle is a group of students who are direct or indirect friends.

 Given a N*N matrix M representing the friend relationship between students in the class. If M[i][j] = 1, then the ith and jth students are direct friends with each other, otherwise not. And you have to output the total number of friend circles among all the students.

 Example 1:
 Input:
 [[1,1,0],
  [1,1,0],
  [0,0,1]]
 Output: 2
 Explanation:The 0th and 1st students are direct friends, so they are in a friend circle.
 The 2nd student himself is in a friend circle. So return 2.
 Example 2:
 Input:
 [[1,1,0],
  [1,1,1],
  [0,1,1]]
 Output: 1
 Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends,
 so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.
 Note:
 N is in range [1,200].
 M[i][i] = 1 for all students.
 If M[i][j] = 1, then M[j][i] = 1.
 */

class Solution {
public:
    /**
    Say, for the i-th student, starting from its next friend, j,
    Add the j-th row to the i-th row; Now there might be new friends.
    continue till no friends left for the i-th.
    
    Note, all rows will be iterated just once, thus only N addition.
    Sine each row has at most N elements, thus addition cost is O(n^2).
    
    After addition, searching for new friend starts from next one, thus
    no repeation, thus at most O(n^2).
    
    So computation cost is O(n^2).
    */
    int findCircleNum(vector<vector<int>>& M) {
        int row = M.size();
        int count = 0;
        for (int i = 0; i < row; ++i) {
            if (M[i][i] < 0) {
                continue;
            }
            
            M[i][i] = -1;
            ++count;
            int j = i + 1;
            for (; j < row;) {
                if (M[j][j] <= 0) {
                    ++j;
                    continue;
                }
                if (M[i][j] > 0) {
                    for (int k = i + 1; k < row; ++k) {
                        M[i][k] += M[j][k];
                    }
                    M[j][j] = -1;
                    j = i + 1;
                } else {
                    ++j;
                }
        
            }
        }
        return count;
    }
    /**
     * union-find
     */
    int findCircleNum2(vector<vector<int>>& M) {
        int n = M.size();
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            p[i] = i;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                if (M[i][j]) {
                    int pi = find(i, p);
                    int pj = find(j, p);
                    if (pi < pj) {
                        p[pj] = pi;
                    } else {
                        p[pi] = pj;
                    }
                }
            }
        }
        unordered_set<int> circles;
        for (int i = 0; i < n; ++i) {
            circles.insert(find(i,p));
        }
        return circles.size();
    }

private:
    int find(int i, vector<int>& p) {
        if (i != p[i]) {
            p[i] = find(p[i], p);
        }
        return p[i];
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> M;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{
            {1,1,0},
            {1,1,0},
            {0,0,1}
        }},
        {{
            {1,1,0},
            {1,1,1},
            {0,1,1}
        }}
    };

    vector< int > answers {
        2,
        1
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findCircleNum::Solution().findCircleNum(dp.M);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
