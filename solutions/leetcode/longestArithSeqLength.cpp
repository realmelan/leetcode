// longestArithSeqLength.cpp
// leetcode
//
// Created by  Song Ding on 5/15/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace longestArithSeqLength {
/*
 1027. Longest Arithmetic Sequence
 Medium
 
 131
 
 10
 
 Favorite
 
 Share
 Given an array A of integers, return the length of the longest arithmetic subsequence in A.
 
 Recall that a subsequence of A is a list A[i_1], A[i_2], ..., A[i_k] with 0 <= i_1 < i_2 < ... < i_k <= A.length - 1, and that a sequence B is arithmetic if B[i+1] - B[i] are all the same value (for 0 <= i < B.length - 1).
 
 
 
 Example 1:
 
 Input: [3,6,9,12]
 Output: 4
 Explanation:
 The whole array is an arithmetic sequence with steps of length = 3.
 Example 2:
 
 Input: [9,4,7,2,10]
 Output: 3
 Explanation:
 The longest arithmetic subsequence is [4,7,10].
 Example 3:
 
 Input: [20,1,15,3,10,5,8]
 Output: 4
 Explanation:
 The longest arithmetic subsequence is [20,15,10,5].
 
 
 Note:
 
 2 <= A.length <= 2000
 0 <= A[i] <= 10000
 */
class Solution {
public:
    /**
     * for all position i from 0 to n-1, keep all possible subsequence.
     * each subsequence includes the gap and the current length.
     *
     * Thus, for the i-th position, go over the possible subsequences and update
     * any subsequence if there is match; and add new possible subsequences by pairing
     * each of the previous element with the i-th element.
     *
     * To make lookup faster, subsequences are indexed by next element. If there is match,
     * remove the old subsequence and insert a new one with updated next element.
     */
    int longestArithSeqLength(vector<int>& A) {
        int n = A.size();
        int res = 2;
        map<int, map<int, int>> allSub;
        int next = 2 * A[1] - A[0];
        allSub[next].insert(make_pair(A[1] - A[0], 2));
        for (int i = 2; i < n; ++i) {
            auto it = allSub.find(A[i]);
            if (it != allSub.end()) {
                for (auto sit = it->second.begin(); sit != it->second.end(); ++sit) {
                    int gap = sit->first;
                    int expect = A[i] + gap;
                    int len = sit->second + 1;
                    if (len > res) {
                        res = len;
                    }
                    auto nit = allSub.find(expect);
                    if (nit != allSub.end()) {
                        auto pit = nit->second.find(gap);
                        if (pit == nit->second.end()) {
                            nit->second.insert(make_pair(gap, len));
                        } else if (pit->second < len) {
                            pit->second = len;
                        }
                    } else {
                        allSub[expect].insert(make_pair(gap, len));
                    }
                }
            }
            
            for (int j = 0; j < i; ++j) {
                int gap = A[i] - A[j];
                int len = 2;
                int expect = A[i] + gap;
                auto nit = allSub.find(expect);
                if (nit != allSub.end()) {
                    auto pit = nit->second.find(gap);
                    if (pit == nit->second.end()) {
                        nit->second.insert(make_pair(gap, len));
                    }
                } else {
                    allSub[expect].insert(make_pair(gap, len));
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
    // TODO: prepare parameters here
    vector< vector<int> > p {
        {3,6,9,12},
        {9,4,7,2,10},
        {20,1,15,3,10,5,8}
    };

    vector< int  > answers {
        4,
        3,
        4
    };
    int i = 2;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = longestArithSeqLength::Solution().longestArithSeqLength(p[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
