// smallestRangeII.cpp
// leetcode
//
// Created by  Song Ding on 9/30/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace smallestRangeII {

class Solution {
public:
    /**
     * For each A[i], bookkeep max-min and min-max for
     * both A[i]+K and A[i]-K.
     * For A[i+1]+K and A[i+1]-K, use the all 4 values from
     * previous record.
     * Cause there are two segments (A[0]+K, A[1]+K, ..., A[i]+K, A[i+1]-K, ..., A[n]-K), the first one is on the left of the current point (A[i] + K is the last element of the first segment), the second one is on the right of the current point (A[i + 1] - K is the first element of the second segment). For the first segment, the smallest element is left, the largest is A[i] + K; For the second segment, A[i + 1] - K is the smallest element, the largest is right. Thus, for each point, the largest element should be either A[i] + K or right, the smallest element should be either left or A[i + 1] - K.
     */
    int smallestRangeII(vector<int>& A, int K) {
        int n = A.size();
        if (n <= 1) {
            return 0;
        }
        sort(A.begin(), A.end());
        int res = A[n - 1] - A[0];
        if (K < 0) {
            K = -K;
        }
        int c1 = A[0] + K;
        int c2 = A[n - 1] - K;
        for (int i = 0; i < n - 1; ++i) {
            int c3 = A[i] + K;
            int c4 = A[i + 1] - K;
            
            int r = std::max(c3, c2) - std::min(c1, c4);
            if (r < res) {
                res = r;
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
    vector<int> A {1,3,6};
    int K = 3;

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = smallestRangeII::Solution().smallestRangeII(A, K);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
