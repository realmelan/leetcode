//
//  smallestGoodBase.cpp
//  leetcode
//
//  Created by  Song Ding on 2/27/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace smallestGoodBase {
/**
 483. Smallest Good Base
 Hard

 108

 277

 Favorite

 Share
 For an integer n, we call k>=2 a good base of n, if all digits of n base k are 1.

 Now given a string representing n, you should return the smallest good base of n in string format.

 Example 1:

 Input: "13"
 Output: "3"
 Explanation: 13 base 3 is 111.
  

 Example 2:

 Input: "4681"
 Output: "8"
 Explanation: 4681 base 8 is 11111.
  

 Example 3:

 Input: "1000000000000000000"
 Output: "999999999999999999"
 Explanation: 1000000000000000000 base 999999999999999999 is 11.
  

 Note:

 The range of n is [3, 10^18].
 The string representing n is always valid and will not have leading zeros.
 */
class Solution {
public:
    /**
     long can be used to represent n.
     // first do 1+x+x^2, then 1+x+x^2+x^3
     // if no match, then start from 2 till sqrt(n).
     */
    string smallestGoodBase(string n) {
        long nl = 0;
        istringstream iss(n);
        iss >> nl;
        
        ostringstream oss;
        
        for (int t = 64; t >= 2; --t) {
            long ntsqrt = pow(exp(1), log((long double)nl)/t);
            cout << "ntsqrt=" << ntsqrt << endl;
            if (ntsqrt <= 1) {
                continue;
            }
        
            long s = 1;
            for (int i = 0; i < t; ++i) {
                s *= ntsqrt;
                ++s;
            }
            if (s == nl) {
                oss << ntsqrt;
                return oss.str();
            }
        }
        
        oss << nl - 1;
        return oss.str();
    }
};
}

/**
int main() {
    string n = "1000000000000000000";
    long i = 199995;
    long s = 1 + i;
    s *= i;
    ++s;
    s *= i;
    ++s;
    cout << s << endl;
    ostringstream oss;
    oss << s;
    clock_t start = clock();
    cout << smallestGoodBase::Solution().smallestGoodBase(n) << endl;
    clock_t end = clock();
    cout << end - start << endl;
    return 0;
}
 */
