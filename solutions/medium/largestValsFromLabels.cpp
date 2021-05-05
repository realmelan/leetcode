// largestValsFromLabels.cpp
// leetcode
//
// Created by  Song Ding on 6/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace largestValsFromLabels {
/*
// TODO: copy problem statement here
 1090. Largest Values From Labels
 Medium
 
 22
 
 44
 
 Favorite
 
 Share
 We have a set of items: the i-th item has value values[i] and label labels[i].
 
 Then, we choose a subset S of these items, such that:
 
 |S| <= num_wanted
 For every label L, the number of items in S with label L is <= use_limit.
 Return the largest possible sum of the subset S.
 
 
 
 Example 1:
 
 Input: values = [5,4,3,2,1], labels = [1,1,2,2,3], num_wanted = 3, use_limit = 1
 Output: 9
 Explanation: The subset chosen is the first, third, and fifth item.
 Example 2:
 
 Input: values = [5,4,3,2,1], labels = [1,3,3,3,2], num_wanted = 3, use_limit = 2
 Output: 12
 Explanation: The subset chosen is the first, second, and third item.
 Example 3:
 
 Input: values = [9,8,8,7,6], labels = [0,0,0,1,1], num_wanted = 3, use_limit = 1
 Output: 16
 Explanation: The subset chosen is the first and fourth item.
 Example 4:
 
 Input: values = [9,8,8,7,6], labels = [0,0,0,1,1], num_wanted = 3, use_limit = 2
 Output: 24
 Explanation: The subset chosen is the first, second, and fourth item.
 
 
 Note:
 
 1 <= values.length == labels.length <= 20000
 0 <= values[i], labels[i] <= 20000
 1 <= num_wanted, use_limit <= values.length
 */

class Solution {
public:
    /**
     * sort values/labels based on value
     */
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int num_wanted, int use_limit) {
        int n = values.size();
        vector<pair<int,int>> vls;
        for (int i = 0; i < n; ++i) {
            vls.push_back(make_pair(values[i], labels[i]));
        }
        sort(vls.begin(), vls.end(), [](const pair<int,int>& a, const pair<int,int>& b){
            if (a.first != b.first) {
                return a.first > b.first;
            } else {
                return a.second < b.second;
            }
        });
        
        int res = 0;
        int num = 0;
        unordered_map<int, int> use_count;
        for (int i = 0; i < n; ++i) {
            if (use_count[vls[i].second] < use_limit) {
                res += vls[i].first;
                ++use_count[vls[i].second];
                if (++num >= num_wanted) {
                    break;
                }
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> values;
        vector<int> labels;
        int num_wanted;
        int use_limit;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{5,4,3,2,1}, {1,1,2,2,3}, 3, 1},
        {{5,4,3,2,1}, {1,3,3,3,2}, 3, 2},
        {{9,8,8,7,6}, {0,0,0,1,1}, 3, 1},
        {{9,8,8,7,6}, {0,0,0,1,1}, 3, 2}
    };

    vector< int > answers {
        9,
        12,
        16,
        24
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = largestValsFromLabels::Solution().largestValsFromLabels(dp.values, dp.labels, dp.num_wanted, dp.use_limit);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
