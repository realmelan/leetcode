//
//  gardenNoAdj.cpp
//  leetcode
//
//  Created by Song Ding on 7/9/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace gardenNoAdj {
/*
// TODO: copy problem statement here
 1042. Flower Planting With No Adjacent
 Easy

 305

 369

 Add to List

 Share
 You have N gardens, labelled 1 to N.  In each garden, you want to plant one of 4 types of flowers.

 paths[i] = [x, y] describes the existence of a bidirectional path from garden x to garden y.

 Also, there is no garden that has more than 3 paths coming into or leaving it.

 Your task is to choose a flower type for each garden such that, for any two gardens connected by a path, they have different types of flowers.

 Return any such a choice as an array answer, where answer[i] is the type of flower planted in the (i+1)-th garden.  The flower types are denoted 1, 2, 3, or 4.  It is guaranteed an answer exists.

  

 Example 1:

 Input: N = 3, paths = [[1,2],[2,3],[3,1]]
 Output: [1,2,3]
 Example 2:

 Input: N = 4, paths = [[1,2],[3,4]]
 Output: [1,2,1,2]
 Example 3:

 Input: N = 4, paths = [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]]
 Output: [1,2,3,4]
  

 Note:

 1 <= N <= 10000
 0 <= paths.size <= 20000
 No garden has 4 or more paths coming into or leaving it.
 It is guaranteed an answer exists.
*/
class Solution {
public:
    // for each node assign a value that's not used before.
    vector<int> gardenNoAdj_greedy(int N, vector<vector<int>>& paths) {
        vector<vector<int>> g(N+1);
        for (auto& v : paths) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }
        vector<int> res(N, 0);
        for (int i = 1; i <= N; ++i) {
            int colors[5] = {0};
            for (auto j : g[i]) {
                colors[res[j-1]] = 1;
            }
            for (int j = 1; j <= 4; ++j) {
                if (colors[j] == 0) {
                    res[i-1] = j;
                    break;
                }
            }
        }
        return res;
    }
    // TODO: copy function signature here
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        vector<vector<int>> g(N+1);
        for (auto& v :paths) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }
        vector<int> color(N+1, 0);
        for (int i = 1; i <= N; ++i) {
            dfs(i, color, g);
        }
        return vector<int>(color.begin()+1, color.end());
    }
    bool dfs(int i, vector<int>& color, vector<vector<int>>& g) {
        if (color[i]) {
            return true;
        }
        set<int> ic{1,2,3,4};
        for (auto j : g[i]) {
            if (color[j]) {
                ic.erase(color[j]);
            }
        }
        for (auto c : ic) {
            color[i] = c;
            int done = 0;
            for (auto j : g[i]) {
                if (dfs(j, color, g)) {
                    ++done;
                }
            }
            if (done == g[i].size()) {
                return true;
            }
        }
        return false;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        int N;
        vector<vector<int>> paths;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {3,{{1,2},{2,3},{3,1}}},
        {4,{{1,2},{3,4}}},
        {4,{{1,2},{2,3},{3,4},{4,1},{1,3},{2,4}}},
    };
    // TODO: provide expected results here
    vector<vector<int>> answers {
        {1,2,3},
        {1,2,1,2},
        {1,2,3,4},
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = gardenNoAdj::Solution().gardenNoAdj_greedy(dp.N, dp.paths);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
