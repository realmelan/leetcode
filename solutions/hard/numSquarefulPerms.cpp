// numSquarefulPerms.cpp
// leetcode
//
// Created by  Song Ding on 9/15/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numSquarefulPerms {
/*
// TODO: copy problem statement here
 996. Number of Squareful Arrays
 Hard
 
 174
 
 14
 
 Favorite
 
 Share
 Given an array A of non-negative integers, the array is squareful if for every pair of adjacent elements, their sum is a perfect square.
 
 Return the number of permutations of A that are squareful.  Two permutations A1 and A2 differ if and only if there is some index i such that A1[i] != A2[i].
 
 
 
 Example 1:
 
 Input: [1,17,8]
 Output: 2
 Explanation:
 [1,8,17] and [17,8,1] are the valid permutations.
 Example 2:
 
 Input: [2,2,2]
 Output: 1
 
 
 Note:
 
 1 <= A.length <= 12
 0 <= A[i] <= 1e9
 */

class Solution {
public:
    int numSquarefulPerms(vector<int>& A) {
        return numSquarefulPerms_simple_dfs(A);
    }
    /**
     * https://leetcode.com/problems/number-of-squareful-arrays/discuss/238562/C%2B%2BPython-Backtracking
     */
    int numSquarefulPerms_simple_dfs(vector<int>& A) {
        unordered_map<int, int> cnt;
        for (auto i : A) {
            ++cnt[i];
        }
        unordered_map<int, unordered_set<int>> cand;
        for (auto& p1 : cnt) {
            for (auto&p2 : cnt) {
                if (is_square(p1.first + p2.first)) {
                    cand[p1.first].insert(p2.first);
                    cand[p2.first].insert(p1.first);
                }
            }
        }
        int res = 0;
        for (auto& p : cnt) {
            --cnt[p.first];
            simple_dfs(p.first, A.size() - 1, cnt, cand, res);
            ++cnt[p.first];
        }
        return res;
    }
    void simple_dfs(int tail, int left, unordered_map<int,int>& cnt, unordered_map<int, unordered_set<int>>& cand, int& res) {
        if (left == 0) {
            ++res;
            return;
        }
        for (auto c : cand[tail]) {
            if (cnt[c]) {
                --cnt[c];
                simple_dfs(c, left-1, cnt, cand, res);
                ++cnt[c];
            }
        }
    }
    bool is_square(int a) {
        int b = sqrt(a);
        return b * b == a;
    }
    
    /**
     * use bits to represent numbers
     *
     * How to deal with duplicate?
     *  divide dp result by cnt(A[i])!
     */
    int numSquarefulPerms_dp(vector<int>& A) {
        int n = A.size();
        sort(A.begin(), A.end());
        int maxSum = A[n-1];
        if (n > 1) {
            maxSum += A[n-2];
        }
        
        unordered_set<int> squared;
        int i = 0;
        int t = 0;
        while ((t = i*i) <= maxSum) {
            squared.insert(t);
            ++i;
        }
        
        vector<vector<int>> dp(1<<n, vector<int>(n,0));
        unordered_map<int, int> cnt;
        int bit = 1;
        for (int i = 0; i < n; ++i) {
            dp[bit][i] = 1;
            ++cnt[A[i]];
            bit <<= 1;
        }
        vector<int> prod(2, 1);
        int p = 1;
        for (int i = 2; i <= n; ++i) {
            p *= i;
            prod.push_back(p);
        }
        
        vector<vector<int>> squareBits(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                if (squared.find(A[i] + A[j]) != squared.end()) {
                    squareBits[i].push_back(j);
                    squareBits[j].push_back(i);
                }
            }
        }
        // states are too many!
        for (int i = 1; i < (1<<n); ++i) {
            for (int j = 0; j < n; ++j) {
                if (dp[i][j]) {
                    for (auto pi : squareBits[j]) {
                        if (!((1<<pi) & i)) {
                            dp[i|(1<<pi)][pi] += dp[i][j];
                        }
                    }
                }
            }
        }
        int res = 0;
        int mask = (1<<n)-1;
        for (auto i : dp[mask]) {
            res += i;
        }
        for (auto& p : cnt) {
            res /= prod[p.second];
        }
        return res;
    }
    /**
     * DFS + memoization
     *  use bitset to represent memoization state
     *  use LSB to find all bits in a bit set
     */
    int numSquarefulPerms_dfs(vector<int>& A) {
        int n = A.size();
        sort(A.begin(), A.end());
        int maxSum = A[n-1];
        if (n > 1) {
            maxSum += A[n-2];
        }
        unordered_map<int, int> bitMap;
        int bit = 1;
        for (int i = 0; i < A.size(); ++i) {
            bitMap[bit] = A[i];
            bit <<= 1;
        }
        
        unordered_set<int> squared;
        int i = 0;
        int t = 0;
        while ((t = i*i) <= maxSum) {
            squared.insert(t);
            ++i;
        }
        
        unordered_map<int, int> memo; // bitset => # of permutations
        return dfs(0, bit-1, squared, bitMap, memo);
    }

private:
    int dfs(int headBit, int bits, const unordered_set<int>& squared, unordered_map<int,int>& bitMap, unordered_map<int,int>& memo) {
        if (bits == 0) {
            return 1;
        }
        int key = (headBit << 12) | bits;
        auto it = memo.find(key);
        if (it != memo.end()) {
            return it->second;
        }
        
        int head = bitMap[headBit];
        int res = 0;
        int last = -1;
        // find last bit of bits
        int nbits = bits;
        for (int i = lsb(nbits); nbits > 0; nbits -= i, i = lsb(nbits)) { // can we optimize this?
            int c = bitMap[i];
            if (last == c) {
                continue;
            }
            
            if (headBit == 0 || squared.find(head + c) != squared.end()) {
                res += dfs(i, bits ^ i, squared, bitMap, memo);
            }
            last = c;
        }
        
        memo[key] = res;
        return res;
    }
    int lsb(int i) {
        return i & (-i);
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> A;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,17,8}},
        {{2,2,2}},
        {{1,1,8,1,8}},
    };

    vector< int > answers {
        2,
        1,
        1
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = numSquarefulPerms::Solution().numSquarefulPerms(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
