//
//  minMoves.cpp
//  leetcode
//
//  Created by Song Ding on 2/7/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minMoves {
/*
// TODO: copy problem statement here
 1703. Minimum Adjacent Swaps for K Consecutive Ones My SubmissionsBack to Contest
 User Accepted: 108
 User Tried: 532
 Total Accepted: 115
 Total Submissions: 1060
 Difficulty: Hard
 You are given an integer array, nums, and an integer k. nums comprises of only 0's and 1's. In one move, you can choose two adjacent indices and swap their values.

 Return the minimum number of moves required so that nums has k consecutive 1's.

  

 Example 1:

 Input: nums = [1,0,0,1,0,1], k = 2
 Output: 1
 Explanation: In 1 move, nums could be [1,0,0,0,1,1] and have 2 consecutive 1's.
 Example 2:

 Input: nums = [1,0,0,0,0,0,1,1], k = 3
 Output: 5
 Explanation: In 5 moves, the leftmost 1 can be shifted right until nums = [0,0,0,0,0,1,1,1].
 Example 3:

 Input: nums = [1,1,0,1], k = 2
 Output: 0
 Explanation: nums already has 2 consecutive 1's.
  

 Constraints:

 1 <= nums.length <= 105
 nums[i] is 0 or 1.
 1 <= k <= sum(nums)
*/
class Solution {
public:
    // TODO: copy function signature here
    int minMoves(vector<int>& nums, int k) {
        return minMoves_bsearch(nums, k);
    }
    // two pointers
    int minMoves_tp(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> t{0};
        t.insert(end(t), begin(nums),end(nums));
        t.push_back(0);
        set<int> one;
        set<int> zero;
        int res = INT_MAX;
        for (int i = 0, j = 0; i <= n+1; ++i) {
            if (t[i]) {
                one.insert(i);
            } else {
                zero.insert(i);
            }
            while (one.size() > k && zero.size() > 2) {
                if (t[j]) {
                    one.erase(j);
                } else {
                    zero.erase(j);
                }
                ++j;
            }
            if (one.size() >= k && zero.size() >= 2) {
                // calculate # of operations needed
                // mid position should be in the range of []
                if (one.size() == k) {
                    // find mid point to move (be sure to have zero at the either side)
                    // if first 1 at j, and last 1 at i, try first move both 1 to nearest 0
                    set<int> onecp(one);
                    int moves = 0;
                    if (t[j]) {
                        int f = j;
                        while (f < i && t[f]) {
                            ++f;
                        }
                        onecp.erase(j);
                        onecp.insert(f);
                        moves += f - j;
                    }
                    if (t[i]) {
                        int s = i;
                        while (s > j && t[s]) {
                            --s;
                        }
                        onecp.erase(i);
                        onecp.insert(s);
                        moves += i - s;
                    }
                    // now ready to move 1 toward mid
                    auto front = begin(onecp);
                    auto back = rbegin(onecp);
                    while (*front < *back) {
                        moves += *back - *front;
                        ++front;
                        ++back;
                    }
                    moves -= k/2*((k+1)/2);
                    res = min(res, moves);
                } else { // move 0 to either side, not right, as there might be >k 1's
                    // get the distance of z1, z2, and compare gap of z1, z2 with k
                    int z1 = *begin(zero), z2 =*rbegin(zero);
                    res = min(res, abs(z2-z1 - (k+1)));
                }
            }
        }
        return res;
    }
    // binary search
    int minMoves_bsearch(vector<int>& nums, int k) {
        int n = nums.size();
            vector<int> pos;
            for (int i = 0; i < n; ++i) {
                if (nums[i]) {
                    pos.push_back(i);
                }
            }
            vector<int> posSum;
            int psum = 0;
            for (auto p : pos) {
                psum += p;
                posSum.push_back(psum);
            }
            int r = (n-1)*k, l = -1;
            while (r-l>1) {
                int m = (l+r)/2;
                if (canMove(pos, posSum, m, k)) {
                    r = m;
                } else {
                    l = m;
                }
            }
            return r;
        }
        bool canMove(vector<int>& pos, vector<int>& posSum, int m, int k) {
            int n = pos.size();
            for (int i = 0; i+k <= n; ++i) {
                int moves = (posSum[i+k-1] - posSum[i+(k-1)/2]) - (posSum[i+(k-2)/2] - (i>0?posSum[i-1]:0)) - (k/2)*((k+1)/2);
                if (moves <= m) {
                    return true;
                }
                
            }
            return false;
        }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nums; int k;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        //{{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},14},
        //{{1,0,0,1,0,1},2},
        {{1,0,0,0,0,0,1,1},3},
        {{1,1,0,1},2},
        {{1,0,0,1,1,1,1,1,1,1,1},7},
        
        
    };
    // TODO: provide expected results here
    vector<int> answers {
        1,
        1,
        5,
        0,
        0,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minMoves::Solution().minMoves(dp.nums, dp.k);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
