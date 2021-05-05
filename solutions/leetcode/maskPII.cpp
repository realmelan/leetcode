// maskPII.cpp
// leetcode
//
// Created by  Song Ding on 6/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maskPII {
/*
// TODO: copy problem statement here
 831. Masking Personal Information
 Medium
 
 48
 
 194
 
 Favorite
 
 Share
 We are given a personal information string S, which may represent either an email address or a phone number.
 
 We would like to mask this personal information according to the following rules:
 
 
 1. Email address:
 
 We define a name to be a string of length ≥ 2 consisting of only lowercase letters a-z or uppercase letters A-Z.
 
 An email address starts with a name, followed by the symbol '@', followed by a name, followed by the dot '.' and followed by a name.
 
 All email addresses are guaranteed to be valid and in the format of "name1@name2.name3".
 
 To mask an email, all names must be converted to lowercase and all letters between the first and last letter of the first name must be replaced by 5 asterisks '*'.
 
 
 2. Phone number:
 
 A phone number is a string consisting of only the digits 0-9 or the characters from the set {'+', '-', '(', ')', ' '}. You may assume a phone number contains 10 to 13 digits.
 
 The last 10 digits make up the local number, while the digits before those make up the country code. Note that the country code is optional. We want to expose only the last 4 digits and mask all other digits.
 
 The local number should be formatted and masked as "***-***-1111", where 1 represents the exposed digits.
 
 To mask a phone number with country code like "+111 111 111 1111", we write it in the form "+***-***-***-1111".  The '+' sign and the first '-' sign before the local number should only exist if there is a country code.  For example, a 12 digit phone number mask should start with "+**-".
 
 Note that extraneous characters like "(", ")", " ", as well as extra dashes or plus signs not part of the above formatting scheme should be removed.
 
 
 
 Return the correct "mask" of the information provided.
 
 
 
 Example 1:
 
 Input: "LeetCode@LeetCode.com"
 Output: "l*****e@leetcode.com"
 Explanation: All names are converted to lowercase, and the letters between the
 first and last letter of the first name is replaced by 5 asterisks.
 Therefore, "leetcode" -> "l*****e".
 Example 2:
 
 Input: "AB@qq.com"
 Output: "a*****b@qq.com"
 Explanation: There must be 5 asterisks between the first and last letter
 of the first name "ab". Therefore, "ab" -> "a*****b".
 Example 3:
 
 Input: "1(234)567-890"
 Output: "***-***-7890"
 Explanation: 10 digits in the phone number, which means all digits make up the local number.
 Example 4:
 
 Input: "86-(10)12345678"
 Output: "+**-***-***-5678"
 Explanation: 12 digits, 2 digits for country code and 10 digits for local number.
 Notes:
 
 S.length <= 40.
 Emails have length at least 8.
 Phone numbers have length at least 10.
 */

class Solution {
public:
    /**
     * use the 1st character to determine whether it is email
     * or phone number.
     */
    string maskPII(string S) {
        int n = S.size();
        if (isUpper(S[0]) || isLower(S[0])) {
            return maskEmail(S);
        } else {
            return maskPhone(S);
        }
    }

private:
    bool isUpper(char c) {
        return (c >= 'A' && c <= 'Z');
    }
    bool isLower(char c) {
        return (c >= 'a' && c <= 'z');
    }
    char toLower(char c) {
        if (isUpper(c)) {
            return c - 'A' + 'a';
        }
        return c;
    }
    
    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }
    
    string maskEmail(const string& s) {
        string res;
        int n = s.size();
        bool passAt = false;
        res.push_back(toLower(s[0]));
        res.append("*****");
        for (int i = 1; i < n; ++i) {
            char c = s[i];
            if (c == '@') {
                res.push_back(toLower(s[i-1]));
                res.push_back(c);
                passAt = true;
            } else if (passAt) {
                res.push_back(toLower(c));
            }
        }
        return res;
    }
    
    string maskPhone(const string& s) {
        string res;
        int n = s.size();
        int dn = 0;
        for (int i = n - 1; i >= 0; --i) {
            char c = s[i];
            if (isDigit(c)) {
                if (dn++ < 4) {
                    res.insert(res.begin(), c);
                } else {
                    res.insert(res.begin(), '*');
                }
                if (dn == 4 || dn == 7 || dn == 10) {
                    res.insert(res.begin(), '-');
                }
            }
        }
        if (res.size() == 13) {
            return res.substr(1);
        } else {
            res.insert(res.begin(), '+');
            return res;
        }
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string S;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"LeetCode@LeetCode.com"},
        {"AB@qq.com"},
        {"1(234)567-890"},
        {"86-(10)12345678"}
    };

    vector< string > answers {
        "l*****e@leetcode.com",
        "a*****b@qq.com",
        "***-***-7890",
        "+**-***-***-5678"
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maskPII::Solution().maskPII(dp.S);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
