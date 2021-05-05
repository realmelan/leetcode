//
//  divide.cpp
//  leetcode
//
//  Created by  Song Ding on 1/25/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace divide {
    class Solution {
    public:
        /**
         bit shift can simulate *2, and subtraction
         can simulate division.
         
         
         */
        int divide(int dividend, int divisor) {
            long d = divisor;
            long n = dividend;
            int MAX_INT = 0x7fffffff;
            int MIN_INT = -(1 << 31);
            
            if (d == 0 || (n == MIN_INT && d == -1)) {
                return MAX_INT;
            } else if (n == 0) {
                return 0;
            }
            
            int sign = 1;
            if (n > 0 && d < 0) {
                sign = -1;
                d = -d;
            } else if (n < 0 && d > 0) {
                sign = -1;
                n = -n;
            } else if (n < 0 && d < 0) {
                n = -n;
                d = -d;
            }
            
            if (d == 1) {
                return sign * n;
            }
            
            long od = d;
            int res = 0;
            long q = 1;
            while (n >= d) {
                d <<= 1;
                q <<= 1;
            }
            d >>= 1;
            q >>= 1;
            
            while (n >= od) {
                if (n >= d) {
                    res += q;
                    n -= d;
                }
                q >>= 1;
                d >>= 1;
            }
            return sign * res;
        }
    };
}
/*
int main() {
    int n = -2147483648;
    int d = 2;
    cout << divide::Solution().divide(n, d) << endl;
    return 0;
}
 */
