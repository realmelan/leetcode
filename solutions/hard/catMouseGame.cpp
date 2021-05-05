// catMouseGame.cpp
// leetcode
//
// Created by  Song Ding on 7/23/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace catMouseGame {
/*
// TODO: copy problem statement here
 913. Cat and Mouse
 Hard
 
 179
 
 41
 
 Favorite
 
 Share
 A game on an undirected graph is played by two players, Mouse and Cat, who alternate turns.
 
 The graph is given as follows: graph[a] is a list of all nodes b such that ab is an edge of the graph.
 
 Mouse starts at node 1 and goes first, Cat starts at node 2 and goes second, and there is a Hole at node 0.
 
 During each player's turn, they must travel along one edge of the graph that meets where they are.  For example, if the Mouse is at node 1, it must travel to any node in graph[1].
 
 Additionally, it is not allowed for the Cat to travel to the Hole (node 0.)
 
 Then, the game can end in 3 ways:
 
 If ever the Cat occupies the same node as the Mouse, the Cat wins.
 If ever the Mouse reaches the Hole, the Mouse wins.
 If ever a position is repeated (ie. the players are in the same position as a previous turn, and it is the same player's turn to move), the game is a draw.
 Given a graph, and assuming both players play optimally, return 1 if the game is won by Mouse, 2 if the game is won by Cat, and 0 if the game is a draw.
 
 
 
 Example 1:
 
 Input: [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
 Output: 0
 Explanation:
 4---3---1
 |   |
 2---5
 \ /
 0
 
 
 Note:
 
 3 <= graph.length <= 50
 It is guaranteed that graph[1] is non-empty.
 It is guaranteed that graph[2] contains a non-zero element.
 */

class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        return catMouseGame_topoligical(graph);
    }
    
