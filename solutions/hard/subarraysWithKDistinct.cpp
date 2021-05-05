// subarraysWithKDistinct.cpp
// leetcode
//
// Created by  Song Ding on 9/18/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace subarraysWithKDistinct {
/*
// TODO: copy problem statement here
 992. Subarrays with K Different Integers
 Hard
 
 420
 
 8
 
 Favorite
 
 Share
 Given an array A of positive integers, call a (contiguous, not necessarily distinct) subarray of A good if the number of different integers in that subarray is exactly K.
 
 (For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)
 
 Return the number of good subarrays of A.
 
 
 
 Example 1:
 
 Input: A = [1,2,1,2,3], K = 2
 Output: 7
 Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
 Example 2:
 
 Input: A = [1,2,1,3,4], K = 3
 Output: 3
 Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
 
 
 Note:
 
 1 <= A.length <= 20000
 1 <= A[i] <= A.length
 1 <= K <= A.length
 */

class Solution {
public:
    // https://leetcode.com/problems/subarrays-with-k-different-integers/discuss/523136/JavaC%2B%2BPython-Sliding-Window
    int subarraysWithKDistinct3(vector<int>& A, int K) {
        int n = A.size();
        int l = 0, r = 0, k = 0, prefix = 0, res = 0;
        vector<int> cnt(n+1, 0);
        while (r < A.size()) {
            if (cnt[A[r++]]++ == 0) {
                ++k;
            }
            // when k > K, r points to a char not in A[l..r-1] for the first time
            // Also, l points to a char that appears only once in A[l..r],
            // so move l right to reduce k
            if (k > K) {
                prefix = 0;
                --cnt[A[l++]];
                --k;
            }
            // move l right to a char that appears just once in A[l..r]
            while (cnt[A[l]] > 1) {
                --cnt[A[l++]];
                ++prefix;
            }
            if (k == K) {
                res += prefix + 1;
            }
        }
        return res;
    }
    
    int subarraysWithKDistinct2(vector<int>& A, int K) {
        int l1 = 0, l2 = 0, r = 0, k1 = 0, k2 = 0, res = 0;
        unordered_map<int, int> cnt1, cnt2;
        while (r < A.size()) {
            if (cnt1[A[r]]++ == 0) {
                ++k1;
            }
            if (cnt2[A[r]]++ == 0) {
                ++k2;
            }
            ++r;
            while (k1 > K) {
                if (--cnt1[A[l1++]] == 0) {
                    --k1;
                }
            }
            while (k2 >= K) {
                if (--cnt2[A[l2++]] == 0) {
                    --k2;
                }
            }
            res += l2 - l1;
        }
        return res;
    }
    /**
     * iteratively for each position i, maintain 2 other position, j, k:
     * such that, [i,j] and [i,k] has K distinct numbers, and j is the min
     * position and k is the max position.
     *
     * Also, for j and k, maintain a count of unique numbers, jcnt and kcnt,
     * and a count map for # of appearances of each number, jmap and kmap.
     *
     * when i advance, update jcnt, kcnt, jmap, kmap accordingly:
     *  if jmap[A[i]] = 0:
     *    --jcnt
     *    move j right until a new unique number is found (update jcnt/jmap)
     *    if j >= k:
     *      k =j; kmap=jmap
     *      move k right until a new unique number is found(update kcnt/kmap)
     *
     *  else:
     *    j,k remain unchanged
     *
     */
    int subarraysWithKDistinct(vector<int>& A, int K) {
        int n = A.size();
        A.push_back(n+1);
        int res = 0;
        // j points to the most left end of range that (i,j) has K distinct numbers
        // k points to the most right end of range that (i,k) has K distinct numbers
        int j = -1, k = -1;
        // jcnt: # of distinct numbers from i to j
        // kcnt: # of distinct numbers from i to k
        int jcnt = 0, kcnt = 0;
        vector<int> jmap(n+2, 0), kmap(n+2, 0);
        for (int i = 0; i <= n-K; ++i) {
            // move j right until jcnt=K
            while (j < n-1 && jcnt < K) {
                ++j;
                if (jmap[A[j]]++ == 0) {
                    ++jcnt;
                }
            }
            if (jcnt < K) {
                break;
            }
            
            // move k right until kcnt = K
            while (k < n && kcnt <= K) {
                ++k;
                if (kmap[A[k]]++ == 0) {
                    ++kcnt;
                }
            }
            
            res += k - j;
            
            // move i right and update
            if (--jmap[A[i]] <= 0) {
                --jcnt;
            }
            if (--kmap[A[i]] <= 0) {
                --kcnt;
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
        vector<int> A;
        int K;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{2,1,1,1,2},1},
        {{1,2,1,2,3}, 2},
        {{1,2,1,3,4}, 3},
        {{2,1,2,1,1}, 3}
    };

    vector< int > answers {
        8,
        7,
        3,
        0
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = subarraysWithKDistinct::Solution().subarraysWithKDistinct3(dp.A, dp.K);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
