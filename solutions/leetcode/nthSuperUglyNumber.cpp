//
//  nthSuperUglyNumber.cpp
//  leetcode
//
//  Created by  Song Ding on 11/28/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

/**
 313. Super Ugly Number
 Medium

 439

 110

 Favorite

 Share
 Write a program to find the nth super ugly number.

 Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k.

 Example:

 Input: n = 12, primes = [2,7,13,19]
 Output: 32
 Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12
              super ugly numbers given primes = [2,7,13,19] of size 4.
 Note:

 1 is a super ugly number for any given primes.
 The given numbers in primes are in ascending order.
 0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
 The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
 */

namespace nthSuperUglyNumber {
    class Solution {
    public:
        int nthSuperUglyNumber3(int n, vector<int>& primes) {
            vector<int> res(1, 1), idx(primes.size(), 0);
            while (res.size() < n) {
                vector<int> tmp;
                int mn = INT_MAX;
                for (int i = 0; i < primes.size(); ++i) {
                    tmp.push_back(res[idx[i]] * primes[i]);
                }
                for (int i = 0; i < primes.size(); ++i) {
                    mn = min(mn, tmp[i]);
                }
                for (int i = 0; i < primes.size(); ++i) {
                    if (mn == tmp[i]) ++idx[i];
                }
                res.push_back(mn);
            }
            return res.back();
        }
        /**
         * given current ugly number set, next ugly number can be constructed by multiplying a prime with
         * one of the ugly number in the current result set.
         * And for each prime, the ugly number that would make next possible ugly number would only increase,
         * so keep position of last ugly number used for each prime. Then to get next ugly number,  for each prime
         * number, try the ugly number at the position.
         */
        int nthSuperUglyNumber(int n, vector<int>& primes) {
            int np = primes.size();
            vector<int> idx(np, 0), res(n, 1);
            for (int i = 1; i < n; ++i) {
                int next = INT_MAX;
                vector<int> matchIdx;
                for (int j = 0; j < np; ++j) {
                    int p = res[idx[j]] * primes[j];
                    if (p < next) {
                        next = p;
                        matchIdx.clear();
                        matchIdx.push_back(j);
                    } else if (p == next) {
                        matchIdx.push_back(j);
                    }
                }
                res[i] = next;
                for (auto mi : matchIdx) {
                    ++idx[mi];
                }
            }
            return res[n-1];
        }
        int nthSuperUglyNumber2(int n, vector<int>& primes) {
            vector<long> res;
            int k = primes.size();
            
            res.reserve(n);
            long current = 1;
            while (res.size() < n) {
                res.push_back(current);
                long next = current * primes[k-1];
                
                for (int m = 0; m < k; ++m) {
                    int p = primes[m];
                    long low = (current + 1) / p;
                    
                    auto it = lower_bound(res.begin(), res.end(), low);
                    if ((*it) * p <= current) {
                        ++it;
                    }
                    if (next > (*it) * p) {
                        next = (*it) * p;
                    }
                }
                current = next;
            }
            //for (auto i : res) {
             //   cout << i << ",";
            //}
            //cout << endl;
            return (int)res[n-1];
        }
    };
}
/*
int main() {
    //vector<int> primes {7,19,29,37,41,47,53,59,61,79,83,89,101,103,109,127,131,137,139,157,167,179,181,199,211,229,233,239,241,251};
    vector<int> primes {2,7,13,19};
    cout << nthSuperUglyNumber::Solution().nthSuperUglyNumber(12, primes) << endl;
    return 0;
}
// */
