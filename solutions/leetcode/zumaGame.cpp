//
//  zumaGame.cpp
//  leetcode
//
//  Created by  Song Ding on 2/8/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace zumaGame {
    class Solution {
    public:
        /**
         Serveral rules apply:
         1, don't insert a new color
         2, don't insert a ball at a place to create a new single ball,
         instead insert a ball at the place where there are two same-color
         balls or just one same-color ball.
         3, to insert same-color ball, either side is ok, so just insert at
         the left side.
         
         Solve the problem recursively, with memoization.
         */
        int findMinStep(string board, string hand) {
            // to remove some case where balls simply can't be removed.
            if (board.empty()) {
                return 0;
            }
            map<char, int> handBalls;
            for (char c : hand) {
                ++handBalls[c];
            }
            string newHand;
            for (const auto& p : handBalls) {
                for (int i = 0; i < p.second; ++i) {
                    newHand.push_back(p.first);
                }
            }
            
            if (!isSolvable(board, newHand)) {
                return -1;
            }
            
            map<string, int> solutions;
            return recur(board, newHand, solutions);
            
        }
    private:
        bool isSolvable(string board, string hand) {
            map<char, int> boardBalls;
            for (char c : board) {
                ++boardBalls[c];
            }
            map<char, int> handBalls;
            for (char c : hand) {
                ++handBalls[c];
            }
            
            for (const auto& p : boardBalls) {
                auto it = handBalls.find(p.first);
                int c = 0;
                if (it != handBalls.end()) {
                    c = it->second;
                }
                if (p.second + c < 3) {
                    return false;
                }
            }
            return true;
        }
        void shrink(string& board, size_t p) {
            char t = board[p];
            int i = p;
            int n = board.size();
            int c = 0;
            for (; i < n; ++i) {
                if (board[i] != t) {
                    break;
                } else {
                    ++c;
                }
            }
            int j = p - 1;
            for (; j >= 0; --j) {
                if (board[j] != t) {
                    break;
                } else {
                    ++c;
                }
            }
            
            if (c >= 3) {
                board.erase(j + 1, c);
                if (j >= 0) {
                    shrink(board, j);
                } else if (i < n) {
                    shrink(board, i - c);
                }
            }
        }
        string slnKey(string board, string hand) {
            return board + "|" + hand;
        }
        int recur(string board, string hand, map<string, int>& solutions) {
            auto it = solutions.find(slnKey(board, hand));
            if (it != solutions.end()) {
                return it->second;
            }
            if (!isSolvable(board, hand)) {
                return -1;
            }
            
            int n = board.size();
            int res = -1;
            int i = 0;
            while (i < n) {
                char c = board[i];
                size_t cit = hand.find(c);
                if (cit != string::npos) {
                    string nb(board);
                    nb.insert(i, 1, c);
                    shrink(nb, i);
                    if (nb.empty()) {
                        solutions[slnKey(board, hand)] = 1;
                        return 1;
                    }
                    
                    string nh(hand);
                    nh.erase(cit, 1);
                    int t = recur(nb, nh, solutions);
                    if (t >= 0) {
                        solutions[slnKey(nb, nh)] = t;
                        if (res == -1 || res > t + 1) {
                            res = t + 1;
                        }
                    }
                }
                
                while (i < n && board[i] == c) {
                    ++i;
                }
            }
            return res;
        }
    };
}

/*
int main() {
    string board("GGYYBRGGRYBYG");
    string hand("RYYBG");
    
    cout << zumaGame::Solution().findMinStep(board, hand) << endl;
    return 0;
}
 */
