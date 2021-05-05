// numMusicPlaylists.cpp
// leetcode
//
// Created by  Song Ding on 10/16/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numMusicPlaylists {

class Solution {
public:
    int numMusicPlaylists(int N, int L, int K) {
        long perm = 1;
        for (int i = 1; i <= N; ++i) {
            perm *= i;
            if (perm > MOD) {
                perm %= MOD;
            }
        }
        
        if (N >= L) {
            return perm;
        }
        
        unordered_map<int, int> memo;
        long res = recur(N, L, K, memo);
        res *= perm;
        return res % MOD;
    }

private:
    static const int MOD = 1000000007;
    
    long recur(int N, int L, int K, unordered_map<int, int>& memo) {
        if (N >= L) {
            return 1;
        } else if (N <= K) {
            return 0;
        } else {
            int id = getId(N, L);
            auto it = memo.find(id);
            if (it != memo.end()) {
                return it->second;
            }
            
            long res = recur(N - 1, L - 1, K, memo)
                + recur(N, L - 1, K, memo) * (N - K);
            
            res %= MOD;
            memo[id] = res;
            return res;
        }
    }
    int getId(int N, int L) {
        return L * 100 + N;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int N = 2;
    int L = 3;
    int K = 1;

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = numMusicPlaylists::Solution().numMusicPlaylists(N, L, K);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
