// largestSumOfAverages.cpp
// leetcode
//
// Created by  Song Ding on 5/14/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace largestSumOfAverages {
/*
 813. Largest Sum of Averages
 Medium
 
 508
 
 18
 
 Favorite
 
 Share
 We partition a row of numbers A into at most K adjacent (non-empty) groups, then our score is the sum of the average of each group. What is the largest score we can achieve?
 
 Note that our partition must use every number in A, and that scores are not necessarily integers.
 
 Example:
 Input:
 A = [9,1,2,3,9]
 K = 3
 Output: 20
 Explanation:
 The best choice is to partition A into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
 We could have also partitioned A into [9, 1], [2], [3, 9], for example.
 That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
 
 
 Note:
 
 1 <= A.length <= 100.
 1 <= A[i] <= 10000.
 1 <= K <= A.length.
 Answers within 10^-6 of the correct answer will be accepted as correct.
 */
class Solution {
public:
    double largestSumOfAverages2(vector<int>& A, int K) {
        int n = A.size();
        double sum = 0;
        vector<double> dp;
        for (int i = 0; i < n; ++i) {
            sum += A[i];
            dp.push_back(sum/(i+1));
        }
        
        for (int k = 2; k <= K; ++k) {
            vector<double> next(n);
            next[k-1] = dp[k-2] + A[k-1];
            for (int i = k; i < n; ++i) {
                double sum = 0;
                for (int j = i; j >= k-1; --j) {
                    sum += A[j];
                    next[i] = max(next[i], dp[j-1]+sum/(i-j+1));
                }
            }
            dp.swap(next);
        }
        return dp.back();
    }
    /**
     * DP:
     * let S(i,k) = largest sum of averages of A[0..i] with k subarrays.
     * then S(i, k) = max(S(j, k-1)+avg(j+1..i)) for all j < i && j >= k-1.
     * Note, S(i,k) only depends S(j, k-1), so one dimension vector would be ok.
     */
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<double> cur;
        double s = 0;
        for (int i = 0; i < n; ++i) {
            s += A[i];
            cur.push_back(s/(i+1));
        }
        for (int k = 2; k <= K; ++k) {
            vector<double> next(k-1, 0);
            for (int i = k-1; i < n; ++i) {
                double s = A[i];
                double res = s + cur[i-1];
                for (int j = i-1; j >= k-1; --j) {
                    s += A[j];
                    double t = s/(i-j+1);
                    if (t + cur[j-1] > res) {
                        res = t + cur[j-1];
                    }
                }
                next.push_back(res);
            }
            cur.swap(next);
        }
        return cur[n-1];
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< pair<vector<int>,int> > params {
        {{1,2,3,4,5,6,7},4}
    };

    vector<  double > answers {
        20.5
    };
    int i = 0;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = largestSumOfAverages::Solution().largestSumOfAverages2(params[i].first, params[i].second);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
