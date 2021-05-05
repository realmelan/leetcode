// prevPermOpt1.cpp
// leetcode
//
// Created by  Song Ding on 6/9/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace prevPermOpt1 {
/*
// TODO: copy problem statement here
 1053. Previous Permutation With One Swap
 Medium
 
 34
 
 132
 
 Favorite
 
 Share
 Given an array A of positive integers (not necessarily distinct), return the lexicographically largest permutation that is smaller than A, that can be made with one swap (A swap exchanges the positions of two numbers A[i] and A[j]).  If it cannot be done, then return the same array.
 
 
 
 Example 1:
 
 Input: [3,2,1]
 Output: [3,1,2]
 Explanation: Swapping 2 and 1.
 Example 2:
 
 Input: [1,1,5]
 Output: [1,1,5]
 Explanation: This is already the smallest permutation.
 Example 3:
 
 Input: [1,9,4,6,7]
 Output: [1,7,4,6,9]
 Explanation: Swapping 9 and 7.
 Example 4:
 
 Input: [3,1,1,3]
 Output: [1,3,1,3]
 Explanation: Swapping 1 and 3.
 
 
 Note:
 
 1 <= A.length <= 10000
 1 <= A[i] <= 10000
 */

class Solution {
public:
    /**
     * start from n -1, compare current position, i, and next position(i-1)
     * and see whether A[i] >= A[i-1]:
     *  if yes, move to i-1
     *  else: find j from n-1, such that A[j] is just smaller than A[i];
    *     if there are multiple A[j], then use the last j.
     */
    vector<int> prevPermOpt1(vector<int>& A) {
        int n = A.size();
        int i = n - 2;
        while (i>=0 && A[i] <= A[i+1]) {
            --i;
        }
        if (i >= 0) {
            // find 1st appearance of next value that's just smaller than A[i]
            // this part can be a binary search as A[i+1] to A[n-1] is in increasing order.
            // TODO: complete binary search
            int j = n - 1;
            while (j > i && A[j] >= A[i]) {
                --j;
            }
            while (j > i && A[j] == A[j-1]) {
                --j;
            }
            swap(A[i], A[j]);
        }
        return A;
    }

private:
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
        {{3,2,1}},
        {{1,1,5}},
        {{1,9,4,6,7}},
        {{3,1,1,3}}
    };

    vector< vector<int> > answers {
        {3,1,2},
        {1,1,5},
        {1,7,4,6,9},
        {1,3,1,3}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = prevPermOpt1::Solution().prevPermOpt1(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
