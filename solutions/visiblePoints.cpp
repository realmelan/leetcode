//
//  visiblePoints.cpp
//  leetcode
//
//  Created by Song Ding on 3/4/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace visiblePoints {
/*
// TODO: copy problem statement here
 1610. Maximum Number of Visible Points My SubmissionsBack to Contest
 User Accepted: 628
 User Tried: 1685
 Total Accepted: 638
 Total Submissions: 5124
 Difficulty: Hard
 You are given an array points, an integer angle, and your location, where location = [posx, posy] and points[i] = [xi, yi] both denote integral coordinates on the X-Y plane.

 Initially, you are facing directly east from your position. You cannot move from your position, but you can rotate. In other words, posx and posy cannot be changed. Your field of view in degrees is represented by angle, determining how wide you can see from any given view direction. Let d be the amount in degrees that you rotate counterclockwise. Then, your field of view is the inclusive range of angles [d - angle/2, d + angle/2].



 You can see some set of points if, for each point, the angle formed by the point, your position, and the immediate east direction from your position is in your field of view.

 There can be multiple points at one coordinate. There may be points at your location, and you can always see these points regardless of your rotation. Points do not obstruct your vision to other points.

 Return the maximum number of points you can see.

  

 Example 1:


 Input: points = [[2,1],[2,2],[3,3]], angle = 90, location = [1,1]
 Output: 3
 Explanation: The shaded region represents your field of view. All points can be made visible in your field of view, including [3,3] even though [2,2] is in front and in the same line of sight.
 Example 2:

 Input: points = [[2,1],[2,2],[3,4],[1,1]], angle = 90, location = [1,1]
 Output: 4
 Explanation: All points can be made visible in your field of view, including the one at your location.
 Example 3:


 Input: points = [[1,0],[2,1]], angle = 13, location = [1,1]
 Output: 1
 Explanation: You can only see one of the two points, as shown above.
  

 Constraints:

 1 <= points.length <= 105
 points[i].length == 2
 location.length == 2
 0 <= angle < 360
 0 <= posx, posy, xi, yi <= 100
*/
class Solution {
public:
    // TODO: copy function signature here
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        // sort points based on angles from 0 degree x axis
        int same = 0;
        vector<vector<int>> ps;
        for (auto& p : points) {
            p[0] -= location[0];
            p[1] -= location[1];
            if (p[0] == 0 && p[1] == 0) {
                ++same;
            } else {
                ps.push_back(p);
            }
        }
        sort(begin(ps), end(ps), [](const auto& a, const auto& b) {
            double phia = atan2(a[1],a[0]), phib = atan2(b[1], b[0]);
            if (phia < 0 && phib < 0) {
                return phia < phib;
            } else if (phia >= 0 && phib >= 0) {
                return phia < phib;
            } else {
                return phia >= 0 && phib < 0;
            }
        });
        // now starting from first point in qs, and move the second index angle counterclockwise
        int pn = ps.size(), res = 0;
        for (int i = 0; i < pn; ++i) {
            // use binary search to find the last points with the angle
            int l = i, r = i+pn;
            while (r-l>1) {
                int m = (l+r)/2;
                if (in_angle(ps[i], ps[m%pn], angle)) {
                    l = m;
                } else {
                    r = m;
                }
            }
            res = max(res, l-i+1);
        }
        return res + same;
    }
    bool in_angle(const vector<int>& a, const vector<int>& b, int angle) {
        // return true if (0,0), a, and b forms an angle <= angle
        static const double pi = acos(-1);
        double phia =  atan2(a[1], a[0]), phib = atan2(b[1],b[0]);
        if (phia < 0) {
            phia += pi*2;
        }
        if (phib < 0) {
            phib += pi*2;
        }
        if (phib < phia) {
            phib += pi*2;
        }
        return phib - phia <= angle*pi/180;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> points;
        int angle;
        vector<int> location;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        //{{{2,1},{2,2},{3,3}}, 90, {1,1}},
        //{{{2,1},{2,2},{3,4},{1,1}}, 90, {1,1}},
        //{{{1,0},{2,1}}, 13, {1,1}},
        {{{41,7},{22,94},{90,53},{94,54},{58,50},{51,96},{87,88},{55,98},{65,62},{36,47},{91,61},{15,41},{31,94},{82,80},{42,73},{79,6},{45,4}},17,{6,84}},
    };
    // TODO: provide expected results here
    vector<int> answers {
        3,
        4,
        1,
        5,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = visiblePoints::Solution().visiblePoints(dp.points, dp.angle, dp.location);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
