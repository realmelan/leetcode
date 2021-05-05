//
//  minMoves3.cpp
//  leetcode
//
//  Created by Song Ding on 2/15/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minMoves3 {
/*
// TODO: copy problem statement here

*/
class Solution {
public:
    // TODO: copy function signature here
    int minMoves(vector<int>& nums, int limit) {
        return minMoves_TLE(nums, limit);
    }
    int minMoves_TLE(vector<int>& nums, int limit) {
        map<int,int> cnts;
        int minval = 1e5, n = nums.size();
        for (int i = 0, j = n-1; i < j; ++i,--j) {
            int sum = nums[i] + nums[j];
            if (nums[i] > nums[j]) {
                swap(nums[i], nums[j]);
            }
            ++cnts[sum];
        }
        int res = n/2;
        priority_queue<vector<int>> sortedCnts;
        for (auto& p : cnts) {
            sortedCnts.push({p.second, p.first});
        }
        // in the case when the extreme case exists for each pair, then using
        // the target sum isn't optimal.
        while (sortedCnts.size()) {
            auto v = sortedCnts.top();
            sortedCnts.pop();
            // at least for p.first, we need to modify n/2-p.second pair
            if (n/2-v[0] >= res) {
                break;
            }
            int tsum = v[1], cnt = 0;
            for (int i = 0, j = n-1; i < j; ++i,--j) {
                int sum = nums[i] + nums[j];
                if (sum > tsum) {
                    ++cnt;
                    if (nums[i]+1 > tsum) {
                        ++cnt;
                    }
                } else if (sum < tsum) {
                    ++cnt;
                    if (nums[j]+limit < tsum) {
                        ++cnt;
                    }
                }
            }
            res = min(res, cnt);
        }
        return res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nums;
        int limit;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        //{{1,3,1,1,1,2,3,2,3,1,3,2,1,3},3},
        //{{20744,7642,19090,9992,2457,16848,3458,15721},22891},
        {{34,24,35,17,58,40,51,28,15,63,36,3,26,30,61,38,45,63},70},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minMoves3::Solution().minMoves(dp.nums, dp.limit);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
