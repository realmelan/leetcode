//
//  combinationSum4.cpp
//  leetcode
//
//  Created by  Song Ding on 11/2/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;
namespace combinationSum4 {
    class Solution {
    public:
        /**
         Find out all unique combinations of 1, 2, 3,
         like ax + by + cz = k, get different (a, b, c) tuples.
         then see to ordering.
        int combinationSum4(vector<int>& nums, int target) {
            // remove any elements which are larger than target
            sort(nums.begin(), nums.end());
            vector<int> nums2;
            for (auto i : nums) {
                if (i <= target) {
                    nums2.push_back(i);
                }
            }
            
            if (nums2.empty()) {
                return 0;
            }
            
            vector<int> t;
            getCombinations(nums2, target, 0, t);
            int res = 0;
            for (auto c : combinations) {
                int start = 1;
                int p = 1;
                for (auto i : c) {
                    if (i <= 0) {
                        continue;
                    }
                    
                    for (int j = 1; j <= i; ++j) {
                        p *= start++;
                        p /= j;
                    }
                }
                
                res += p;
            }
            return res;
            
        }
    private:
        void getCombinations(vector<int>& nums, int target, int index, vector<int> com) {
            if (index >= nums.size()) {
                return;
            }
            
            int num = nums[index];
            
            for (int i = 0; i <= target / num; ++i) {
                int t = target - num * i;
                if (t == 0) {
                    vector<int> tcom(com);
                    tcom.push_back(i);
                    for (int j = index + 1; j < nums.size(); ++j) {
                        tcom.push_back(0);
                    }
                    combinations.push_back(tcom);
                    break;
                } else if (t > 0) {
                    com.push_back(i);
                    getCombinations(nums, t, index + 1, com);
                    com.pop_back();
                } else {
                    break;
                }
            }
        }
        vector<vector<int>> combinations;
         */
        
        int combinationSum4(vector<int>& nums, int target) {
            int res = 0;
            sort(nums.begin(), nums.end());
            nums.erase(remove_if(nums.begin(), nums.end(), [target](int a) { return a > target;}), nums.end());
            if (nums.empty()) {
                return 0;
            }
            
            vector<int> comb(target + 1, 0);
            comb[0] = 1;
            for (int i = 0; i <= target; ++i) {
                for (auto k : nums) {
                    if (i >= k) {
                        comb[i] += comb[i - k];
                    }
                }
            }
            return comb[target];
        }
        
        int combinationSum4_dfs(vector<int>& nums, int target) {
            vector<int> dp(target + 1, -1);
            dp[0] = 1;
            return dfs(target, nums, dp);
        }
        int dfs(int t, vector<int>& nums, vector<int>& dp) {
            if (dp[t] >= 0) {
                return dp[t];
            }
            dp[t] = 0;
            for (auto k : nums) {
                if (t >= k) {
                    dp[t] += dfs(t-k, nums, dp);
                }
            }
            return dp[t];
        }
        int combinationSum4_2(vector<int>& nums, int target) {
            sort(begin(nums), end(nums));
            vector<int> dp(target+1,0);
            dp[0] = 1;
            for (int t = 1; t <= target; ++t) {
                for (int i : nums) {
                    if (t<i) {
                        break;
                    }
                    dp[t] += min(dp[t-i], INT_MAX-dp[t]);
                    /*
                    if (dp[t] < 0) {
                        cout << "bad things happen" << endl;
                    }
                     */
                }
            }
            /*
            for (auto i : nums) {
                for (int t = target; t >= i; --t) {
                    dp[t] += dp[t-i];
                }
            }
            */
            return dp[target];
        }
    };


}

/*
int main() {
    vector<int> v{10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,560,570,580,590,600,610,620,630,640,650,660,670,680,690,700,710,720,730,740,750,760,770,780,790,800,810,820,830,840,850,860,870,880,890,900,910,920,930,940,950,960,970,980,990,111};
    int target = 999;
    cout << combinationSum4::Solution().combinationSum4_2(v, target) << endl;
    return 0;
}
// */
