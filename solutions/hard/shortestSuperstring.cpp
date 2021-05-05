// shortestSuperstring.cpp
// leetcode
//
// Created by  Song Ding on 7/16/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace shortestSuperstring {
/*
// TODO: copy problem statement here
 943. Find the Shortest Superstring
 Hard
 
 164
 
 52
 
 Favorite
 
 Share
 Given an array A of strings, find any smallest string that contains each string in A as a substring.
 
 We may assume that no string in A is substring of another string in A.
 
 
 Example 1:
 
 Input: ["alex","loves","leetcode"]
 Output: "alexlovesleetcode"
 Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
 Example 2:
 
 Input: ["catg","ctaagt","gcta","ttca","atgcatc"]
 Output: "gctaagttcatgcatc"
 
 
 Note:
 
 1 <= A.length <= 12
 1 <= A[i].length <= 20
 */

class Solution {
public:
    string shortestSuperstring(vector<string>& A) {
        return shortestSuperstring_DP(A);
    }
    /**
     * based on https://en.wikipedia.org/wiki/Held%E2%80%93Karp_algorithm#Pseudocode[5]
     * support there is a starting node, s, then the problem is to find the minimium
     * length to start from s and end at any of the 0..n-1 string.
     *
     * However, there is situation that a non-visited string might be a substring
     * of previous path, but not individual string.
     */
    string shortestSuperstring_DP(vector<string>& A) {
        int n = A.size();
        vector<vector<int>> dist(n);
        for (int i = 0; i < n; ++i) {
            dist[i].resize(n, -1);
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    dist[i][j] = A[j].size() - common(A[i], A[j]);
                }
            }
        }
        
        // layer 1 => end node
        // layer 2 => mask for all other nodes encountered from s to end node
        vector<vector<int>> res(n);
        vector<vector<vector<int>>> prev(n+1);
        for (int i = 0; i < n; ++i) {
            res[i].resize((1<<n), -1);
            res[i][(1<<i)] = A[i].size();
        }
        for (int k = 2; k <= n; ++k) {
            vector<vector<int>> next(n);
            prev[k].resize(n);
            for (int i = 0; i < n; ++i) {
                prev[k][i].resize((1<<n), -1);
                next[i].resize((1<<n), -1);
                for (int j = 0; j < n; ++j) {
                    if (j != i) {
                        for (int s = 0; s < (1<<n); ++s) {
                            if ((s&(1<<i)) == 0 && res[j][s] >= 0) {
                                int t = res[j][s] + dist[j][i];
                                if (next[i][s|(1<<i)] < 0 || t < next[i][s|(1<<i)]) {
                                    next[i][s|(1<<i)] = t;
                                    prev[k][i][s|(1<<i)] = j;
                                }
                            }
                        }
                    }
                }
            }
            res.swap(next);
        }
        int minDist = INT_MAX;
        int last = -1;
        for (int i = 0; i < n; ++i) {
            if (minDist > res[i][(1<<n)-1]) {
                minDist = res[i][(1<<n)-1];
                last = i;
            }
        }
        
        // construct path
        string super(A[last]);
        int k = n;
        int s = (1<<n) - 1;
        while (k > 1) {
            int p = prev[k][last][s];
            // concatenate
            int comm = A[last].size() - dist[p][last];
            string t = A[p].substr(0, A[p].size() - comm);
            t.append(super);
            super.swap(t);
            //cout << super << endl;
            s -= (1<<last);
            last = p;
            --k;
        }
        return super;
    }
    
    
    
    /**
     * create a graph between strings, and the edge value between two strings(i,j)
     * is the longest common part of i's suffix and j's prefix.
     * Note the edge is directional.
     *
     * For each string as a starting node, do DFS to find the shortest super string.
     * This would request n! steps.
     *
     * As expected, it is TLE.
     * TODO: need some pruning when doing DFS.
     */
    string shortestSuperstring_DFS(vector<string>& A) {
        int n = A.size();
        string res(256, 'c');
        for (int i = 0; i < n; ++i) {
            string current(A[i]);
            vector<int> visited(n, 0);
            visited[i] = 1;
            int used = 1;
            dfs(A, current, visited, used, res);
        }
        return res;
    }
    string combine(string cur, const string& a) {
        int n = cur.size();
        int na = a.size();
        int i = 0;
        int j = 0;
        for (; i < n; ++i) {
            int ci = i;
            while (j < na && ci < n && a[j] == cur[ci]) {
                ++j;
                ++ci;
            }
            if (j >= na || ci >= n) {
                break;
            }
            j = 0;
        }
        cur.append(a.substr(j));
        return cur;
    }
    void dfs(vector<string>& a, string current, vector<int>& visited, int& used, string& res) {
        if (used >= a.size()) {
            if (current.size() < res.size()) {
                res.swap(current);
            }
            return;
        }
        for (int i = 0; i < a.size(); ++i) {
            if (visited[i]) {
                continue;
            }
            visited[i] = 1;
            ++used;
            string next = combine(current, a[i]);
            dfs(a, next, visited, used, res);
            --used;
            visited[i] = 0;
        }
    }
    int common(const string& a, const string& b) {
        int na = a.size();
        int nb = b.size();
        int n = min(na, nb);
        int i = n;
        while (i > 0 && a.substr(na - i) != b.substr(0, i)) {
            --i;
        }
        return i;
    }
    
    //TODO:
    string shortestSuperstringx(vector<string>& A) {
        int n = A.size();
        vector<vector<string>> dp(1<<n, vector<string>(n));
        for (int i = 0; i < n; ++i) {
            dp[1<<i][i] = A[i];
        }
        for (int i = 1; i < 1<<n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i & (1<<j)) == 0) {
                    int key = i | (1<<j);
                    for (int k = 0; k < n; ++k) {
                        if (dp[i][k].empty()) {
                            continue;
                        }
                        const string& s = dp[i][k];
                        
                        // merge A[j] at the right side of dp[i][k]
                        int nj = A[j].size();
                        int ni = s.size();
                        int l = min(ni, nj);
                        for (; l >= 1; --l) {
                            int ki = ni-l, kj = 0;
                            for (; kj < nj && ki < ni; ++ki, ++kj) {
                                if (s[ki] != A[j][kj]) {
                                    break;
                                }
                            }
                            if (ki == ni) {
                                break;
                            }
                        }
                        string t = s.substr(0, ni - l);
                        t.append(A[j]);
                        
                        if (dp[key][j].empty() || dp[key][j].size() > t.size()) {
                            dp[key][j] = t;
                        }
                    }
                    
                }
            }
        }
        int len = INT_MAX, r = n;
        for (int i = 0; i < dp.back().size(); ++i) {
            if (len > dp.back()[i].size()) {
                len = dp.back()[i].size();
                r = i;
            }
        }
        return dp.back()[r];
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<string> A;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{"alex","loves","leetcode"}},
        {{"catg","ctaagt","gcta","ttca","atgcatc"}},
        {{"ift","efd","dnete","tef","fdn"}},
        {{"xas","nxv","ownx","xvf","vfv"}},
        {{"chakgmeinq","lhdbntkf","mhkelhye","hdbntkfch","kfchakgme","wymhkelh","kgmeinqw"}},
        {{"uhozqhxcqmkifljvcie","epuhozqhxcqmkifljvci","ugmqnepuhozqhxcqm","iexdudtvurjkrovrhmpa","rovrhmpaasblgaosw","qmkifljvciexdudtv","zsgtuowskyzphybeugm","uowskyzphybeugmq","qhxcqmkifljvciex"}}
    };

    vector< string > answers {
        "alexlovesleetcode",
        "gctaagttcatgcatc",
        "iftefdnete",
        "ownxvfvxas",
        "lhdbntkfchakgmeinqwymhkelhye"
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = shortestSuperstring::Solution().shortestSuperstringx(dp.A);
        cout << clock() - tstart << endl;
        cout << res << " " << res.size() << endl;
    }
    
    //cout << strlen("lhdbntkfchakgmeinqwymhkelhye") << endl;
    return 0;
}
//*/
