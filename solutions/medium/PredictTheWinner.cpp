// PredictTheWinner.cpp
// leetcode
//
// Created by  Song Ding on 10/9/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace PredictTheWinner {
/*
// TODO: copy problem statement here
 486. Predict the Winner
 Medium

 1123

 73

 Favorite

 Share
 Given an array of scores that are non-negative integers. Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on. Each time a player picks a number, that number will not be available for the next player. This continues until all the scores have been chosen. The player with the maximum score wins.

 Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.

 Example 1:
 Input: [1, 5, 2]
 Output: False
 Explanation: Initially, player 1 can choose between 1 and 2.
 If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2).
 So, final score of player 1 is 1 + 2 = 3, and player 2 is 5.
 Hence, player 1 will never be the winner and you need to return False.
 Example 2:
 Input: [1, 5, 233, 7]
 Output: True
 Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
 Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
 Note:
 1 <= length of the array <= 20.
 Any scores in the given array are non-negative integers and will not exceed 10,000,000.
 If the scores of both players are equal, then player 1 is still the winner.
 */

class Solution {
public:
    /**
     * let score(i,j) = max score player 1 can get, then
     * score(i,j) = sum(i,j) - min(score(i+1,j),score(i,j-1)).
     * result is true if score(0,n-1) > sum(0,n-1)/2.
     */
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<int> sum(n+1, 0);
        for (int i = 0; i < n; ++i) {
            sum[i+1] = sum[i] + nums[i];
        }
        if (n <= 2 || sum[n] <= 0) {
            return true;
        }
        vector<int> score(nums);
        for (int k = 2; k <= n; ++k) {
            vector<int> nscore(n);
            for (int i = 0; i <= n-k; ++i) {
                int j = i+k-1;
                nscore[i] = sum[j+1]-sum[i] - min(score[i], score[i+1]);
            }
            score.swap(nscore);
        }
        return score[0] * 2 >= sum[n];
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nums;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{0}},
        {{1,5,2}},
        {{1, 5, 233, 7}},
    };

    vector< bool > answers {
        true,
        false,
        true,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = PredictTheWinner::Solution().PredictTheWinner(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
