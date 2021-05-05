// threeEqualParts.cpp
// leetcode
//
// Created by  Song Ding on 11/15/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace threeEqualParts {

class Solution {
public:
    vector<int> threeEqualParts(vector<int>& A) {
        int n = A.size();
        int sum = 0;
        for_each(A.begin(), A.end(), [&sum](int a){
            sum += a;
        });
        if (sum % 3) {
            return {-1,-1};
        } else if (sum == 0) {
            return {0,2};
        }
        
        int oneCnt = sum / 3;
        int trailZero = 0;
        int i = n - 1;
        while (i >= 0 && A[i] == 0) {
            --i;
        }
        trailZero = n - i - 1;
        
        // move back to find the first 1 of the 3rd binary
        int cnt = 0;
        while (i >= 0 && cnt < oneCnt) {
            cnt += A[i] & 1;
            --i;
        }
        int r2 = i + 1;
        int zeroCnt = 0;
        while (i >= 0 && A[i] == 0) {
            ++zeroCnt;
            --i;
        }
        if (zeroCnt < trailZero) {
            return {-1,-1};
        }
        
        r2 -= zeroCnt - trailZero;
        int r2len = n - r2;
        
        // move back to find the first 1 of the 2nd binary
        cnt = 0;
        i += trailZero;
        while (i >= 0 && cnt < oneCnt && A[i] == A[i + r2len]) {
            cnt += A[i] & 1;
            --i;
        }
        if (cnt < oneCnt) {
            return {-1,-1};
        }
        int r1 = i + 1;
        zeroCnt = 0;
        while (i >= 0 && A[i] == 0) {
            ++zeroCnt;
            --i;
        }
        if (zeroCnt < trailZero) {
            return {-1,-1};
        }
        r1 -= zeroCnt - trailZero;
        int r1len = r2 - r1;
        
        cnt = 0;
        i += trailZero;
        while (i >= 0 && cnt < oneCnt && A[i] == A[i + r1len]) {
            cnt += A[i] & 1;
            --i;
        }
        if (cnt < oneCnt) {
            return {-1,-1};
        }

        return {r1-1, r2};
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> A {
        {1,0,1,0,1},
        {1,1,0,1,1},
        {0,1,0,1,1,0,0,1,0,1,0,0,0,0,1,0,1,1,1,0}
    };
    vector< vector<int> > answers {
        {0,3},
        {-1,-1},
        {-1,-1}
    };
    int i = 2;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = threeEqualParts::Solution().threeEqualParts(A[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
