// validTicTacToe.cpp
// leetcode
//
// Created by  Song Ding on 5/13/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace validTicTacToe {

class Solution {
public:
    /**
     * valid state satisfies:
     *  1, # of X = # of O or # of X = 1 + # of O
     *  2, there is only 1 winner (either X or O)
     *  3, if X wins, # of X = 1 + # of O
     */
    bool validTicTacToe(vector<string>& board) {
        map<char, int> counts;
        counts['X'] = 0;
        counts[' '] = 0;
        counts['O'] = 0;
        
        for (const auto& s : board) {
            for (auto c : s) {
                ++counts[c];
            }
        }
        int xwin = isWinner(board, 'X');
        int owin = isWinner(board, 'O');
        if (xwin + owin > 1) {
            return false;
        }
        
        if (xwin) {
            return counts['X'] == counts['O'] + 1;
        } else if (owin) {
            return counts['X'] == counts['O'];
        } else {
            return (counts['X'] == counts['O']) || (counts['X'] == counts['O'] + 1);
        }
    }

private:
    int isWinner(vector<string>& board, char c) {
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == c && board[i][1] == c && board[i][2] == c) {
                return 1;
            }
            if (board[0][i] == c && board[1][i] == c && board[2][i] == c) {
                return 1;
            }
        }
        if ((board[0][0] == c && board[1][1] == c && board[2][2] == c)
            || (board[0][2] == c && board[1][1] == c && board[2][0] == c)) {
            return 1;
        }
        return 0;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<string> board{
        //"O  ", "   ", "   " // => false
        //"XOX", " X ", "   " // => false
        //"XXX", "   ", "OOO" // => false
        //"XOX", "O O", "XOX" // => true
        //"XXX","XOO","OO " // => false
        //"XXX", "OOX", "OOX" // => true;
        "OXX","XOX","OXO" // => false
    };
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = validTicTacToe::Solution().validTicTacToe(board);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
