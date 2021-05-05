// queryString.cpp
// leetcode
//
// Created by  Song Ding on 5/31/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace queryString {
/*
// TODO: copy problem statement here
 1016. Binary String With Substrings Representing 1 To N
 Medium
 
 35
 
 154
 
 Favorite
 
 Share
 Given a binary string S (a string consisting only of '0' and '1's) and a positive integer N, return true if and only if for every integer X from 1 to N, the binary representation of X is a substring of S.
 
 
 
 Example 1:
 
 Input: S = "0110", N = 3
 Output: true
 Example 2:
 
 Input: S = "0110", N = 4
 Output: false
 
 
 Note:
 
 1 <= S.length <= 1000
 1 <= N <= 10^9
 */

class Solution {
public:
    /**
     * test every substring of S and see whether it covers the 1 to N.
     * suppose bit(N) = k, and length(S) = n, then
     * for b in 1 to k - 1, test whether it covers all
     * for b = k, then check whether n - k > N - 2^k:
     *   if n - k < N - 2^k, then substrings of k can't cover numbers from
     *     N-2^k to N;
     *   else, use a hash map to check whether all number in N-2^k to N are
     *     covered.
     */
    bool queryString(string S, int N) {
        int n = S.size();
        int nsub = n * (n+1) / 2;
        if (nsub < N) {
            return false;
        }
        
        // should start from length of 1 and expand to length of l.
        // so that length of test substrings can be expanded
        map<string, bool> strs1 {
            {"0", true}, {"1", false}
        };
        unordered_set<string> strs0{"0", "1"};
        int l = 1;
        int t = 1 << l;
        while (t <= N) {
            int lsub = n - l + 1;
            if (lsub < (t>>1)) {
                return false;
            }
            
            for (int i = 0; i <= n - l; ++i) {
                if (S[i] == '1') {
                    strs1[S.substr(i, l)] = true;
                }
            }
            
            unordered_set<string> nstrs0;
            map<string, bool> nstrs1;
            for (const auto& p : strs1) {
                if (!p.second) {
                    return false;
                }
                nstrs1["1" + p.first] = false;
                nstrs0.insert("0" + p.first);
            }
            
            for (const auto& s : strs0) {
                nstrs1["1" + s] = false;
                nstrs0.insert("0" + s);
            }
            
            strs1.swap(nstrs1);
            strs0.swap(nstrs0);
            
            t <<= 1;
            ++l;
        }

        t >>= 1;
        int lsub = n - l + 1;
        if (lsub < N - t + 1) {
            return false;
        }
        
        for (int i = 0; i <= n - l; ++i) {
            if (S[i] == '1') {
                strs1[S.substr(i, l)] = true;
            }
        }
        auto it = strs1.begin();
        for (int i = t; i <= N; ++i, ++it) {
            if (!it->second) {
                return false;
            }
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
        int N;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{"0110", 3},
        //{"0110", 4},
        {"1", 1}
    };

    vector< bool > answers {
        true,
        false,
        true
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = queryString::Solution().queryString(dp.S, dp.N);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
