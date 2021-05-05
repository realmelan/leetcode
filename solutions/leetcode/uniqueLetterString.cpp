// uniqueLetterString.cpp
// leetcode
//
// Created by  Song Ding on 10/21/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace uniqueLetterString {

class Solution {
public:
    int uniqueLetterString(string S) {
        int n = S.size();
        vector<vector<int>> idx(26);
        for (int i = 0; i < n; ++i) {
            idx[S[i] - 'A'].push_back(i);
        }
        
        int mod = 1000000007;
        int res = 0;
        for (auto& v : idx) {
            int vn = v.size();
            if (vn <= 0) {
                continue;
            }
            int last = -1;
            v.push_back(n);
            for (int i = 0; i < vn; ++i) {
                res += (v[i] - last) * (v[i+1] - v[i]);
                res %= mod;
                last = v[i];
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
    string S = "ABA";

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = uniqueLetterString::Solution().uniqueLetterString(S);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
