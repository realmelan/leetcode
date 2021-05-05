// magicalString.cpp
// leetcode
//
// Created by  Song Ding on 10/26/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace magicalString {
/*
// TODO: copy problem statement here
 481. Magical String
 Medium

 90

 583

 Favorite

 Share
 A magical string S consists of only '1' and '2' and obeys the following rules:

 The string S is magical because concatenating the number of contiguous occurrences of characters '1' and '2' generates the string S itself.

 The first few elements of string S is the following: S = "1221121221221121122……"

 If we group the consecutive '1's and '2's in S, it will be:

 1 22 11 2 1 22 1 22 11 2 11 22 ......

 and the occurrences of '1's or '2's in each group are:

 1 2 2 1 1 2 1 2 2 1 2 2 ......

 You can see that the occurrence sequence above is the S itself.

 Given an integer N as input, return the number of '1's in the first N number in the magical string S.

 Note: N will not exceed 100,000.

 Example 1:
 Input: 6
 Output: 3
 Explanation: The first 6 elements of magical string S is "12211" and it contains three 1's, so return 3.
 */

class Solution {
public:
    /**
     * let i be the counting position, which will direct how many 1 or 2 will be appended to the tail of the string.
     * when appending 1 or 2 to the tail, keep counting the # of 1's appended.
     * when the size of the string reaches N, return the count.
     */
    int magicalString(int n) {
        if (n <= 0) {
            return 0;
        } else if (n <= 3) {
            return 1;
        }
        string s("122");
        s.reserve(n);
        int res = 1;
        int i = 2;
        char c = '1';
        while (s.size() < n) {
            s.push_back(c);
            res += '2' - c;
            if (s.size() == n) {
                break;
            }
            if (s[i] == '2') {
                s.push_back(c);
                res += '2' - c;
            }
            ++i;
            c = '1' + ('2'- c);
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
        int n;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {6}
    };

    vector< int > answers {
        3,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = magicalString::Solution().magicalString(dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
