// maxScoreSightseeingPair.cpp
// leetcode
//
// Created by  Song Ding on 5/19/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxScoreSightseeingPair {
/*
// TODO: copy problem statement here
 1014. Best Sightseeing Pair
 Medium
 
 167
 
 11
 
 Favorite
 
 Share
 Given an array A of positive integers, A[i] represents the value of the i-th sightseeing spot, and two sightseeing spots i and j have distance j - i between them.
 
 The score of a pair (i < j) of sightseeing spots is (A[i] + A[j] + i - j) : the sum of the values of the sightseeing spots, minus the distance between them.
 
 Return the maximum score of a pair of sightseeing spots.
 
 
 
 Example 1:
 
 Input: [8,1,5,2,6]
 Output: 11
 Explanation: i = 0, j = 2, A[i] + A[j] + i - j = 8 + 5 + 0 - 2 = 11
 
 
 Note:
 
 2 <= A.length <= 50000
 1 <= A[i] <= 1000
 */

class Solution {
public:
    /**
     * the score of a pair can be sum of (A[i] + i) and (A[j]-j) (i < j)
     * So, for any i, we need to know max value of A[j]-j for all j < i.
     * this can be built reversely.
     */
    int maxScoreSightseeingPair(vector<int>& A) {
        int n = A.size();
        vector<int> mminus(n+1, INT_MIN);
        for (int i = n - 1; i >= 0; --i) {
            mminus[i] = max(mminus[i+1], A[i] - i);
        }
        int res = INT_MIN;
        for (int i = 0; i < n - 1; ++i) {
            res = max(res, (A[i]+i + mminus[i+1]));
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
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{8,1,5,2,6}}
    };

    vector< int > answers {
        11
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxScoreSightseeingPair::Solution().maxScoreSightseeingPair(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
