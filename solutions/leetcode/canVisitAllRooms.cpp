// canVisitAllRooms.cpp
// leetcode
//
// Created by  Song Ding on 5/31/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace canVisitAllRooms {
/*
// TODO: copy problem statement here
 841. Keys and Rooms
 Medium
 
 458
 
 37
 
 Favorite
 
 Share
 There are N rooms and you start in room 0.  Each room has a distinct number in 0, 1, 2, ..., N-1, and each room may have some keys to access the next room.
 
 Formally, each room i has a list of keys rooms[i], and each key rooms[i][j] is an integer in [0, 1, ..., N-1] where N = rooms.length.  A key rooms[i][j] = v opens the room with number v.
 
 Initially, all the rooms start locked (except for room 0).
 
 You can walk back and forth between rooms freely.
 
 Return true if and only if you can enter every room.
 
 Example 1:
 
 Input: [[1],[2],[3],[]]
 Output: true
 Explanation:
 We start in room 0, and pick up key 1.
 We then go to room 1, and pick up key 2.
 We then go to room 2, and pick up key 3.
 We then go to room 3.  Since we were able to go to every room, we return true.
 Example 2:
 
 Input: [[1,3],[3,0,1],[2],[0]]
 Output: false
 Explanation: We can't enter the room with number 2.
 Note:
 
 1 <= rooms.length <= 1000
 0 <= rooms[i].length <= 1000
 The number of keys in all rooms combined is at most 3000.
 */

class Solution {
public:
    /**
     * BFS
     */
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<int> visited(n, 0);
        visited[0] = 1;
        unordered_set<int> keys{0};
        while (keys.size()) {
            unordered_set<int> nkeys;
            for (auto k : keys) {
                visited[k] = 1;
                for (auto i : rooms[k]) {
                    if (visited[i] == 0) {
                        nkeys.insert(i);
                    }
                }
            }
            keys.swap(nkeys);
        }
        int sum = 0;
        for (auto i : visited) {
            sum += i;
        }
        return sum == n;
        
        
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> rooms;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{1},{2},{3},{}}},
        {{{1,3},{3,0,1},{2},{0}}}
    };

    vector< bool > answers {
        true
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = canVisitAllRooms::Solution().canVisitAllRooms(dp.rooms);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
