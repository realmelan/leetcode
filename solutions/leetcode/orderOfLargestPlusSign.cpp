// orderOfLargestPlusSign.cpp
// leetcode
//
// Created by  Song Ding on 9/4/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace orderOfLargestPlusSign {

class Solution {
public:
    /**
     * for each point, compute the vertical and horizontal largest number of
     * consecutive 1's, centered on it.
     * the minimum value of vertical and horizontal values is the order of
     * largest plus sign for that point.
     *
     * Loop through all points to get the largest.
     */
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        vector<vector<int>> h(N), v(N);
        for (auto& hv : h) {
            for (int i = 0; i < N; ++i) {
                hv.push_back(min(i + 1, N - i));
            }
        }
        for (int i = 0; i < N; ++i) {
            auto& vv = v[i];
            for (int j = 0; j < N; ++j) {
                vv.push_back(min(i + 1, N - i));
            }
        }
        
        vector<vector<int>> hm(N), vm(N);
        for (const auto& m : mines) {
            hm[m[0]].push_back(m[1]);
            vm[m[1]].push_back(m[0]);
        }
        for (int i = 0; i < N; ++i) {
            if (hm[i].empty()) {
                continue;
            }
            sort(hm[i].begin(), hm[i].end());
            int lz = -1;
            for (int j : hm[i]) {
                h[i][j] = 0;
                for (int k = lz + 1; k < j; ++k) {
                    h[i][k] = min(k - lz, j - k);
                }
                lz = j;
            }
            for (int k = lz + 1; k < N; ++k) {
                h[i][k] = min(k - lz, N - k);
            }
        }
        for (int i = 0; i < N; ++i) {
            if (vm[i].empty()) {
                continue;
            }
            sort(vm[i].begin(), vm[i].end());
            int lz = -1;
            for (int j : vm[i]) {
                v[j][i] = 0;
                for (int k = lz + 1; k < j; ++k) {
                    v[k][i] = min(k - lz, j - k);
                }
                lz = j;
            }
            for (int k = lz + 1; k < N; ++k) {
                v[k][i] = min(k - lz, N - k);
            }
        }
        
        int res = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int t = min(h[i][j], v[i][j]);
                if (res < t) {
                    cout << i << "," << j << "=>" << t << endl;
                    res = t;
                }
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
    int N = 10;
    vector<vector<int>> mines {
        {1,2},{1,8},{2,4},{4,7},{5,0},{5,6},{6,4},{6,9}
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = orderOfLargestPlusSign::Solution().orderOfLargestPlusSign(N, mines);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
