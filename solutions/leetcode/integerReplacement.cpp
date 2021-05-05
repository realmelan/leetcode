//
//  integerReplacement.cpp
//  leetcode
//
//  Created by  Song Ding on 1/1/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace integerReplacement {
    class Solution {
    public:
        /**
         * when n is odd, mod 4 and see whether mod 4 is 1 or 3;
         */
        int integerReplacement2(int n) {
            int res = 0;
            while (n != 1) {
                if (n%2 == 0) {
                    n >>= 1;
                } else if (n%4 == 1) {
                    --n;
                } else {
                    ++n;
                }
                ++res;
            }
            return res;
        }
        /**
         For i = 2^k, r(i) = k;
         when there is a chance to go /2, it is an optimal
         move. When i is odd, choose +1 or -1 which make the
         new number divisible by 4.
         */
        int integerReplacement(int n) {
            int res = 0;
            while (n > 1) {
                if (n % 2 == 0) {
                    n >>= 1;
                } else {
                    if (n == 3) {
                        res += 2;
                        break;
                    }
                    if ((n + 1) % 4 == 0) {
                        ++n;
                    } else {
                        --n;
                    }
                }
                ++res;
            }
            return res;
        }
    };
}
/*
int main() {
    int i = 5;
    cout << integerReplacement::Solution().integerReplacement2(i) << endl;
}
// */
