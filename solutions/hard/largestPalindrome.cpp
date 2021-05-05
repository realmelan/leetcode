// largestPalindrome.cpp
// leetcode
//
// Created by  Song Ding on 7/23/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace largestPalindrome {
/*
// TODO: copy problem statement here
 479. Largest Palindrome Product
 Hard
 
 73
 
 1231
 
 Favorite
 
 Share
 Find the largest palindrome made from the product of two n-digit numbers.
 
 Since the result could be very large, you should return the largest palindrome mod 1337.
 
 
 
 Example:
 
 Input: 2
 
 Output: 987
 
 Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
 
 
 
 Note:
 
 The range of n is [1,8].
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    int largestPalindrome2(int n) {
        vector<int> start{0, 9, 99, 990, 9999, 99990, 999999, 9999990, 99999999};
        vector<int> bottom{0, 0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
        for (int i = start[n]; i >= bottom[n]; i -= 11) {
            for (int j = bottom[n+1]-1; j >= bottom[n]; --j) {
                long t = (long)i * j;
                if (isPalindrome(t)) {
                    cout << i << "*" << j << "=" << t << endl;
                    return t % 1337;
                }
            }
        }
        return 0;
    }
    
    int largestPalindrome(int n) {
        static const vector<int> p10{0, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
        for (int i = p10[n+1]-1; i >= p10[n]; --i) {
            int t = i;
            long k = t;
            while (t) {
                int a = t % 10;
                k *= 10;
                k += a;
                t /= 10;
            }
            if (good(k, n)) {
                return k % 1337;
            }
        }
        return -1;
    }
    
    

private:
    bool isPalindrome(long k) {
        vector<int> bs;
        while (k) {
            bs.push_back(k%10);
            k /= 10;
        }
        int n = bs.size();
        for (int i = 0, j = n - 1; i < j; ++i,--j) {
            if (bs[i] != bs[j]) {
                return false;
            }
        }
        return true;
    }
    
    bool good(long k, int n) {
        static const vector<int> bottom{0, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
        for (long i = bottom[n+1]-1; i * i >= k; --i) {
            if (k % i == 0 && k / i < bottom[n+1]) {
                return true;
            }
        }
        return false;
    }
    
public:
    int largestPalindrome3(int n) {
        long prefix = (long)pow(10, n) - 1; // 9999 for n = 4.
        long prefixMin = (long)pow(10, n - 1); // 1000 for n = 4.
        for (long i = prefix; i >= prefixMin; --i) {
            long pal = construct1(i);
            if (canFind(pal, prefix)) {
                return (int)(pal % 1337);
            }
        }
        // At least we know answer always exists, 1111 * 1111 = 1234321 for n = 4.
        for (long i = prefix; i >= prefixMin; --i) {
            long pal = construct2(i);
            if (canFind(pal, prefix)) {
                return (int)(pal % 1337);
            }
        }
        return -1;
    }
    
    // With prefix xyz, construct pal xyzzyx.
    long construct1(long prefix) {
        long base = prefix;
        long rst = 0;
        while (prefix > 0) {
            base *= 10;
            long d = prefix % 10;
            rst = rst * 10 + d;
            prefix /= 10;
        }
        rst += base;
        return rst;
    }
    
    // With prefix xyz, construct pal xyzyx.
    long construct2(long prefix) {
        long base = prefix;
        prefix /= 10;
        long rst = 0;
        while (prefix > 0) {
            base *= 10;
            long d = prefix % 10;
            rst = rst * 10 + d;
            prefix /= 10;
        }
        rst += base;
        return rst;
    }
    
    // Check if there are 2 integers x, y such that
    // x * y = pal and x <= upper and y <= upper.
    bool canFind(long pal, long upper) {
        for (long i = upper; i * i >= pal; --i) {
            if (pal % i == 0 && pal / i <= upper) {
                return true;
            }
        }
        return false;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int n;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {2},
        {3},
        {4},
        {5}, // 230 ms
        {6},
        {7}, // 26 seconds
        {8}
    };

    vector< int > answers {
        987,
        650056
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = largestPalindrome::Solution().largestPalindrome(dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
