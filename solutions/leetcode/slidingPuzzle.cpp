// slidingPuzzle.cpp
// leetcode
//
// Created by  Song Ding on 10/8/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace slidingPuzzle {

class Solution {
public:
    /**
     * BFS:
     * starting from the destionation, swap 0 and adjacent digit.
     * return the number of steps that are required to reach the
     * given board.
     *
     * No duplicate board should be allowed.
     *
     * How to swap:
     */
    int slidingPuzzle(vector<vector<int>>& board) {
        int dest = 0;
        for (const auto& v : board) {
            for (int i : v) {
                dest *= 10;
                dest += i;
            }
        }
        if (dest == 123450) {
            return 0;
        }
        
        int res = 0;
        unordered_set<int> used;
        unordered_set<int> cur {123450};
        while (cur.size()) {
            ++res;
            unordered_set<int> next;
            for (int i : cur) {
                used.insert(i);
                vector<int> vnext = nextBoards(i);
                for (int j : vnext) {
                    if (j == dest) {
                        return res;
                    }
                    if (used.find(j) == used.end()) {
                        next.insert(j);
                    }
                }
            }
            cur.swap(next);
        }
        return -1;
    }

private:
    vector<int> nextBoards(int current) {
        vector<int> digits;
        int t = current;
        while (t) {
            digits.insert(digits.begin(), t % 10);
            t /= 10;
        }
        if (digits.size() == 5) {
            digits.insert(digits.begin(), 0);
        }
        
        vector<int> res;
        if (digits[0] == 0) {
            res.push_back(current - digits[1] * 10000 + digits[1] * 100000);
            res.push_back(current - digits[3] * 100 + digits[3] * 100000);
        } else if (digits[1] == 0) {
            res.push_back(current - digits[0] * 100000 + digits[0] * 10000);
            res.push_back(current - digits[2] * 1000 + digits[2] * 10000);
            res.push_back(current - digits[4] * 10 + digits[4] * 10000);
        } else if (digits[2] == 0) {
            res.push_back(current - digits[1] * 10000 + digits[1] * 1000);
            res.push_back(current - digits[5] + digits[5] * 1000);
        } else if (digits[3] == 0) {
            res.push_back(current - digits[0] * 100000 + digits[0] * 100);
            res.push_back(current - digits[4] * 10 + digits[4] * 100);
        } else if (digits[4] == 0) {
            res.push_back(current - digits[1] * 10000 + digits[1] * 10);
            res.push_back(current - digits[3] * 100 + digits[3] * 10);
            res.push_back(current - digits[5] + digits[5] * 10);
        } else {
            res.push_back(current - digits[2] * 1000 + digits[2]);
            res.push_back(current - digits[4] * 10 + digits[4]);
        }
        return res;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> board {
        {3,2,4},{1,5,0}
    };
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = slidingPuzzle::Solution().slidingPuzzle(board);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
