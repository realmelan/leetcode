// isValid.cpp
// leetcode
//
// Created by  Song Ding on 5/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace isValid {
/*
// TODO: copy problem statement here
 1003. Check If Word Is Valid After Substitutions
 Medium
 
 67
 
 119
 
 Favorite
 
 Share
 We are given that the string "abc" is valid.
 
 From any valid string V, we may split V into two pieces X and Y such that X + Y (X concatenated with Y) is equal to V.  (X or Y may be empty.)  Then, X + "abc" + Y is also valid.
 
 If for example S = "abc", then examples of valid strings are: "abc", "aabcbc", "abcabc", "abcabcababcc".  Examples of invalid strings are: "abccba", "ab", "cababc", "bac".
 
 Return true if and only if the given string S is valid.
 
 
 
 Example 1:
 
 Input: "aabcbc"
 Output: true
 Explanation:
 We start with the valid string "abc".
 Then we can insert another "abc" between "a" and "bc", resulting in "a" + "abc" + "bc" which is "aabcbc".
 Example 2:
 
 Input: "abcabcababcc"
 Output: true
 Explanation:
 "abcabcabc" is valid after consecutive insertings of "abc".
 Then we can insert "abc" before the last letter, resulting in "abcabcab" + "abc" + "c" which is "abcabcababcc".
 Example 3:
 
 Input: "abccba"
 Output: false
 Example 4:
 
 Input: "cababc"
 Output: false
 
 
 Note:
 
 1 <= S.length <= 20000
 S[i] is 'a', 'b', or 'c'
 */

class Solution {
public:
    /**
     * First idea:
     *   remove an substring "abc" from S to get S1, and solve the same problem
     *   on S1.
     */
    bool isValid(string S) {
        vector<int> counts(3);
        for (auto c : S) {
            ++counts[c-'a'];
        }
        if (S.size() % 3 != 0
            || counts[0] != counts[1]
            || counts[1] != counts[2]) {
            return false;
        }
        
        while (S != "abc") {
            int i = 0;
            int n = S.size();
            string next;
            next.reserve(n);
            bool found = false;
            for (i = 0; i < n;) {
                if (i < n - 3 && S[i] == 'a' && S[i+1] == 'b' && S[i+2] == 'c') {
                    i += 3;
                    found = true;
                } else {
                    next.push_back(S[i]);
                    ++i;
                }
            }
            if (!found) {
                return false;
            }
            S.swap(next);
        }
        return true;
    }

private:
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
        {"aabcbc"},
        {"abcabcababcc"},
        {"abccba"},
        {"cababc"}
    };

    vector< bool > answers {
        true,
        true,
        false,
        false
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = isValid::Solution().isValid(dp.S);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
