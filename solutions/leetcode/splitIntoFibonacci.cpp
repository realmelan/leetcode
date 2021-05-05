// splitIntoFibonacci.cpp
// leetcode
//
// Created by  Song Ding on 6/11/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace splitIntoFibonacci {

class Solution {
public:
    /**
     * determine all possible combinations of the first two numbers.
     *   1, suppose length of S is n, then the length of the first number
     *      would not exceed (n - 1) / 2.
     *   2, given the length of the first number, k, then the length of the
     *      second number would not exceed n - 2*k.
     *
     */
    vector<int> splitIntoFibonacci(string S) {
        int n = S.size();
        vector<int> res;
        if (n < 3) {
            return {};
        }
        
        int flen = (n - 1) / 2;
        if (S[0] == '0') {
            flen = 1;
        }
        for (int i = 1; i <= flen; ++i) {
            int fn = 0;
            
            for (int k = 0; k < i; ++k) {
                fn *= 10;
                fn += S[k] - '0';
            }
            
            int slen = n - 2 * i;
            if (S[i] == '0') {
                slen = 1;
            }
            for (int j = 1; j <= slen; ++j) {
                int sn = 0;
                for (int k = 0; k < j; ++k) {
                    sn *= 10;
                    sn += S[i + k] - '0';
                }
                res.push_back(fn);
                res.push_back(sn);
                if (verifyFib(S, fn, sn, i + j, res)) {
                    return res;
                }
                res.pop_back();
                res.pop_back();
            }
        }
        return {};
    }

private:
    bool verifyFib(const std::string& s, int fn, int sn, int cur, vector<int>& res) {
        int n = s.size();
        int tn = 0;
        int k = cur;
        int tlen = 0;
        if (s[k] == '0') {
            tn = 0;
            ++k;
            ++tlen;
        } else {
            for (; k < n && tn < fn + sn; ++k) {
                tn *= 10;
                tn += s[k] - '0';
                ++tlen;
            }
        }
        if (tn != fn + sn || tlen == 0) {
            return false;
        }
        
        res.push_back(tn);
        if (k == n) {
            return true;
        }
        bool ret = verifyFib(s, sn, tn, k, res);
        if (!ret) {
            res.pop_back();
        }
        return ret;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string S = "00246";
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = splitIntoFibonacci::Solution().splitIntoFibonacci(S);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
