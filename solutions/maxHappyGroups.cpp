//
//  maxHappyGroups.cpp
//  leetcode
//
//  Created by Song Ding on 4/10/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace maxHappyGroups {
/*
// TODO: copy problem statement here
 1815. Maximum Number of Groups Getting Fresh Donuts My SubmissionsBack to Contest
 User Accepted: 68
 User Tried: 487
 Total Accepted: 82
 Total Submissions: 1356
 Difficulty: Hard
 There is a donuts shop that bakes donuts in batches of batchSize. They have a rule where they must serve all of the donuts of a batch before serving any donuts of the next batch. You are given an integer batchSize and an integer array groups, where groups[i] denotes that there is a group of groups[i] customers that will visit the shop. Each customer will get exactly one donut.

 When a group visits the shop, all customers of the group must be served before serving any of the following groups. A group will be happy if they all get fresh donuts. That is, the first customer of the group does not receive a donut that was left over from the previous group.

 You can freely rearrange the ordering of the groups. Return the maximum possible number of happy groups after rearranging the groups.

  

 Example 1:

 Input: batchSize = 3, groups = [1,2,3,4,5,6]
 Output: 4
 Explanation: You can arrange the groups as [6,2,4,5,1,3]. Then the 1st, 2nd, 4th, and 6th groups will be happy.
 Example 2:

 Input: batchSize = 4, groups = [1,3,2,5,2,2,1,6]
 Output: 4
  

 Constraints:

 1 <= batchSize <= 9
 1 <= groups.length <= 30
 1 <= groups[i] <= 109
*/
class Solution {
public:
    // TODO: copy function signature here
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        // try group size from 1 to 30
        int sum = 0;
        vector<long> gcnt(batchSize,0);
        for (auto i : groups) {
            ++gcnt[i%batchSize];
            sum += i%batchSize;
        }
        vector<unordered_map<long,int>> dp(batchSize);
        int res = dfs(0, batchSize, gcnt, dp);
        return res + gcnt[0] + (sum%batchSize?1:0);
    }
private:
    int dfs(int sum, int batchSize, vector<long>& gcnt, vector<unordered_map<long,int>>& dp) {
        long key = 0;
        for (int i = 1; i < batchSize; ++i) {
            key |= gcnt[i] << (i*5);
        }
        if (dp[sum].count(key)) {
            return dp[sum][key];
        }
        int res = 0;
        for (int i = 1; i < batchSize; ++i) {
            if (gcnt[i]) {
                --gcnt[i];
                int more = 0;
                if ((sum+i)%batchSize == 0) {
                    more = 1;
                }
                res = max(res, more+dfs((sum+i)%batchSize, batchSize, gcnt, dp));
                ++gcnt[i];
            }
        }
        return dp[sum][key] = res;
    }
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        int batchSize;
        vector<int> groups;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {3,{1,2,3,4,5,6}},
        {4,{1,3,2,5,2,2,1,6}},
        {7,{839562595,994462569,405916966,82304069,612871994,590853022,240211157,607701921,87771155,286392333,391799587,956454997,317347197,606070171,573694014,993283352,122745984,491525998,962888093}},
        {6,{911597275,593046764,399017856,177359293,752996524,752989336,790722936,499051964,638423060,91239286,919420580,132332127,962721609,650800467,551850946,613356440,405012957,189274807,167266666,269074770,458222420,233666284,611514594,772662113}},
        {8, {244197059,419273145,329407130,44079526,351372795,200588773,340091770,851189293,909604028,621703634,959388577,989293607,325139045,263977422,358987768,108391681,584357588,656476891,621680874,867119215,639909909,98831415,263171984,236390093,21876446}},
    };
    // TODO: provide expected results here
    vector<int> answers {
        4,
        4,
        10,
        14,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxHappyGroups::Solution().maxHappyGroups(dp.batchSize, dp.groups);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
