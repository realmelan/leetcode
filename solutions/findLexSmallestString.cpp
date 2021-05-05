//
//  findLexSmallestString.cpp
//  leetcode
//
//  Created by Song Ding on 3/1/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace findLexSmallestString {
/*
// TODO: copy problem statement here
 1625. Lexicographically Smallest String After Applying Operations My SubmissionsBack to Contest
 User Accepted: 1053
 User Tried: 1511
 Total Accepted: 1089
 Total Submissions: 2393
 Difficulty: Medium
 You are given a string s of even length consisting of digits from 0 to 9, and two integers a and b.

 You can apply either of the following two operations any number of times and in any order on s:

 Add a to all odd indices of s (0-indexed). Digits post 9 are cycled back to 0. For example, if s = "3456" and a = 5, s becomes "3951".
 Rotate s to the right by b positions. For example, if s = "3456" and b = 1, s becomes "6345".
 Return the lexicographically smallest string you can obtain by applying the above operations any number of times on s.

 A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. For example, "0158" is lexicographically smaller than "0190" because the first position they differ is at the third letter, and '5' comes before '9'.

  

 Example 1:

 Input: s = "5525", a = 9, b = 2
 Output: "2050"
 Explanation: We can apply the following operations:
 Start:  "5525"
 Rotate: "2555"
 Add:    "2454"
 Add:    "2353"
 Rotate: "5323"
 Add:    "5222"
 ​​​​​​​Add:    "5121"
 ​​​​​​​Rotate: "2151"
 ​​​​​​​Add:    "2050"
 There is no way to obtain a string that is lexicographically smaller then "2050".
 Example 2:

 Input: s = "74", a = 5, b = 1
 Output: "24"
 Explanation: We can apply the following operations:
 Start:  "74"
 Rotate: "47"
 ​​​​​​​Add:    "42"
 ​​​​​​​Rotate: "24"
 There is no way to obtain a string that is lexicographically smaller then "24".
 Example 3:

 Input: s = "0011", a = 4, b = 2
 Output: "0011"
 Explanation: There are no sequence of operations that will give us a lexicographically smaller string than "0011".
 Example 4:

 Input: s = "43987654", a = 7, b = 3
 Output: "00553311"
  

 Constraints:

 2 <= s.length <= 100
 s.length is even.
 s consists of digits from 0 to 9 only.
 1 <= a <= 9
 1 <= b <= s.length - 1
*/
class Solution {
public:
    // TODO: copy function signature here
    // BFS
    string findLexSmallestString(string s, int a, int b) {
        int n = s.size();
        int kb = 0;
        unordered_set<string> cur;
        
        string res = s;
        int ka = 0;
        while (ka == 0 || ka%10) {
            string t(s);
            for (int i = 1; i < n; i+=2) {
                t[i] = (s[i]-'0'+ka)%10+'0';
            }
            cur.insert(t);
            res = min(res, t);
            ka += a;
        }
        while (kb == 0 || kb%n) {
            unordered_set<string> next;
            for (auto& c : cur) {
                string cr = c.substr(b) + c.substr(0, b);
                int ka = 0;
                while (ka == 0 || ka%10) {
                    string t(cr);
                    for (int i = 1; i < n; i+=2) {
                        t[i] = (cr[i]-'0'+ka)%10+'0';
                    }
                    next.insert(t);
                    res = min(res, t);
                    ka += a;
                }
            }
            cur.swap(next);
            kb += b;
        }
        return res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        string s;
        int a;
        int b;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {"74",5,1},
    };
    // TODO: provide expected results here
    vector<string> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findLexSmallestString::Solution().findLexSmallestString(dp.s, dp.a, dp.b);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
