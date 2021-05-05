//
//  findRotateSteps.cpp
//  leetcode
//
//  Created by  Song Ding on 2/5/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;
/**
 514. Freedom Trail
 Hard

 312

 18

 Favorite

 Share
 In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring", and use the dial to spell a specific keyword in order to open the door.

 Given a string ring, which represents the code engraved on the outer ring and another string key, which represents the keyword needs to be spelled. You need to find the minimum number of steps in order to spell all the characters in the keyword.

 Initially, the first character of the ring is aligned at 12:00 direction. You need to spell all the characters in the string key one by one by rotating the ring clockwise or anticlockwise to make each character of the string key aligned at 12:00 direction and then by pressing the center button.

 At the stage of rotating the ring to spell the key character key[i]:

 You can rotate the ring clockwise or anticlockwise one place, which counts as 1 step. The final purpose of the rotation is to align one of the string ring's characters at the 12:00 direction, where this character must equal to the character key[i].
 If the character key[i] has been aligned at the 12:00 direction, you need to press the center button to spell, which also counts as 1 step. After the pressing, you could begin to spell the next character in the key (next stage), otherwise, you've finished all the spelling.
 Example:


  
 Input: ring = "godding", key = "gd"
 Output: 4
 Explanation:
 For the first key character 'g', since it is already in place, we just need 1 step to spell this character.
 For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
 Also, we need 1 more step for spelling.
 So the final output is 4.
 Note:

 Length of both ring and key will be in range 1 to 100.
 There are only lowercase letters in both strings and might be some duplcate characters in both strings.
 It's guaranteed that string key could always be spelled by rotating the string ring.
 */

namespace findRotateSteps {
    class Solution {
    public:
        int findRotateSteps(string ring, string key) {
            return findRotateSteps_dp2(ring, key);
        }
        
        int findRotateSteps_dp2(string ring, string key) {
            int n = ring.size(), m = key.size();
            vector<int> dp(n, INT_MAX);
            for (int i = 0; i < n; ++i) {
                if (ring[i] == key[0]) {
                    dp[i] = min(i, n-i);
                }
            }
            for (int i = 1; i < m; ++i) {
                vector<int> next(n, INT_MAX);
                for (int j = 0; j < n; ++j) {
                    if (ring[j] == key[i]) {
                        for (int k = 0; k < n; ++k) {
                            if (dp[k] != INT_MAX) {
                                next[j] = min(next[j], dp[k] + min(abs(j-k), n - abs(j-k)));
                            }
                        }
                    }
                }
                dp.swap(next);
            }
            int res = INT_MAX;
            for (int i = 0; i < n; ++i) {
                if (ring[i] == key[m-1]) {
                    res = min(res, dp[i]);
                }
            }
            return res + m;
        }
        
        /**
         let dp[i][j] = min # of steps to get keys[i..m-1] from start position j.
         then dp[i][j] = min(dp[i+1][k]+distance(j,k)) for all k ring[k] = key[i].
         */
        int findRotateSteps_dp(string ring, string key) {
            int n = ring.size();
            int m = key.size();
            vector<vector<int>> dp(m+1, vector<int>(n,0));
            for (int i = m-1; i >= 0; --i) {
                for (int j = 0; j < n; ++j) {
                    // check the steps need to get key[i..m-1] from start position j.
                    dp[i][j] = INT_MAX;
                    for (int k = 0; k < n; ++k) {
                        if (ring[k] == key[i]) {
                            // from j to k and then dp[i+1][k]
                            // there are 2 directions from j to k
                            int dist = abs(j-k);
                            dp[i][j] = min(dp[i][j], dp[i+1][k]+min(dist, n-dist));
                        }
                    }
                }
            }
            return dp[0][0]+m;
        }
        /**
         This looks like minimum path, but at each step just check
         whether a prefix of key has been reached.
         */
        int findRotateSteps_bfs(string ring, string key) {
            int res = 0;
            int n = key.size();
            if (n <= 0) {
                return res;
            }
            int rn = ring.size();
            map<int, int> current;
            current[0] = 0;
            int toReach = 0;
            while (toReach < n) {
                map<int, int> w;
                char t = key[toReach];
                for (int i = 0; i < rn; ++i) {
                    if (ring[i] == t) {
                        int dist = rn * n;
                        for (const auto& p : current) {
                            int d = i < p.first ? p.first - i : i - p.first;
                            if (d > rn - d) {
                                d = rn - d;
                            }
                            if (d + p.second < dist) {
                                dist = d + p.second;
                            }
                        }
                        w[i] = dist;
                    }
                }
                current.swap(w);
                ++toReach;
            }
            res = rn * n;
            for (const auto& p : current) {
                if (res > p.second) {
                    res = p.second;
                }
            }
            res += n;
            return res;
        }
    };
}

/*
int main() {
    string ring("pqwcx");
    string key("cpqwx");
    cout << findRotateSteps::Solution().findRotateSteps(ring, key) << endl;
    return 0;
}
// */
