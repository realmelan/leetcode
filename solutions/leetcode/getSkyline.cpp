// getSkyline.cpp
// leetcode
//
// Created by  Song Ding on 3/21/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

/**
 218. The Skyline Problem
 Hard

 1511

 78

 Favorite

 Share
 A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings collectively (Figure B).

 Buildings Skyline Contour
 The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

 For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

 The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height. Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

 For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

 Notes:

 The number of buildings in any input list is guaranteed to be in the range [0, 10000].
 The input list is already sorted in ascending order by the left x position Li.
 The output list must be sorted by the x position.
 There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
 */
namespace getSkyline {

class Solution {
public:
    /**
     Use a multimap to record all height changes:
     positive heights for starting edge, negative heights for ending edge.
     
     meanwhile, use a multiset to recording all heights currently active.
     if a negative height is encountered, remove one from multiset.
     
     recording the all points where maximal active height changes.
     */
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        map<int, multiset<int>> edges;
        for (const auto& b : buildings) {
            edges[b[0]].insert(b[2]);
            edges[b[1]].insert(-b[2]);
        }
        
        map<int,int> activeHeights;
        vector<pair<int, int>> res;
        int activeh = 0;
        for (const auto& e : edges) {
            for (auto h : e.second) {
                if (h > 0) {
                    ++activeHeights[h];
                } else {
                    if (--activeHeights[-h] == 0) {
                        activeHeights.erase(-h);
                    }
                }
            }
            
            int newh = 0;
            if (activeHeights.size()) {
                newh = activeHeights.rbegin()->first;
            }
            
            if (newh != activeh) {
                res.push_back(make_pair(e.first, newh));
                activeh = newh;
            }
        }
        return res;
    }
private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> buildings {
        {2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}
        //{0,2,3},{2,5,3}
    };
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto r = getSkyline::Solution().getSkyline(buildings);
    cout << clock() - start << endl;
    cout << r << endl;
    return 0;
}
//*/
