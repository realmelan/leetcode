// strongPasswordChecker.cpp
// leetcode
//
// Created by  Song Ding on 6/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace strongPasswordChecker {
/*
// TODO: copy problem statement here
 420. Strong Password Checker
 Hard
 
 85
 
 358
 
 Favorite
 
 Share
 A password is considered strong if below conditions are all met:
 
 It has at least 6 characters and at most 20 characters.
 It must contain at least one lowercase letter, at least one uppercase letter, and at least one digit.
 It must NOT contain three repeating characters in a row ("...aaa..." is weak, but "...aa...a..." is strong, assuming other conditions are met).
 Write a function strongPasswordChecker(s), that takes a string s as input, and return the MINIMUM change required to make s a strong password. If s is already strong, return 0.
 
 Insertion, deletion or replace of any one character are all considered as one change.
 */

class Solution {
public:
    /**
    * It's always better to replace a character with a char needed.
    * Say, if some char requirements are not met, say missing a capital char
    * then if a >=3 repeating character sequence is met, it is better to
    * alter the 3rd character to the one missing.
    *
    * If length is <6, then it's better to add a character that's missing instead
    * of replace.
    *
    * If length is >20, then first delete some characters, then do some replacements
    * if some characters are missing.
    *
    * However, which characters are to be deleted? characters should be deleted in this order:
    *   1, a repeating substring of 3*k characters, deleting 1 char would reduce 1
    *.     replacement
    *.  2, a repeating substring of 3*k+1 characters, deleting 2 chars would reduce 1
    *.     replacement
    *.  3, a repeating substring of 3*k+2 characters, deleting 3 chars would reduce 1
    *.     replacement
    * Note, once a(2) char(s) is deleted from a repeating substring, it is transformed
    * into a 3*(k-1)+2 repeating substring.
    */
    int strongPasswordChecker2(string s) {
        int needUpper = 1, needLower = 1, needDigit = 1;
        int toReplace = 0;
        int n = s.size();
        
        int addTarget = max(0, 6-n), toAdd = 0;
        for (int l = 0, r = 0; r < n; ++r) {
            if (isUpper(s[r])) {
                needUpper = 0;
            } else if (isLower(s[r])) {
                needLower = 0;
            } else if (isDigit(s[r])) {
                needDigit = 0;
            }

            if (s[r] == s[l]) {
                if (r - l >= 2) {
                    if (toAdd < addTarget) {
                        ++toAdd;
                    } else {
                        ++toReplace;
                    }
                    l = r+1;
                }
            } else {
                l = r;
            }
        }
        
        if (n <= 20) {
            return max(addTarget+toReplace, needUpper+needLower+needDigit);
        } else {
            toReplace = 0;
            vector<unordered_map<int,int>> lenCnt(3);
            for (int l = 0, r = 0; r <= n; ++r) {
                if ((r == n || s[r] != s[l])) {
                    if (r-l>2) {
                        ++lenCnt[(r-l)%3][r-l];
                    }
                    l = r;
                }
            }
            int toDelete = 0, deleteTarget = n-20;
            for (int i = 0; i < 3; ++i) {
                for (auto& p : lenCnt[i]) {
                    if (i < 2) {
                        int d = max(0, min(p.second, (deleteTarget - toDelete) / (i+1)));
                        toDelete += d * (i+1);
                        p.second -= d;
                        if (p.first - i-1 > 2) {
                            lenCnt[2][p.first-i-1] += d;
                        }
                    }
                    
                    toReplace += p.second * (p.first / 3);
                }
            }
            // now consider deletions from 3*k+2 substrings;
            int d = (deleteTarget - toDelete) / 3;
            toReplace -= d;
            return deleteTarget + max(toReplace, needUpper+needLower+needDigit);
        }
    }
    
    
    bool isUpper(char c) {
        return c >= 'A' && c <= 'Z';
    }
    int upperMask() {
        return 1;
    }
    bool isLower(char c) {
        return c >= 'a' && c <= 'z';
    }
    int lowerMask() {
        return 2;
    }
    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }
    int digitMask() {
        return 4;
    }
    int mask(char c) {
        if (isUpper(c)) {
            return upperMask();
        } else if (isLower(c)) {
            return lowerMask();
        } else if (isDigit(c)) {
            return digitMask();
        } else {
            return 0;
        }
    }
    int bitsize(int mask) {
        switch(mask) {
            case 0: return 0;
            case 1:
            case 2:
            case 4: return 1;
            case 3:
            case 5:
            case 6: return 2;
            case 7: return 3;
            default: return -1;
        }
    }
    
    /**
     * Based on the TLE version, don't need to keep count for every character.
     * When replacing a char, it makes sense to replace it with a char that will not be the same
     * as previous or after chars. That means we can think it will not be the same as left/right
     * chars.
     *
     * Only keep count for each mask(uppercase, lowercase, and digit, and the last two characters).
     * Note, if there is a replace, then the replacing character is a special character that will not
     * match later characters in s.
     */
    int strongPasswordChecker(string s) {
        struct st {
            struct maskSt {
                int nch;
                char c1;
                char c2;
                
                maskSt() {
                    nch = -1;
                    c1 = 0;
                    c2 = 0;
                }
            };
            vector<maskSt> masks;
            
            st() : masks(8) {}
        };
        
        int n = s.size();
        if (n <= 3) {
            return 6 - n;
        }
        
        int ma = mask(s[0]);
        vector<st> cur(2);
        cur[0].masks[0].nch = 1;
        const vector<int> allMasks{0,1,2,4};
        for (auto m : allMasks) {
            if (m == ma) {
                cur[1].masks[m].nch = 0;
                cur[1].masks[m].c2 = s[0];
            } else {
                cur[1].masks[m].nch = 1;
            }
        }
        
        for (int i = 1; i < n; ++i) {
            int c = s[i];
            int ma = mask(c);
            int ni = i + 2 < 21 ? i+2 : 21;
            vector<st> next(ni);
            
            // section j = 0
            next[0].masks[0].nch = cur[0].masks[0].nch + 1; // delete all
            
            // section j = 1
            // from previous j = 0
            for (auto m : allMasks) {
                if (m != ma) { // replace char
                    next[1].masks[m].nch = cur[0].masks[0].nch + 1;
                } else { // keep current char
                    next[1].masks[m].nch = cur[0].masks[0].nch;
                    next[1].masks[m].c2 = s[0];
                }
            }
            // from previous j = 1, delete current char
            for (int k = 0; k < 8; ++k) {
                if (cur[1].masks[k].nch >= 0) {
                    int t = cur[1].masks[k].nch + 1;
                    if (next[1].masks[k].nch < 0 || next[1].masks[k].nch > t) {
                        next[1].masks[k].nch = t;
                        next[1].masks[k].c1 = cur[1].masks[k].c1;
                        next[1].masks[k].c2 = cur[1].masks[k].c2;
                    }
                }
            }
            
            for (int j = 2; j <= i+1 && j <= 20; ++j) {
                // from previous j (delete current char)
                if (j < cur.size()) {
                    for (int k = 0; k < 8; ++k) {
                        if (cur[j].masks[k].nch >= 0) {
                            next[j].masks[k].nch = cur[j].masks[k].nch + 1;
                            next[j].masks[k].c1 = cur[j].masks[k].c1;
                            next[j].masks[k].c2 = cur[j].masks[k].c2;
                        }
                    }
                }
                
                
                if (j - 1 < cur.size()) {
                    // from previous j-1, keep current one
                    for (int k = 0; k < 8; ++k) {
                        if (cur[j-1].masks[k].nch >= 0
                            && !(cur[j-1].masks[k].c1 == cur[j-1].masks[k].c2 && cur[j-1].masks[k].c2 == c)
                            && (next[j].masks[k|ma].nch < 0 || next[j].masks[k|ma].nch >= cur[j-1].masks[k].nch)) {
                            if (next[j].masks[k|ma].nch < 0 || next[j].masks[k|ma].nch > cur[j-1].masks[k].nch || c != cur[j-1].masks[k].c2) {
                                next[j].masks[k|ma].c1 = cur[j-1].masks[k].c2;
                                next[j].masks[k|ma].c2 = c;
                            } else {
                                next[j].masks[k|ma].c1 = next[j].masks[k|ma].c2;
                                next[j].masks[k|ma].c2 = c;
                            }
                            next[j].masks[k|ma].nch = cur[j-1].masks[k].nch;
                        }
                    }
                
                    // from previous j-1, replace it
                    for (int k = 0; k < 8; ++k) {
                        if (cur[j-1].masks[k].nch >= 0) {
                            for (auto m : allMasks) {
                                // replace it with uppercase, lowercase, digit
                                if (next[j].masks[k|m].nch < 0 || next[j].masks[k|m].nch >= cur[j-1].masks[k].nch + 1) {
                                    next[j].masks[k|m].nch = cur[j-1].masks[k].nch + 1;
                                    next[j].masks[k|m].c1 = cur[j-1].masks[k].c2;
                                    next[j].masks[k|m].c2 = 0;
                                }
                            }
                        }
                    }
                }
                
            } // for j from 2 to i+1
            
            cur.swap(next);
        } // for i from 1 to n
        
        
        int res = INT_MAX;
        
        int ni = n < 20 ? n : 20;
        for (int k = 0; k < 8; ++k) {
            if (cur[ni].masks[k].nch >= 0) {
                int t = cur[ni].masks[k].nch + 3 - bitsize(k);
                if (n + t < 6) {
                    t += 6 - n - t;
                }
                res = min(res, t);
            }
        }
        
        return res;
    }
    
    /**
     * if n <= 2, (6 - n) insertions have to be done, and the insertions can have lowercase
     *  uppercase, digit.
     *
     * Insertion is only good for n < 6, for n >= 6, replace is better than insertion.
     *
     * let dp[i][j][0..7][c3][c2][c1] = min # of changes to have s[0..i] to have j valid characters. 0 to 7
     *  represent different scenarios:
     *   bit 0 => for lowercase, 1 for having lowercase
     *   bit 1 => for uppercase
     *   bit 2 => for digit
     *  j belongs to [0..n]
     *  //c3 = last but two character
     *  c2 = last but one character
     *  c1 = last character
     *  so, totally there will be k(<=i) * 128 * 128 *  8 * n states, but normally we only need states for current and
     *  previous positions.
     */
    int strongPasswordChecker_TLE(string s) {
        struct st {
            int nch[8][128][128];
            st() {
                for (int i = 0; i < 8; ++i) {
                    for (int j = 0; j < 128; ++j) {
                        for (int k = 0; k < 128; ++k) {
                            nch[i][j][k] = -1;
                        }
                    }
                }
            }
        };
        
        int n = s.size();
        if (n <= 3) {
            return 6 - n;
        }
        
        // deal s[0]
        vector<st> cur(2);
        cur[0].nch[0][0][0] = 1; // deletion
        cur[1].nch[mask(s[0])][0][s[0]] = 0;
        
        for (int i = 1; i < n; ++i) {
            char c = s[i];
            int ma = mask(c);
            int nn = i + 2 < 21 ? i+2 : 21;
            vector<st> next(nn);
            
            // j = 0
            next[0].nch[0][0][0] = i+1; // delete all
            
            // for j = 1
            // 1, from previous j=0, keep current character
            next[1].nch[ma][0][c] = cur[0].nch[0][0][0];
            // 2, from previous j=1, but delete current
            for (int k = 0; k < 8; ++k) {
                for (int l = 0; l < 128; ++l) {
                    if (cur[1].nch[k][0][l] >= 0
                        && (next[1].nch[k][0][l] == -1 || next[1].nch[k][0][l]  > cur[1].nch[k][0][l] + 1)) {
                        next[1].nch[k][0][l] = cur[1].nch[k][0][l] + 1;
                    }
                }
            }
            
            // for other j's
            for (int j = 2; j <= i+1 && j <= 20; ++j) {
                // from previous j (delete current char)
                if (j < cur.size()) {
                    for (int k = 0; k < 8; ++k) {
                        for (int l = 0; l < 128; ++l) {
                            for (int m = 0; m < 128; ++m) {
                                if (cur[j].nch[k][l][m] >= 0) {
                                    next[j].nch[k][l][m] = cur[j].nch[k][l][m] + 1;
                                }
                            }
                        }
                    }
                }
                // from previous j - 1 (keep current one, or replace it with other characters)
                // Here: no need to replace with non better characters.
                // need to check whether the previous two characters are same as current character.
                // update values if smaller than above step
                if (j <= cur.size() && next.size() > j) {
                    for (int ch = 0; ch < 128; ++ch) { // replace with ch
                        int ma = mask(ch);
                        for (int k = 0; k < 8; ++k) {
                            for (int l = 0; l < 128; ++l) {
                                for (int m = 0; m < 128; ++m) {
                                    if (cur[j-1].nch[k][l][m] >= 0 && !(l == m && m == ch)) {
                                        int t = cur[j-1].nch[k][l][m] + (c == ch ? 0 : 1);
                                        if (next[j].nch[k|ma][m][ch] == -1 || t < next[j].nch[k|ma][m][ch]) {
                                            next[j].nch[k|ma][m][ch] = t;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            
            cur.swap(next);
            
        } // loop if i'th character
        
        // deal n=4,5
        if (n < 6) {
            int res = INT_MAX;
            // always think a replace as an insertion
            for (int k = 0; k < 8; ++k) {
                for (int l = 0; l < 128; ++l) {
                    for (int m = 0; m < 128; ++m) {
                        if (cur[n].nch[k][l][m] >= 0) {
                            int t = cur[n].nch[k][l][m] + 3 - bitsize(k);
                            if (n + t < 6) {
                                t += 6 - n - t;
                            }
                            if (t < res) {
                                res = t;
                            }
                        }
                    }
                }
            }
            return res;
        } else {
            int res = INT_MAX;
            int i = n < 20 ? n : 20;
            for (int l = 0; l < 128; ++l) {
                for (int m = 0; m < 128; ++m) {
                    if (cur[i].nch[7][l][m] >= 0 && cur[i].nch[7][l][m] < res) {
                        res = cur[i].nch[7][l][m];
                    }
                }
            }
            
            return res;
        }
        
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string s;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"aaaaaaaaaaaaaaaaaaaaa"},
        {"1234567890123456Baaaaa"},
        {"aaaaaaaa"},
        {"aaaaaaaaa"},
        {""},
        {"aaa111"},
        {"aaaa"},
        {"aaaaa"},
        {"%%%%"},
        {"%%%%%"},
        {"aA1$"}
    };

    vector< int > answers {
        7,
        3,
        2,
        3,
        6,
        2,
        2,
        2,
        3,
        3,
        2
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = strongPasswordChecker::Solution().strongPasswordChecker2(dp.s);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
