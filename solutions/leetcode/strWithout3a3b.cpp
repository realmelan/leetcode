// strWithout3a3b.cpp
// leetcode
//
// Created by  Song Ding on 4/25/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace strWithout3a3b {

class Solution {
public:
    string strWithout3a3b(int A, int B) {
        char a = 'a';
        char b = 'b';
        if (A < B) {
            swap(a, b);
            swap(A, B);
        }
        
        string res;
        while (A != B && B > 0) {
            res.push_back(a);
            res.push_back(a);
            res.push_back(b);
            --A;
            --A;
            --B;
        }
        while (B > 0) {
            res.push_back(a);
            res.push_back(b);
            --A;
            --B;
        }
        while (A > 0) {
            res.push_back(a);
            --A;
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<int> > AB {
        {1,2},
        {4,1}
    };

    vector<  string > answers {
        "abb"
        "aabaa"
    };
    int i = 0;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = strWithout3a3b::Solution().strWithout3a3b(AB[i][0], AB[i][1]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
