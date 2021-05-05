// numMovesStonesII.cpp
// leetcode
//
// Created by  Song Ding on 5/6/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numMovesStonesII {
/*
 1040. Moving Stones Until Consecutive II
 
 On an infinite number line, the position of the i-th stone is given by stones[i].  Call a stone an endpoint stone if it has the smallest or largest position.
 
 Each turn, you pick up an endpoint stone and move it to an unoccupied position so that it is no longer an endpoint stone.
 
 In particular, if the stones are at say, stones = [1,2,5], you cannot move the endpoint stone at position 5, since moving it to any position (such as 0, or 3) will still keep that stone as an endpoint stone.
 
 The game ends when you cannot make any more moves, ie. the stones are in consecutive positions.
 
 When the game ends, what is the minimum and maximum number of moves that you could have made?  Return the answer as an length 2 array: answer = [minimum_moves, maximum_moves]
 
 
 
 Example 1:
 
 Input: [7,4,9]
 Output: [1,2]
 Explanation:
 We can move 4 -> 8 for one move to finish the game.
 Or, we can move 9 -> 5, 4 -> 6 for two moves to finish the game.
 Example 2:
 
 Input: [6,5,4,3,10]
 Output: [2,3]
 We can move 3 -> 8 then 10 -> 7 to finish the game.
 Or, we can move 3 -> 7, 4 -> 8, 5 -> 9 to finish the game.
 Notice we cannot move 10 -> 2 to finish the game, because that would be an illegal move.
 Example 3:
 
 Input: [100,101,104,102,103]
 Output: [0,0]
 
 
 Note:
 
 3 <= stones.length <= 10^4
 1 <= stones[i] <= 10^9
 stones[i] have distinct values.
 */

class Solution {
public:
    /**
     * sort stones in increasing order, and get the gaps between
     * consecutive stones.
     *
     * To get max moves, pick the endpoint stone that has the smaller
     * gap to its neighbor, and move it to the neighbor position + 1.
     * Next, move the endpoint stone to remove just one gap.
     * Do this until all stones are consecutive.
     *
     * To get min moves, select a starting point and ending point such that
     * the interval between the two points can hold all stones.
     *   1, if both points are occupied, #move = # of empty slots
     *   2, if only 1 end point is occupied, #move = # of empty slots + 1
     * find a starting point which would give the smallest #move
     */
    vector<int> numMovesStonesII(vector<int>& stones) {
        int n = stones.size();
        sort(stones.begin(), stones.end());
        
        int res_min = INT_MAX;
        int j = 0;
        for (int i = 0; i < n && i <= res_min; ++i) {
            int start = stones[i];
            int end = start + n - 1;
            while (j < n && stones[j] < end) {
                ++j;
            }
            
            int r = 0;
            if (j == n) {
                r = i + 1;
            } else if (stones[j] == end) {
                r = n - (j - i + 1);
            } else if (j - i == n - 1) {
                r = 2;
            } else {
                r = n - (j - i);
            }
            res_min = min(res_min, r);
        }
        
        int res_max = 0;
        for (int i = 1; i < n; ++i) {
            res_max += stones[i] - stones[i-1] - 1;
        }
        int first_gap = stones[1] - stones[0] - 1;
        int last_gap = stones[n-1] - stones[n-2] - 1;
        res_max -= min(first_gap, last_gap);
        return {res_min, res_max};
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<int> > stones {
        {7,4,9},
        {6,5,4,3,10},
        {100,101,104,102,103},
        {1,500000000,1000000000}
        
    };

    vector<  vector<int> > answers {
        {1,2},
        {2,3},
        {0,0},
        {2,499999999}
    };
    int i = 3;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = numMovesStonesII::Solution().numMovesStonesII(stones[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
