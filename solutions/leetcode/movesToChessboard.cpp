//
//  movesToChessboard.cpp
//  leetcode
//
//  Created by  Song Ding on 3/1/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;
/**
 782. Transform to Chessboard
 Hard

 92

 100

 Favorite

 Share
 An N x N board contains only 0s and 1s. In each move, you can swap any 2 rows with each other, or any 2 columns with each other.

 What is the minimum number of moves to transform the board into a "chessboard" - a board where no 0s and no 1s are 4-directionally adjacent? If the task is impossible, return -1.

 Examples:
 Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
 Output: 2
 Explanation:
 One potential sequence of moves is shown below, from left to right:

 0110     1010     1010
 0110 --> 1010 --> 0101
 1001     0101     1010
 1001     0101     0101

 The first move swaps the first and second column.
 The second move swaps the second and third row.


 Input: board = [[0, 1], [1, 0]]
 Output: 0
 Explanation:
 Also note that the board with 0 in the top left corner,
 01
 10

 is also a valid chessboard.

 Input: board = [[1, 0], [1, 0]]
 Output: -1
 Explanation:
 No matter what sequence of moves you make, you cannot end with a valid chessboard.
 Note:

 board will have the same number of rows and columns, a number in the range [2, 30].
 board[i][j] will be only 0s or 1s.
 */

