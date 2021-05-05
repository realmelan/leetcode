//
//  solveSudoku.cpp
//  leetcode
//
//  Created by Song Ding on 7/23/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace solveSudoku {
/*
// TODO: copy problem statement here
 37. Sudoku Solver
 Hard

 1838

 91

 Add to List

 Share
 Write a program to solve a Sudoku puzzle by filling the empty cells.

 A sudoku solution must satisfy all of the following rules:

 Each of the digits 1-9 must occur exactly once in each row.
 Each of the digits 1-9 must occur exactly once in each column.
 Each of the the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
 Empty cells are indicated by the character '.'.


 A sudoku puzzle...


 ...and its solution numbers marked in red.

 Note:

 The given board contain only digits 1-9 and the character '.'.
 You may assume that the given Sudoku puzzle will have a single unique solution.
 The given board size is always 9x9.
*/
class Solution {
public:
    // TODO: copy function signature here
    void solveSudoku(vector<vector<char>>& board) {
        int mask = (1<<10) - 1;
        vector<int> rcand(9, mask), ccand(9, mask);
        vector<vector<int>> gcand(3, vector<int>(3, mask));
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.') {
                    rcand[i] ^= 1<<(board[i][j]-'0');
                    ccand[j] ^= 1<<(board[i][j]-'0');
                    gcand[i/3][j/3] ^= 1<<(board[i][j]-'0');
                }
            }
        }
        dfs(board, 0, 0, rcand, ccand, gcand);
    }
private:
    bool dfs(vector<vector<char>>& b, int x, int y, vector<int>& rcand, vector<int>& ccand, vector<vector<int>>& gcand) {
        while (x < 9 && b[x][y] != '.') {
            if (++y == 9) {
                ++x;
                y = 0;
            }
        }
        if (x == 9) {
            return true;
        }
        // find options for current location
        int cand = rcand[x] & ccand[y] & gcand[x/3][y/3];
        
        for (int i = 1; i <= 9; ++i) {
            if (cand & (1<<i)) {
                rcand[x] ^= 1 << i;
                ccand[y] ^= 1 << i;
                gcand[x/3][y/3] ^= 1 << i;
                b[x][y] = '0' + i;
                int nx = x, ny = y;
                if (++ny == 9) {
                    ++nx;
                    ny = 0;
                }
                if (dfs(b, nx, ny, rcand, ccand, gcand)) {
                    return true;
                }
                rcand[x] ^= 1 << i;
                ccand[y] ^= 1 << i;
                gcand[x/3][y/3] ^= 1 << i;
                b[x][y] = '.';
            }
        }
        return false;
    }
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<char>> board;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}}},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        solveSudoku::Solution().solveSudoku(dp.board);
        cout << dp.board << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
