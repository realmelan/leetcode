// sequenceReconstruction.cpp
// leetcode
//
// Created by  Song Ding on 10/28/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace sequenceReconstruction {
/*
// TODO: copy problem statement here
 444. Sequence Reconstruction

 Check whether the original sequence org can be uniquely reconstructed from the sequences in seqs. The org sequence is a permutation of the integers from 1 to n, with 1 ≤ n ≤ 104. Reconstruction means building a shortest common supersequence of the sequences in seqs (i.e., a shortest sequence so that all sequences in seqs are subsequences of it). Determine whether there is only one sequence that can be reconstructed from seqs and it is the org sequence.

 Example 1:

 Input:
 org: [1,2,3], seqs: [[1,2],[1,3]]

 Output:
 false

 Explanation:
 [1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be reconstructed.
 Example 2:

 Input:
 org: [1,2,3], seqs: [[1,2]]

 Output:
 false

 Explanation:
 The reconstructed sequence can only be [1,2].
 Example 3:

 Input:
 org: [1,2,3], seqs: [[1,2],[1,3],[2,3]]

 Output:
 true

 Explanation:
 The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].
 Example 4:

 Input:
 org: [4,1,5,2,6,3], seqs: [[5,2,6,3],[4,1,5,2]]

 Output:
 true
 UPDATE (2017/1/8):
 The seqs parameter had been changed to a list of list of strings (instead of a 2d array of strings). Please reload the code definition to get the latest changes.
 */

class Solution {
public:
    /**
     * use topological sort to order all elements, and at each stage of topological sort, there should
     * be only one element, and it should be the one in the org array
     */
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        unordered_map<int, unordered_set<int>> out;
        unordered_map<int, unordered_set<int>> in;
        int n = INT_MIN;
        for (auto& seq : seqs) {
            for (int i = 0; i < seq.size() - 1; ++i) {
                n = max(n, seq[i]);
                out[seq[i]].insert(seq[i+1]);
                in[seq[i+1]].insert(seq[i]);
            }
            if (seq.size()) {
                n = max(n, seq.back());
            }
        }
        if (org.size() != n) {
            return false;
        }
        
        int k = 0;
        vector<int> cur;
        for (int i = 1; i <= n; ++i) {
            if (in[i].size() == 0) {
                cur.push_back(i);
            }
        }
        while (cur.size()) {
            if (cur.size() != 1 || k >= org.size() || org[k] != cur[0]) {
                return false;
            }
            ++k;
            vector<int> next;
            for (auto u : out[cur[0]]) {
                in[u].erase(cur[0]);
                if (in[u].size() == 0) {
                    next.push_back(u);
                }
            }
            cur.swap(next);
        }
        return k == n;
        
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> org;
        vector<vector<int>> seqs;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3},{{1,2},{1,3}}},
        {{1,2,3},{{1,2}}},
        {{1,2,3},{{1,2},{1,3},{2,3}}},
        {{4,1,5,2,6,3},{{5,2,6,3},{4,1,5,2}}},
    };

    vector< bool > answers {
        false,
        false,
        true,
        true,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = sequenceReconstruction::Solution().sequenceReconstruction(dp.org, dp.seqs);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
