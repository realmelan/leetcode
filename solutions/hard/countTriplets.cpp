// countTriplets.cpp
// leetcode
//
// Created by  Song Ding on 9/15/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace countTriplets {
/*
// TODO: copy problem statement here
 982. Triples with Bitwise AND Equal To Zero
 Hard
 
 65
 
 91
 
 Favorite
 
 Share
 Given an array of integers A, find the number of triples of indices (i, j, k) such that:
 
 0 <= i < A.length
 0 <= j < A.length
 0 <= k < A.length
 A[i] & A[j] & A[k] == 0, where & represents the bitwise-AND operator.
 
 
 Example 1:
 
 Input: [2,1,3]
 Output: 12
 Explanation: We could choose the following i, j, k triples:
 (i=0, j=0, k=1) : 2 & 2 & 1
 (i=0, j=1, k=0) : 2 & 1 & 2
 (i=0, j=1, k=1) : 2 & 1 & 1
 (i=0, j=1, k=2) : 2 & 1 & 3
 (i=0, j=2, k=1) : 2 & 3 & 1
 (i=1, j=0, k=0) : 1 & 2 & 2
 (i=1, j=0, k=1) : 1 & 2 & 1
 (i=1, j=0, k=2) : 1 & 2 & 3
 (i=1, j=1, k=0) : 1 & 1 & 2
 (i=1, j=2, k=0) : 1 & 3 & 2
 (i=2, j=0, k=1) : 3 & 2 & 1
 (i=2, j=1, k=0) : 3 & 1 & 2
 
 
 Note:
 
 1 <= A.length <= 1000
 0 <= A[i] < 2^16
 */

class Solution {
public:
    int countTriplets(vector<int>& A) {
        return countTriplets_dp_simple(A);
    }
    /**
     * https://leetcode.com/problems/triples-with-bitwise-and-equal-to-zero/discuss/226721/Java-DP-O(3-*-216-*-n)-time-O(216)-space
     * dp[i][j] represents the number of combinations if we pick i numbers where the AND of these numbers is j:
     */
    int countTriplets_dp_simple(vector<int>& A) {
        int N = 1 << 16, M = 3;
        vector<vector<int>> dp(M+1, vector<int>(N));
        dp[0][N - 1] = 1;
        for (int i = 0; i < M; i++) {
            for (int k = 0; k < N; k++) {
                for (int a : A) {
                    dp[i + 1][k & a] += dp[i][k];
                }
            }
        }
        return dp[M][0];
    }
    /**
     * let pair(i,k)= # of pairs up to A[i-1] that ending at bit state k
     * then pair(i,k) = pair(i-1,k) + # of A[i] pairing with A[0..i-1] at k.
     *
     * Now that we have pair(i,k), we can get triplets triplet(i).
     * let triplet(i) = # of triplets for A[0..i] that bitwise and to 0.
     * then triplet(i) = 3 * SUM(pair(i-1,k) which bitwise and with A[i] to be 0)
     *     + SUM(# of A[k] who bitwise and A[i] to be 0) * 3(this is for two A[i]'s).
     */
    int countTriplets_dp(vector<int>& A) {
        const int mask = 1<<17-1;
        int n = A.size();
        int res = 0;
        // # of pairs whose bitwise and result is k, up to current element
        vector<int> dp(mask+1, 0);
        dp[A[0]] = 1;
        if (!A[0]) {
            res = 1;
        }
        for (int i = 1; i < n; ++i) {
            for (int k = 0; k <= mask; ++k) {
                if ((A[i] & k) == 0) {
                    res += dp[k] * 3; // 1 A[i] and 2 other
                }
            }
            // update pair A[j],A[i]
            for (int j = 0; j < i; ++j) {
                dp[ A[j]&A[i] ] += 2;
                if ((A[j] & A[i]) == 0) {
                    res += 3; // a triplet of 2 A[i], 1 A[j].
                }
            }
            // pair of A[i],A[i]
            dp[A[i]] += 1;
            
            // three A[i]
            if (!A[i]) {
                res += 1;
            }
        }
        return res;
    }
    /**
     * for each bit find indices of A's element that has the bit set.
     * Note, a triplet may have several bit set, so use LSB to find out.
     *
     * Note, i may be same as j or k
     */
    int countTriplets_TLE(vector<int>& A) {
        int n = A.size();
        vector<vector<int>> bitIdx(16);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 16; ++j) {
                if (A[i] & (1<<j)) {
                    bitIdx[j].push_back(i);
                }
            }
        }
        unordered_map<int,int> addback;
        int res = n * n * n;
        for (auto& v : bitIdx) {
            int vn = v.size();
            res -= vn * vn * vn;
            for (auto i : v) {
                for (auto j : v) {
                    for (auto k : v) {
                        int p = A[i] & A[j] & A[k];
                        int cnt = 0;
                        for (int x = lsb(p); p > 0; x = lsb(p)) {
                            ++cnt;
                            p -= x;
                        }
                        // i,j,k will appear cnt times,
                        // TODO: how to add it back later (cnt-1) after loop
                        addback[(i<<20) | (j<<10) | k] = cnt - 1;
                    }
                }
            }
        }
        for (auto& p : addback) {
            res += p.second;
        }
        return res;
    }

private:
    int lsb(int i) {
        return i & (-i);
    }
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
        {{2,1,3}},
        {{0,0,0}},
        {{58615,60272,41074,24613,63868,41869,4314,5548,49143,4007,514,25808,34013,29395,32022,38331,44518,27724,24138,64779,17099,50928,28260,23495,4184,56595,46006,59179,29596,44362,7792,26080,13581,2759,62125,14148,9591,12974,24774,35808,9917,64794,64421,9725,26601,44559,57518,32466,60099,21132,32665,32679,43913,13237,39961,14337,22296,63082,58917,53616,2324,9723,16835,51391,55203,38204,47063,52891,4348,5547,56943,2583,14751,2662,1001,55309,21665,10530,9753,42997,63478,33095,59053,32927,37609,44470,52763,49666,64915,48953,59361,13507,35089,39230,54112,31602,51841,25465,38429,55791,52301,43056,15,11925,33217,16676,4300,56353,61796,19844,26743,53086,4080,42007,8344,18814,54390,3639,2354,27385,32232,56578,47001,44141,9920,64664,26944,40093,25341,3082,30860,9920,2127,40461,41285,6900,35988,22719,25127,50883,32133,57755,39984,30617,41439,22142,8147,44730,40765,51679,8330,59754,52385,60089,57182,44630,53100,34013,51477,12394,51256,29135,49585,29849,51744,4937,2925,61229,31861,59052,61917,43680,37473,14154,6126,53699,58246,51078,45777,27532,20008,7434,27916,37094,60481,61325,27239,6501,50712,48121,2012,29276,44985,1974,60246,63061,47352,5147,4609,23544}}
    };

    vector< int > answers {
        12,
        27
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = countTriplets::Solution().countTriplets(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
