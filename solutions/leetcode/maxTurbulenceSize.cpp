// maxTurbulenceSize.cpp
// leetcode
//
// Created by  Song Ding on 5/14/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxTurbulenceSize {
/*
 978. Longest Turbulent Subarray
 Medium
 
 79
 
 38
 
 Favorite
 
 Share
 A subarray A[i], A[i+1], ..., A[j] of A is said to be turbulent if and only if:
 
 For i <= k < j, A[k] > A[k+1] when k is odd, and A[k] < A[k+1] when k is even;
 OR, for i <= k < j, A[k] > A[k+1] when k is even, and A[k] < A[k+1] when k is odd.
 That is, the subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.
 
 Return the length of a maximum size turbulent subarray of A.
 
 
 
 Example 1:
 
 Input: [9,4,2,10,7,8,8,1,9]
 Output: 5
 Explanation: (A[1] > A[2] < A[3] > A[4] < A[5])
 Example 2:
 
 Input: [4,8,12,16]
 Output: 2
 Example 3:
 
 Input: [100]
 Output: 1
 
 
 Note:
 
 1 <= A.length <= 40000
 0 <= A[i] <= 10^9
 */
class Solution {
public:
    /**
     * For each i from 0 to n - 1, let ts(i) = max size of turbulent
     * subarray ending at A[i].
     * ts(i) = ts(i-1)+1 if A[i] has same relation with A[i-1] as A[i-2]
     * or 2 if not
     */
    int maxTurbulenceSize(vector<int>& A) {
        int n = A.size();
        if (n <= 1) {
            return 1;
        }
        
        int res = 1;
        int ts = 1;
        if (A[0] != A[1]) {
            ts = res = 2;
        }
        for (int i = 2; i < n; ++i) {
            if ((A[i] > A[i-1] && A[i-2] > A[i-1])
                || (A[i] < A[i-1] && A[i-2] < A[i-1])) {
                ts += 1;
                if (ts > res) {
                    res = ts;
                }
            } else {
                ts = 2;
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<int> > p {
        {9,4,2,10,7,8,8,1,9},
        {4,8,12,16},
        {100},
        {9,9},
        {100,100,100}
    };

    vector< int  > answers {
        5,
        2,
        1,
        1,
        1
    };
    int i = 4;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = maxTurbulenceSize::Solution().maxTurbulenceSize(p[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
