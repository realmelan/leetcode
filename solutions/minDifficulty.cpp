//
//  minDifficulty.cpp
//  leetcode
//
//  Created by Song Ding on 3/3/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minDifficulty {
/*
// TODO: copy problem statement here
 1335. Minimum Difficulty of a Job Schedule
 Hard

 110

 3

 Add to List

 Share
 You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the i-th job, you have to finish all the jobs j where 0 <= j < i).

 You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a job done in that day.

 Given an array of integers jobDifficulty and an integer d. The difficulty of the i-th job is jobDifficulty[i].

 Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.

  

 Example 1:


 Input: jobDifficulty = [6,5,4,3,2,1], d = 2
 Output: 7
 Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
 Second day you can finish the last job, total difficulty = 1.
 The difficulty of the schedule = 6 + 1 = 7
 Example 2:

 Input: jobDifficulty = [9,9,9], d = 4
 Output: -1
 Explanation: If you finish a job per day you will still have a free day. you cannot find a schedule for the given jobs.
 Example 3:

 Input: jobDifficulty = [1,1,1], d = 3
 Output: 3
 Explanation: The schedule is one job per day. total difficulty will be 3.
 Example 4:

 Input: jobDifficulty = [7,1,7,1,7,1], d = 3
 Output: 15
 Example 5:

 Input: jobDifficulty = [11,111,22,222,33,333,44,444], d = 6
 Output: 843
  

 Constraints:

 1 <= jobDifficulty.length <= 300
 0 <= jobDifficulty[i] <= 1000
 1 <= d <= 10
*/
class Solution {
public:
    // TODO: copy function signature here
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        vector<vector<int>> dp(d, vector<int>(n, -1));
        dp[0][0] = jobDifficulty[0];
        for (int i = 1; i < n; ++i) {
            dp[0][i] = max(dp[0][i-1], jobDifficulty[i]);
        }
        for (int i = 1; i < d; ++i) {
            for (int j = i; j+(d-i-1) < n; ++j) {
                int jd = jobDifficulty[j];
                dp[i][j] = jd + dp[i-1][j-1];
                for (int k = j-1; k >= i; --k) {
                    jd = max(jd, jobDifficulty[k]);
                    if (dp[i-1][k-1] >= 0) {
                        dp[i][j] = min(dp[i][j], jd+dp[i-1][k-1]);
                    }
                }
            }
        }
        return dp[d-1][n-1];
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> jobDifficulty;
        int d;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{6,5,4,3,2,1},2},
        {{9,9,9},4},
        {{1,1,1},3},
        {{7,1,7,1,7,1},3},
        {{11,111,22,222,33,333,44,444},6}
        
    };
    // TODO: provide expected results here
    vector<int> answers {
        7,
        -1,
        3,
        15,
        843,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minDifficulty::Solution().minDifficulty(dp.jobDifficulty, dp.d);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
