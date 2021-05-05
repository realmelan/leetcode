// superPow.cpp
// leetcode
//
// Created by  Song Ding on 10/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace superPow {
/*
// TODO: copy problem statement here
 372. Super Pow
 Medium

 156

 621

 Favorite

 Share
 Your task is to calculate ab mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.

 Example 1:

 Input: a = 2, b = [3]
 Output: 8
 Example 2:

 Input: a = 2, b = [1,0]
 Output: 1024
 */

class Solution {
public:
    int superPow3(int a, vector<int>& b) {
        int t = a % 1337;
        int res = 1, i = b.size() - 1;
        while (t != 1 && i >= 0) {
            res = res * powerx(t, b[i]) % 1337;
            t = powerx(t, 10) % 1337;
            --i;
        }
        return res;
    }
    int powerx(int t, int b) {
        // b <= 10;
        int res = 1;
        while (b) {
            if (b&1) {
                res = res * t % 1337;
            }
            t = (t * t) % 1337;
            b >>= 1;
        }
        return res;
    }
    /**
     * a^(10*b+c) = a^(10*b) * a^c = (a^10)^b * a^c
     */
    int superPow(int a, vector<int>& b) {
            int len = b.size();
            if (len <= 0) {
                return 1;
            }
            
            long res = power(a, b[len - 1]);
            if ((res % 1337) == 0) {
                return 0;
            } else if (res > 1337) {
                res = res % 1337;
            }
            int ap10 = power(a, 10);
            for (int i = len - 2; i >= 0; --i) {
                int d = b[i];
                res *= power(ap10, d);
                if ((res % 1337) == 0) {
                    return 0;
                } else if (res > 1337) {
                    res = res % 1337;
                }
                ap10 = power(ap10, 10);
            }
            
            return static_cast<int>(res);
        }
    private:
        int power(int a, int b) {
            long res = 1;
            for (int i = 0; i < b; ++i) {
                res *= a;
                if (res % 1337 == 0) {
                    return 0;
                } else if (res > 1337) {
                    res = res % 1337;
                }
            }
            return static_cast<int>(res);
        }
    
    /**
     * record every mod until a loop appears
     */
    int superPow2(int a, vector<int>& b) {
        if (a > 1337) {
            a %= 1337;
        }
        vector<int> mods;
        unordered_map<int, int> used;
        int c = 1;
        bool loop = false;
        while (dec(b)) {
            // decrease b and update c = c * a % 1337
            c *= a;
            c %= 1337;
            if (used.count(c)) {
                loop = true;
                break;
            } else {
                used[c] = used.size();
                mods.push_back(c);
            }
        }
        if (!loop) {
            return c;
        }
        int cprev = used[c];
        // there will be duplication from cprev to cnt
        // need to get b % (ccur - cprev)
        int mi = mod(b, mods.size() - cprev) + 1;
        return mods[mi%mods.size()];
    }

private:
    bool dec(vector<int>& b) {
        int n = b.size();
        int i = n-1;
        while (i >= 0 && b[i] == 0) {
            b[i] = 9;
            --i;
        }
        if (i < 0) {
            return false;
        }
        --b[i];
        return true;
    }
    
    int mod(vector<int>& b, int len) {
        
        int n = b.size();
        int t = len;
        vector<int> s;
        while (t) {
            s.push_back(t % 10);
            t /= 10;
        }
        
        int res = 0;
        while (true) {
            int i = n-1;
            for (int j = 0; j < s.size() && i >= 0; ++j, --i) {
                b[i] -= s[j];
                if (b[i] < 0) {
                    b[i] += 10;
                    --b[i-1];
                }
            }
            while (i > 0 && b[i] < 0) {
                b[i] += 10;
                --b[i-1];
            }
            if (i == 0 && b[i] < 0) {
                // found result
                for (int j = 0; j < n; ++j) {
                    res *= 10;
                    res += b[j];
                }
                break;
            }
        }
        return res + len;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int a;
        vector<int> b;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{2,{3}},
        {2,{1,0}},
    };

    vector< int > answers {
        8,
        1024
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = superPow::Solution().superPow3(dp.a, dp.b);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
