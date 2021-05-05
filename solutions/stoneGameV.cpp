//
//  stoneGameV.cpp
//  leetcode
//
//  Created by Song Ding on 3/19/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace stoneGameV {
/*
// TODO: copy problem statement here
 1563. Stone Game V My SubmissionsBack to Contest
 User Accepted: 801
 User Tried: 1473
 Total Accepted: 834
 Total Submissions: 3059
 Difficulty: Hard
 There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.

 In each round of the game, Alice divides the row into two non-empty rows (i.e. left row and right row), then Bob calculates the value of each row which is the sum of the values of all the stones in this row. Bob throws away the row which has the maximum value, and Alice's score increases by the value of the remaining row. If the value of the two rows are equal, Bob lets Alice decide which row will be thrown away. The next round starts with the remaining row.

 The game ends when there is only one stone remaining. Alice's is initially zero.

 Return the maximum score that Alice can obtain.

  

 Example 1:

 Input: stoneValue = [6,2,3,4,5,5]
 Output: 18
 Explanation: In the first round, Alice divides the row to [6,2,3], [4,5,5]. The left row has the value 11 and the right row has value 14. Bob throws away the right row and Alice's score is now 11.
 In the second round Alice divides the row to [6], [2,3]. This time Bob throws away the left row and Alice's score becomes 16 (11 + 5).
 The last round Alice has only one choice to divide the row which is [2], [3]. Bob throws away the right row and Alice's score is now 18 (16 + 2). The game ends because only one stone is remaining in the row.
 Example 2:

 Input: stoneValue = [7,7,7,7,7,7,7]
 Output: 28
 Example 3:

 Input: stoneValue = [4]
 Output: 0
  

 Constraints:

 1 <= stoneValue.length <= 500
 1 <= stoneValue[i] <= 10^6
*/
class Solution {
public:
    // TODO: copy function signature here
    int stoneGameV(vector<int>& stoneValue) {
        // let dp[i][j] = maximum score alice can get given current row
        // starts at stones[i], ends at stones[j]
        // then dp[i][j] = max(dp[i][k] or dp[k][j]) for all k, if sum[i][k]<sum[k+1][j]
        // or sum[i][k-1]>sum[k][j]
        // cost: O(n^3), TLE
        // we can use a deque to hold <sum,score> pair for all entries starting at i or ending
        // at j
        int n = stoneValue.size();
        vector<int> psum{0};
        for (auto i : stoneValue) {
            psum.push_back(psum.back()+i);
        }
        // front[i] = deque<pair<sum, score>>
        vector<deque<pair<int,int>>> front(n), back(n);
        for (int i = 0; i < n; ++i) {
            front[i].push_back({stoneValue[i],stoneValue[i]});
            back[i].push_back({stoneValue[i],stoneValue[i]});
        }
        int res = 0;
        for (int l = 2; l <= n; ++l) {
            for (int i = 0; i+l<=n; ++i) {
                int j = i+l-1;
                // we don't need to go from i to j, only limited number of positions will provide
                // possible maximum score for alice
                // like [i..i+1] is less useful compared to [i..i+2]
                int sum = psum[j+1] - psum[i];
                int score = 0;
                auto& fq = front[i];
                while (fq.size() && fq.front().first <= sum-fq.front().first) {
                    auto last = fq.front();
                    fq.pop_front();
                    score = max(score, last.second);
                    if (fq.empty() || fq.front().first > sum-fq.front().first) {
                        fq.push_front(last);
                        break;
                    }
                }
                auto& bq = back[j];
                while (bq.size() && bq.front().first <= sum-bq.front().first) {
                    auto last = bq.front();
                    bq.pop_front();
                    score = max(score, last.second);
                    if (bq.empty() || bq.front().first > sum-bq.front().first) {
                        bq.push_front(last);
                        break;
                    }
                }
                if (l == n) {
                    res = max(res, score);
                }
                score += sum;
                int prevScore = 0;
                if (fq.size()) {
                    prevScore = fq.back().second;
                }
                fq.push_back({sum, max(prevScore, score)});
                prevScore = 0;
                if (bq.size()) {
                    prevScore = bq.back().second;
                }
                bq.push_back({sum, max(prevScore, score)});
            }
        }
        return res;
    }
    
    int stoneGameV_TLE(vector<int>& stoneValue) {
        // let dp[i][j] = maximum score alice can get given current row
        // starts at stones[i], ends at stones[j]
        // then dp[i][j] = max(dp[i][k] or dp[k][j]) for all k, if sum[i][k]<sum[k+1][j]
        // or sum[i][k-1]>sum[k][j]
        // cost: O(n^3), TLE
        int n = stoneValue.size();
        vector<int> psum{0};
        for (auto i : stoneValue) {
            psum.push_back(psum.back()+i);
        }
        vector<vector<int>> dp(n,vector<int>(n,0));
        for (int l = 2; l <= n; ++l) {
            for (int i = 0; i+l<=n; ++i) {
                int j = i+l-1;
                // we don't need to go from i to j, only limited number of positions will provide
                // possible maximum score for alice
                // like [i..i+1] is less useful compared to [i..i+2]
                int midsum = (psum[i]+psum[j+1]+1)/2;
                auto it = lower_bound(begin(psum), end(psum), midsum);
                int k = distance(begin(psum),it)-1;
                if (psum[j+1]-psum[k+1] == psum[k+1]-psum[i]) {
                    dp[i][j] = max(dp[i][j], psum[k+1]-psum[i]+max(dp[i][k], dp[k+1][j]));
                } else {
                    if (k+1<=j) {
                        dp[i][j] = max(dp[i][j], psum[j+1]-psum[k+1]+dp[k+1][j]);
                    }
                    if (k-1>=0) {
                        dp[i][j] = max(dp[i][j], psum[k]-psum[i]+dp[i][k-1]);
                    }
                }
            }
        }
        return dp[0][n-1];
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> stoneValue;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{10,9,8,7,6,5,4,3,2}},
        {{10,9,8,7,6,5,4,3,2,1}},
        {{6,2,3,4,5,5}},
        {{98,77,24,49,6,12,2,44,51,96}},
        {{9,8,2,4,6,3,5,1,7}},
        
    };
    // TODO: provide expected results here
    vector<int> answers {
        46,
        37,
        18,
        330,
        34,    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = stoneGameV::Solution().stoneGameV(dp.stoneValue);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
