// nearestPalindromic.cpp
// leetcode
//
// Created by  Song Ding on 4/15/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace nearestPalindromic {
/*
 564. Find the Closest Palindrome
 Hard
 
 146
 
 592
 
 Favorite
 
 Share
 Given an integer n, find the closest integer (not including itself), which is a palindrome.
 
 The 'closest' is defined as absolute difference minimized between two integers.
 
 Example 1:
 Input: "123"
 Output: "121"
 Note:
 The input n is a positive integer represented by string, whose length will not exceed 18.
 If there is a tie, return the smaller one as answer.
 */
class Solution {
public:
    /**
     * Don't manipute strings, but convert the upper half and whole palimdrom into a long integer
     * to find diff.
     */
    string nearestPalindromic(string n) {
        return "";
    }
    /**
     * since n has at most 18, the halves can be expressed using integer.
     * now, for any number, considering increasing and decreasing the mid
     * digit or the last digit of the first half.
     */
    string nearestPalindromic_optimal(string n) {
        int nl = n.size();
        int i = 0;
        int j = nl - 1;
        int x = 0, xp = 0, y = 0;
        int xb = 1;
        while (i < j) {
            x *= 10;
            x += n[i] - '0';
            
            xp += (n[i] - '0') * xb;
            y += (n[j] - '0') * xb;
            
            xb *= 10;
            
            ++i;
            --j;
        }
        int xpb = xb;
        while (xpb > xp) {
            xpb /= 10;
        }
        xpb *= 10;
        
        string res;
        if (nl == 1) {
            char c = n[0];
            if (c == '0') {
                res.push_back('1');
            } else {
                --c;
                res.push_back(c);
            }
            return res;
        } else if (i == j) {
            int df = INT_MAX;
            ostringstream oss1;
            int mid = n[i] - '0';
            // increase mid
            int mid1 = mid + 1;
            int x1 = x;
            if (mid1 > 9) {
                x1 = x + 1;
                mid1 = 0;
            }
            if (x1 == xb) {
                df = xb + 1 - y;
                oss1 << x1;
                int t = x1;
                while (t) {
                    oss1 << t%10;
                    t /= 10;
                }
                res.assign(oss1.str());
            } else {
                df = xb - y + xp;
                oss1 << x1 << mid1;
                int t = x1;
                while (t) {
                    oss1 << t%10;
                    t /= 10;
                }
                res.assign(oss1.str());
            }
            
            // mid stays the same if xp != y
            int df2 = 0;
            if (xp != y) {
                ostringstream oss2;
                df2 = abs(y - xp);
                if (df2 <= df) {
                    df = df2;
                    oss2 << x << mid;
                    int t = x;
                    while (t) {
                        oss2 << t%10;
                        t /= 10;
                    }
                    res.assign(oss2.str());
                }
            }
            // decrease mid
            int df3 = 0;
            int mid3 = mid - 1;
            int x3 = x;
            if (mid3 < 0) {
                x3 -= 1;
                mid3 = 9;
            }
            ostringstream oss3;
            if (x3 < x) {
                // if # of digits is smaller in x3 than in x1, 10->9, or 100->99
                if (x3 == 0) {
                    int df3 = 1 + y;
                    if (df3 <= df) {
                        oss3 << 99;
                        res.assign(oss3.str());
                    }
                } else if (x3 < xb/10) {
                    int df3 = 1 + y;
                    if (df3 <= df) {
                        oss3 << x3 << 9 << (xb - 1);
                        res.assign(oss3.str());
                    }
                } else {
                    int df3 = y - xp + xpb + xpb/10;
                    if (df3 <= df) {
                        oss3 << x3 << 9;
                        int t = x3;
                        while (t) {
                            oss3 << t%10;
                            t /= 10;
                        }
                        res.assign(oss3.str());
                    }
                }
            } else {
                ostringstream oss3;
                df3 = xb + y - xp;
                if (df3 <= df) {
                    df = df3;
                    oss3 << x << mid3;
                    int t = x;
                    while (t) {
                        oss3 << t%10;
                        t /= 10;
                    }
                    res.assign(oss3.str());
                }
            }
        } else {
            // i > j, which means there are even number of digits
            int df = INT_MAX;
            ostringstream oss1;
            // increase the last digit of x
            int x1 = x + 1;
            if (x1 == xb) {
                df = xb + 1 - y;
                oss1 << x1;
                int t = x1/10;
                while (t) {
                    oss1 << t%10;
                    t /= 10;
                }
            } else {
                df = xb + xb/10 + xp - y;
                oss1 << x1 << xp + xb/10;
            }
            res.assign(oss1.str());
            
            // x stay the same if y != xp
            if (xp != y) {
                ostringstream oss2;
                int df2 = abs(y - xp);
                if (df2 <= df) {
                    df = df2;
                    oss2 << x;
                    int t = x;
                    while (t) {
                        oss2 << t%10;
                        t /= 10;
                    }
                    res.assign(oss2.str());
                }
            }
            
            // decrease x
            int x3 = x - 1;
            ostringstream oss3;
            if (x3 == 0) {
                int df3 = y + 1;
                if (df3 <= df) {
                    oss3 << 9;
                    res.assign(oss3.str());
                }
            } else if (x3 < xb/10) {
                //10->9, 100->99
                int df3 = 1 + y;
                if (df3 <= df) {
                    oss3 << xb/10 - 1 << xb - 1;
                    res.assign(oss3.str());
                }
            } else {
                int df3 = xpb + y + xpb/10 - xp;
                if (df3 <= df) {
                    oss3 << x3;
                    int t = x3;
                    while (t) {
                        oss3 << t%10;
                        t /= 10;
                    }
                    res.assign(oss3.str());
                }
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
        string n;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"123"},
        {"121"},
        {"10000"},
        {"1000"},
        {"9999"},
        {"11"},
        {"10"},
        {"100001"},
        {"100000"},
        {"99999"},
        {"10001"},
        {"10002"},
        {"9"},
        {"1"},
        {"0"},
        {"202"},
        {"101"},
        {"10"},
        {"1237000456789"},
        {"123700456789"},
        {"1213"}
        
    };
    
    vector< string > answers {
        "121",
        "9999",
        "10001"
    };
    
    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = nearestPalindromic::Solution().nearestPalindromic(dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
