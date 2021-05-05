// makeArrayIncreasing.cpp
// leetcode
//
// Created by  Song Ding on 9/8/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace makeArrayIncreasing {
/*
// TODO: copy problem statement here
 1187. Make Array Strictly Increasing
 Hard
 
 51
 
 1
 
 Favorite
 
 Share
 Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.
 
 In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].
 
 If there is no way to make arr1 strictly increasing, return -1.
 
 
 
 Example 1:
 
 Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
 Output: 1
 Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].
 Example 2:
 
 Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
 Output: 2
 Explanation: Replace 5 with 3 and then replace 3 with 4. arr1 = [1, 3, 4, 6, 7].
 Example 3:
 
 Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
 Output: -1
 Explanation: You can't make arr1 strictly increasing.
 
 
 Constraints:
 
 1 <= arr1.length, arr2.length <= 2000
 0 <= arr1[i], arr2[i] <= 10^9
 */

class Solution {
public:
    int makeArrayIncreasing3(vector<int>& arr1, vector<int>& arr2) {
        int n1 = arr1.size(), n2 = arr2.size();
        sort(begin(arr2), end(arr2));
        // [i,j] = for arr1[0..i], if j swaps are executed, the min value at arr1[i]
        // if not possible, -1.
        const int kInf = 1000000001;
        vector<vector<int>> dp(n1, vector<int>(n2+1, kInf));
        dp[0][0] = arr1[0];
        if (arr2[0] < arr1[0]) {
            dp[0][1] = arr2[0];
        } else {
            dp[0][1] = arr1[0];
        }
        for (int i = 1; i < n1; ++i) {
            if (arr1[i] > dp[i-1][0]) {
                dp[i][0] = arr1[i];
            }
            // do j swaps
            for (int j = 1; j <= min(i+1, n2); ++j) {
                if (arr1[i] > dp[i-1][j]) {
                    dp[i][j] = arr1[i];
                }
                auto it = upper_bound(begin(arr2), end(arr2), dp[i-1][j-1]);
                if (it != end(arr2) && *it < dp[i][j]) {
                    dp[i][j] = *it;
                }
            }
        }
        for (int i = 0; i <= n2; ++i) {
            if (dp[n1-1][i] < kInf) {
                return i;
            }
        }
        return -1;
    }
    int makeArrayIncreasing2(vector<int>& arr1, vector<int>& arr2) {
        int n1 = arr1.size(), n2 = arr2.size();
        sort(begin(arr2), end(arr2));
        unordered_map<int, int> nextBig;
        for (int i = 0; i < n2-1; ++i) {
            if (arr2[i] != arr2[i+1]) {
                nextBig[arr2[i]] = arr2[i+1];
            }
        }
        for (int i = 0; i < n1; ++i) {
            auto it = upper_bound(begin(arr2), end(arr2), arr1[i]);
            if (it != end(arr2)) {
                nextBig[arr1[i]] = *it;
            }
        }
        // [i,j] = for arr1[0..i], if j swaps are executed, the min value at arr1[i]
        const int kInf = 1000000001;
        vector<vector<int>> dp(n1, vector<int>(n2+1, kInf));
        dp[0][0] = arr1[0];
        if (arr2[0] < arr1[0]) {
            dp[0][1] = arr2[0];
        } else {
            dp[0][1] = arr1[0];
        }
        for (int i = 1; i < n1; ++i) {
            if (arr1[i] > dp[i-1][0]) {
                dp[i][0] = arr1[i];
            }
            // do j swaps
            for (int j = 1; j <= min(i+1, n2); ++j) {
                if (arr1[i] > dp[i-1][j]) {
                    dp[i][j] = arr1[i];
                }
                auto it = nextBig.find(dp[i-1][j-1]);
                if (it != end(nextBig) && it->second < dp[i][j]) {
                    dp[i][j] = it->second;
                }
            }
        }
        for (int i = 0; i <= n2; ++i) {
            if (dp[n1-1][i] < kInf) {
                return i;
            }
        }
        return -1;
    }
    /**
     * let end(i,j) = min value of arr[i] if at most j replacements can be done.
     * then we have end(i,j+1) <= end(i,j).
     *  end(i,j) = for each end(i-1,k), check whether arr[i] need to be updated or not.
     */
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(), arr2.end());
        unordered_map<int, int> nextBig;
        int j = 1;
        for (int i = 0; i < arr2.size() - 1; ++i) {
            while (j < arr2.size() && arr2[j] == arr2[i]) {
                ++j;
            }
            if (j < arr2.size()) {
                nextBig[arr2[i]] = arr2[j];
            } else {
                break;
            }
        }
        // find nextBig for arr1
        vector<int> t(arr1);
        sort(t.begin(), t.end());
        j = 0;
        for (int i = 0; i < t.size(); ++i) {
            while (j < arr2.size() && arr2[j] <= t[i]) {
                ++j;
            }
            if (j < arr2.size()) {
                nextBig[t[i]] = arr2[j];
            } else {
                break;
            }
        }
        
        map<int, int> minEnd;
        minEnd[0] = arr1[0];
        if (arr2[0] < minEnd[0]) {
            minEnd[1] = arr2[0];
        }
        
        for (int i = 1; i < arr1.size() && minEnd.size(); ++i) {
            map<int, int> nextMinEnd;
            for (auto it = minEnd.begin(); it != minEnd.end(); ++it) {
                if (arr1[i] > it->second) {
                    auto nmit = nextMinEnd.find(it->first);
                    if (nmit != nextMinEnd.end()) {
                        nextMinEnd[it->first] = min(arr1[i], nmit->second);
                    } else {
                        nextMinEnd[it->first] = arr1[i];
                    }
                }
                // find an element in arr2 which is just larger than it->second
                auto nbit = nextBig.find(it->second);
                if (nbit != nextBig.end()) {
                    nextMinEnd[it->first+1] = nbit->second;
                    //auto nmit = nextMinEnd.find(it->first + 1);
                    //if (nmit == nextMinEnd.end() || nmit->second > nbit->second) {
                    //    nextMinEnd[it->first+1] = nbit->second;
                    //}
                }
            }
            minEnd.swap(nextMinEnd);
        }
        
        if (minEnd.size()) {
            return minEnd.begin()->first;
        }
        return -1;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> arr1;
        vector<int> arr2;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{{1,5,3,6,7}, {1,3,2,4}},
        //{{1,5,3,6,7}, {4,3,1}},
        //{{1,5,3,6,7}, {1,6,3,3}},
        //{{5,16,19,2,1,12,7,14,5,16},{6,17,4,3,6,13,4,3,18,17,16,7,14,1,16}},
        //{{23,10,9,12,3,14,21,16,7,10,17,12},{6,5,0,15,2,17,4,11,6,5,8,15,10,1,20,11,14,13,8}},
        {{31,18,1,12,23,14,25,4,17,18,29,28,35,34,19,8,25,6,35},{13,10,25,18,3,8,37,20,23,12,9,36,17,22,29,6,1,12,37,6,3,14,37,2}},
    };

    vector< int > answers {
        1,
        2,
        -1,
        8,
        11,
        19
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = makeArrayIncreasing::Solution().makeArrayIncreasing2(dp.arr1, dp.arr2);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
