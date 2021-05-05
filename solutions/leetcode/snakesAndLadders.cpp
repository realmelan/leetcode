// snakesAndLadders.cpp
// leetcode
//
// Created by  Song Ding on 3/11/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace snakesAndLadders {

class Solution {
public:
    /**
     * Let reached[i] = set of nodes that are reached at step i.
     * for each node in reached[i], do 1-6 distance move, reach
     * a new node; all the new nodes form reached[i+1].
     *
     * At most N*N-1 step is needed to reach all nodes if they are
     * reachable.
     */
    int snakesAndLadders(vector<vector<int>>& board) {
        int N = board.size();
        int step = 0;
        
        int target = N * N;
        int total = target + 1;
        vector<int> sb(total);
        int id = 1;
        int dir = 1;
        for (int r = N-1; r >= 0; --r, dir*=-1) {
            if (dir > 0) {
                for (int c = 0; c < N; ++c) {
                    sb[id++] = board[r][c];
                }
            } else {
                for (int c = N-1; c >= 0; --c) {
                    sb[id++] = board[r][c];
                }
            }
        }
        
        set<int> reached{1};
        while (step++ < N*N-1) {
            set<int> next;
            for (int n : reached) {
                for (int i = 1; i <= 6; ++i) {
                    int nn = n + i;
                    if (sb[nn] != -1) {
                        nn = sb[nn];
                    }
                    if (nn == target) {
                        return step;
                    } else {
                        next.insert(nn);
                    }
                }
            }
            
            if (next.empty()) {
                break;
            }
            reached.swap(next);
        }
        return -1;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<vector<int>> > board {
        {
            {-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1},
            {-1,35,-1,-1,13,-1},
            {-1,-1,-1,-1,-1,-1},
            {-1,15,-1,-1,-1,-1}
        }
    };

    vector< int  > answers {
    };
    int i = 0;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = snakesAndLadders::Solution().snakesAndLadders(board[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
