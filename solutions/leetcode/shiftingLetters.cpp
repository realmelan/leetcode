// shiftingLetters.cpp
// leetcode
//
// Created by  Song Ding on 10/4/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace shiftingLetters {

class Solution {
public:
    string shiftingLetters(string S, vector<int>& shifts) {
        int sn = S.size();
        int n = shifts.size();
        if (sn <= 0 || n <= 0) {
            return S;
        }
        
        string res;
        int t = 0;
        while (n > sn) {
            t += shifts[n - 1];
            --n;
        }
        while (sn > n) {
            res.insert(res.begin(), S[sn - 1]);
            --sn;
        }
        for (int i = n - 1; i >= 0; --i) {
            t += shifts[i];
            t %= 26;
            unsigned char c = S[i] + t;
            if (c > 'z') {
                c -= 26;
            }
            res.insert(res.begin(), c);
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string S = "ruu";
    vector<int> shifts {26,9,17};
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = shiftingLetters::Solution().shiftingLetters(S, shifts);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
