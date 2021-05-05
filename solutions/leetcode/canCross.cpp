//
//  canCross.cpp
//  leetcode
//
//  Created by  Song Ding on 3/11/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;
/**
 403. Frog Jump
 Hard

 605

 72

 Favorite

 Share
 A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

 Given a list of stones' positions (in units) in sorted ascending order, determine if the frog is able to cross the river by landing on the last stone. Initially, the frog is on the first stone and assume the first jump must be 1 unit.

 If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units. Note that the frog can only jump in the forward direction.

 Note:

 The number of stones is ≥ 2 and is < 1,100.
 Each stone's position will be a non-negative integer < 231.
 The first stone's position is always 0.
 Example 1:

 [0,1,3,5,6,8,12,17]

 There are a total of 8 stones.
 The first stone at the 0th unit, second stone at the 1st unit,
 third stone at the 3rd unit, and so on...
 The last stone at the 17th unit.

 Return true. The frog can jump to the last stone by jumping
 1 unit to the 2nd stone, then 2 units to the 3rd stone, then
 2 units to the 4th stone, then 3 units to the 6th stone,
 4 units to the 7th stone, and 5 units to the 8th stone.
 Example 2:

 [0,1,2,3,4,8,9,11]

 Return false. There is no way to jump to the last stone as
 the gap between the 5th and 6th stone is too large.
 */
namespace canCross {
    class Solution {
    public:
        /**
         * let step[i] = set of steps a frog can jump to stone[i].
         */
        bool canCross(vector<int>& stones) {
            int n = stones.size();
            if (stones[1] != 1) {
                return false;
            }
            
            unordered_map<int, int> dist2Stone;
            for (int i = 0; i < n; ++i) {
                dist2Stone[stones[i]] = i;
            }
            
            const static vector<int> diff {-1,0,1};
            vector<unordered_set<int>> jumps(n);
            jumps[1].insert(1);
            for (int i = 1; i < n-1; ++i) {
                // update other jumps
                for (auto k : jumps[i]) {
                    for (int d : diff) {
                        int nd = stones[i] + k + d;
                        auto it = dist2Stone.find(nd);
                        if (it != dist2Stone.end()) {
                            if (it->second == n-1) {
                                return true;
                            } else {
                                jumps[it->second].insert(k+1);
                            }
                        }
                    }
                }
            }
            return false;
            
        }
        /**
         let bool reachable[n][k] to record whether the n'th store is
         reachable by a k-unit step from previous stone
         then reachable[i][k] = reachable[stone(distance[i] - k)]{k-1,k,k+1}
         */
        bool canCross2(vector<int>& stones) {
            int n = stones.size();
            if (stones[1] != 1) {
                return false;
            }
            
            unordered_map<int, int> dist2Stone;
            for (int i = 0; i < n; ++i) {
                dist2Stone[stones[i]] = i;
            }
            vector<unordered_set<int>> r(n);
            r[1] = unordered_set<int>{1};
            int maxstep = 1;
            for (int i = 2; i < n; ++i) {
                int d = stones[i];
                int nmaxstep = 0;
                for (int j = maxstep + 1; j >= 1; --j) {
                    int td = d - j;
                    auto it = dist2Stone.find(td);
                    if (it != dist2Stone.end()) {
                        int st = it->second;
                        if (r[st].count(j - 1) || r[st].count(j)
                            || r[st].count(j + 1)) {
                            r[i].insert(j);
                            if (j > nmaxstep) {
                                nmaxstep = j;
                            }
                        }
                    }
                }
                if (nmaxstep > maxstep) {
                    maxstep = nmaxstep;
                }
            }
            return r[n - 1].size();
        }
    };
}
/*
int main() {
    vector<int> stones {
        0,1,3,6,10,15,16,21
    };
    cout << canCross::Solution().canCross(stones) << endl;
    return 0;
}
// */
