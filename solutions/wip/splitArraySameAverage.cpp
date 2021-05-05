// splitArraySameAverage.cpp
// leetcode
//
// Created by  Song Ding on 7/8/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace splitArraySameAverage {
/*
// TODO: copy problem statement here
 805. Split Array With Same Average
 Hard
 
 227
 
 45
 
 Favorite
 
 Share
 In a given integer array A, we must move every element of A to either list B or list C. (B and C initially start empty.)
 
 Return true if and only if after such a move, it is possible that the average value of B is equal to the average value of C, and B and C are both non-empty.
 
 Example :
 Input:
 [1,2,3,4,5,6,7,8]
 Output: true
 Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have the average of 4.5.
 Note:
 
 The length of A will be in the range [1, 30].
 A[i] will be in the range of [0, 10000].
 */

class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        return splitArraySameAverage_DFS(A);
    }
    bool splitArraySameAverage_DFS(vector<int>& A) {
        int n = A.size();
        int sum = 0;
        for (auto i : A) {
            sum += i;
        }
        
        sort(A.begin(), A.end());
        for (int k = 1; k <= n/2; ++k) {
            if (sum * k % n) { // k-element sum has to be an integer.
                continue;
            }
            if (dfs(0, A, sum * k / n, k)) {
                return true;
            }
        }
        return false;
    }
    bool dfs(int start, vector<int>& arr, int sumk, int k) {
        int n = arr.size();
        if (k == 0) {
            return sumk == 0;
        }
        if (arr[start] > sumk/k) {
            return false; // elements are only getting larger
        }
        for (int i = start; i < n - k + 1; ++i) {
            if (i > start && arr[i] == arr[i-1]) { // arr[i-1] already failed to work.
                continue;
            }
            if (dfs(i+1, arr, sumk - arr[i], k-1)) {
                return true;
            }
        }
        return false;
    }
    /**
     * DP:
     *  let dp[i][s] = true if there is a split of i elements with sum equaling s.
     *  for i from 0 to n-1, update this dp[i][s] accordingly
     *
     *  During the updating process, check whether s/i = (sum/n).
     *
     *  s may ranges from 0 to 10000*30.
     */
    bool splitArraySameAverage_DP_Slow(vector<int>& A) {
        int n = A.size();
        int sum = 0;
        for (auto i : A) {
            sum += i;
        }
        sort(A.begin(), A.end());
        
        vector<unordered_set<int>> dp(n+1);
        dp[0] = {0};
        for (int i = 0; i < n; ++i) {
            vector<unordered_set<int>> next(dp);
            for (int j = 0; j <= i; ++j) {
                for (auto& s : dp[j]) {
                    int t = s + A[i];
                    int nt = j + 1;
                    if (sum * nt < t * n) {
                        continue;
                    } else if (sum * nt == t * n && nt < n) {
                        return true;
                    }
                    
                    next[nt].insert(t);
                }
            }
            dp.swap(next);
        }
        return false;
    }

private:
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
        {{1,2,3,4,5,6,7,8}},
        {{17,3,7,12,1}},
        {{2,12,18,16,19,3}}
    };

    vector< bool > answers {
        true,
        false,
        false
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = splitArraySameAverage::Solution().splitArraySameAverage(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
