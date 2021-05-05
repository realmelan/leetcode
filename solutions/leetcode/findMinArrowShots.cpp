//
//  findMinArrowShots.cpp
//  leetcode
//
//  Created by  Song Ding on 10/12/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include <vector>
#include <list>
#include <utility>
#include <iostream>

using namespace std;

/**
 452. Minimum Number of Arrows to Burst Balloons
 Medium

 604

 29

 Favorite

 Share
 There are a number of spherical balloons spread in two-dimensional space. For each balloon, provided input is the start and end coordinates of the horizontal diameter. Since it's horizontal, y-coordinates don't matter and hence the x-coordinates of start and end of the diameter suffice. Start is always smaller than end. There will be at most 104 balloons.

 An arrow can be shot up exactly vertically from different points along the x-axis. A balloon with xstart and xend bursts by an arrow shot at x if xstart ≤ x ≤ xend. There is no limit to the number of arrows that can be shot. An arrow once shot keeps travelling up infinitely. The problem is to find the minimum number of arrows that must be shot to burst all balloons.

 Example:

 Input:
 [[10,16], [2,8], [1,6], [7,12]]

 Output:
 2

 Explanation:
 One way is to shoot one arrow for example at x = 6 (bursting the balloons [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two balloons).
 */

namespace findMinArrowShots {
    class Solution {
    public:
        /**
         * sort the balloons based on the ending point in ascending order, and starting point in descending order.
         * and record the last arrow point, and current balloon starting beyond last arrow point, increase result and update
         * last arrow point to the ending point of current balloons.
         */
        int findMinArrowShots2(vector<vector<int>>& points) {
            int n = points.size();
            if (n <= 0) {
                return 0;
            }
            sort(points.begin(), points.end(), [](const vector<int>&a, const vector<int>& b){
                return a[1] != b[1] ? a[1] < b[1] : a[0] > b[0];
            });
            int res = 1;
            int last = points[0][1];
            for (int i = 1; i < n; ++i) {
                if (points[i][0] > last) {
                    ++res;
                    last = points[i][1];
                }
            }
            return res;
        }
        /**
         Looks like a greedy algorithm.
         Order the balloons in ascending order of the end point.
         then iteratively shoot the end point in order.
         When an arrow is shot, remove balloons that are bursted.
         
         However, cost would be O(n^2);
         */
        int findMinArrowShots(vector<pair<int, int>>& points) {
            sort(points.begin(), points.end(), orderByEnd);
            list<pair<int, int>> balloons(points.begin(), points.end());
            
            int res = 0;
            while (balloons.size()) {
                auto head = balloons.front();
                balloons.pop_front();
                res++;
                
                int endp = head.second;
                auto it = balloons.begin();
                while (it != balloons.end()) {
                    if (endp >= it->first && endp <= it->second) {
                        it = balloons.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
            return res;
        }
    private:
        static bool orderByEnd(const pair<int, int>& p1, const pair<int, int>& p2) {
            return p1.second < p2.second;
        }
    };
}
