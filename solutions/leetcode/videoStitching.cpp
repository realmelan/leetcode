// videoStitching.cpp
// leetcode
//
// Created by  Song Ding on 5/19/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace videoStitching {
/*
// TODO: copy problem statement here
 1024. Video Stitching
 Medium
 
 131
 
 15
 
 Favorite
 
 Share
 You are given a series of video clips from a sporting event that lasted T seconds.  These video clips can be overlapping with each other and have varied lengths.
 
 Each video clip clips[i] is an interval: it starts at time clips[i][0] and ends at time clips[i][1].  We can cut these clips into segments freely: for example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].
 
 Return the minimum number of clips needed so that we can cut the clips into segments that cover the entire sporting event ([0, T]).  If the task is impossible, return -1.
 
 
 
 Example 1:
 
 Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
 Output: 3
 Explanation:
 We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
 Then, we can reconstruct the sporting event as follows:
 We cut [1,9] into segments [1,2] + [2,8] + [8,9].
 Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].
 Example 2:
 
 Input: clips = [[0,1],[1,2]], T = 5
 Output: -1
 Explanation:
 We can't cover [0,5] with only [0,1] and [0,2].
 Example 3:
 
 Input: clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], T = 9
 Output: 3
 Explanation:
 We can take clips [0,4], [4,7], and [6,9].
 Example 4:
 
 Input: clips = [[0,4],[2,8]], T = 5
 Output: 2
 Explanation:
 Notice you can have extra video after the event ends.
 
 
 Note:
 
 1 <= clips.length <= 100
 0 <= clips[i][0], clips[i][1] <= 100
 0 <= T <= 100
 */

class Solution {
public:
    /**
     * Greedy algorithm
     * sort the clips based on the right end point, in descending order.
     * Every turn, pop clips out of the array, and pick the clip that covers current ending point
     * but reaches farthest left.
     *
     */
    int videoStitching(vector<vector<int>>& clips, int T) {
        sort(clips.begin(), clips.end(),[](const vector<int>& a, const vector<int>& b){
            if (a[1] != b[1]) {
                return a[1] > b[1];
            } else {
                return a[0] < b[0];
            }
        });
        int n = clips.size();
        int res = 0;
        int cur = T;
        int i = 0;
        int next = cur;
        while (cur > 0 && i < n) {
            while (i < n && clips[i][1] >= cur) {
                if (clips[i][0] < next) {
                    next = clips[i][0];
                }
                ++i;
            }
            if (next == cur) {
                return -1;
            } else {
                cur = next;
                ++res;
            }
        }
        
        if (cur == 0) {
            return res;
        } else {
            return -1;
        }
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> clips;
        int T;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{0,2},{4,6},{8,10},{1,9},{1,5},{5,9}},10},
        {{{0,1},{1,2}},5},
        {{{0,1},{6,8},{0,2},{5,6},{0,4},{0,3},{6,7},{1,3},{4,7},{1,4},{2,5},{2,6},{3,4},{4,5},{5,7},{6,9}},9},
        {{{0,4},{2,8}},5}
    };

    vector< int > answers {
        3,
        -1,
        3,
        2
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = videoStitching::Solution().videoStitching(dp.clips, dp.T);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
