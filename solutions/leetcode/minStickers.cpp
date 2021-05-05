//
//  minStickers.cpp
//  leetcode
//
//  Created by  Song Ding on 2/19/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
#include <numeric>
using namespace std;

namespace minStickers {
    class Solution {
    public:
        /**
         divide target into counts of unique letters. Then find out
         the minimum number of stickers to cover these letters.
         
         Recursive and remove stickers that are not useful.
         */
        int minStickers(vector<string>& stickers, string target) {
            
            vector<int> ntarget(26, 0);
            for (auto c : target) {
                ++ntarget[c - 'a'];
            }
            
            vector<vector<int>> nstickers;
            for (const auto& s : stickers) {
                vector<int> st(26, 0);
                int useful = 0;
                for (auto c : s) {
                    if (ntarget[c - 'a'] > 0) {
                        ++st[c - 'a'];
                        ++useful;
                    }
                }
                if (useful) {
                    nstickers.push_back(st);
                }
            }
            
            return dfs(nstickers, ntarget);
        }
        /**
         This method is by dreamoon, and it is quite confusing to me
         initially.
         
         This is actually BFS: each round, for current states, applying
         stickers, to get new set of states(which positions are covered).
         
         TODO: figure whether some states are ignored because of the loop of i
         from 0 to m.
         A: not possible, because each round it applies all stickers, so, smaller
         state must have been reached before processing larger state.
         */
        int minStickers2(vector<string>& stickers, string target) {
            int n = target.size(), m = 1 << n; // if target has n chars, there will be m=2^n-1 subset of characters in target
            vector<uint> dp(m, -1); // use index 0 - 2^n-1 as bitmaps to represent each subset of all chars of target
            dp[0] = 0; // first thing we know is : dp[empty set] requires 0 stickers,
            for (int i = 0; i < m; i++) { // for every subset i, start from 00000...(emptyset) to 111111...(the target)
                if (dp[i] == -1) continue;
                for (string& s : stickers) { // try use each sticker as an char provider to populate a super-set of i,
                    int sup = i;
                    for (char c : s) { // to do that, for each char in the sticker,
                        for (int r = 0; r < n; r++) {
                            if (target[r] == c && !((sup >> r) & 1)) { // try apply it on a missing char in the subset of target
                                sup |= 1 << r;
                                break;
                            }
                        }
                    }
                    // after you apply all possible chars in a sticker, you get an superset that take 1 extra sticker than subset
                    // would take, so you can try to update the superset's minsticker number with dp[sub]+1;
                    dp[sup] = min(dp[sup], dp[i] + 1);
                }
            }
            return dp[m - 1]; // and the ultimate result
        }
    private:
        int dfs(const vector<vector<int>>& stickers, const vector<int>& target) {
            vector<int> ntarget(target);
            vector<vector<int>> t;
            for (const auto& st : stickers) {
                int useful = 0;
                vector<int> nst(st);
                for (int i = 0; i < 26; ++i) {
                    ntarget[i] -= nst[i];
                    if (nst[i] > 0 && target[i] > 0) {
                        ++useful;
                    } else {
                        nst[i] = 0;
                    }
                }
                if (useful) {
                    t.push_back(nst);
                }
            }
            for (int i = 0; i < 26; ++i) {
                if (ntarget[i] == target[i] && target[i] > 0) {
                    return -1;
                }
            }
            
            sort(t.begin(), t.end(), [](const vector<int>& a, const vector<int>& b){
                return (std::accumulate(a.begin(), a.end(), 0)) > (std::accumulate(b.begin(), b.end(), 0));
            });
            vector<vector<int>> nstickers;
            for (const auto& st : t) {
                int notCovered = 0;
                for (const auto & alrdy : nstickers) {
                    for (int i = 0; i < 26; ++i) {
                        if (st[i] > alrdy[i]) {
                            ++notCovered;
                            break;
                        }
                    }
                }
                if (notCovered == nstickers.size()) {
                    nstickers.push_back(st);
                }
            }
            
            int res = -1;
            for (auto it = nstickers.begin(); it != nstickers.end(); ++it) {
                int done = 0;
                vector<int> ntarget(target);
                for (int i = 0; i < 26; ++i) {
                    ntarget[i] -= (*it)[i];
                    if (ntarget[i] <= 0) {
                        ++done;
                    }
                }
                if (done >= 26) {
                    return 1;
                }
                
                vector<vector<int>> nst(it, nstickers.end());
                int t = dfs(nst, ntarget);
                if (res < 0 || (t > 0 && (t + 1) < res)) {
                    res = t + 1;
                }
            }
            return res;
        }
    };
}

/*
int main() {
    vector<string> stickers {"control","heart","interest","stream","sentence","soil","wonder","them","month","slip","table","miss","boat","speak","figure","no","perhaps","twenty","throw","rich","capital","save","method","store","meant","life","oil","string","song","food","am","who","fat","if","put","path","come","grow","box","great","word","object","stead","common","fresh","the","operate","where","road","mean"};
    string target("stoodcrease");
    clock_t start = clock();
    cout << minStickers::Solution().minStickers(stickers, target) << endl;
    clock_t mid = clock();
    cout << minStickers::Solution().minStickers2(stickers, target) << endl;
    clock_t end = clock();
    cout << "my = " << mid - start << ", dreamoon = " << end - mid << endl;
    return 0;
}
 */
