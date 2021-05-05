//
//  canMouseWin.cpp
//  leetcode
//
//  Created by Song Ding on 1/21/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace canMouseWin {
/*
// TODO: copy problem statement here
 1728. Cat and Mouse II My SubmissionsBack to Contest
 User Accepted: 45
 User Tried: 250
 Total Accepted: 49
 Total Submissions: 698
 Difficulty: Hard
 A game is played by a cat and a mouse named Cat and Mouse.

 The environment is represented by a grid of size rows x cols, where each element is a wall, floor, player (Cat, Mouse), or food.

 Players are represented by the characters 'C'(Cat),'M'(Mouse).
 Floors are represented by the character '.' and can be walked on.
 Walls are represented by the character '#' and cannot be walked on.
 Food is represented by the character 'F' and can be walked on.
 There is only one of each character 'C', 'M', and 'F' in grid.
 Mouse and Cat play according to the following rules:

 Mouse moves first, then they take turns to move.
 During each turn, Cat and Mouse can jump in one of the four directions (left, right, up, down). They cannot jump over the wall nor outside of the grid.
 catJump, mouseJump are the maximum lengths Cat and Mouse can jump at a time, respectively. Cat and Mouse can jump less than the maximum length.
 Staying in the same position is allowed.
 Mouse can jump over Cat.
 The game can end in 4 ways:

 If Cat occupies the same position as Mouse, Cat wins.
 If Cat reaches the food first, Cat wins.
 If Mouse reaches the food first, Mouse wins.
 If Mouse cannot get to the food within 1000 turns, Cat wins.
 Given a rows x cols matrix grid and two integers catJump and mouseJump, return true if Mouse can win the game if both Cat and Mouse play optimally, otherwise return false.

  

 Example 1:



 Input: grid = ["####F","#C...","M...."], catJump = 1, mouseJump = 2
 Output: true
 Explanation: Cat cannot catch Mouse on its turn nor can it get the food before Mouse.
 Example 2:



 Input: grid = ["M.C...F"], catJump = 1, mouseJump = 4
 Output: true
 Example 3:

 Input: grid = ["M.C...F"], catJump = 1, mouseJump = 3
 Output: false
 Example 4:

 Input: grid = ["C...#","...#F","....#","M...."], catJump = 2, mouseJump = 5
 Output: false
 Example 5:

 Input: grid = [".M...","..#..","#..#.","C#.#.","...#F"], catJump = 3, mouseJump = 1
 Output: true
  

 Constraints:

 rows == grid.length
 cols = grid[i].length
 1 <= rows, cols <= 8
 grid[i][j] consist only of characters 'C', 'M', 'F', '.', and '#'.
 There is only one of each character 'C', 'M', and 'F' in grid.
 1 <= catJump, mouseJump <= 8
*/
class Solution {
public:
    // TODO: copy function signature here
    bool canMouseWin(vector<string>& grid, int catJump, int mouseJump) {
        static const vector<int> dirs{1,0,-1,0,1};
        int m = grid.size(), n = grid[0].size();
        vector<int> food, cat, mouse;
        vector<vector<int>> cells;
        queue<vector<int>> q;
        constexpr int MOUSE_TURN = 0, CAT_TURN = 1, MOUSE_WIN = 1, CAT_WIN = 2;
        // turn => 0(mouse turn),1(cat turn)
        // mouse x, mouse y, cat x, cat y
        // value => whose will win, 1=>mouse win, 2=>cat win, 0 => not determined
        vector<vector<vector<vector<vector<int>>>>> states(2, vector<vector<vector<vector<int>>>>(m, vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(n,0)))));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'F') {
                    food = {i,j};
                } else if (grid[i][j] == 'C') {
                    cat = {i,j};
                } else if (grid[i][j] == 'M') {
                    mouse = {i,j};
                }
                if (grid[i][j] != '#' && grid[i][j] != 'F') {
                    cells.push_back({i,j});
                }
            }
        }
        
        vector<vector<vector<vector<int>>>> catOptions(m, vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(n, 0))));
        vector<vector<vector<vector<int>>>> mouseOptions(m, vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(n, 0))));
        for (auto& v : cells) {
            int x = v[0], y = v[1];
            states[MOUSE_TURN][food[0]][food[1]][x][y] = states[CAT_TURN][food[0]][food[1]][x][y] = MOUSE_WIN;
            states[MOUSE_TURN][x][y][food[0]][food[1]] = states[CAT_TURN][x][y][food[0]][food[1]] = CAT_WIN;
            states[MOUSE_TURN][x][y][x][y] = states[CAT_TURN][x][y][x][y] = CAT_WIN;
            q.push({MOUSE_TURN,food[0],food[1],x,y});
            q.push({CAT_TURN,food[0],food[1],x,y});
            q.push({MOUSE_TURN,x,y,food[0],food[1]});
            q.push({CAT_TURN,x,y,food[0],food[1]});
            q.push({MOUSE_TURN,x,y,x,y});
            q.push({CAT_TURN,x,y,x,y});
            
            int catOpt = 1, mouseOpt = 1;
            for (int i = 0; i < 4; ++i) {
                for (int j = 1; j <= catJump; ++j) {
                    int x = v[0]+dirs[i]*j, y = v[1]+dirs[i+1]*j;
                    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y]=='#') {
                        break;
                    }
                    ++catOpt;
                }
            }
            for (int i = 0; i < 4; ++i) {
                for (int j = 1; j <= mouseJump; ++j) {
                    int x = v[0]+dirs[i]*j, y = v[1]+dirs[i+1]*j;
                    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y]=='#') {
                        break;
                    }
                    ++mouseOpt;
                }
            }
            for (auto& v2 : cells) {
                catOptions[v2[0]][v2[1]][x][y] = catOpt;
                mouseOptions[x][y][v2[0]][v2[1]] = mouseOpt;
            }
        }
        while (q.size()) {
            auto v = q.front();
            q.pop();
            int WHO_WIN = states[v[0]][v[1]][v[2]][v[3]][v[4]];
            if (v[0] == MOUSE_TURN) { // now cat's turn
                if (WHO_WIN == CAT_WIN) {
                    int x = v[3], y = v[4];
                    if (!states[CAT_TURN][v[1]][v[2]][x][y]) {
                        states[CAT_TURN][v[1]][v[2]][x][y] = CAT_WIN;
                        q.push({CAT_TURN, v[1], v[2], x, y});
                    }
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 1; j <= catJump; ++j) {
                            int x = v[3]+dirs[i]*j, y = v[4]+dirs[i+1]*j;
                            if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y]=='#') {
                                break;
                            }
                            if (!states[CAT_TURN][v[1]][v[2]][x][y]) {
                                states[CAT_TURN][v[1]][v[2]][x][y] = CAT_WIN;
                                q.push({CAT_TURN, v[1], v[2], x, y});
                            }
                        }
                    }
                } else { // mouse wins, check whether a position is surrounded by mouse_win positions
                    int x = v[3], y = v[4];
                    if (!states[CAT_TURN][v[1]][v[2]][x][y]) {
                        if (--catOptions[v[1]][v[2]][x][y] == 0) {
                            states[CAT_TURN][v[1]][v[2]][x][y] = MOUSE_WIN;
                            q.push({CAT_TURN, v[1], v[2], x, y});
                        }
                    }
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 1; j <= catJump; ++j) {
                            int x = v[3]+dirs[i]*j, y = v[4]+dirs[i+1]*j;
                            if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y]=='#') {
                                break;
                            }
                            
                                if (--catOptions[v[1]][v[2]][x][y] == 0) {
                                    states[CAT_TURN][v[1]][v[2]][x][y] = MOUSE_WIN;
                                    q.push({CAT_TURN, v[1], v[2], x, y});
                                }
                        }
                    }
                }
                
            } else { // now mouse's turn
                if (WHO_WIN == MOUSE_WIN) {
                    int x = v[1], y = v[2];
                    if (!states[MOUSE_TURN][x][y][v[3]][v[4]]) {
                        states[MOUSE_TURN][x][y][v[3]][v[4]] = MOUSE_WIN;
                        q.push({MOUSE_TURN, x, y, v[3], v[4]});
                    }
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 1; j <= mouseJump; ++j) {
                            int x = v[1]+dirs[i]*j, y = v[2]+dirs[i+1]*j;
                            if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y]=='#') {
                                break;
                            }
                            if (!states[MOUSE_TURN][x][y][v[3]][v[4]]) {
                                states[MOUSE_TURN][x][y][v[3]][v[4]] = MOUSE_WIN;
                                q.push({MOUSE_TURN, x, y, v[3], v[4]});
                            }
                        }
                    }
                } else { // cat wins v, check whether a position is surrounded by cat_win positions
                    int x = v[1], y = v[2];
                    if (!states[MOUSE_TURN][x][y][v[3]][v[4]]) {
                        if (--mouseOptions[x][y][v[3]][v[4]] == 0) {
                            states[MOUSE_TURN][x][y][v[3]][v[4]] = CAT_WIN;
                            q.push({MOUSE_TURN, x, y, v[3], v[4]});
                        }
                    }
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 1; j <= mouseJump; ++j) {
                            int x = v[1]+dirs[i]*j, y = v[2]+dirs[i+1]*j;
                            if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y]=='#') {
                                break;
                            }
                            if (!states[MOUSE_TURN][x][y][v[3]][v[4]]) {
                                if (--mouseOptions[x][y][v[3]][v[4]] == 0) {
                                    states[MOUSE_TURN][x][y][v[3]][v[4]] = CAT_WIN;
                                    q.push({MOUSE_TURN, x, y, v[3], v[4]});
                                }
                            }
                        }
                    }
                }
                
            }
        }
        
        
        return states[MOUSE_TURN][mouse[0]][mouse[1]][cat[0]][cat[1]] == MOUSE_WIN;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<string> grid;
        int catJump;
        int mouseJump;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        //{{"####F","#C...","M...."},1,2},
        //{{"M.C...F"},1,4},
        //{{"M.C...F"},1,3},
        //{{"C...#","...#F","....#","M...."},2,3},
        //{{".M...","..#..","#..#.","C#.#.","...#F"},3,1},
        {{"CM..","###.","###F"},1,1},
        {{"CM..","###.","....","F###"},1,1},
        {{"CM......","#######.","........",".#######","........","#######.","........","F#######"},1,1},
    };
    // TODO: provide expected results here
    vector<bool> answers {
        true,
        true,
        false,
        false,
        true,
        true,
        true,
        true,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = canMouseWin::Solution().canMouseWin(dp.grid, dp.catJump, dp.mouseJump);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
