// findIntegers.cpp
// leetcode
//
// Created by  Song Ding on 9/4/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findIntegers {
/*
// TODO: copy problem statement here
 600. Non-negative Integers without Consecutive Ones
 Hard
 
 249
 
 65
 
 Favorite
 
 Share
 Given a positive integer n, find the number of non-negative integers less than or equal to n, whose binary representations do NOT contain consecutive ones.
 
 Example 1:
 Input: 5
 Output: 5
 Explanation:
 Here are the non-negative integers <= 5 with their corresponding binary representations:
 0 : 0
 1 : 1
 2 : 10
 3 : 11
 4 : 100
 5 : 101
 Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule.
 Note: 1 <= n <= 109
 */

class Solution {
public:
    /**
     https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/discuss/103754/C%2B%2B-Non-DP-O(32)-Fibonacci-solution
     */
    int findIntegers3(int num) {
        vector<int> f(32);
        f[0] = 1; f[1] = 2; // # of integers for 0-(1<<i)-1
        int i = 0;
        for (; i <= 32 && (1<<i) <= num; ++i) {
            if (i >= 2) {
                f[i] = f[i-1]+f[i-2];
            }
        }
        int res = 0;
        for (--i; i >= 0; --i) {
            if ((1<<i)&num) {
                res += f[i];
                if ((1<<(i+1)&num)) {
                    return res;
                }
            }
        }
        return res+1;
    }
    int findIntegers2(int num) {
        vector<int> s(32), f(32);
        f[0] = 1; f[1] = 1; // (1<<i) bit is 1
        s[0] = 2; s[1] = 3;
        int i = 0;
        for (; i <= 32 && (1<<i) <= num; ++i) {
            if (i >= 2) {
                f[i] = s[i-2];
            }
            if (i >= 1) {
                s[i] = s[i-1]+f[i];
            }
        }
        int res = 0;
        for (--i; i >= 0; --i) {
            if ((1<<i)&num) {
                if (i == 0 || 1<<(i-1)&num) {
                    res += s[i];
                    break;
                } else {
                    res += s[i-1];
                }
            } else if (i == 0) {
                ++res;
            }
        }
        return res;
    }
    /**
     * let S(i) = # of integers that have i-bits.
     * then
     *   S(i) = SUM(S(k)), where 1<=k<=n-2
     *   S(1) = 2, S(2) = 1
     *
     */
    int findIntegers(int num) {
        // get bits of n
        vector<int> bits;
        int x = num;
        while (x) {
            bits.push_back(x&1);
            x >>= 1;
        }
        int n = bits.size();
        vector<int> cnt(n+3, 0);
        cnt[1] = 2;
        cnt[2] = 1;
        int sum = 0;
        for (int i = 3; i <= n+2; ++i) {
            sum += cnt[i-2];
            cnt[i] = sum;
        }
        
        // get cnt[1] to cnt[n-1], which = cnt[n+1]
        int res = 0;
        // when encounter >=2 consecutive 1's, then stop
        for (int i = n - 1; i >= 0; --i) {
            if (bits[i]) {
                // e.g. 100111... when i points to the 2nd 1.
                // then the prefix would be 1001, and all possible
                // candidate with prefix 1001 is cnt[i+1]+cnt[i]+...+cnt[1]
                if (i == 0 || bits[i-1]) {
                    res += cnt[i+3]; // cnt[i+1]+cnt[i]+...+cnt[1]
                    break;
                } else {
                    // e.g. 1001000..., when i points to 2nd 1.
                    // then prefix would be 10001, and all possible
                    // candiates with prefix 10001, is cnt[i]+...+cnt[1]
                    res += cnt[i+2]; // cnt[i]+cnt[i-1]+...+cnt[1]
                }
            } else if (i == 0) {
                ++res;
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int num;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {1},
        {2},
        {5},
    };

    vector< int > answers {
        2,
        3,
        5,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findIntegers::Solution().findIntegers3(dp.num);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
