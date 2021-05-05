// permuteUnique.cpp
// leetcode
//
// Created by  Song Ding on 11/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace permuteUnique {
/*
// TODO: copy problem statement here
 47. Permutations II
 Medium

 1344

 47

 Favorite

 Share
 Given a collection of numbers that might contain duplicates, return all possible unique permutations.

 Example:

 Input: [1,1,2]
 Output:
 [
   [1,1,2],
   [1,2,1],
   [2,1,1]
 ]
 */

class Solution {
public:
    /**
     * dfs
     */
    vector<vector<int>> permuteUnique2(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> cur, visited(n, 0);
        dfs(nums, visited, cur, res);
        return res;
    }

private:
    void dfs(vector<int>& nums, vector<int>& visited, vector<int>& cur, vector<vector<int>>& res) {
        if (cur.size() == nums.size()) {
            res.push_back(cur);
        } else {
            int last = -1;
            for (int i = 0; i < nums.size(); ++i) {
                if (visited[i] || (last != -1 && nums[i] == nums[last])) {
                    continue;
                }
                last = i;
                visited[i] = 1;
                cur.push_back(nums[i]);
                dfs(nums, visited, cur, res);
                cur.pop_back();
                visited[i] = 0;
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        sort(begin(nums), end(nums));
        dfs(0, nums, res);
        return res;
    }
    void dfs(int st, vector<int>& nums, vector<vector<int>>& res) {
        if (st >= nums.size()) {
            res.push_back(nums);
            return;
        }
        for (int i = st; i < nums.size(); ++i) {
            if (i > st && nums[i] == nums[st]) {
                continue;
            }
            swap(nums[st], nums[i]);
            for (int j = 0; j < st; ++j) {
                cout << "\t";
            }
            cout << i << ", " << nums << endl;
            dfs(st+1, nums, res);
            //swap(nums[st], nums[i]);
        }
    }
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
        //{{1,1,2}},
        //{{2,2,1,1}},
        {{0,1,0,0,9}}
    };

    vector< vector<vector<int>> > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = permuteUnique::Solution().permuteUnique(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
