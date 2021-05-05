// superEggDrop.cpp
// leetcode
//
// Created by  Song Ding on 8/6/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace superEggDrop {
/*
// TODO: copy problem statement here
 887. Super Egg Drop
 Hard
 
 408
 
 43
 
 Favorite
 
 Share
 You are given K eggs, and you have access to a building with N floors from 1 to N.
 
 Each egg is identical in function, and if an egg breaks, you cannot drop it again.
 
 You know that there exists a floor F with 0 <= F <= N such that any egg dropped at a floor higher than F will break, and any egg dropped at or below floor F will not break.
 
 Each move, you may take an egg (if you have an unbroken one) and drop it from any floor X (with 1 <= X <= N).
 
 Your goal is to know with certainty what the value of F is.
 
 What is the minimum number of moves that you need to know with certainty what F is, regardless of the initial value of F?
 
 
 
 Example 1:
 
 Input: K = 1, N = 2
 Output: 2
 Explanation:
 Drop the egg from floor 1.  If it breaks, we know with certainty that F = 0.
 Otherwise, drop the egg from floor 2.  If it breaks, we know with certainty that F = 1.
 If it didn't break, then we know with certainty F = 2.
 Hence, we needed 2 moves in the worst case to know what F is with certainty.
 Example 2:
 
 Input: K = 2, N = 6
 Output: 3
 Example 3:
 
 Input: K = 3, N = 14
 Output: 4
 
 
 Note:
 
 1 <= K <= 100
 1 <= N <= 10000
 */

class Solution {
public:
    /**
     * Let story[k][min_st] = # of layers that k eggs and minimum steps can measure.
     * then story[k+1][min_st] = story[k][1] + 1 + story[k][min_st-x+1] + 1 + ... + 1 + story[k][min_st]
     */
    int superEggDrop(int K, int N) {
        vector<int> maxfloors(N+1); // 1 egg
        for (int i = 0; i <= N; ++i) {
            maxfloors[i] = i;
        }
        
        for (int k = 2; k <= K; ++k) {
            int maxfl = 0;
            vector<int> next{0, 1};
            for (int st = 2; st <= N && maxfl < N; ++st) {
                int fl = 1; // the highest level (N) doesn't have to be tested.
                for (int x = 1; x < st; ++x) {
                    fl += 1 + maxfloors[st - x];
                }
                next.push_back(fl);
                maxfl = max(maxfl, next[st]);
            }
            maxfloors.swap(next);
        }
        
        // find which st has floors >= N
        return maxfloors.size()-1;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int K;
        int N;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {1,2},
        {2,6},
        {3,14}
    };

    vector< int > answers {
        2,
        3,
        4
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = superEggDrop::Solution().superEggDrop(dp.K, dp.N);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
