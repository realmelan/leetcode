// numSubarrayBoundedMax.cpp
// leetcode
//
// Created by  Song Ding on 6/10/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numSubarrayBoundedMax {

class Solution {
public:
    /**
     * construct two arrays:
     * A: positions where L <= A[i] <= R;
     * B: positions where A[i] > R
     *
     * For each position in A:
     *   extend A[i] leftwards, until A[i - 1], say m,
     *   extend A[i] rightwards until B[j] where B[j] > A[i] (use binary search), say n.
     * Then # of subarrays containing A[i] will be (m+1)*(n+1).
     */
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        int n = A.size();
        if (n <= 0 || L > R) {
            return 0;
        }
        vector<int> lr{-1};
        for (int i = 0; i < n; ++i) {
            if (A[i] >= L && A[i] <= R) {
                lr.push_back(i);
            }
        }
        
        int res = 0;
        int lrn = lr.size();
        int i = 1;
        int last = 0;
        while (i < lrn) {
            int nc = lr[i];
            int lastNc = lr[i - 1];
           
            int j = nc - 1;
            while (j > lastNc && A[j] <= R) {
                --j;
            }
            int left = nc - j - 1;
            
            int right = 0;
            if (last > nc) {
                right = last - nc - 1;
            } else {
                int j = nc + 1;
                while (j < n && A[j] <= R) {
                    ++j;
                }
                last = j;
                right = last - nc - 1;
            }
            
            res += (left + 1) * (right + 1);
            ++i;
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> A{
        445,730,557,930,797,398,9,441,194,706,419,840,164,718,559,783,760,934,771,89,494,253,503,563,6,915,861,361,296,647,730,792,523,24,805,296,600,542,367,974,875,569,56,921,330,348,355,890,940,577,490,289,860,195,350,11,752,796,390,604,116,382,497,924,750,180,466,449,177,45,663,592,328,857,195,166,558,164,895,922,311,714,110,934,373,25,323,239,808,541,419,694,961,397,355,162,728,974,872,709
        
        
    };
    int L = 493;
    int R = 915;
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = numSubarrayBoundedMax::Solution().numSubarrayBoundedMax(A, L, R);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
