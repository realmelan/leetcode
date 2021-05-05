// fallingSquares.cpp
// leetcode
//
// Created by  Song Ding on 9/26/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace fallingSquares {
/*
// TODO: copy problem statement here
 699. Falling Squares
 Hard

 185

 35

 Favorite

 Share
 On an infinite number line (x-axis), we drop given squares in the order they are given.

 The i-th square dropped (positions[i] = (left, side_length)) is a square with the left-most point being positions[i][0] and sidelength positions[i][1].

 The square is dropped with the bottom edge parallel to the number line, and from a higher height than all currently landed squares. We wait for each square to stick before dropping the next.

 The squares are infinitely sticky on their bottom edge, and will remain fixed to any positive length surface they touch (either the number line or another square). Squares dropped adjacent to each other will not stick together prematurely.

  
 Return a list ans of heights. Each height ans[i] represents the current highest height of any square we have dropped, after dropping squares represented by positions[0], positions[1], ..., positions[i].

 Example 1:

 Input: [[1, 2], [2, 3], [6, 1]]
 Output: [2, 5, 5]
 Explanation:
 After the first drop of positions[0] = [1, 2]: _aa _aa ------- The maximum height of any square is 2.

 After the second drop of positions[1] = [2, 3]: __aaa __aaa __aaa _aa__ _aa__ -------------- The maximum height of any square is 5. The larger square stays on top of the smaller square despite where its center of gravity is, because squares are infinitely sticky on their bottom edge.

 After the third drop of positions[1] = [6, 1]: __aaa __aaa __aaa _aa _aa___a -------------- The maximum height of any square is still 5. Thus, we return an answer of [2, 5, 5].

  

  
 Example 2:

 Input: [[100, 100], [200, 100]]
 Output: [100, 100]
 Explanation: Adjacent squares don't get stuck prematurely - only their bottom edge can stick to surfaces.
  

 Note:

 1 <= positions.length <= 1000.
 1 <= positions[i][0] <= 10^8.
 1 <= positions[i][1] <= 10^6.
 */

class Solution {
public:
    // skyline, keep a list of [left x, height] for points starting at 0
    // use lower_bound, upper_bound, and map.erase(firstIt, lastId) to update
    // heights map
    vector<int> fallingSquares2(vector<vector<int>>& positions) {
        vector<int> res;
        map<int, int> heights;
        int mh = 0;
        heights[0] = 0;
        heights[INT_MAX] = 0;
        for (auto& p : positions) {
            int x = p[0], y = p[1];
            auto lit = heights.upper_bound(x);
            auto rit = heights.lower_bound(x+y);
            // find height for p
            int ch = 0, lasth = 0;
            for (auto it = --lit; it != rit; ++it) {
                ch = max(ch, it->second);
                lasth = it->second;
            }
            ch += y;
            heights.erase(++lit, rit);
            heights[x] = ch;
            if (!heights.count(x+y)) {
                heights[x+y] = lasth;
            }
            mh = max(mh, ch);
            res.push_back(mh);
        }
        return res;
    }
    /**
     * use a map to record all height changing points, using negative value to indicate a ending
     * of height.
     * so a positive height h1 at x1, means starting from x1 right ward, the height is h1, till
     * next right point, which changes height, might be zero.
     * As lee215 said, it is similar to skyline problem.
     */
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size();
        vector<int> res;
        map<int, int> hs;
        int highest = 0;
        for (const auto& sq : positions) {
            int sqx = sq[0];
            int sqh = sq[1];
            
            // find a point that is just before sqx or at sqx
            // which will determins the starting height of sqx
            // and find the largest height till sqx+sqh(exclusive)
            auto fit = hs.lower_bound(sqx);
            if (fit == hs.end()) {
                // it is the right most square
                hs[sqx] = sqh;
                hs[sqx+sqh] = 0;
                highest = max(highest, sqh);
                res.push_back(highest);
                continue;
            }
            // move start position earlier
            auto it = fit;
            int nh = 0;
            if (fit->first != sqx && fit != hs.begin()) {
                --fit;
                nh = fit->second;
            }
            int lasth = nh;
            while (it != hs.end() && it->first < sqx + sqh) {
                nh = max(nh, it->second);
                lasth = it->second;
                it = hs.erase(it);
            }
            nh += sqh;
            
            
            if (it == hs.end() || it->first > sqx+sqh) {
                hs[sqx+sqh] = lasth;
            }
            hs[sqx] = nh;
            
            highest = max(highest, nh);
            res.push_back(highest);
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
        vector<vector<int>> positions;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{1, 2}, {2, 3}, {6, 1}}},
        {{{100, 100}, {200, 100}}},
    };

    vector< vector<int> > answers {
        {2, 5, 5},
        {100,100},
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = fallingSquares::Solution().fallingSquares2(dp.positions);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
