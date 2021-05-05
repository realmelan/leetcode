// canPartitionKSubsets.cpp
// leetcode
//
// Created by  Song Ding on 6/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace canPartitionKSubsets {
/*
// TODO: copy problem statement here
 698. Partition to K Equal Sum Subsets
 Medium
 
 839
 
 52
 
 Favorite
 
 Share
 Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into k non-empty subsets whose sums are all equal.
 
 
 
 Example 1:
 
 Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
 Output: True
 Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
 
 
 Note:
 
 1 <= k <= len(nums) <= 16.
 0 < nums[i] < 10000.

 */

class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        return canPartitionKSubsets_dp(nums, k);
    }
    bool canPartitionKSubsets_dp(vector<int>& nums, int k) {
        int n = nums.size();
        int sum = accumulate(begin(nums),end(nums), 0);
        if (sum % k) {
            return false;
        }
        sort(begin(nums), end(nums));
        int target = sum / k;
        if (nums[n-1] > target) {
            return false;
        }
        vector<int> sums(1<<n, -1);
        sums[0] = 0;
        for (int i = 0; i < (1<<n); ++i) {
            if (sums[i] != -1) {
                for (int j = 0; j < n; ++j) {
                    if ((i | (1<<j)) != i) {
                        if (nums[j] + sums[i]%target <= target) {
                            sums[i|(1<<j)] = sums[i] + nums[j];
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        return sums[(1<<n)-1] != -1;
    }
    bool canPartitionKSubsets2(vector<int>& nums, int k) {
        int sum = accumulate(begin(nums),end(nums), 0);
        if (sum % k) {
            return false;
        }
        int target = sum / k;
        for (auto i : nums) {
            if (i > target) {
                return false;
            }
        }
        sort(rbegin(nums), rend(nums));
        vector<int> sums(k, 0);
        if (0) {
            sums[0] += nums[0];
            return dfs(sums, nums, 1, target);
        }
        {
            return dfs2(sums, 0, nums, k, target);
        }
    }
    bool dfs(vector<int>& sums, vector<int>& nums, int j, int target) {
        if (j == nums.size()) {
            for (auto k : sums) {
                if (k != target) {
                    return false;
                }
            }
            return true;
        }
        for (int i = 0; i < sums.size(); ++i) {
            if (sums[i] == 0) {
                sums[i] += nums[j];
                bool res = dfs(sums, nums, j+1, target);
                sums[i] -= nums[j];
                if (res) {
                    return true;
                }
            }
            if (sums[i] + nums[j] <= target) {
                sums[i] += nums[j];
                bool res = dfs(sums, nums, j+1, target);
                sums[i] -= nums[j];
                if (res) {
                    return true;
                }
            }
        }
        return false;
    }
    bool dfs2(vector<int>& sums, int i, vector<int>& nums, int k, int target) {
        if (i == k) {
            return true;
        } else if (sums[i] == target) {
            return dfs2(sums, i+1, nums, k, target);
        }
        for (auto& j : nums) {
            if (j != 0 && sums[i] + j <= target) {
                sums[i] += j;
                int oldj = j;
                j = 0;
                bool res = dfs2(sums, i, nums, k, target);
                j = oldj;
                sums[i] -= j;
                if (res) {
                    return true;
                }
            }
        }
        return false;
    }
    
    /**
     * DFS:
     *  1, sort nums into descending order. otherwise, it may give false negative answers. {6,6,6,6,2,2,2,2},4
     *  2, can use # of elements left for pruning.
     */
    bool canPartitionKSubsets3(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end(), [](int a, int b){
            return a > b;
        });
        int sum = 0;
        for (auto i : nums) {
            sum += i;
        }
        
        if (sum % k) {
            return false;
        }
        
        int tsum = sum / k;
        if (nums[0] > tsum) {
            return false;
        }

        int tused = 0; // total numbr used so far
        vector<int> used(n, 0);
        for (int i = 0; i < k - 1; ++i) {
            // find first not used element
            int j = i;
            for (; j < n; ++j) {
                if (used[j] == 0) {
                    break;
                }
            }
            vector<int> ids{j};
            used[j] = 0;
            if (!dfs(nums, used, ids, tsum - nums[j], (n-tused) - (k-i-1))) {
                return false;
            }
            
            for (auto id : ids) {
                used[id] = 1;
            }
            tused += ids.size();
        }
        
        return true;
    }
    
    int binary_search(const int a[], const int size, const int val) {
        int lower = 0;
        int upper = size-1;
        
        /* invariant: if a[i]==val for any i, then lower <= i <= upper */
        /* bound function: upper-lower+1 */
        while (lower <= upper) {
            int i = lower + (upper-lower)/2;
            if (val == a[i]) {
                return i;
            } else if (val < a[i]) {
                upper = i-1;
            } else { /* val > a[i] */
                lower = i+1;
            }
        }
        return -1;
    }

private:
    bool dfs(vector<int>& nums, vector<int>& used, vector<int>& ids, int t, int use_limit) {
        if (t == 0) {
            return true;
        } else if (ids.size() >= use_limit) {
            return false;
        }
        
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i] || nums[i] > t) {
                continue;
            }
            used[i] = 1;
            ids.push_back(i);
            if (dfs(nums, used, ids, t - nums[i], use_limit)) {
                return true;
            }
            
            ids.pop_back();
            used[i] = 0;
        }
        return false;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nums;
        int k;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{4, 3, 2, 3, 5, 2, 1}, 4},
        {{6,6,6,6,2,2,2,2}, 4},
        {{3522,181,521,515,304,123,2512,312,922,407,146,1932,4037,2646,3871,269},5}
    };

    vector< bool > answers {
        true,
        true
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = canPartitionKSubsets::Solution().canPartitionKSubsets(dp.nums, dp.k);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
