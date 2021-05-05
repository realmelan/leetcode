//
//  minSideJumps.cpp
//  leetcode
//
//  Created by Song Ding on 4/14/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minSideJumps {
/*
// TODO: copy problem statement here
 1824. Minimum Sideway Jumps My SubmissionsBack to Contest
 User Accepted: 1912
 User Tried: 2812
 Total Accepted: 1975
 Total Submissions: 5264
 Difficulty: Medium
 There is a 3 lane road of length n that consists of n + 1 points labeled from 0 to n. A frog starts at point 0 in the second lane and wants to jump to point n. However, there could be obstacles along the way.

 You are given an array obstacles of length n + 1 where each obstacles[i] (ranging from 0 to 3) describes an obstacle on the lane obstacles[i] at point i. If obstacles[i] == 0, there are no obstacles at point i. There will be at most one obstacle in the 3 lanes at each point.

 For example, if obstacles[2] == 1, then there is an obstacle on lane 1 at point 2.
 The frog can only travel from point i to point i + 1 on the same lane if there is not an obstacle on the lane at point i + 1. To avoid obstacles, the frog can also perform a side jump to jump to another lane (even if they are not adjacent) at the same point if there is no obstacle on the new lane.

 For example, the frog can jump from lane 3 at point 3 to lane 1 at point 3.
 Return the minimum number of side jumps the frog needs to reach any lane at point n starting from lane 2 at point 0.

 Note: There will be no obstacles on points 0 and n.

  

 Example 1:


 Input: obstacles = [0,1,2,3,0]
 Output: 2
 Explanation: The optimal solution is shown by the arrows above. There are 2 side jumps (red arrows).
 Note that the frog can jump over obstacles only when making side jumps (as shown at point 2).
 Example 2:


 Input: obstacles = [0,1,1,3,3,0]
 Output: 0
 Explanation: There are no obstacles on lane 2. No side jumps are required.
 Example 3:


 Input: obstacles = [0,2,1,0,3,0]
 Output: 2
 Explanation: The optimal solution is shown by the arrows above. There are 2 side jumps.
  

 Constraints:

 obstacles.length == n + 1
 1 <= n <= 5 * 105
 0 <= obstacles[i] <= 3
 obstacles[0] == obstacles[n] == 0
*/
class Solution {
public:
    // TODO: copy function signature here
    int minSideJumps(vector<int>& obstacles) {
        vector<int> dp{INT_MAX,1,0,1};
        int n = obstacles.size();
        for (int i = 1; i < n; ++i) {
            vector<int> next = dp;
            int j = obstacles[i];
            if (j) {
                next[j] = INT_MAX;
            }
            int k = obstacles[i-1];
            if (k && k!=j) {
                if (j) {
                    next[k] = dp[6-k-j]+1;
                } else {
                    next[k] = min({dp[1],dp[2],dp[3]}) + 1;
                }
            }
            
            dp.swap(next);
        }
        return *min_element(begin(dp), end(dp));
    }
    
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> obstacles;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{0,0,3,1,0,1,0,2,3,1,0}},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minSideJumps::Solution().minSideJumps(dp.obstacles);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
