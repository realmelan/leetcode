// minDeletionSize.cpp
// leetcode
//
// Created by  Song Ding on 9/19/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minDeletionSize {
/*
// TODO: copy problem statement here
 960. Delete Columns to Make Sorted III
 Hard
 
 168
 
 5
 
 Favorite
 
 Share
 We are given an array A of N lowercase letter strings, all of the same length.
 
 Now, we may choose any set of deletion indices, and for each string, we delete all the characters in those indices.
 
 For example, if we have an array A = ["babca","bbazb"] and deletion indices {0, 1, 4}, then the final array after deletions is ["bc","az"].
 
 Suppose we chose a set of deletion indices D such that after deletions, the final array has every element (row) in lexicographic order.
 
 For clarity, A[0] is in lexicographic order (ie. A[0][0] <= A[0][1] <= ... <= A[0][A[0].length - 1]), A[1] is in lexicographic order (ie. A[1][0] <= A[1][1] <= ... <= A[1][A[1].length - 1]), and so on.
 
 Return the minimum possible value of D.length.
 
 
 
 Example 1:
 
 Input: ["babca","bbazb"]
 Output: 3
 Explanation: After deleting columns 0, 1, and 4, the final array is A = ["bc", "az"].
 Both these rows are individually in lexicographic order (ie. A[0][0] <= A[0][1] and A[1][0] <= A[1][1]).
 Note that A[0] > A[1] - the array A isn't necessarily in lexicographic order.
 Example 2:
 
 Input: ["edcba"]
 Output: 4
 Explanation: If we delete less than 4 columns, the only row won't be lexicographically sorted.
 Example 3:
 
 Input: ["ghi","def","abc"]
 Output: 0
 Explanation: All rows are already lexicographically sorted.
 
 
 Note:
 
 1 <= A.length <= 100
 1 <= A[i].length <= 100
 */

class Solution {
public:
    /**
     *
     */
    int minDeletionSize(vector<string>& A) {
        int na = A.size();
        int n = A[0].size();
        vector<vector<bool>> nolarger(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                bool res = true;
                for (int k = 0; res && k < na; ++k) {
                    if (A[k][i] > A[k][j]) {
                        res = false;
                    }
                }
                nolarger[i][j] = res;
            }
        }
        
        int res = 0;
        vector<int> dp(n, 1);
        for (int j = 1; j < n; ++j) {
            for (int i = 0; i < j; ++i) {
                if (nolarger[i][j]) {
                    dp[j] = max(dp[j], dp[i]+1);
                }
            }
            res = max(res, dp[j]);
        }
        return n - res;
    }
    /**
     * find out whether A[i]<A[j] holds for all A strings
     * then use this info to find out longest increasing sequence
     */
    int minDeletionSize_2(vector<string>& A) {
        int n = A[0].size();
        int na = A.size();
        vector<vector<bool>> nolarger(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                bool res = true;
                for (int k = 0; res && k < na; ++k) {
                    if (A[k][i] > A[k][j]) {
                        res = false;
                    }
                }
                nolarger[i][j] = res;
            }
        }
        
        vector<vector<bool>> larger(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                bool res = true;
                for (int k = 0; res && k < na; ++k) {
                    if (A[k][i] <= A[k][j]) {
                        res = false;
                    }
                }
                larger[i][j] = res;
            }
        }
        
        // use nolarger[i][j] and larger[i][j] to build longest sequence
        vector<vector<vector<int>>> seq(1);
        seq[0].push_back({0}); // len=1 seq
        for (int i = 1; i < n; ++i) {
            int ns = seq.size();
            vector<vector<vector<int>>> nseq(ns);
            int iadded = 0; // if i has been added as the tail of a sequence already, skip any shorter ones ending at i
            for (int j = ns-1; j>=0; --j) {
                for (auto& v : seq[j]) { // len = j+1
                    int k2 = v[j];
                    if (larger[k2][i]) { // if A[i] is smaller than len=j+1 seq's last element
                        if (j > iadded) {
                            if (j == 0 || nolarger[v[j-1]][i]) {
                                v.back() = i;
                                iadded = j;
                            }
                        }
                        nseq[j].push_back(v);
                    } else {
                        nseq[j].push_back(v);
                        if (nolarger[k2][i] && j+1 > iadded) { // this might be longer!
                            auto nv(v);
                            nv.push_back(i);
                            if (j+1 == nseq.size()) {
                                nseq.resize(ns+1);
                            }
                            nseq[j+1].push_back(nv);
                            iadded = j+1;
                        }
                    }
                }
            }
            if (!iadded) {
                nseq[0].push_back({i});
            }
            seq.swap(nseq);
        }
        return n - seq.back()[0].size();
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<string> A;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{"babca","bbazb"}},
        {{"edcba"}},
        {{"ghi","def","abc"}},
        {{"abcbcbc","cbacbcb"}},
        {{"babbba","bbaaab"}},
        {{"baabab"}},
        {{"abbabb","babbaa","bbbbbb","babbaa"}},
        {{"aaababaabaababaaabbaaaabbabbbababbaaabbabbbbbabaaaaabbabbbbbaaababaaaaabaaabbbbbaaabbabababaabbaabab","aaaaaaaaaaabbaaaabaaaaabaabaabbbaabaaaaaababbbbabaabababbaabababaaabbabaaaaaaaaabbbaabbabbaaaaaaaabb"}},
    };

    vector< int > answers {
        3,
        4,
        0,
        4,
        3,
        2,
        3,
        57,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minDeletionSize::Solution().minDeletionSize(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
