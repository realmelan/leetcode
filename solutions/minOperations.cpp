//
//  minOperations.cpp
//  leetcode
//
//  Created by Song Ding on 2/2/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minOperations {
/*
// TODO: copy problem statement here
 1713. Minimum Operations to Make a Subsequence
 Hard

 191

 3

 Add to List

 Share
 You are given an array target that consists of distinct integers and another integer array arr that can have duplicates.

 In one operation, you can insert any integer at any position in arr. For example, if arr = [1,4,1,2], you can add 3 in the middle and make it [1,4,3,1,2]. Note that you can insert the integer at the very beginning or end of the array.

 Return the minimum number of operations needed to make target a subsequence of arr.

 A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements), while [2,4,2] is not.

  

 Example 1:

 Input: target = [5,1,3], arr = [9,4,2,3,4]
 Output: 2
 Explanation: You can add 5 and 1 in such a way that makes arr = [5,9,4,1,2,3,4], then target will be a subsequence of arr.
 Example 2:

 Input: target = [6,4,8,1,3,2], arr = [4,7,6,2,3,8,6,1]
 Output: 3
  

 Constraints:

 1 <= target.length, arr.length <= 105
 1 <= target[i], arr[i] <= 109
 target contains no duplicates.
*/
class Solution {
public:
    // TODO: copy function signature here
    int minOperations(vector<int>& target, vector<int>& arr) {
        int nt = target.size(), na = arr.size();
        vector<vector<int>> memo(nt, vector<int>(na,-1));
        unordered_map<int,set<int>> v2i;
        for (int i = na-1; i >= 0; --i) {
            v2i[arr[i]].insert(i);
        }
        unordered_set<int> t;
        vector<vector<int>> t2a(nt, vector<int>(na,na));
        for (int ti = nt-1; ti >= 0; --ti) {
            t.insert(target[ti]);
            for (int ai = na-1; ai >= 0; --ai) {
                if (t.count(arr[ai])) {
                    t2a[ti][ai] = ai;
                } else {
                    t2a[ti][ai] = ai<na-1? na : t2a[ti][ai+1];
                }
            }
        }
        return dfs(0, target, 0, arr, v2i, t2a, memo);
        
    }
    int dfs(int ti, vector<int>& t, int ai, vector<int>& arr, unordered_map<int,set<int>>& v2i, vector<vector<int>>& t2a, vector<vector<int>>& memo) {
        if (ti >= t.size()) {
            return 0;
        } else if (ai >= arr.size()) {
            return t.size()-ti;
        } else if (memo[ti][ai]>=0) {
            return memo[ti][ai];
        } else if (arr[ai] == t[ti]) {
            return memo[ti][ai] = dfs(ti+1,t,ai+1,arr,v2i,t2a,memo);
        } else {
            // this one might not be necessary
            int res = INT_MAX;
            if (v2i.count(t[ti])) {
                auto it = v2i[t[ti]].lower_bound(ai);
                if (it != end(v2i[t[ti]])) {
                    res = dfs(ti+1, t, *it+1, arr, v2i, t2a, memo);
                    if (ti+1 >= t.size() || t2a[ti+1][ai] > *it) {
                        return memo[ti][ai] = res;
                    }
                }
            }
            res = min(res, 1+dfs(ti+1, t, ai, arr, v2i, t2a, memo));
            return memo[ti][ai] = res;
        }
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> target;
        vector<int> arr;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{5,1,3},{9,4,2,3,4}},
        {{6,4,8,1,3,2}, {4,7,6,2,3,8,6,1}},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minOperations::Solution().minOperations(dp.target, dp.arr);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
