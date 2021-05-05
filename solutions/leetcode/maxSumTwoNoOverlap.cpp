// maxSumTwoNoOverlap.cpp
// leetcode
//
// Created by  Song Ding on 5/27/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxSumTwoNoOverlap {
/*
// TODO: copy problem statement here
 1031. Maximum Sum of Two Non-Overlapping Subarrays
 Medium
 
 136
 
 7
 
 Favorite
 
 Share
 Given an array A of non-negative integers, return the maximum sum of elements in two non-overlapping (contiguous) subarrays, which have lengths L and M.  (For clarification, the L-length subarray could occur before or after the M-length subarray.)
 
 Formally, return the largest V for which V = (A[i] + A[i+1] + ... + A[i+L-1]) + (A[j] + A[j+1] + ... + A[j+M-1]) and either:
 
 0 <= i < i + L - 1 < j < j + M - 1 < A.length, or
 0 <= j < j + M - 1 < i < i + L - 1 < A.length.
 
 
 Example 1:
 
 Input: A = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
 Output: 20
 Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.
 Example 2:
 
 Input: A = [3,8,1,3,2,1,8,9,0], L = 3, M = 2
 Output: 29
 Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9] with length 2.
 Example 3:
 
 Input: A = [2,1,5,6,0,9,5,0,3,8], L = 4, M = 3
 Output: 31
 Explanation: One choice of subarrays is [5,6,0,9] with length 4, and [3,8] with length 3.
 
 
 Note:
 
 L >= 1
 M >= 1
 L + M <= A.length <= 1000
 0 <= A[i] <= 1000
 */

class Solution {
public:
    /**
     * suppose we get L subarray before M subarray first.
     * for i from 0 to n-1:
     *   v[i] = msL(0, i) + msM(i+1, n-1)
     *
     * then it becomes two sub problems:
     * msL(0,i) = max sum of subarray in A[0..i]
     * msM(i,n) = max sum of subarray in A[i..n]
     */
    int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
        
        vector<int> cumSum;
        int n = A.size();
        int s = 0;
        for (auto i : A) {
            s += i;
            cumSum.push_back(s);
        }
        
        vector<int> msL0(n, 0), msLn(n, 0);
        msL0[L-1] = cumSum[L-1];
        for (int i = L; i < n; ++i) {
            msL0[i] = max(msL0[i-1], cumSum[i] - cumSum[i-L]);
        }
        msLn[n-L] = cumSum[n-1] - cumSum[n-L-1];
        for (int i = n-L-1; i > 0; --i) {
            msLn[i] = max(msLn[i+1], cumSum[i+L-1] - cumSum[i-1]);
        }
        msLn[0] = max(msLn[1], cumSum[L-1]);
        
        vector<int> msM0(n, 0), msMn(n, 0);
        msM0[M-1] = cumSum[M-1];
        for (int i = M; i < n; ++i) {
            msM0[i] = max(msM0[i-1], cumSum[i] - cumSum[i-M]);
        }
        msMn[n-M] = cumSum[n-1] - cumSum[n-M-1];
        for (int i = n-M-1; i > 0; --i) {
            msMn[i] = max(msMn[i+1], cumSum[i+M-1] - cumSum[i-1]);
        }
        msMn[0] = max(msMn[1], cumSum[M-1]);
        
        int res = 0;
        // L before M
        for (int i = L-1; i < n - M; ++i) {
            res = max(res, msL0[i] + msMn[i+1]);
        }
        // M before L
        for (int i = M-1; i < n - L; ++i) {
            res =max(res, msM0[i] + msLn[i+1]);
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
        vector<int> A;
        int L;
        int M;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{0,6,5,2,2,5,1,9,4},1,2},
        {{3,8,1,3,2,1,8,9,0},3,2},
        {{2,1,5,6,0,9,5,0,3,8},4,3}
    };

    vector< int > answers {
        20,
        29,
        31
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxSumTwoNoOverlap::Solution().maxSumTwoNoOverlap(dp.A, dp.L, dp.M);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
