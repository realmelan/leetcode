// intervalIntersection.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace intervalIntersection {
/*
// TODO: copy problem statement here
 986. Interval List Intersections
 Medium
 
 225
 
 15
 
 Favorite
 
 Share
 Given two lists of closed intervals, each list of intervals is pairwise disjoint and in sorted order.
 
 Return the intersection of these two interval lists.
 
 (Formally, a closed interval [a, b] (with a <= b) denotes the set of real numbers x with a <= x <= b.  The intersection of two closed intervals is a set of real numbers that is either empty, or can be represented as a closed interval.  For example, the intersection of [1, 3] and [2, 4] is [2, 3].)
 
 
 
 Example 1:
 
 
 
 Input: A = [[0,2],[5,10],[13,23],[24,25]], B = [[1,5],[8,12],[15,24],[25,26]]
 Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
 Reminder: The inputs and the desired output are lists of Interval objects, and not arrays or lists.
 
 
 Note:
 
 0 <= A.length < 1000
 0 <= B.length < 1000
 0 <= A[i].start, A[i].end, B[i].start, B[i].end < 10^9
 NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature
 */

class Solution {
public:
    /**
     * For each interval in A and B, record +1 for the starting point, and -1 for closing point.
     * Then walk through the records(min to max), and add up values along the walk, and for any
     * point that has value of 2, and it is the starting point of an overlap, and ends at next point
     * which has value of 1.
     *
     * Note, if any point along the way has value of 0, then it is a single point overlap.
     */
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        map<int, int> mk;
        for (const auto& i : A) {
            mk[i[0]] += 1;
            mk[i[1]] -= 1;
        }
        for (const auto& i : B) {
            mk[i[0]] += 1;
            mk[i[1]] -= 1;
        }
        
        vector<vector<int>> res;
        int c = 0;
        int start = -1;
        for (auto it = mk.begin(); it != mk.end(); ++it) {
            c += it->second;
            if (c == 2) {
                start = it->first;
            } else if (start > 0) {
                res.push_back({start, it->first});
                start = -1;
            }
            if (it->second == 0) {
                res.push_back({it->first, it->first});
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
        vector<vector<int>> A;
        vector<vector<int>> B;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{0,2},{5,10},{13,23},{24,25}},{{1,5},{8,12},{15,24},{25,26}}},
        {{{3,10}},{{5,10}}}
    };

    vector< vector<vector<int>> > answers {
        {{1,2},{5,5},{8,10},{15,23},{24,24},{25,25}},
        {{5,10}}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = intervalIntersection::Solution().intervalIntersection(dp.A, dp.B);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
