// isEscapePossible.cpp
// leetcode
//
// Created by  Song Ding on 8/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace isEscapePossible {
/*
// TODO: copy problem statement here
 1036. Escape a Large Maze
 Hard
 
 105
 
 68
 
 Favorite
 
 Share
 In a 1 million by 1 million grid, the coordinates of each grid square are (x, y) with 0 <= x, y < 10^6.
 
 We start at the source square and want to reach the target square.  Each move, we can walk to a 4-directionally adjacent square in the grid that isn't in the given list of blocked squares.
 
 Return true if and only if it is possible to reach the target square through a sequence of moves.
 
 
 
 Example 1:
 
 Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
 Output: false
 Explanation:
 The target square is inaccessible starting from the source square, because we can't walk outside the grid.
 Example 2:
 
 Input: blocked = [], source = [0,0], target = [999999,999999]
 Output: true
 Explanation:
 Because there are no blocked cells, it's possible to reach the target square.
 
 
 Note:
 
 0 <= blocked.length <= 200
 blocked[i].length == 2
 0 <= blocked[i][j] < 10^6
 source.length == target.length == 2
 0 <= source[i][j], target[i][j] < 10^6
 source != target
 */

class Solution {
public:
    // say the blocked area is N, if both source and target can do a BFS whose steps exceed N
    // then source and target can reach each other.
    bool isEscapePossible2(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        return bfs(source, target, blocked) && bfs(target, source, blocked);
    }
    bool bfs(const vector<int>& source, const vector<int>& target, const vector<vector<int>>& blocked) {
        constexpr int CNT = 20000, N = 1000000;
        static const vector<int> dirs{1,0,-1,0,1};
        unordered_map<int, unordered_set<int>> visited;
        visited[source[0]].insert(source[1]);
        for (auto& v : blocked) {
            visited[v[0]].insert(v[1]);
        }
        queue<vector<int>> q;
        q.emplace(source);
        int cnt = 1;
        while (q.size() && cnt < CNT) {
            auto v = q.front(); q.pop();
            for (int i = 0; i < 4; ++i) {
                int x = v[0] + dirs[i];
                int y = v[1] + dirs[i+1];
                if (x >= 0 && x < N && y >= 0 && y < N && (!visited.count(x) || !visited[x].count(y))) {
                    if (x == target[0] && y == target[1]) {
                        return true;
                    }
                    q.emplace(std::initializer_list<int>{x,y});
                    visited[x].insert(y);
                    ++cnt;
                }
            }
        }
        return cnt >= CNT;
    }
    
    /**
     * Do BFS expansion from source and target, and count the # of cells visited:
     *  1, if target is met during expansion, return true;
     *  2, if expansion is stopped, return false;
     *  3, if expansion passes the possible number of cells that blocked can circle, return true.
     *
     * the threshold of 3 can be set to square(# of blocked).
     */
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        int nb = blocked.size();
        int thr = nb * nb;
        const int n = 1000000;
        long sid = id(source[0], source[1]);
        long tid = id(target[0], target[1]);
        
        unordered_set<long> bids;
        for (auto& b : blocked) {
            bids.insert(id(b[0], b[1]));
        }
        
        unordered_set<long> visited(bids);
        visited.insert(sid);
        unordered_set<long> cur {sid};
        static const vector<vector<int>> move{{-1,0},{1,0},{0,-1},{0,1}};
        int cnt1 = 0;
        while (cur.size()) {
            unordered_set<long> next;
            for (auto cid : cur) {
                long x, y;
                toxy(cid, x, y);
                
                for (auto& m : move) {
                    long nx = x + m[0];
                    long ny = y + m[1];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
                        continue;
                    }
                    long nid = id(nx, ny);
                    if (nid == tid) {
                        return true;
                    } else if (visited.find(nid) == visited.end()) {
                        if (++cnt1 >= thr) {
                            break;
                        }
                        visited.insert(nid);
                        next.insert(nid);
                    }
                }
            }
            cur.swap(next);
        }
        
        if (cnt1 < thr) {
            return false;
        }
        
        // now check expansion from target
        visited.clear();
        visited.insert(bids.begin(), bids.end());
        visited.insert(tid);
        cur.clear();
        cur.insert(tid);
        int cnt2 = 0;
        while (cur.size()) {
            unordered_set<long> next;
            for (auto cid : cur) {
                long x, y;
                toxy(cid, x, y);
                
                for (auto& m : move) {
                    long nx = x + m[0];
                    long ny = y + m[1];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
                        continue;
                    }
                    long nid = id(nx, ny);
                    if (nid == sid) {
                        return true;
                    } else if (visited.find(nid) == visited.end()) {
                        if (++cnt2 >= thr) {
                            break;
                        }
                        visited.insert(nid);
                        next.insert(nid);
                    }
                }
            }
            cur.swap(next);
        }
        
        return cnt2 >= thr;
    }

private:
    long id(long x, long y) {
        return (x << 20 | y);
    }
    void toxy(long cid, long& x, long& y) {
        y = cid & 0xFFFFF;
        x = cid >> 20;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> blocked;
        vector<int> source;
        vector<int> target;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{0,1},{1,0}}, {0,0}, {0,2}},
        //{{}, {0,0}, {999999,999999}},
        {{{100059,100063},{100060,100064},{100061,100065},{100062,100066},{100063,100067},{100064,100068},{100065,100069},{100066,100070},{100067,100071},{100068,100072},{100069,100073},{100070,100074},{100071,100075},{100072,100076},{100073,100077},{100074,100078},{100075,100079},{100076,100080},{100077,100081},{100078,100082},{100079,100083},{100080,100082},{100081,100081},{100082,100080},{100083,100079},{100084,100078},{100085,100077},{100086,100076},{100087,100075},{100088,100074},{100089,100073},{100090,100072},{100091,100071},{100092,100070},{100093,100069},{100094,100068},{100095,100067},{100096,100066},{100097,100065},{100098,100064},{100099,100063},{100098,100062},{100097,100061},{100096,100060},{100095,100059},{100094,100058},{100093,100057},{100092,100056},{100091,100055},{100090,100054},{100089,100053},{100088,100052},{100087,100051},{100086,100050},{100085,100049},{100084,100048},{100083,100047},{100082,100046},{100081,100045},{100080,100044},{100079,100043},{100078,100044},{100077,100045},{100076,100046},{100075,100047},{100074,100048},{100073,100049},{100072,100050},{100071,100051},{100070,100052},{100069,100053},{100068,100054},{100067,100055},{100066,100056},{100065,100057},{100064,100058},{100063,100059},{100062,100060},{100061,100061},{100060,100062}},{100079,100063},{999948,999967}},
    };

    vector< bool > answers {
        false,
        true,
        false
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = isEscapePossible::Solution().isEscapePossible2(dp.blocked, dp.source, dp.target);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
