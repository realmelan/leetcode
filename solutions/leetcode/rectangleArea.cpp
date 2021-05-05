// rectangleArea.cpp
// leetcode
//
// Created by  Song Ding on 10/14/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace rectangleArea {

class Solution {
public:
    /**
     * For each x point, calculate the height of intervals formed by
     * the vertical edges of the rectangles.
     *
     * Scanning from the 1st x position(x1), get the length of the vertical
     * intervals, the horizontal length is x2 - x1. Now area formed by the verticals
     * at x1 position till x2 is obtained. Do this for all other x positions.
     */
    int rectangleArea(vector<vector<int>>& rectangles) {
        map<int,int> verticals;
        multimap<int, pair<int,int>> edges;
        // add all right vertical edges
        for (const auto& v : rectangles) {
            edges.insert(make_pair(v[2], make_pair(-v[1], -v[3])));
        }
        for (const auto& v : rectangles) {
            edges.insert(make_pair(v[0], make_pair(v[1], v[3])));
        }
        
        // maintain verticals
        long area = 0;
        int x = 0;
        long y = 0;
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            area += y * (it->first - x);
            y = updateVertical(verticals, it->second);
            x = it->first;
        }
        return area % 1000000007;
    }

private:
    long updateVertical(map<int,int>& verticals, const std::pair<int,int>& edge) {
        if (edge.first < 0 || edge.second < 0) {
            // remove right edge
            // Note: it is fully covered by one edge in verticals
            int y3 = -edge.first;
            int y4 = -edge.second;
            --verticals[y3];
            ++verticals[y4];
        } else {
            int y3 = edge.first;
            int y4 = edge.second;
            ++verticals[y3];
            --verticals[y4];
        }
        
        int cnt = 0;
        long res = 0;
        int last = 0;
        for (auto it = verticals.begin(); it != verticals.end(); ++it) {
            if (cnt > 0 && (cnt += it->second) == 0) {
                res += it->first - last;
            } else if (cnt == 0 && (cnt += it->second) > 0) {
                last = it->first;
            }
        }
        return res;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> rectangles {
        //{0,0,2,2},{1,0,2,3},{1,0,3,1}
        //{0,0,1000000000,1000000000}
        //{0,0,1,1},{2,2,3,3}
        //{0,0,2,2},{1,0,2,3},{1,0,3,1}
        {25,20,70,27},{68,80,79,100},{37,41,66,76}
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = rectangleArea::Solution().rectangleArea(rectangles);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
