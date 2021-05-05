//
//  minimumDistance.cpp
//  leetcode
//
//  Created by Song Ding on 1/31/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minimumDistance {
/*
// TODO: copy problem statement here
 1320. Minimum Distance to Type a Word Using Two Fingers
 Hard

 512

 23

 Add to List

 Share


 You have a keyboard layout as shown above in the XY plane, where each English uppercase letter is located at some coordinate, for example, the letter A is located at coordinate (0,0), the letter B is located at coordinate (0,1), the letter P is located at coordinate (2,3) and the letter Z is located at coordinate (4,1).

 Given the string word, return the minimum total distance to type such string using only two fingers. The distance between coordinates (x1,y1) and (x2,y2) is |x1 - x2| + |y1 - y2|.

 Note that the initial positions of your two fingers are considered free so don't count towards your total distance, also your two fingers do not have to start at the first letter or the first two letters.

  

 Example 1:

 Input: word = "CAKE"
 Output: 3
 Explanation:
 Using two fingers, one optimal way to type "CAKE" is:
 Finger 1 on letter 'C' -> cost = 0
 Finger 1 on letter 'A' -> cost = Distance from letter 'C' to letter 'A' = 2
 Finger 2 on letter 'K' -> cost = 0
 Finger 2 on letter 'E' -> cost = Distance from letter 'K' to letter 'E' = 1
 Total distance = 3
 Example 2:

 Input: word = "HAPPY"
 Output: 6
 Explanation:
 Using two fingers, one optimal way to type "HAPPY" is:
 Finger 1 on letter 'H' -> cost = 0
 Finger 1 on letter 'A' -> cost = Distance from letter 'H' to letter 'A' = 2
 Finger 2 on letter 'P' -> cost = 0
 Finger 2 on letter 'P' -> cost = Distance from letter 'P' to letter 'P' = 0
 Finger 1 on letter 'Y' -> cost = Distance from letter 'A' to letter 'Y' = 4
 Total distance = 6
 Example 3:

 Input: word = "NEW"
 Output: 3
 Example 4:

 Input: word = "YEAR"
 Output: 7
  

 Constraints:

 2 <= word.length <= 300
 Each word[i] is an English uppercase letter.
*/
class Solution {
public:
    // TODO: copy function signature here
    int minimumDistance(string word) {
        static constexpr int INF = 300*26;
        int n = word.size();
        vector<int> moves(n,0); // from 0 to i-th letter of word
        for (int i = 1; i < n; ++i) {
            moves[i] = moves[i-1] + dist(word[i-1], word[i]);
        }
        
        vector<vector<int>> dp(n+1, vector<int>(n+1, INF));
        dp[1][0] = 0; // first at 0-th letter of word
        for (int i = 1; i < n; ++i) { // current head
            // first hand at i, second at j(<i-1), then first hand at i-1
            for (int j = -1; j < i-1; ++j) {
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j+1]+moves[i]-moves[i-1]);
            }
            // case 2: second hand at i-1, then first hand may be at [0,i-2)
            for (int j = 0; j < i-1; ++j) {
                dp[i+1][i] = min(dp[i+1][i], dp[j+1][i]+dist(word[i],word[j]));
            }
            
            // second hand at i, first at j (< i-1), then second hand at i-1
            for (int j = 0; j < i-1; ++j) {
                dp[j+1][i+1] = min(dp[j+1][i+1], dp[j+1][i]+moves[i]-moves[i-1]);
            }
            // first hand at i-1
            for (int j = -1; j < i-1; ++j) {
                dp[i][i+1] = min(dp[i][i+1], dp[i][j+1]+ (j>=0?dist(word[i],word[j]):0));
            }
        }
        int res = INF;
        for (int i = 0; i <= n; ++i) {
            res = min(res, dp[n][i]);
            res = min(res, dp[i][n]);
        }
        return res;
    }
    int minimumDistance_TLE(string word) {
        static constexpr int INF = 300*26;
        int n = word.size();
        vector<int> moves(n,0); // from 0 to i-th letter of word
        for (int i = 1; i < n; ++i) {
            moves[i] = moves[i-1] + dist(word[i-1], word[i]);
        }
        
        int res = INF;
        // second hand ending at i-th letter, it moves toword w[0]
        for (int k = n-2; k >= 0; --k) {
            // 0,1 => first hand, second hand
            // i => i-th letter of word
            vector<vector<int>> dp(k+2, vector<int>(k+2,INF));
            dp[k+1][k] = moves[n-1]-moves[k+1];
            for (int i = k-1; i >= 0; --i) { // i is current head
                // first hand at i, second at j(>i+1), then first hand at i+1
                for (int j = k; j > i+1; --j) {
                    dp[i][j] = min(dp[i][j], dp[i+1][j]+moves[i+1]-moves[i]);
                }
                // case 2: second hand at i+1, then first hand may be at (k+1, i+2)
                for (int j = k+1; j > i+1; --j) {
                    dp[i][i+1] = min(dp[i][i+1], dp[j][i+1]+dist(word[i],word[j]));
                }
                
                // second hand at i, first at j (> i+1), then second hand at i+1
                for (int j = k+1; j > i+1; --j) {
                    dp[j][i] = min(dp[j][i], dp[j][i+1]+moves[i+1]-moves[i]);
                }
                // first at i+1
                for (int j = k; j >i+1; --j) {
                    dp[i+1][i] = min(dp[i+1][i], dp[i+1][j]+dist(word[i],word[j]));
                }
            }
            for (int i = 0; i <= k+1; ++i) {
                res = min(res, dp[0][i]);
                res = min(res, dp[i][0]);
            }
        }
        return res;
    }
    int dist(char a, char b) {
        return abs((b-'A')/6-(a-'A')/6) + abs((a-'A')%6-(b-'A')%6);
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        string word;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {"CAKE"}
    };
    // TODO: provide expected results here
    vector<int> answers {
        3,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minimumDistance::Solution().minimumDistance(dp.word);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
