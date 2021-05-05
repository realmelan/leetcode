// eraseOverlapIntervals.cpp
// leetcode
//
// Created by  Song Ding on 10/28/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace eraseOverlapIntervals {
/*
// TODO: copy problem statement here
 435. Non-overlapping Intervals
 Medium

 628

 26

 Favorite

 Share
 Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

  

 Example 1:

 Input: [[1,2],[2,3],[3,4],[1,3]]
 Output: 1
 Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.
 Example 2:

 Input: [[1,2],[1,2],[1,2]]
 Output: 2
 Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.
 Example 3:

 Input: [[1,2],[2,3]]
 Output: 0
 Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
  

 Note:

 You may assume the interval's end point is always bigger than its start point.
 Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.
 */

class Solution {
public:
    /**
     * greedy:
     * sort intervals by end point into ascending order, and then by start point into descending order.
     * if current start point is >= last end point, update end point; else the interval should be removed.
     */
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),[](const vector<int>& a, const vector<int>& b){
            return a[1] != b[1] ? a[1] < b[1] : a[0] > b[0];
        });
        int n = intervals.size();
        int res = 0;
        int endp = INT_MIN;
        for (int i = 0; i < n; ++i) {
            if (intervals[i][0] >= endp) {
                endp = intervals[i][1];
            } else {
                ++res;
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
        vector<vector<int>> intervals;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{1,2},{2,3},{3,4},{1,3}}},
        {{{1,2},{1,2},{1,2}}},
        {{{1,2},{2,3}}},
    };

    vector< int > answers {
        1,
        2,
        0,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = eraseOverlapIntervals::Solution().eraseOverlapIntervals(dp.intervals);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
