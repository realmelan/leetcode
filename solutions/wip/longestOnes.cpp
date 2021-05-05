// longestOnes.cpp
// leetcode
//
// Created by  Song Ding on 5/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace longestOnes {
/*
// TODO: copy problem statement here
 1004. Max Consecutive Ones III
 Medium
 
 196
 
 6
 
 Favorite
 
 Share
 Given an array A of 0s and 1s, we may change up to K values from 0 to 1.
 
 Return the length of the longest (contiguous) subarray that contains only 1s.
 
 
 
 Example 1:
 
 Input: A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
 Output: 6
 Explanation:
 [1,1,1,0,0,1,1,1,1,1,1]
 Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.
 Example 2:
 
 Input: A = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
 Output: 10
 Explanation:
 [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
 Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.
 
 
 Note:
 
 1 <= A.length <= 20000
 0 <= K <= A.length
 A[i] is 0 or 1
 */

class Solution {
public:
    /**
     * keep two pointers, lb, rb, which marks current left and right boundary.
     * Note, only when lb passes a zero, will rb possibly shift right.
     */
    int longestOnes3(vector<int>& A, int K) {
        int n = A.size();
        int lb = 0, rb = 0;
        int cnt = K;
        while (rb < n && (A[rb] || cnt-- > 0)) {
            ++rb;
        }
        int res = rb - lb;
        while (rb < n) {
            while (lb < n && A[lb]) {
                ++lb;
            }
            ++lb; // lb points the 2nd zero
            ++cnt;
            // shift rb right
            ++rb;
            while (rb < n && (A[rb] || cnt-- > 0)) {
                ++rb;
            }
            res = max(res, rb - lb);
        }
        return res;
    }
    /**
     * https://leetcode.com/problems/max-consecutive-ones-iii/discuss/247564/JavaC%2B%2BPython-Sliding-Window
     */
    int longestOnes(vector<int>& A, int K) {
        int j = 0, i = 0;
        for (; i < A.size(); ++i) {
            // always move i right, and update debt.
            if (A[i] == 0) {
                --K;
            }
            // when K < 0, j will always move right, to compensate for borrowed 1's
            // to cover 0's. When j passes a 0, reduce debt.
            // that is, when K < 0, window size will not expand, but keep the same as before.
            // but when K >= 0, window size will expand.
            if (K < 0 && A[j++] == 0) {
                ++K;
            }
        }
        return i - j;
    }
    /**
     * check https://leetcode.com/problems/max-consecutive-ones-iii/discuss/247564/JavaC%2B%2BPython-Sliding-Window
     */
    int longestOnes2(vector<int>& A, int K) {
        int n = A.size();
        vector<int> next1(n+1);
        int id1 = -1;
        vector<int> next0(n+1);
        int id0 = -1;
        for (int i = 0; i < n; ++i) {
            if (A[i] == 0) {
                for (int j = id0 + 1; j <= i; ++j) {
                    next0[j] = i;
                }
                id0 = i;
            } else {
                for (int j = id1 + 1; j <= i; ++j) {
                    next1[j] = i;
                }
                id1 = i;
            }
        }
        for (int i = id0+1; i <= n; ++i) {
            next0[i] = n;
        }
        for (int i = id1+1; i <= n; ++i) {
            next1[i] = n;
        }
        
        int res = 0;
        int start = 0;
        while (start < n) {
            int len = 0;
            int start1 = next1[start];
            int start0 = next0[start1];
            int k = K;
            while (k >= 0 && start0 < n && start1 < n) {
                len += start0 - start1;
                start1 = next1[start0];
                k -= start1 - start0;
                start0 = next0[start1];
            }
            if (k < 0) {
                len += K;
                len = min(len, n);
                res = max(res, len);
            } else {
                len += start0 - start1 + K;
                len = min(len, n);
                res = max(res, len);
                break;
            }
            start = next1[next0[start]];
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
        int K;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,1,1,0,0,0,1,1,1,1,0}, 2},
        {{0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1}, 3},
        {{0,0,0,1},4},
        {{0,0,1,1,1,0,0},0}
    };

    vector< int > answers {
        6,
        10,
        4,
        3
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = longestOnes::Solution().longestOnes3(dp.A, dp.K);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