namespace movesToChessboard {
    class Solution {
    public:
        /**
         by lee215@leetcode
         Intuition:
         Two conditions to help solve this problem:

         In a valid chess board, there are 2 and only 2 kinds of rows and one is inverse to the other.
         For example if there is a row 01010011 in the board, any other row must be either 01010011 or 10101100.
         The same for columns
         A corollary is that, any rectangle inside the board with corners top left, top right, bottom left, bottom right must be 4 zeros or 2 ones 2 zeros or 4 zeros.

         Another important property is that every row and column has half ones. Assume the board is N * N:
         If N = 2*K, every row and every column has K ones and K zeros.
         If N = 2*K + 1, every row and every column has K ones and K + 1 zeros or K + 1 ones and K zeros.


         Explanation:
         Since the swap process does not break this property, for a given board to be valid, this property must hold.
         These two conditions are necessary and sufficient condition for a valid chessboard.

         Once we know it is a valid cheese board, we start to count swaps.
         Basic on the property above, when we arange the first row, we are actually moving all columns.

         I try to arrange one row into 01010 and 10101 and I count the number of swaps.

         In case of N even, I take the minimum swaps, because both are possible.
         In case of N odd, I take the even swaps. because one major cell would be at its correct place, and if we try
         to move all minor cells to major cells, the displacement value woul be odd; if we try to move major cells to
         correct place, one major cell doesn't have to move, so the displacement value is even.
         
         Because when we make a swap, we move 2 columns or 2 rows at the same time.
         final result should be divided by 2.
         */
        int movesToChessboard(vector<vector<int>>& b) {
            int n = b.size();
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (b[0][0]^b[i][0]^b[0][j]^b[i][j]) {
                        return -1;
                    }
                }
            }
            int rowSum = 0, colSum = 0;
            int rowDisplace = 0, colDisplace = 0;
            for (int i = 0; i < n; ++i) {
                rowSum += b[0][i];
                colSum += b[i][0];
                rowDisplace += ((b[i][0] == i%2) ? 1 : 0);
                colDisplace += ((b[0][i] == i%2) ? 1 : 0);
            }
            if (rowSum < n/2 || rowSum > (n+1)/2
                || colSum < n/2 || colSum > (n+1)/2) {
                return -1;
            }
            if (n%2) {
                if (rowDisplace%2) {
                    rowDisplace = n - rowDisplace;
                }
                if (colDisplace%2) {
                    colDisplace = n - colDisplace;
                }
            } else {
                rowDisplace = min(n - rowDisplace, rowDisplace);
                colDisplace = min(n - colDisplace, colDisplace);
            }
            return (rowDisplace + colDisplace) / 2;
        }
        /**
         as the moves makes the same change to all rows, or all columns, so initially
         there should be two kinds of rows, and two kinds of columns, and they should
         have the right # of 1's.
         */
        int movesToChessboard_complicated(vector<vector<int>>& board) {
            int n = board.size();
            int cnt1 = 0;
            int row1 = -1, row1cnt = 0;
            int row0 = -1, row0cnt = 0; // first row starting with 1 or 0
            for (int i = 0; i < n; ++i) {
                int rowBase = -1;
                if (board[i][0] == 0){
                    if (row0 == -1) {
                        row0 = i;
                    } else {
                        rowBase = row0;
                    }
                    ++row0cnt;
                } else {
                    if (row1 == -1) {
                        row1 = i;
                    } else {
                        rowBase = row1;
                    }
                    ++row1cnt;
                }
                for (int j = 0; rowBase != -1 && j < n; ++j) {
                    if (board[i][j] != board[rowBase][j]) {
                        return -1;
                    }
                }
                for (int j = 0; j < n; ++j) {
                    cnt1 += board[i][j];
                }
            }
            
            int col1 = -1, col1cnt = 0;
            int col0 = -1, col0cnt = 0; // first column starting with 1 or 0
            
            // same thing for column
            for (int i = 0; i < n; ++i) {
                int colBase = -1;
                if (board[0][i] == 0){
                    if (col0 == -1) {
                        col0 = i;
                    } else {
                        colBase = col0;
                    }
                    ++col0cnt;
                } else {
                    if (col1 == -1) {
                        col1 = i;
                    } else {
                        colBase = col1;
                    }
                    ++col1cnt;
                }
                for (int j = 0; colBase != -1 && j < n; ++j) {
                    if (board[j][i] != board[j][colBase]) {
                        return -1;
                    }
                }
            }
            
            // now check # of row0 and row1, col0, col1
            // they should be equal or have a difference of 1
            if (row0cnt > row1cnt + 1 || row1cnt > row0cnt + 1
                || col0cnt > col1cnt + 1 || col1cnt > col0cnt + 1
                || (row0cnt > row1cnt && col0cnt < col1cnt)
                || (row0cnt < row1cnt && col0cnt > col1cnt)
                || cnt1 > (n*n+1)/2 || cnt1 < n*n/2) {
                return -1;
            }
            
            // need to check majority
            // now move row0 and row1 into place (swap columns)
            // check how many columns are not in place
            int colMove = INT_MAX;
            int rowMove = INT_MAX;
            if (n%2) {
                // 1 is major element
                int major = 0;
                if (cnt1 > (n*n+1)/2) {
                    major = 1;
                }
                // we need to know whether row0 or row1 is major row
                // col0 or col1 is major column
                int colMove0 = 0, colMove1 = 0;
                int rowMove0 = 0, rowMove1 = 0;
                for (int i = 0; i < n; i+=2) {
                    if (board[row1][i] != 1) {
                        ++colMove1;
                    }
                    if (board[row0][1] != 1) {
                        ++colMove0;
                    }
                    if (board[i][col1] != 1) {
                        ++rowMove1;
                    }
                    if (board[i][col0] != 1) {
                        ++rowMove0;
                    }
                }
                rowMove = min(rowMove1, rowMove0);
                colMove = min(colMove1, colMove0);
            } else {
                for (int m = 0; m <= 1; ++m){
                    int colMove0 = 0, colMove1 = 0;
                    int rowMove0 = 0, rowMove1 = 0;
                    for (int i = 0; i < n; i+=2) {
                        if (board[row1][i] != 1) {
                            ++colMove1;
                        }
                        if (board[row0][i] != 1) {
                            ++colMove0;
                        }
                        if (board[i][col1] != 1) {
                            ++rowMove1;
                        }
                        if (board[i][col0] != 1) {
                            ++rowMove0;
                        }
                    }
                    colMove = min(colMove, min(colMove0, colMove1));
                    rowMove = min(rowMove, min(rowMove0, rowMove1));
                }
                
            }
            
            
            return colMove + rowMove;
        }
        /**
         Note, the move operation will NOT alter the # of 1's
         in each row of column.
         
         Valid boards meet below criteria:
         1, if N is even, then each row/column has equal 0's and 1's
         else:
         1) (N+1)/2 rows have (N+1)/2 0's, (N-1)/2 1's, (N+1)/2
         columns have (N+1)/2 0's (N-1)/2 1's
         2) or (N+1)/2 rows have (N+1)/2 1's, (N-1)/2 1's
         
         First of all, move rows so that they all match the # criteria.
         
         Now, we can do the moving row by row:
         for the 1st row, move columns so that the 1st row is ok.
         this can be by scanning linearly at each position, and
         switch column with anothe column both are not at the its
         position.
         Now that 1st row is ok, move to the second:
         check whether there is a row is a proper row for 2nd row,
         if so, move onto next row
         otherwise, do column switch again. This time, we can only
         switch columns that have same value at the 1st row.
         This goes on for all the other rows.
         
         But how to find the minimum number of moves needed?
         */
        /**
         Validness property:
         for any rectangle in a valid chessboard, the 4 corners
         meet below criterion:
         NW xor NE == SW xor SE
         
         and swap rows or columns will not alter this property.
         
         Then this means the given board board will also have to meet
         this criterion, thus it has to have only 2 different kinds of
         rows, itself and its inverse.
         
         To change given board to a valid board, just need to change
         the first row and column.
         */
        int movesToChessboard2(vector<vector<int>>& board) {
            int n = board.size();
            int diff = 0;
            
            int rowSum = 0;
            for (int i = 0; i < n; ++i) {
                rowSum += board[0][i];
            }
            for (int i = 1; i < n; ++i) {
                int t = board[0][0] ^ board[i][0];
                for (int j = 1; j < n; ++j) {
                    if (board[0][j] ^ board[i][j] != t) {
                        return -1;
                    }
                }
                diff += t;
            }
            
            int rf = 0;
            int bf = 0;
            if (n % 2) {
                int s1 = (n + 1) / 2;
                int s2 = (n - 1) / 2;
                if ((diff != s1 && diff != s2) || (rowSum != s1 && rowSum != s2)) {
                    return -1;
                }
                
                bf = rowSum - s2;
                rf = board[0][0];
                if (diff == s1) {
                    rf = 1 - rf;
                    bf = 1 - bf;
                }
                
                return findMoves(board, bf, rf);
            } else {
                int s = n / 2;
                if (s != diff || s != rowSum) {
                    return -1;
                }
                
                int res = n * n;
                for (int i = 0; i < 2; ++i) {
                    for (int j = 0; j < 2; ++j) {
                        int t = findMoves(board, i, j);
                        if (res > t) {
                            res = t;
                        }
                    }
                }
                return res;
            }
        }
            
    private:
        int findMoves(vector<vector<int>> board, int bf, int rf) {
            // try arrange rows first.
            int n = board.size();
            int res = 0;
            for (int r = 0; r < n; ++r, rf = 1 - rf) {
                if (board[r][0] == rf) {
                    continue;
                }
                for (int j = r + 1; j < n; j += 2) {
                    if (board[j][0] == rf) {
                        // swith row[0] and row[i];
                        vector<int> t(board[r]);
                        board[r] = board[j];
                        board[j] = t;
                        ++res;
                        break;
                    }
                }
            }
            
            // now all rows are ok, we don't move row, change columns only
            for (int c = 0; c < n; ++c, bf = 1 - bf) {
                if (board[0][c] == bf) {
                    continue;
                }
                for (int j = c + 1; j < n; j += 2) {
                    if (board[0][j] == bf) {
                        int t = board[0][c];
                        board[0][c] = board[0][j];
                        board[0][j] = t;
                        ++res;
                        break;
                    }
                }
            }
            return res;
        }
    };
}
/*
int main() {
    vector<vector<int>> board{
        //{0,1,1,0},{0,1,1,0},{1,0,0,1},{1,0,0,1}
        //{1,0},{1,0}
        //{0,0,1,0,1,1},{1,1,0,1,0,0},{1,1,0,1,0,0},{0,0,1,0,1,1},{1,1,0,1,0,0},{0,0,1,0,1,1}
        {1,1,0},{1,1,0},{0,0,1}
    };
    cout << movesToChessboard::Solution().movesToChessboard(board) << endl;
    return 0;
}
 //*/
