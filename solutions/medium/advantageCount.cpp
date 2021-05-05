// advantageCount.cpp
// leetcode
//
// Created by  Song Ding on 6/7/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace advantageCount {
/*
// TODO: copy problem statement here
 870. Advantage Shuffle
 Medium
 
 249
 
 20
 
 Favorite
 
 Share
 Given two arrays A and B of equal size, the advantage of A with respect to B is the number of indices i for which A[i] > B[i].
 
 Return any permutation of A that maximizes its advantage with respect to B.
 
 
 
 Example 1:
 
 Input: A = [2,7,11,15], B = [1,10,4,11]
 Output: [2,11,7,15]
 Example 2:
 
 Input: A = [12,24,8,32], B = [13,25,32,11]
 Output: [24,32,8,12]
 
 
 Note:
 
 1 <= A.length = B.length <= 10000
 0 <= A[i] <= 10^9
 0 <= B[i] <= 10^9
 */

class Solution {
public:
    /**
     * sort A & B
     * let bp[i] = j if A[j] > B[i] and j is the smallest.
     * by greedy algorithm, we choose the smallest B to gain advantage point.
     */
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        int n = A.size();
        sort(A.begin(), A.end());
        vector<pair<int,int>> BI;
        for (int i = 0; i < n; ++i) {
            BI.push_back(make_pair(B[i], i));
        }
        sort(BI.begin(), BI.end(), [](const pair<int,int>& a, const pair<int,int>& b){
            return a.first < b.first;
        });

        unordered_set<int> notused;
        for (int i = 0; i < n; ++i) {
            notused.insert(i);
        }
        vector<int> res(n, -1);
        int j = -1;
        for (int i = 0; i < n; ++i) { // index of B
            for (++j; j < n; ++j) {
                if (A[j] > BI[i].first) {
                    notused.erase(j);
                    res[BI[i].second] = A[j];
                    break;
                }
            }
        }
        
        auto it = notused.begin();
        for (int i = 0; i < n; ++i) {
            if (res[i] < 0) {
                res[i] = A[*it];
                ++it;
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
        vector<int> B;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{2,7,11,15},{1,10,4,11}},
        {{12,24,8,32},{13,25,32,11}}
    };

    vector< vector<int> > answers {
        {2,11,7,15},
        {24,32,8,12}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = advantageCount::Solution().advantageCount(dp.A, dp.B);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
