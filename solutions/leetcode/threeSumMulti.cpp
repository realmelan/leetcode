// threeSumMulti.cpp
// leetcode
//
// Created by  Song Ding on 6/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace threeSumMulti {
/*
// TODO: copy problem statement here
 923. 3Sum With Multiplicity
 Medium
 
 192
 
 38
 
 Favorite
 
 Share
 Given an integer array A, and an integer target, return the number of tuples i, j, k  such that i < j < k and A[i] + A[j] + A[k] == target.
 
 As the answer can be very large, return it modulo 10^9 + 7.
 
 
 
 Example 1:
 
 Input: A = [1,1,2,2,3,3,4,4,5,5], target = 8
 Output: 20
 Explanation:
 Enumerating by the values (A[i], A[j], A[k]):
 (1, 2, 5) occurs 8 times;
 (1, 3, 4) occurs 8 times;
 (2, 2, 4) occurs 2 times;
 (2, 3, 3) occurs 2 times.
 Example 2:
 
 Input: A = [1,1,2,2,2,2], target = 5
 Output: 12
 Explanation:
 A[i] = 1, A[j] = A[k] = 2 occurs 12 times:
 We choose one 1 from [1,1] in 2 ways,
 and two 2s from [2,2,2,2] in 6 ways.
 
 
 Note:
 
 3 <= A.length <= 3000
 0 <= A[i] <= 100
 0 <= target <= 300
 */

class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        int n = arr.size(), M=1e9+7;
        vector<int> cnt(101,0);
        cnt[arr[0]] = 1;
        vector<long> dp(target+1,0);
        long res = 0;
        for (int i = 1; i < n; ++i) {
            if (target >= arr[i]) {
                res = (res + dp[target-arr[i]])%M;
            }
            for (int k = target; k >= 0; --k) {
                dp[k] = (dp[k] + (k>=arr[i]&&k-arr[i]<=100?cnt[k-arr[i]]:0))%M;
            }
            ++cnt[arr[i]];
        }
        return res;
    }
    /**
     * //TODO: explain algorithm here
     */
    int threeSumMulti2(vector<int>& A, int target) {
        long res = 0;
        vector<int> count(101, 0);
        for (auto i : A) {
            ++count[i];
        }
        
        for (int i = 0; i < 101; ++i) {
            if (count[i] == 0) {
                continue;
            }
            for (int j = i + 1; j < 101; ++j) {
                if (count[j] != 0) {
                    int t = target - i - j;
                    if (t > j && t <= 100) {
                        res += (long)count[i] * count[j] * count[t];
                    }
                }
            }
        }
        
        for (int i = 0; i < 101; ++i) {
            if (count[i] == 0) {
                continue;
            }
            int c = count[i] * (count[i]-1) / 2;
            int t = target - i - i;
            if (t > i && t <= 100) {
                res += c * count[t];
            }
        }
        
        for (int i = 0; i < 101; ++i) {
            if (count[i] == 0) {
                continue;
            }
            if ((target - i) % 2 == 0) {
                int t = (target - i) / 2;
                if (t > i && t <= 100) {
                    res += (long)count[i] * count[t] * (count[t]-1) / 2;
                }
            }
        }
        
        if (target % 3 == 0) {
            int t = target / 3;
            if (count[t] > 0) {
                long c = count[t];
                res += c * (c-1) * (c-2) / 6;
            }
        }
        
        return res % 1000000007;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> A;
        int target;
        
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{92,4,59,23,100,16,7,15,3,78,98,17,77,33,83,15,87,35,54,72,58,14,87,47,58,31,72,58,87,22,25,54,27,53,13,54,61,12,96,24,35,43,94,1,88,76,89,89,41,56,61,65,60,91,89,79,86,52,27,2,97,46,50,46,87,93,71,87,95,78,65,10,35,51,34,66,61,7,49,38,10,1,88,37,50,84,35,20,7,83,51,85,11,12,89,93,54,23,36,95,100,19,82,67,96,77,53,56,51,16,54,7,30,68,78,13,38,52,91,44,54,17,21,44,4,10,85,19,11,88,73,36,47,53,3,21,41,24,60,53,88,35,48,89,35,3,43,85,45,67,56,78,44,49,29,35,68,96,29,21,51,17,52,99,3,48,65,51,22,38,77,81,30,64,99,35,88,72,73,29,29,2},105},
        {{1,1,2,2,3,3,4,4,5,5}, 8},
        {{1,1,2,2,2,2}, 5},
        {{12,97,74,39,56,3,85,39,18,29,41,7,33,97,13,47,11,52,32,45,8,36,35,45,59,54,18,55,63,65,57,63,60,71,86,76,65,12,59,83,70,100,20,2,41,70,53,39,54,64,48,93,86,100,75,100,23,2,46,54,81,10,94,32,75,31,20,35,49,46,46,96,43,75,37,37,51,86,4,18,30,73,65,1,55,22,32,12,86,100,95,24,16,40,13,95,43,87,46,86},213}
    };

    vector< int > answers {
        20,
        12
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = threeSumMulti::Solution().threeSumMulti(dp.A, dp.target);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
