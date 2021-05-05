// shortestDistance.cpp
// leetcode
//
// Created by  Song Ding on 10/23/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace shortestDistance {
/*
// TODO: copy problem statement here
 505. The Maze II

 There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won\'t stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

 Given the ball\'s start position, the destination and the maze, find the shortest distance for the ball to stop at the destination. The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included). If the ball cannot stop at the destination, return -1.

 The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.

 Example 1

 Input 1: a maze represented by a 2D array

 0 0 1 0 0
 0 0 0 0 0
 0 0 0 1 0
 1 1 0 1 1
 0 0 0 0 0

 Input 2: start coordinate (rowStart, colStart) = (0, 4)
 Input 3: destination coordinate (rowDest, colDest) = (4, 4)

 Output: 12
 Explanation: One shortest way is : left -> down -> left -> down -> right -> down -> right.
              The total distance is 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12.

 Example 2

 Input 1: a maze represented by a 2D array

 0 0 1 0 0
 0 0 0 0 0
 0 0 0 1 0
 1 1 0 1 1
 0 0 0 0 0

 Input 2: start coordinate (rowStart, colStart) = (0, 4)
 Input 3: destination coordinate (rowDest, colDest) = (3, 2)

 Output: -1
 Explanation: There is no way for the ball to stop at the destination.

 Note:

 There is only one ball and one destination in the maze.
 Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
 The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
 The maze contains at least 2 empty spaces, and both the width and height of the maze won\'t exceed 100.
 */

class Solution {
public:
    /**
     * BFS:
     * one step at a time? or directly to a wall?
     */
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int n = maze.size(), m = maze[0].size();
        vector<vector<vector<int>>> visited(n, vector<vector<int>>(m, vector<int>(4, false)));
        static const vector<vector<int>> dirs{{0,1},{1,0},{-1,0},{0,-1}};
        vector<vector<int>> st;
        for (int i = 0; i < dirs.size(); ++i) {
            vector<int> t(start);
            t.push_back(i);
            st.push_back(t);
            visited[start[0]][start[1]][i] = true;
        }
        int moves = 0;
        while (st.size()) {
            ++moves;
            vector<vector<int>> next;
            for (auto& pd : st) {
                int di = pd[2];
                int x = pd[0] + dirs[di][0];
                int y = pd[1] + dirs[di][1];
                if (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && !visited[x][y][di]) {
                    if (x == destination[0] && y == destination[1]) {
                        return moves;
                    }
                    
                    next.push_back({x,y,di});
                    visited[x][y][di] = true;
                } else {
                    // change direction
                    for (int i = 0; i < dirs.size(); ++i) {
                        if (i != di && i != 3 - di) {
                            int x = pd[0] + dirs[i][0];
                            int y = pd[1] + dirs[i][1];
                            if (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && !visited[x][y][i]) {
                                next.push_back({x,y,i});
                                visited[x][y][i] = true;
                            }
                        }
                    }
                }
                
            }
            st.swap(next);
        }
        return -1;
        
    }
    /**
     BFS: hit a wall and update distance if shorter
     */
    int shortestDistance2(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int n = maze.size(), m = maze[0].size();
        vector<vector<int>> dist(n, vector<int>(m,INT_MAX));
        dist[start[0]][start[1]] = 0;
        static const vector<vector<int>> dirs{{0,1},{0,-1},{1,0},{-1,0}};
        vector<vector<int>> cur{start};
        while (cur.size()) {
            vector<vector<int>> next;
            for (auto& p : cur) {
                int x = p[0];
                int y = p[1];
                for (auto& dir : dirs) {
                    int i = x;
                    int j = y;
                    int move = 0;
                    while (i+dir[0] >= 0 && i+dir[0] < n && j+dir[1] >= 0 && j+dir[1] < m
                           && maze[i+dir[0]][j+dir[1]] == 0) {
                        i += dir[0];
                        j += dir[1];
                        ++move;
                    }
                    if (dist[x][y] + move < dist[i][j]) {
                        dist[i][j] = dist[x][y] + move;
                        next.push_back({i,j});
                    }
                }
            }
            cur.swap(next);
        }
        if (dist[destination[0]][destination[1]] == INT_MAX) {
            return -1;
        }
        return dist[destination[0]][destination[1]];
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> maze;
        vector<int> start;
        vector<int> destination;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {
            {
                {0,0,1,0,0},
                {0,0,0,0,0},
                {0,0,0,1,0},
                {1,1,0,1,1},
                {0,0,0,0,0}
            },
            {0,4},{4,4}
        },
        {
            {
                {0,0,1,0,0},
                {0,0,0,0,0},
                {0,0,0,1,0},
                {1,1,0,1,1},
                {0,0,0,0,0}
            },
            {0,4},{3,2}
        }
    };

    vector< int > answers {
        12,
        -1
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = shortestDistance::Solution().shortestDistance(dp.maze, dp.start, dp.destination);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
