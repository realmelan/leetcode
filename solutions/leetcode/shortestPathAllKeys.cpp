// shortestPathAllKeys.cpp
// leetcode
//
// Created by  Song Ding on 10/25/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

/**
 
 864. Shortest Path to Get All Keys
 Hard

 248

 8

 Favorite

 Share
 We are given a 2-dimensional grid. "." is an empty cell, "#" is a wall, "@" is the starting point, ("a", "b", ...) are keys, and ("A", "B", ...) are locks.

 We start at the starting point, and one move consists of walking one space in one of the 4 cardinal directions.  We cannot walk outside the grid, or walk into a wall.  If we walk over a key, we pick it up.  We can't walk over a lock unless we have the corresponding key.

 For some 1 <= K <= 6, there is exactly one lowercase and one uppercase letter of the first K letters of the English alphabet in the grid.  This means that there is exactly one key for each lock, and one lock for each key; and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.

 Return the lowest number of moves to acquire all keys.  If it's impossible, return -1.

  

 Example 1:

 Input: ["@.a.#","###.#","b.A.B"]
 Output: 8
 Example 2:

 Input: ["@..aA","..B#.","....b"]
 Output: 6
  

 Note:

 1 <= grid.length <= 30
 1 <= grid[0].length <= 30
 grid[i][j] contains only '.', '#', '@', 'a'-'f' and 'A'-'F'
 The number of keys is in [1, 6].  Each key has a different letter and opens exactly one lock.
 */
namespace shortestPathAllKeys {

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int r = grid.size();
        int c = grid[0].size();
        int si = 0;
        int sj = 0;
        int total_keys = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                char ch =  grid[i][j];
                if (ch >= 'a' && ch <= 'f') {
                    total_keys |= (1 << (ch - 'a'));
                } else if (ch == '@') {
                    si = i;
                    sj = j;
                }
            }
        }
        
        const vector<pair<int,int>> moves {
            {-1, 0},{1, 0},{0, -1},{0, 1}
        };
        int steps = 0;
        vector<vector<set<int>>> visited(r, vector<set<int>>(c));
        visited[si][sj] = {0};
        vector<vector<int>> cur{{si, sj, 0}};
        while (!cur.empty()) {
            ++steps;
            vector<vector<int>> next;
            for (const auto& s : cur) {
                int i = s[0];
                int j = s[1];
                int keys = s[2];
                for (const auto& m : moves) {
                    int ni = i + m.first;
                    int nj = j + m.second;
                    
                    if (ni < 0 || ni >= r || nj < 0 || nj >= c || grid[ni][nj] == '#') {
                        continue;
                    }
                    
                    int nkeys = keys;
                    char nextc = grid[ni][nj];
                    if (nextc >= 'A' && nextc <= 'F') {
                        if (!unlock(nextc, keys)) {
                            continue;
                        }
                    } else if (nextc >= 'a' && nextc <= 'f') {
                        nkeys |= (1 << (nextc - 'a'));
                        if (nkeys == total_keys) {
                            return steps;
                        }
                    }
                    
                    if (visited[ni][nj].empty()
                        || !contains(visited[ni][nj], nkeys)) {
                        visited[ni][nj].insert(nkeys);
                        next.push_back({ni, nj, nkeys});
                    }
                } // end for moves
            } // end cur
            cur.swap(next);
        }
        return -1;
    }
    /**
     * DFS: state = <position, keys collected, # of steps>
     *
     * trim: if reached a position with fewer keys but more steps, then discard current state.
     * time limit exceeded.
     */
    int shortestPathAllKeys2(vector<string>& grid) {
        int si = 0;
        int sj = 0;
        int total_keys = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                char c =  grid[i][j];
                if (c >= 'a' && c <= 'f') {
                    total_keys |= 1 << (c - 'a');
                } else if (c == '@') {
                    si = i;
                    sj = j;
                }
            }
        }
        
        int res = -1;
        int keys = 0;
        int steps = 0;
        unordered_map<int, set<int>> optimalStates;
        dfs(si, sj, grid, total_keys, steps, keys, optimalStates, res);
        return res;
    }

private:
    static const int N = 30;
    void dfs(int i, int j, const vector<string>& grid, int total_keys, int steps, int keys, unordered_map<int, set<int>>& optimalStates, int& res) {
        int r = grid.size();
        int c = grid[0].size();
        
        if (total_keys == keys && (res < 0 || steps < res)) {
            res = steps;
            return;
        }
        
        const vector<pair<int,int>> moves {
            {-1, 0},{1, 0},{0, -1},{0, 1}
        };
        for (const auto& m : moves) {
            int ni = i + m.first;
            int nj = j + m.second;
            
            if (ni < 0 || ni >= r || nj < 0 || nj >= c || grid[ni][nj] == '#') {
                continue;
            }
            
            int nsteps = steps;
            int nkeys = keys;
            int nextc = grid[ni][nj];
            int nid = ni * N + nj;
            if (nextc >= 'A' && nextc <= 'F'
                && unlock(nextc, keys)) {
                ++nsteps;
            } else if (nextc >= 'a' && nextc <= 'f') {
                ++nsteps;
                nkeys |= (1 << (nextc - 'a'));
            } else if (nextc == '.' || nextc == '@') {
                ++nsteps;
            }
            
            if (nsteps > steps && !worseState(nsteps, nkeys, optimalStates[nid])) {
                optimalStates[nid].insert(state(nsteps, nkeys));
                dfs(ni, nj, grid, total_keys, nsteps, nkeys, optimalStates, res);
            }
        }
    }
    
    int state(int steps, int keys) {
        return (steps << 6) + keys;
    }
    int steps(int state) {
        return state >> 6;
    }
    int keys(int state) {
        return state & 0x3F;
    }
    bool unlock(char lock, int keys) {
        return keys & (1 << (lock - 'A'));
    }
    bool contains(const set<int>& keys, int nkeys) {
        for (auto i : keys) {
            if ((i | nkeys) == i) {
                return true;
            }
        }
        return false;
    }
    bool contains(int keys, int nkeys) {
        return (keys | nkeys) == keys;
    }
    bool worseState(int nsteps, int nkeys, set<int>& states) {
        for (auto s : states) {
            if (steps(s) <= nsteps && (keys(s) | nkeys) == keys(s)) {
                return true;
            }
        }
        return false;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<string> grid {
        "@.a.#","###.#","b.A.B" // 8
        //"@..aA","..B#.","....b" // 6
        //".@aA" // 1
        //"@...a",".###A","b.BCc" // 10
        //"..Ff..#..e.#...",".....#.##...#..","....#.#...#....","##.......##...#","...@#.##....#..","#........b.....","..#...#.....##.",".#....#E...#...","......A.#D.#...","...#...#..#....","...a.#B#.......",".......c.....#.","....#...C#...#.","##.#.....d..#..",".#..#......#..." // 25
        //".#.b.","A.#aB","#d...","@.cC.","D...#" // 8
    };

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = shortestPathAllKeys::Solution().shortestPathAllKeys(grid);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
