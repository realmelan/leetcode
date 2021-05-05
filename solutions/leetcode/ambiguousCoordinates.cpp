// ambiguousCoordinates.cpp
// leetcode
//
// Created by  Song Ding on 5/8/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace ambiguousCoordinates {

class Solution {
public:
    /**
     * Divide the string into (1, n-1), (2,n-2),..., (n-1,1) parts.
     * for each division, check how many different forms can be produced
     * by adding decimal point:
     *   1, string with only >1 0, is invalid
     *   2, strings starting with '0' can only have 1 form, that is 0.xxx
     *   3, strings ending with '0' shall not have a decimal point, thus
     *      only 1 form.
     *   4, all other strings can have n-1 different forms.(n being length of string).
     *
     */
    vector<string> ambiguousCoordinates(string S) {
        vector<string> res;
        int n = S.size() - 2;
        if (n <= 1) {
            return res;
        }
        
        for (int i = 1; i < n; ++i) {
            string p1 = S.substr(1, i);
            vector<string> first;
            gen(p1, first);
            if (first.empty()) {
                continue;
            }
            
            string p2 = S.substr(i+1, n - i);
            vector<string> second;
            gen(p2, second);
            if (second.empty()) {
                continue;
            }
            
            for (const auto& s1 : first) {
                for (const auto& s2 : second) {
                    string r("(");
                    r.append(s1);
                    r.append(", ");
                    r.append(s2);
                    r.append(")");
                    res.push_back(r);
                }
            }
        }
        return res;
    }
private:
    void gen(string s, vector<string>& forms) {
        int n = s.size();
        if (n == 1) {
            forms.push_back(s);
        } else {
            if (s[n - 1] == '0'){
                if (s[0] != '0') {
                    forms.push_back(s);
                }
            } else if (s[0] == '0') {
                string decimal(s);
                decimal.insert(1, ".");
                forms.push_back(decimal);
            } else {
                // i = length of digits before decimal point
                for (int i = 1; i < n; ++i) {
                    string decimal(s.substr(0, i));
                    decimal.push_back('.');
                    decimal.append(s.substr(i));
                    forms.push_back(decimal);
                }
                forms.push_back(s);
            }
        }
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    string S("(00011)");
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = ambiguousCoordinates::Solution().ambiguousCoordinates(S);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
