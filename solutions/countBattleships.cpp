// countBattleships.cpp
// leetcode
//
// Created by  Song Ding on 10/29/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace countBattleships {
/*
// TODO: copy problem statement here
 419. Battleships in a Board
 Medium

 493

 375

 Favorite

 Share
 Given an 2D board, count how many battleships are in it. The battleships are represented with 'X's, empty slots are represented with '.'s. You may assume the following rules:
 You receive a valid board, made of only battleships or empty slots.
 Battleships can only be placed horizontally or vertically. In other words, they can only be made of the shape 1xN (1 row, N columns) or Nx1 (N rows, 1 column), where N can be of any size.
 At least one horizontal or vertical cell separates between two battleships - there are no adjacent battleships.
 Example:
 X..X
 ...X
 ...X
 In the above board there are 2 battleships.
 Invalid Example:
 ...X
 XXXX
 ...X
 This is an invalid board that you will not receive - as battleships will always have a cell separating between them.
 Follow up:
 Could you do it in one-pass, using only O(1) extra memory and without modifying the value of the board?
 */

class Solution {
public:
    /**
     * for each 'X':
     *  1, check whether there is a 'X' on the left or at the top, if so, ignore it
     *  2, add 1 to final.
     */
    int countBattleships(vector<vector<char>>& board) {
        int n = board.size(), m = board[0].size();
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (board[i][j] == 'X') {
                    if ((i == 0 || board[i-1][j] == '.')
                        && (j == 0 || board[i][j-1] == '.')) {
                        ++res;
                    }
                }
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
        vector<vector<char>> board;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{
            {'X','.','.','X'},
            {'.','.','.','X'},
            {'.','.','.','X'},
        }},
        {{
            {'.','.','.','X'},
            {'X','X','X','X'},
            {'.','.','.','X'},
        }},
    };

    vector< int > answers {
        2,
        -1,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = countBattleships::Solution().countBattleships(dp.board);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
