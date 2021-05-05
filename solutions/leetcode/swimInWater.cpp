// swimInWater.cpp
// leetcode
//
// Created by  Song Ding on 10/8/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace swimInWater {

class Solution {
public:
    /**
     * For each candidate water height t, do DFS to see whether t is a good time.
     * Use binary search to find the least candiate height, from (max(grid[0][0], grid[N-1][N-1], N^N-1).
     */
    int swimInWater(vector<vector<int>>& grid) {
        int N = grid.size();
        int l = max(grid[0][0], grid[N - 1][N - 1]);
        int r = N * N - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (canSwim(m, grid)) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return r;
    }

private:
    bool canSwim(int t, vector<vector<int>> grid) {
        int N = grid.size();
        unordered_set<int> reached;
        unordered_set<int> cur{0};
        while (cur.size()) {
            unordered_set<int> next;
            for (int n : cur) {
                reached.insert(n);
                int r = n / N;
                int c = n % N;
                
                if (r - 1 >= 0 && grid[r-1][c] <= t) {
                    int id = n - N;
                    if (reached.find(id) == reached.end()) {
                        next.insert(id);
                    }
                }
                if (r + 1 < N && grid[r + 1][c] <= t) {
                    int id = n + N;
                    if (reached.find(id) == reached.end()) {
                        next.insert(id);
                    }
                }
                if (c - 1 >= 0 && grid[r][c - 1] <= t) {
                    int id = n - 1;
                    if (reached.find(id) == reached.end()) {
                        next.insert(id);
                    }
                }
                if (c + 1 < N && grid[r][c + 1] <= t) {
                    int id = n + 1;
                    if (reached.find(id) == reached.end()) {
                        next.insert(id);
                    }
                }
            }
            if (next.find(N * N - 1) != next.end()) {
                return true;
            }
            cur.swap(next);
        }
        return false;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> grid {
        //{0,3},{1,2}
        {0,1,2,3,4},{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6}
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = swimInWater::Solution().swimInWater(grid);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
