//
//  repeatedStringMatch.cpp
//  leetcode
//
//  Created by Song Ding on 2/14/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace repeatedStringMatch {
/*
// TODO: copy problem statement here
 686. Repeated String Match
 Easy

 668

 658

 Add to List

 Share
 Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.

 For example, with A = "abcd" and B = "cdabcdab".

 Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").

 Note:
 The length of A and B will be between 1 and 10000.
*/
class Solution {
public:
    // TODO: copy function signature here
    int repeatedStringMatch(string A, string B) {
        int na = A.size(), nb = B.size();
        int rep = (nb + na - 1 + na - 1) / na;
        string t(B);
        t.reserve(nb + na * rep + 1);
        t.append("#");
        for (int i = 0; i < rep; ++i) {
            t.append(A);
        }
        
        // find longest proper suffix
        int nt = t.size();
        vector<int> lps(nt, 0);
        int i = 1, j = 0;
        while (i < nt) {
            if (t[i] == t[j]) {
                ++j;
                lps[i] = j;
                ++i;
                if (j == nb) {
                    break;
                }
            } else {
                if (j > 0) {
                    j = lps[j-1];
                } else {
                    j = 0;
                    ++i;
                    lps.push_back(0);
                }
            }
        }
        if (j == nb) {
            return (i - nb - 1 + na - 1) / na;
        }
        return -1;
        
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        string A;
        string B;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {"abcd","cdabcdab"},
    };
    // TODO: provide expected results here
    vector< int > answers {
        3,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = repeatedStringMatch::Solution().repeatedStringMatch(dp.A, dp.B);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
