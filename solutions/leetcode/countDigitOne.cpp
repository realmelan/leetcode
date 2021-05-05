// countDigitOne.cpp
// leetcode
//
// Created by  Song Ding on 3/20/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;
/**
 233. Number of Digit One
 Hard

 201

 506

 Favorite

 Share
 Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

 Example:

 Input: 13
 Output: 6
 Explanation: Digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.
 */

namespace countDigitOne {

class Solution {
public:
    int countDigitOne(int n) {
        int res = 0;
        int base = 1; // the # of 1 on the 100-th position or 1000-th position.
        int c = 0; // # of 1's for all numbers up to base (exclusive)
        int r = 0; // reminder of n % base
        while (n > 0) {
            int d = n % 10;
            if (d == 1) {
                res += r + 1; // when prefix is n, 1 on base's position can appear r+1 times.
            } else if (d > 1) {
                res += base; // else it can appear base times.
            }
            res += d * c; // add # of 1's for all lower positions up to base for prefix from 0 to d-1.
            // update # of 1's up to base*10, here, 10*c means all lower numbers can have prefix at base position from 0 to 9
            // that is, # of 1's up to base(exclusive) can be duplicated 10 times, when extending to base
            // base means add all 1's on the base-position.
            c = base + 10 * c;

            r += d * base;
            
            n /= 10;
            base *= 10;
        }
        return res;
    }
    /**
     * https://leetcode.com/problems/number-of-digit-one/discuss/64381/4%2B-lines-O(log-n)-C%2B%2BJavaPython
     * sum up # of 1's on each position(1's, 10-th, 100-th)
     * for n, # of 1's on the 100-th = (n/100/10+1) * 100 if n/100%10 >= 2, that is, set the 100-th position to 1, the lowest bits can vary from 0 to 100-1,
     * that is total 100 for a fixed prefix n/100/10.
     * When the 100-th digit is 1, for prefix of n/100, there are only n%100+1 times, 1 can appear on the 100-th.
     * When the 100-th digit is 0, only prefix n/100/10+1 will work.
     * The case of 100-th digit being 0,1 and >1 can be expressed using (n/100+8)/10*base.
     */
    int countDigitOne2(int n) {
        int res = 0;
        int base = 1;
        for (; base <= n; base *= 10) {
            res += (n/base+8)/10 * base + ((n/base%10 == 1) ? n%base+1 : 0);
        }
        return res;
    }
private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int num = 999;
    // TODO: add return type and paramters.
    clock_t start = clock();
    int res = countDigitOne::Solution().countDigitOne2(num);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
