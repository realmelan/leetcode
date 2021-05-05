// isRectangleCover.cpp
// leetcode
//
// Created by  Song Ding on 3/23/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace isRectangleCover {

class Solution {
public:
    /**
     first of all, find out bottom left and up right coordinates.
     Starting from the left x coordinate, and check whether every
     cell is covered by only one rectangle.
     
     Rectangles are sorted according to their x coordinates, and then
     y coordinates.
     */
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        sort(rectangles.begin(), rectangles.end(), [](const vector<int>& a, const vector<int>& b){
            if (a[0] != b[0]) {
                return a[0] < b[0];
            } else if (a[1] != b[1]) {
                return a[1] < b[1];
            } else if (a[2] != b[2]) {
                return a[2] < b[2];
            } else {
                return a[3] < b[3];
            }
        });
        if (rectangles.size()) {
            const vector<int>& last = rectangles.back();
            int ymin = INT_MAX;
            int ymax = INT_MIN;
            int xmin = INT_MAX;
            int xmax = INT_MIN;
            // y axis based.
            for (const auto& r : rectangles) {
                if (r[1] < ymin) {
                    ymin = r[1];
                }
                if (r[3] > ymax) {
                    ymax = r[3];
                }
                if (r[0] < xmin) {
                    xmin = r[0];
                }
                if (r[2] > xmax) {
                    xmax = r[2];
                }
            }
            vector<int> reached(ymax - ymin, INT_MIN);
            for (const auto& r : rectangles) {
                int x1 = r[0];
                int y1 = r[1];
                int x2 = r[2];
                int y2 = r[3];
                
                for (int y = y1; y < y2; ++y) {
                    if (reached[y - ymin] == INT_MIN) {
                        if (x1 == xmin) {
                            reached[y - ymin] = x2;
                        } else {
                            return false;
                        }
                    } else {
                        if (reached[y - ymin] == x1) {
                            reached[y - ymin] = x2;
                        } else {
                            return false;
                        }
                    }
                } // end loop of y
            } // end loop of all rectangles
            
            for (int i = 0; i < ymax - ymin; ++i) {
                if (reached[i] != xmax) {
                    return false;
                }
            }
        }
        return true;
    }
private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> rectangles{
        {1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4}
    };
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = isRectangleCover::Solution().isRectangleCover(rectangles);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
