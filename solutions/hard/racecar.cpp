// racecar.cpp
// leetcode
//
// Created by  Song Ding on 4/25/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace racecar {
/**
 818. Race Car
 Hard
 
 270
 
 32
 
 Favorite
 
 Share
 Your car starts at position 0 and speed +1 on an infinite number line.  (Your car can go into negative positions.)
 
 Your car drives automatically according to a sequence of instructions A (accelerate) and R (reverse).
 
 When you get an instruction "A", your car does the following: position += speed, speed *= 2.
 
 When you get an instruction "R", your car does the following: if your speed is positive then speed = -1 , otherwise speed = 1.  (Your position stays the same.)
 
 For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.
 
 Now for some target position, say the length of the shortest sequence of instructions to get there.
 
 Example 1:
 Input:
 target = 3
 Output: 2
 Explanation:
 The shortest instruction sequence is "AA".
 Your position goes from 0->1->3.
 Example 2:
 Input:
 target = 6
 Output: 5
 Explanation:
 The shortest instruction sequence is "AAARA".
 Your position goes from 0->1->3->7->7->6.
 
 
 Note:
 
 1 <= target <= 10000.
 */
class Solution {
public:
    /**
     // https://leetcode.com/problems/race-car/discuss/123834/JavaC%2B%2BPython-DP-solution
     the sequence of instructions can be grouped as
     A*k1|R|A*k2|R|... note, k1, k2, can be 0.
     so it includes case of RR.
     
     Note, each odd A*ki can be added together, as it points to the same direction, and it goes that k should be as big
     as possible, to reduce total number of instructions.
     */
    int racecar_dp(int target) {
        vector<int> dp(10000);
        return recur(target, dp);
    }
    int recur(int t, vector<int>& dp) {
        if (dp[t]) {
            return dp[t];
        }
        int m = floor(log2(t+1));
        if ((1<<m) == t+1) {
            dp[t] = m;
            return m;
        }
        dp[t] = m+1+1+recur((1<<(m+1))-1-t, dp);
        for (int i = 0; i < m; ++i) {
            dp[t] = min(dp[t], m+1+i+1+recur(t - (1<<m) + (1<<i), dp));
        }
        return dp[t];
    }
    /**
     * DP:
     * let dp[i] = min # of operations to reach target i from position 0(speed=1).
     * there are two ways of reaching i:
     *  1, from left, it goes very closely at first, then back up some distance, from this new position,
     *     it starts again.
     *  2, from right, it goes just past i, and reverse, to race to i.
     *
     */
    int racecar(int target) {
        vector<int> dp(target + 1, INT_MAX);
        int k = 0;
        int dist = 0;
        int move = 1;
        while (dist <= target) {
            dp[dist] = k++;
            dist += move;
            move <<= 1;
        }
        return race(target, dp);
    }
    
    int race(int target, vector<int>& dp) {
        if (dp[target] != INT_MAX) {
            return dp[target];
        }
        
        // race close to target
        int dist = 0;
        int move = 1;
        int k = 0;
        vector<int> backup;
        while (dist < target) {
            backup.push_back(dist);
            dist += move;
            move <<= 1;
            ++k;
        }
        
        // can't be dist = target
        // dist > target
        dp[target] = race(dist - target, dp) + k + 1;
        
        // approach target from left
        --k;
        dist -= (move>>1);
        for (int i = 0; i < backup.size(); ++i) {
            dp[target] = min(dp[target], race(target - dist + backup[i], dp) + k+1+i+1);
        }
        
        return dp[target];
    }
    
    struct phash {
        size_t operator()(const pair<int,int>& p) const {
            static std::hash<std::string> sh;
            ostringstream oss;
            oss << p.first << "," << p.second;
            return sh(oss.str());
        }
    };
    
    
    
    /**
     Time limit exceeded
     */
    int racecar_bfs(int target) {
        int res = 0;
        unordered_set<pair<int,int>, phash> cur{{0,1}};
        unordered_set<pair<int,int>, phash> visited{{0,1}};
        while (cur.size()) {
            ++res;
            unordered_set<pair<int,int>, phash> next;
            for (const auto& p : cur) {
                int ns1 = 0;
                if (abs(p.second) >= 65536) {
                    continue;
                } else if (p.second < 0) {
                    ns1 = -((-p.second) << 1);
                } else {
                    ns1 = (p.second << 1);
                }
                
                int nt1 = p.first + p.second;
                if (nt1 == target) {
                    return res;
                }
                if (visited.find(make_pair(nt1, ns1)) == visited.end()) {
                    next.insert(make_pair(nt1, ns1));
                    visited.insert(make_pair(nt1, ns1));
                }
                
                int nt2 = p.first;
                int ns2 = 1;
                if (p.second > 0) {
                    ns2 = -1;
                }
                if (visited.find(make_pair(nt2, ns2)) == visited.end()) {
                    next.insert(make_pair(nt2, ns2));
                    visited.insert(make_pair(nt2, ns2));
                }
            }
            cur.swap(next);
        }
        return -1;
    }
    /**
     if target in on position 2^k - 1, relative to starting point
     then the shortest is A...A(there is k A).
     
     Now if target is not on such positions, say 2^(k-1) - 1 < t < 2^k - 1.
     then there are two scenarios the car can approach target:
     1, k-1 A to reach 2^(k-1) - 1, and then press RR to reset speed to 1,
     solve subproblem of t = t - 2^(k-1) + 1
     2, k A to reach 2^k - 1, then press R to reset speed to -1. Now also a
     subproblem of t = 2^k - 1 - t, with speed = 1.
     
     Can use memoization to record solutions to sub problems.
     */
    int racecar2(int target) {
        unordered_map<pair<int,int>, int, phash> memo;
        int speed = 1;
        return dfs(target, speed, memo);
    }
private:
    int dfs(int target, int speed, unordered_map<pair<int, int>, int, phash>& memo) {
        if (target == speed) {
            return 1;
        }
        auto it = memo.find(make_pair(target, speed));
        if (it != memo.end()) {
            return it->second;
        }
        
        int res = INT_MAX;
        if (target >= speed * 2) {
            res = 1 + dfs(target - speed, (speed<<1), memo);
        } else if (target > speed) {
            int res1 = 1 + dfs(target - speed, (speed << 1), memo);
            int res2 = 2 + dfs(target, 1, memo);
            res = min(res1, res2);
        } else {
            // two options:
            // 1, RR to reset and dfs(target, 1, memo);
            // or, A to pass target, and R to reverse speed
            int res1 = 2 + dfs(target, 1, memo);
            int res2 = 2 + dfs(speed - target, 1, memo);
            res = min(res1, res2);
        }
        
        memo[make_pair(target, speed)] = res;
        return res;
    }
    
    
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int target;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {3},
        {6},
        {5},
        {4},
        {5478}
    };
    
    vector< int > answers {
        2,
        5,
        7,
        5
    };
    
    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = racecar::Solution().racecar_dp(dp.target);
        //cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
