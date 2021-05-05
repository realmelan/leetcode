//
//  singleNumber2.cpp
//  leetcode
//
//  Created by  Song Ding on 11/5/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace singleNumber2 {

    class Solution {
    public:
        /**
         * https://leetcode.com/problems/single-number-ii/discuss/43295/Detailed-explanation-and-generalization-of-the-bitwise-operation-method-for-single-numbers
         */
        int singleNumber(vector<int>& nums) {
            int x1 = 0, x2= 0;
            for (int i : nums) {
                x2 ^= x1 & i;
                x1 ^= i;
                int mask = ~(x2 & x1);
                x1 &= mask;
                x2 &= mask;
            }
            return x1;
        }
        /**
         https://github.com/realmelan/leetcode/blob/master/SingleNumber.md
         */
        int singleNumber3(vector<int>& nums) {
            int x2 = 0, x1 = 0;
            for (auto k : nums) {
                int t = x1|x2;
                x2 = (x2&~k) | (x1&k);
                x1 = (x1&~k) | (~t&k);
            }
            return x1;
        }
        /**
         For each bit of an integer, count the number of bits
         which are set to 1. If the count exceeds k, get # % k.
         
         if # % k == 1, then the bit of the single number is set.
         */
        int singleNumber2(vector<int>& nums) {
            vector<unsigned int> n;
            int min = nums[0];
            for (int i : nums) {
                if (min > i) {
                    min = i;
                }
            }
            for (int i : nums) {
                n.push_back(i - min);
            }
            
            vector<int> bitCounts(32, 0);
            for (unsigned int i : n) {
                int j = 0;
                while (i) {
                    if (i & 1) {
                        ++bitCounts[j];
                    }
                    ++j;
                    i >>= 1;
                }
            }
            
            unsigned int base = 1;
            unsigned int res = 0;
            for (int i : bitCounts) {
                res += (i % 3) * base;
                base <<= 1;
            }
            int r = res + min;
            return r;
        }
    };
    
}
/*
int main() {
    vector<int> v{-2,-2,1,1,-3,1,-3,-3,-4,-2};
    cout << singleNumber2::Solution().singleNumber(v) << endl;
    return 0;
}
// */