public:
    // https://leetcode.com/problems/cat-and-mouse/discuss/399346/C%2B%2B-solution-with-super-detailed-explanation-(topological-sort)
    int catMouseGame_topoligical(vector<vector<int>>& graph) {
        constexpr int MWIN = 1, CWIN = 2, DRAW = 0;
        constexpr int MTURN = 0, CTURN = 1;
        int n = graph.size();
        vector<vector<vector<int>>> states(n, vector<vector<int>>(n, vector<int>(2, DRAW)));
        vector<vector<vector<int>>> in(n, vector<vector<int>>(n, vector<int>(2, 0)));
        queue<tuple<int,int,int,int>> q;
        for (int i = 0; i < n; ++i) {
            if (i != 0) {
                states[i][i][MTURN] = states[i][i][CTURN] = CWIN;
                q.emplace(i,i,MTURN,CWIN);
                q.emplace(i,i,CTURN,CWIN);
                
                states[0][i][MTURN] = states[0][i][CTURN] = MWIN;
                q.emplace(0,i,MTURN,MWIN);
                q.emplace(0,i,CTURN,MWIN);
            }
            
            for (int j = 0; j < n; ++j) {
                in[i][j][MTURN] = graph[i].size();
                in[i][j][CTURN] = graph[j].size();
            }
            
            for (auto k : graph[0]) {
                --in[i][k][CTURN];
            }
        }
        
        while (q.size()) {
            auto [mpos, cpos, turn, result] = q.front(); q.pop();
            int prevTurn = 1 - turn;
            if (prevTurn == MTURN) {
                for (auto i : graph[mpos]) {
                    if (DRAW == states[i][cpos][prevTurn]) {
                        if (result == MWIN) {
                            states[i][cpos][prevTurn] = MWIN;
                        } else if (--in[i][cpos][prevTurn] == 0) {
                            states[i][cpos][prevTurn] = CWIN;
                        }
                        if (states[i][cpos][prevTurn] != DRAW) {
                            q.emplace(i, cpos, prevTurn, states[i][cpos][prevTurn]);
                        }
                    }
                }
            } else {
                for (auto i : graph[cpos]) {
                    if (DRAW == states[mpos][i][prevTurn]) {
                        if (result == CWIN) {
                            states[mpos][i][prevTurn] = CWIN;
                        } else if (--in[mpos][i][prevTurn] == 0) {
                            states[mpos][i][prevTurn] = MWIN;
                        }
                        if (states[mpos][i][prevTurn] != DRAW) {
                            q.emplace(mpos, i, prevTurn, states[mpos][i][prevTurn]);
                        }
                    }
                }
            }
        }
        return states[1][2][MTURN];
    }
    /**
     * mark each position pair(i,j) as 2, 1, 0, where i = cat positon, j = mouse position
     *  start with (i, 0) = 1; and (i,i) = 2.
     *
     */
    int catMouseGame_markposition(vector<vector<int>>& graph) {
        return 0;
    }
    // dfs:
    //  for each position a mouse at, check whether it can succeed
    int catMouseGame_dfs(vector<vector<int>>& graph) {
        int n = graph.size();
        map<int, int> memo;
        for (int i = 0; i < n; ++i) {
            memo[i*50+i] = 2;
            memo[i] = 1;
        }
        bool updated = true;
        while (updated) {
            updated = false;
            for (auto it = memo.begin(); it != memo.end();) {
                if (it->second == -1) {
                    it = memo.erase(it);
                } else {
                    ++it;
                }
            }
            int ret = test(graph, 1, 2, memo, updated);
            if (ret >= 0) {
                return ret;
            }
        }
        return 0; // when no nodes can be updated, it is a draw.
    }
    int test(vector<vector<int>>& graph, int m, int c, map<int, int>& memo, bool& updated) {
        if (m == 0 || c == 0) {
            return 1;
        } else if (m == c) {
            return 2;
        }
        
        int key = m * 50 + c;
        auto it = memo.find(key);
        if (it != memo.end()) {
            return it->second;
        }
        
        // if there is a mi, such that for all next possible cat position, mouse wins
        // then mouse wins;
        // else if for all possible mi, there is a position ci, that cat wins, then cat wins
        // else: draw
        // TODO: how to deal with a position from which a mouse comes?
        int res = -1;
        int catWin = 0;
        int draw = 0;
        int prev = 0;
        memo[key] = -1;
        for (auto mi : graph[m]) {
            if (mi == c) {
                ++catWin;
                continue;
            }
            int mouseWin = 0;
            // mouse wins if all ci returns 1
            for (auto ci : graph[c]) {
                int t = test(graph, mi, ci, memo, updated);
                if (t < 0) { // back to a previous position, not necessarily a draw!
                    ++prev;
                } else if (t == 2) {
                    ++catWin;
                    break;
                } else if (t == 1) {
                    ++mouseWin;
                } else { // (mi, ci) is a draw
                    ++draw;
                }
            }
            
            if (mouseWin == graph[c].size()) {
                res = 1;
                break;
            }
        }
        if (res == 1) {
            memo[key] = 1;
            updated = true;
            cout << "update (" << m << "," << c << ") => " << res << endl;
        } else if (catWin == graph[m].size()) {
            updated = true;
            memo[key] = 2;
            res = 2;
            cout << "update (" << m << "," << c << ") => " << res << endl;
        } else if (draw && prev == 0) {
            memo[key] = 0;
            res = 0;
            updated = true;
            cout << "update (" << m << "," << c << ") => " << res << endl;
        }
        return res;
    }
    /**
     * If mouse can reach any node in graph[0] faster than cat, then mouse wins;
     * else if mouse is able to enter a loop before cat touches the node along the way, then draw
     * else cat wins
     *
     * Use topological sort to find loop nodes, but removing nodes with 1 degree at each step
     *
     * Then use BFS to expand territory for cat and mouse, and check at each expansion that whether
     * mouse reaches 0 or mouse enters loop before the node is in cat's territory.
     *
     * What is missing?
     *   It considers only the absolute cases, where cat or mouse has absolute advantage over the other.
     */
    int catMouseGame_wrong(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> degree(n, 0);
        for (int i = 0; i < n; ++i) {
            degree[i] = graph[i].size();
        }
        while (true) {
            vector<int> ndegree(degree);
            bool updated = false;
            for (int i = 0; i < n; ++i) {
                if (degree[i] == 1) {
                    // update degree because of removing i
                    for (auto j : graph[i]) {
                        if (degree[j]) {
                            updated = true;
                            --ndegree[j];
                            --ndegree[i];
                        }
                    }
                }
            }
            if (!updated) {
                break;
            }
            degree.swap(ndegree);
        }
        
        unordered_set<int> loop;
        for (int i = 0; i < n; ++i) {
            if (degree[i]) {
                loop.insert(i);
            }
        }
        
        // do BFS expansion
        unordered_set<int> catCur{2};
        unordered_set<int> mouseCur{1};
        
        bool enterLoop = false;
        while (mouseCur.size()) {
            unordered_set<int> catNext;
            unordered_set<int> mouseNext;
            unordered_set<int> loopNext;
            for (auto i : mouseCur) {
                for (auto j : graph[i]) {
                    if (catCur.find(j) == catCur.end()) {
                        if (j == 0) {
                            return 1; // mouse wins
                        }
                        mouseNext.insert(j);
                        
                        if (loop.find(j) != loop.end()) {
                            loopNext.insert(j);
                        }
                    }
                }
            }
            
            for (auto i : catCur) {
                for (auto j : graph[i]) {
                    if (j != 0) {
                        catNext.insert(j);
                    }
                }
            }
            
            // check whether mouseNext are already in catTerr, if so, remove it from mouseNext
            for (auto it = mouseNext.begin(); it != mouseNext.end();) {
                if (catNext.find(*it) != catNext.end()) {
                    it = mouseNext.erase(it);
                } else {
                    ++it;
                }
            }
            for (auto it = loopNext.begin(); it != loopNext.end(); ++it) {
                if (mouseNext.find(*it) != mouseNext.end()) {
                    enterLoop = true;
                    break;
                }
            }
            mouseNext.swap(mouseCur);
            catNext.swap(catCur);
        }
        
        if (enterLoop) {
            return 0;
        } else {
            return 2;
        }
    }
    
    int catMouseGame3(vector<vector<int>>& graph) {
        constexpr int S = 50;
        vector<vector<int>> memo(S, vector<int>(S, -2));
        int res = -1;
        //int i = 0;
        bool updated = true;
        while (updated) {
            updated = false;
            //cout << "round " << i++ << endl;
            res = dfs(1, 2, graph, memo, updated);
            if (res >= 0) {
                return res;
            }
            for (auto& v : memo) {
                for (auto& i : v) {
                    if (i < 0) {
                        i = -2;
                    }
                }
            }
        }
        return 0;
    }
    int dfs(int m, int c, const vector<vector<int>>& graph, vector<vector<int>>& memo, bool& updated) {
        if (m == 0) {
            return 1;
        } else if (m == c) {
            return 2;
        } else if (memo[m][c] >= -1) {
            return memo[m][c];
        } else {
            memo[m][c] = -1;
            int result = -1;
            int cwin = 0;
            int draw = 0;
            int prev = 0;
            for (auto nm : graph[m]) {
                if (nm == c) {
                    ++cwin;
                    continue;
                }
                int mwin = 0;
                for (auto nc : graph[c]) {
                    if (nc == 0) {
                        ++mwin;
                        continue;
                    }
                    int res = dfs(nm, nc, graph, memo, updated);
                    if (res < 0) {
                        ++prev;
                    } else if (res == 1) {
                        ++mwin;
                    } else if (res == 2) {
                        ++cwin;
                        break;
                    } else {
                        ++draw;
                    }
                }
                if (mwin == graph[c].size()) {
                    result = 1;
                    break;
                }
            }
            //v[m][c] = 0;
            if (result != 1) {
                if (cwin == graph[m].size()) {
                    result = 2;
                    updated = true;
                    //cout << "update (" << m << "," << c << ") => " << result << endl;
                } else if (prev == 0) {
                    result = 0;
                    updated = true;
                    //cout << "update (" << m << "," << c << ") => " << result << endl;
                }
            } else {
                //cout << "update (" << m << "," << c << ") => " << result << endl;
                updated = true;
            }
            
            memo[m][c] = result;
            return result;
        }
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> graph;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{2,5},{3},{0,4,5},{1,4,5},{2,3},{0,2,3}}},
        {{{2,3,4},{2,4},{0,1,4},{0,4},{0,1,2,3}}},
        {{{6},{4,11},{9,12},{5},{1,5,11},{3,4,6},{0,5,10},{8,9,10},{7},{2,7,12},{6,7},{1,4},{2,9}}},
        {{{3,4,6,7,9,15,16,18},{4,5,8,19},{3,4,6,9,17,18},{0,2,11,15},{0,1,10,6,2,12,14,16},{1,10,7,9,15,17,18},{0,10,4,7,9,2,11,12,13,14,15,17,19},{0,10,5,6,9,16,17},{1,9,14,15,16,19},{0,10,5,6,7,8,2,11,13,15,16,17,18},{4,5,6,7,9,18},{3,6,9,12,19},{4,6,11,15,17,19},{6,9,15,17,18,19},{4,6,8,15,19},{0,3,5,6,8,9,12,13,14,16,19},{0,4,7,8,9,15,17,18,19},{5,6,7,9,2,12,13,16},{0,10,5,9,2,13,16},{1,6,8,11,12,13,14,15,16}}}
    };

    vector< int > answers {
        0,
        2,
        1,
        1
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = catMouseGame::Solution().catMouseGame(dp.graph);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
