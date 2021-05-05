// kmp.cpp
// leetcode
//
// Created by  Song Ding on 11/28/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace kmp {

class Solution {
public:
    static void kmpPreprocess(vector<int>& b, const string&p)
    {
        int m = p.size();
        b.resize(m);
        int i=0, j=-1;
        b[i]=j;
        while (i<m)
        {
            while (j>=0 && p[i]!=p[j]) j=b[j];
            i++; j++;
            if (p[i] != p[j]) {
                b[i] = j;
            } else {
                b[i] = b[j];
            }
        }
    }
    
    static void kmp(const string&t, const string& p)
    {
        vector<int> b;
        kmpPreprocess(b, p);
        cout << b << endl;
        
        int n = t.size();
        int m = p.size();
        int i=0, j=0;
        while (i<n)
        {
            while (j>=0 && t[i]!=p[j]) j=b[j];
            i++; j++;
            if (j==m)
            {
                cout << "match at " << i - j << endl;
                j=b[j];
            }
        }
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<string> t {
        "abababaababababaab",
        "babcbabcabcaabcabcabcacabc"
    };
    vector<string> p {
        "ababaa",
        "abcabcacab"
    };
    vector< int  > answers {
    };
    int i = 0;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    kmp::Solution().kmp(t[i], p[i]);
    cout << clock() - tstart << endl;
    return 0;
}
//*/
