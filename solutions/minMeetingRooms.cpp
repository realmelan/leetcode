//
//  minMeetingRooms.cpp
//  leetcode
//
//  Created by Song Ding on 2/28/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minMeetingRooms {
/*
// TODO: copy problem statement here
 253. Meeting Rooms II

 Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

 For example,
 Given [[0, 30],[5, 10],[15, 20]],
 return 2.
*/
class Solution {
public:
    // TODO: copy function signature here
    int minMeetingRooms(vector<vector<int>>& intervals) {
        map<int, int> count;
        for (auto& v : intervals) {
            ++count[v[0]];
            --count[v[1]];
        }
        int res = 0;
        int cur = 0;
        for (auto& p : count) {
            cur += p.second;
            res = max(res, cur);
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
        vector<vector<int>> intervals;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{{0, 30},{5, 10},{15, 20}}},
    };
    // TODO: provide expected results here
    vector<int> answers {
        2,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minMeetingRooms::Solution().minMeetingRooms(dp.intervals);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
