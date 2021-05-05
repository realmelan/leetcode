//
//  decodeString.cpp
//  leetcode
//
//  Created by  Song Ding on 11/8/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace decodeString {
    class Solution {
    public:
        string decodeString_recursive(string s) {
            int n = s.size();
            string res;
            int lcnt = 0;
            int multi = 0;
            string t;
            for (int i = 0; i < n; ++i) {
                if (lcnt > 1) {
                    t.push_back(s[i]);
                    if (s[i] == ']') {
                        --lcnt;
                    } else if (s[i] == '[') {
                        ++lcnt;
                    }
                } else if (lcnt == 1) {
                    if (s[i] == ']') {
                        --lcnt;
                        string x = decodeString(t);
                        for (int i = 0; i < multi; ++i) {
                            res.append(x);
                        }
                        multi = 0;
                    } else {
                        t.push_back(s[i]);
                        if (s[i] == '[') {
                            ++lcnt;
                        }
                    }
                } else {
                    if (s[i] == '[') {
                        t.clear();
                        lcnt = 1;
                    } else if (s[i] >= 0 && s[i] <= '9'){
                        multi *= 10;
                        multi += s[i] - '0';
                    } else {
                        res.push_back(s[i]);
                    }
                }
            }
            return res;
        }
        /**
         Use stack to find complete compound.
         */
        string decodeString(string s) {
            string res;
            stack<int> multiSt;
            stack<string> strSt;
            
            int len = s.size();
            int i = 0;
            string multiStr, str;
            while (i < len) {
                char c = s[i];
                ++i;
                if (c == '[') {
                    strSt.push("[");
                    int multi = 0;
                    istringstream iss(multiStr);
                    iss >> multi;
                    multiSt.push(multi);
                    multiStr.clear();
                } else if (c == ']') {
                    // non-consecutive ']'
                    if (str.size()) {
                        strSt.push(str);
                        str.clear();
                    }
                    // compose a part string and push it back to strSt.
                    string t;
                    while (strSt.size()) {
                        const string top = strSt.top();
                        strSt.pop();
                        if (top != "[") {
                            t.insert(t.begin(), top.begin(), top.end());
                        } else {
                            int multi = multiSt.top();
                            multiSt.pop();
                            string nt;
                            int j = 0;
                            while (j < multi) {
                                nt.append(t);
                                ++j;
                            }
                            strSt.push(nt);
                            break;
                        }
                    }
                } else if (c >= '0' && c <= '9') {
                    multiStr.push_back(c);
                    if (str.size()) {
                        strSt.push(str);
                        str.clear();
                    }
                } else {
                    str.push_back(c);
                }
            } // end while loop of s
            
            if (str.size()) {
                strSt.push(str);
                str.clear();
            }
            while (strSt.size()) {
                const string top = strSt.top();
                strSt.pop();
                res.insert(res.begin(), top.begin(), top.end());
            }
            
            return res;
        }
    };
}

/*
int main() {
    string s("3[a2[c]]");
    cout << decodeString::Solution().decodeString_recursive(s) << endl;
    return 0;
}
// */
