// findKthNumber.cpp
// leetcode
//
// Created by  Song Ding on 3/30/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findKthNumber {

class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        if (k > m * n) {
            return m * n;
        } else {
            long l = 1;
            long h = m * n;
            int res = 0;
            while (l <= h) {
                long mid = (l + h) / 2;
                int cnt = 0;
                int t = 0;
                for (int i = 1; i <= m; ++i) {
                    int j = min(mid / i, (long)n);
                    cnt += j;
                    if (t < j * i) {
                        t = j * i;
                    }
                }
                if (cnt >= k) {
                    res = t;
                }
                if (cnt < k) {
                    l = mid + 1;
                } else if (cnt > k) {
                    h = mid - 1;
                } else {
                    break;
                }
            }
            return res;
        }
        return m * n;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    //int m = 9895;
    //int n = 28405;
    //int k = 100787757;
    int m = 2;
    int n = 3;
    int k = 6; // res = 3
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = findKthNumber::Solution().findKthNumber(m, n, k);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
