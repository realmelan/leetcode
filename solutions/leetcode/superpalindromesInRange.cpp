// superpalindromesInRange.cpp
// leetcode
//
// Created by  Song Ding on 11/13/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace superpalindromesInRange {
/**
 906. Super Palindromes
 Hard

 56

 138

 Favorite

 Share
 Let's say a positive integer is a superpalindrome if it is a palindrome, and it is also the square of a palindrome.

 Now, given two positive integers L and R (represented as strings), return the number of superpalindromes in the inclusive range [L, R].

  

 Example 1:

 Input: L = "4", R = "1000"
 Output: 4
 Explanation: 4, 9, 121, and 484 are superpalindromes.
 Note that 676 is not a superpalindrome: 26 * 26 = 676, but 26 is not a palindrome.
  

 Note:

 1 <= len(L) <= 18
 1 <= len(R) <= 18
 L and R are strings representing integers in the range [1, 10^18).
 int(L) <= int(R)
 */
class Solution {
public:
    /**
     * construct all palindromes:
     * for number x, construct xx and x0x, x1x, ..., x9x.
     * then starting from sqrt(L) and test whether each palindrome square is still a palindrome.
     *
     * for all new palindrome numbers, adding same digit at both end and form a new one
     * do it for odd and even separately.
     */
    int superpalindromesInRange(string L, string R) {
        long l = strtol(L.c_str(), NULL, 10), r = strtol(R.c_str(), NULL, 10);
        vector<int> oddPa{0,1,2,3,4,5,6,7,8,9}, evenPa{0,11,22,33,44,55,66,77,88,99};
            
        return 0;
    }
    /**
     * find next palindrome and test whether its squre is palindrome too.
     */
    int superpalindromesInRange_Slow(string L, string R) {
        long l = strtol(L.c_str(), NULL, 10), r = strtol(R.c_str(), NULL, 10);
        int lroot = sqrt(l);
        long t = lroot;
        if (t*t >= l) {
            --lroot;
        }
        
        long c = lroot;
        int res = 0;
        while (true) {
            long t = next_palindrome(c);
            long tsq = t * t;
            if (tsq > r) {
                break;
            }
            if (is_palindrome(tsq)) {
                //cout << tsq << endl;
                ++res;
            }
            c = t;
        }
        return res;
    }
    long next_palindrome(long x) {
        if (x <= 0) {
            return 1;
        }
        vector<int> d;
        long t = x;
        while (t) {
            d.push_back(t%10);
            t /= 10;
        }
        int nd = d.size();
        t = 0;
        long base=1;
        int i = nd-1;
        for (; i >= nd/2; --i) {
            t *= 10;
            t += d[i];
            base*=10;
        }
        long tt = t;
        i = nd/2;
        if (nd%2) {
            ++i;
        }
        for (; i < nd; ++i) {
            tt *= 10;
            tt += d[i];
        }
        if (tt > x) {
            return tt;
        }
        // t is 99999...
        ++t;
        if (t >= base) {
            t *= base;
            if (nd%2) {
                t /= 10;
            }
            ++t;
            return t;
        }
        d.clear();
        x = t;
        while (x) {
            d.push_back(x%10);
            x /= 10;
        }
        i = 0;
        if (nd%2) {
            ++i;
        }
        for (; i < d.size(); ++i) {
            t *= 10;
            t += d[i];
        }
        return t;
    }
    bool is_palindrome(long x) {
        vector<int> d;
        while (x) {
            d.push_back(x%10);
            x /= 10;
        }
        int n = d.size();
        int i = 0, j = n-1;
        while (i < j) {
            if (d[i] != d[j]) {
                return false;
            }
            ++i;
            --j;
        }
        return true;
    }
    /**
     * only consider numbers that when squared, there is no carry-over.
     *
     * So, only numbers that meet below conditions:
     *  1, the first and last digit is 2, then there is at most one '1'
     *  2, the first and last digit is 1, then there is at most one '2':
     *    1), if there is one '2', then it can only have at most two '1'
     *    2), if tehre is no '2', then it can only have at most nine '1'.
     *
     * This can be proved by trying different first/last digit.
     */
    int superpalindromesInRange2(string L, string R) {
        int ln = L.size();
        int rn = R.size();
        
        int lres = 0;
        if (ln % 2 == 0) {
            lres = spcnt(ln - 1);
        } else {
            lres = spcnt(ln - 1) + spler(L, 1);
        }
        
        int rres = 0;
        if (rn % 2 == 0) {
            rres = spcnt(rn - 1);
        } else {
            rres = spcnt(rn - 1) + spler(R, 0);
        }
        return rres - lres;
    }

private:
    int spcnt(int n) {
        /*
        static const vector<int> preset {
            0,3,0,2,0,5,0,3,0,8,0,5,0,13,0,9,0,22,0
        };
         */
        static const vector<int> preset {
            0,3,3,5,5,10,10,13,13,21,21,26,26,39,39,48,48,70,70
        };
        return preset[n];
    }
    int spler(string R, int diff) {
        static const vector<vector<int>> preset {
            {},
            {1,2,3},
            {11,22},
            {101,111,121,202,212},
            {1001,1111,2002},
            {10001,10101,10201,11011,11111,11211,20002,20102},
            {100001,101101,110011,111111,200002},
            {1000001,1001001,1002001,1010101,1011101,1012101,1100011,1101011,1102011,1110111,1111111,2000002,2001002},
            {10000001,10011001,10100101,10111101,11000011,11011011,11100111,11111111,20000002},
            {100000001,100010001,100020001,100101001,100111001,100121001,101000101,101010101,101020101,101101101,101111101,110000011,110010011,110020011,110101011,110111011,111000111,111010111,111101111,111111111,200000002,200010002}
        };
        int n = R.size();
        double dr = 0;
        for (int i = 0; i < n; ++i) {
            dr *= 10;
            dr += R[i] - '0';
        }
        dr -= diff;
        int root = (int)sqrt(dr);
        int rootn = 0;
        int t = root;
        while (t) {
            ++rootn;
            t /= 10;
        }
        auto it = std::upper_bound(preset[rootn].begin(), preset[rootn].end(), root);
        if (it == preset[rootn].end()) {
            return preset[rootn].size();
        } else {
            return std::distance(preset[rootn].begin(), it);
        }
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    struct d {
        string L;
        string R;
    };
    
    vector<struct d> p {
        {"4","1000"},
        {"5","1000"},
        {"5","44944"},
        {"1","2"},
        {"1","19028"},
        {"111","231"},
    };

    vector< int > answers {
        4,
        3,
        8,
        1,
        8,
        1
    };
    int i = 5;

    // TODO: add return type and paramters.
    for (auto& dp : p) {
        clock_t tstart = clock();
        auto res = superpalindromesInRange::Solution().superpalindromesInRange2(dp.L, dp.R);
        cout << clock() - tstart << endl;
        cout << res << endl << endl;
    }
    return 0;
}
//*/
