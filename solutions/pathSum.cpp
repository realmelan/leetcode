// pathSum.cpp
// leetcode
//
// Created by  Song Ding on 10/18/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace pathSum {
/*
// TODO: copy problem statement here
 666. Path Sum IV

 If the depth of a tree is smaller than 5, then this tree can be represented by a list of three-digits integers.

 For each integer in this list:

 The hundreds digit represents the depth D of this node, 1 <= D <= 4.
 The tens digit represents the position P of this node in the level it belongs to, 1 <= P <= 8. The position is the same as that in a full binary tree.
 The units digit represents the value V of this node, 0 <= V <= 9.
 Given a list of ascending three-digits integers representing a binary with the depth smaller than 5. You need to return the sum of all paths from the root towards the leaves.

 Example 1:

 Input: [113, 215, 221]
 Output: 12
 Explanation:
 The tree that the list represents is:
     3
    / \\
   5   1

 The path sum is (3 + 5) + (3 + 1) = 12.
 Example 2:

 Input: [113, 221]
 Output: 4
 Explanation:
 The tree that the list represents is:
     3
      \\
       1

 The path sum is (3 + 1) = 4.
 */

class Solution {
public:
    /**
     * starting from last level, and count # of times that a node will be
     * added toward result.
     */
    int pathSum(vector<int>& nums) {
        int n = nums.size();
        int level = nums[n-1] / 100;
        int res = 0;
        vector<int> cnt((1<<(level-1))+1, 0);
        for (int i = n-1; i >= 0 && level >= 1; --level) {
            int cntn = level > 2 ? (1<<(level-2)) : 2;
            vector<int> ncnt(cntn+1, 0);
            while (i >= 0 && nums[i]/100 >= level) {
                
                int v = nums[i] % 10;
                int p = (nums[i] % 100) / 10;
                int icnt = max(1, cnt[p]);
                res += v * icnt;
                ncnt[(p+1)/2] += icnt;
                --i;
            }
            cnt.swap(ncnt);
        }
        return res;
    }
    /**
     * parent(i) = (i+1)/2
     * When going over current level, should sum up leaf nodes on previous level, if no
     * nodes in current level reference back.
     */
    int pathSum2(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        vector<int> sum;
        sum.push_back(0);
        sum.push_back(nums[0]%10);
        // FIXME: the leaf nodes are on different levels...
        for (int i = 1, level = 2; i < n; ++level) {
            vector<int> nsum((1<<(level-1))+1, 0);
            int j = 0;
            while (i < n && nums[i]/100 < level + 1) {
                // find up level sum
                int v = nums[i] % 10;
                int p = (nums[i] % 100) / 10;
                
                nsum[p] = sum[(p+1)/2] + v;
                ++i;
                
                // add leaf nodes on previous level
                for (; j < (p+1)/2; ++j) {
                    res += sum[j];
                }
                j = (p+1)/2+1;
            }
            for (; j < 1<<(level-2); ++j) {
                res += sum[j];
            }
            sum.swap(nsum);
        }
        return res + accumulate(sum.begin(), sum.end(), 0);
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
        {{113, 215, 221}},
        {{113, 221}},
        {{115,213,227,334,345}},
    };

    vector< int > answers {
        12,
        4,
        41,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = pathSum::Solution().pathSum(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
