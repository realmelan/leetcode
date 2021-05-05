// primePalindrome.cpp
// leetcode
//
// Created by  Song Ding on 9/27/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace primePalindrome {

class Solution {
public:
    /**
     * First of all, a prime palindrome can't be "abcddcba" form,
     * because it will be divisible by 11. It can only be "abcdcba".
     *
     * Suppose N has k digits, then, k must be less than 8, and total
     * number of candidates is 5 * 10^((k-1)/2) <= 5000.
     */
    int primePalindrome(int N) {
        if (N <= 11) {
            while (true) {
                if (isPrime(N)) {
                    break;
                }
                ++N;
            }
            return N;
        }
        
        vector<int> d;
        while (N > 0) {
            d.insert(d.begin(), N % 10);
            N /= 10;
        }
        int s = d.size();
        if (s % 2) {
            int k = 1;
            for (; k <= s/2; ++k) {
                if (d[s/2 + k] > d[s/2 - k]) {
                    d.resize(s/2 + 1);
                    incr(d);
                    break;
                } else if (d[s/2 + k] < d[s/2 - k]) {
                    d.resize(s/2 + 1);
                    break;
                }
            }
            if (k >= s/2) {
                d.resize(s/2 + 1);
            }
        } else {
            d.clear();
            d.push_back(1);
            for (int i = 0; i < s/2; ++i) {
                d.push_back(0);
            }
        }
        
        int res = 0;
        while (true) {
            res = getPalindrome(d);
            if (isPrime(res)) {
                break;
            }
            incr(d);
        }
        return res;
    }

private:
    void incr(vector<int>& d) {
        int c = 1;
        for (int i = d.size() - 1; i >= 0; --i) {
            d[i] += c;
            if (d[i] > 9) {
                d[i] = 0;
                c = 1;
            } else {
                c = 0;
            }
        }
        if (c == 1) {
            d.insert(d.begin(), 1);
        } else if (d[0] % 2 == 0) {
            ++d[0];
        }
    }
    int getPalindrome(vector<int>& d) {
        int s = d.size();
        int res = 0;
        for (int i = 0; i < s; ++i) {
            res *= 10;
            res += d[i];
        }
        for (int i = s - 2; i >= 0; --i) {
            res *= 10;
            res += d[i];
        }
        return res;
    }
    bool isPrime(int n) {
        if (n % 2 == 0) {
            return n == 2;
        } else if (n == 1) {
            return false;
        }
        
        int nroot = sqrt(n);
        for (int i = 3; i <= nroot; ++i) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int N = 102;

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = primePalindrome::Solution().primePalindrome(N);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
