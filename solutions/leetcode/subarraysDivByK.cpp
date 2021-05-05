// subarraysDivByK.cpp
// leetcode
//
// Created by  Song Ding on 5/9/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace subarraysDivByK {
/*
 974. Subarray Sums Divisible by K
 Medium
 
 231
 
 20
 
 Favorite
 
 Share
 Given an array A of integers, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.
 
 
 
 Example 1:
 
 Input: A = [4,5,0,-2,-3,1], K = 5
 Output: 7
 Explanation: There are 7 subarrays with a sum divisible by K = 5:
 [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
 
 
 Note:
 
 1 <= A.length <= 30000
 -10000 <= A[i] <= 10000
 2 <= K <= 10000
 */
class Solution {
public:
    /**
     * for each position i, find sum(A[0] .. A[i]) and mod it by K to
     * get modSum[0, n-1]
     * group modSum, then any pair inside each subgroup would be an subarray.
     */
    int subarraysDivByK(vector<int>& A, int K) {
        int n = A.size();
        vector<int> sum;
        int s = 0;
        for (auto i : A) {
            s += i;
            int m = s % K;
            if (m < 0) {
                m += K;
            }
            sum.push_back(m);
        }
        
        vector<int> g(K, 0);
        for (auto s : sum) {
            ++g[s];
        }
        ++g[0];
        
        int res = 0;
        for (auto i : g) {
            if (i > 1) {
                res += i * (i-1) / 2;
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
    vector< pair<vector<int>,int> > params{
        {{4,5,0,-2,-3,1},5},
        {{-2},6},
        {{2},6},
        {{8,-5,-4}, 6},
        {{4,5,0,-2,-3,1},5}
    };

    vector<  int > answers {
        7,
        0,
        0,
        0,
        7
    };
    int i = 4;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = subarraysDivByK::Solution().subarraysDivByK(params[i].first, params[i].second);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
