// possibleBipartition.cpp
// leetcode
//
// Created by  Song Ding on 10/8/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

/**
 886. Possible Bipartition
 Medium

 340

 16

 Favorite

 Share
 Given a set of N people (numbered 1, 2, ..., N), we would like to split everyone into two groups of any size.

 Each person may dislike some other people, and they should not go into the same group.

 Formally, if dislikes[i] = [a, b], it means it is not allowed to put the people numbered a and b into the same group.

 Return true if and only if it is possible to split everyone into two groups in this way.

  

 Example 1:

 Input: N = 4, dislikes = [[1,2],[1,3],[2,4]]
 Output: true
 Explanation: group1 [1,4], group2 [2,3]
 Example 2:

 Input: N = 3, dislikes = [[1,2],[1,3],[2,3]]
 Output: false
 Example 3:

 Input: N = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
 Output: false
  

 Note:

 1 <= N <= 2000
 0 <= dislikes.length <= 10000
 1 <= dislikes[i][j] <= N
 dislikes[i][0] < dislikes[i][1]
 There does not exist i != j for which dislikes[i] == dislikes[j].
 */
namespace possibleBipartition {

class Solution {
public:
    bool possibleBipartition_dfs(int N, vector<vector<int>>& dislikes) {
        return false;
    }
    
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        vector<int> as(N+1, 2);
        unordered_map<int, unordered_set<int>> d;
        for (const auto& v : dislikes) {
            d[v[0]].insert(v[1]);
            d[v[1]].insert(v[0]);
        }
        unordered_set<int> todo;
        for (int i = 1; i <= N; ++i) {
            todo.insert(i);
        }
        while (todo.size()) {
            int start = *todo.begin();
            unordered_set<int> cur{start};
            todo.erase(start);
            
            int asg = 0;
            as[start] = asg;
            
            while (cur.size()) {
                unordered_set<int> next;
                for (auto i : cur) {
                    for (auto j : d[i]) {
                        if (as[j] == 2) {
                            as[j] = 1 - asg;
                            next.insert(j);
                            todo.erase(j);
                        } else if (as[j] == asg) {
                            return false;
                        }
                    }
                }
                cur.swap(next);
                asg = 1 - asg;
            }
        }
        return true;
    }
    bool possibleBipartition2(int N, vector<vector<int>>& dislikes) {
        unordered_map<int, set<int>> d;
        for (const auto& v : dislikes) {
            d[v[0]].insert(v[1]);
            d[v[1]].insert(v[0]);
        }
        
        
        vector<int> assign(N+1, 0);
        while (d.size()) {
            // try find an independent subset
            auto it = d.begin();
            set<int> cur {it->first};
            assign[it->first] = 1;
            while (cur.size()) {
                set<int> next;
                for (int node : cur) {
                    const auto& ndis = d[node];
                    for (int nd : ndis) {
                        if (assign[nd] == assign[node]) {
                            return false;
                        }
                        if (assign[nd] == 0) {
                            assign[nd] = 0 - assign[node];
                            next.insert(nd);
                        }
                    }
                    d.erase(node);
                }
                cur.swap(next);
                
            }
        }
        return true;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int N = 5;
    vector<vector<int>> dislikes {
        //{1,2},{1,3},{1,4},{1,5},{1,8},{1,6},{1,9},{1,7},{1,10}
        {{1,2},{3,4},{4,5},{3,5}}
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = possibleBipartition::Solution().possibleBipartition(N, dislikes);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
