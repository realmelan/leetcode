// numDupDigitsAtMostN.cpp
// leetcode
//
// Created by  Song Ding on 8/31/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numDupDigitsAtMostN {
/*
// TODO: copy problem statement here
 1012. Numbers With Repeated Digits
 Hard
 
 97
 
 33
 
 Favorite
 
 Share
 Given a positive integer N, return the number of positive integers less than or equal to N that have at least 1 repeated digit.
 
 
 
 Example 1:
 
 Input: 20
 Output: 1
 Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
 Example 2:
 
 Input: 100
 Output: 10
 Explanation: The positive numbers (<= 100) with atleast 1 repeated digit are 11, 22, 33, 44, 55, 66, 77, 88, 99, and 100.
 Example 3:
 
 Input: 1000
 Output: 262
 
 
 Note:
 
 1 <= N <= 10^9
 */

class Solution {
public:
    int numDupDigitsAtMostN(int N) {
        return numDupDigitsAtMostN_clean(N);
    }
    /**
     * much cleaner implementation!
     * https://leetcode.com/problems/numbers-with-repeated-digits/discuss/256725/JavaPython-Count-the-Number-Without-Repeated-Digit
     *
     * 1, use N+1 instead of N, so that the last prefix doesn't require special handling
     * 2, use permuation(m,n) to simplify coding!
     */
    int numDupDigitsAtMostN_clean(int N) {
        vector<int> digits;
        for (int x = N+1; x > 0; x /= 10) {
            digits.push_back(x % 10);
        }
        
        int dn = digits.size();
        int cnt = 0;
        for (int i = 1; i < dn; ++i) {
            cnt += 9 * permutation(9, i-1);
        }
        
        // get prefix
        reverse(digits.begin(), digits.end());
        vector<bool> used(10, false);
        for (int i = 0; i < dn; ++i) {
            int vd = 0;
            for (int j = i == 0 ? 1 : 0; j < digits[i]; ++j) {
                if (!used[j]) {
                    ++vd;
                }
            }
            cnt += vd * permutation(9 - i, dn - 1 - i);
            if (used[digits[i]]) {
                break;
            }
            used[digits[i]] = true;
        }
        return N - cnt;
    }
    int permutation(int m, int n) {
        return n <= 0 ? 1 : permutation(m, n-1) * (m-n+1);
    }
    /**
     * count # of numbers that don't contain duplicate digit that are <=N
     */
    int numDupDigitsAtMostN_notclean(int N) {
        vector<int> digits;
        int n = N;
        int sum = 0;
        int s = 9;
        int m = 9;
        vector<int> t;
        while (n/10) {
            digits.push_back(n%10);
            t.push_back(s);
            sum += s;
            
            n /= 10;
            s *= m--;
        }
        digits.push_back(n);
        
        // now consider numbers that have same # of digits as N that
        // have unique digits.
        vector<int> prefix;
        vector<bool> used(10,false);
        bool good = true;
        for (int i = digits.size() - 1; i >= 0; --i) {
            int m = 10 - prefix.size();
            for (int j = prefix.size() - 1; j >= 0; --j) {
                prefix[j] *= m;
            }
            prefix.push_back(0);
            if (good) {
                // find out how many digits are possible
                int j = i == digits.size() - 1 ? 1 : 0;
                for (; j < digits[i]; ++j) {
                    if (!used[j]) {
                        ++prefix.back();
                    }
                }
                good = !used[digits[i]];
            }
            used[digits[i]] = true;
        
        }
        for (auto i : prefix) {
            sum += i;
        }
        sum += good ? 1 : 0;
        
        return N - sum;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int N;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {20},
        {100},
        {1000},
        {110},
        
        {200},
    };

    vector< int > answers {
        1,
        10,
        262,
        12,
        38
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = numDupDigitsAtMostN::Solution().numDupDigitsAtMostN(dp.N);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
