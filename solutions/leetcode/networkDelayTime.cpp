//
//  networkDelayTime.cpp
//  leetcode
//
//  Created by  Song Ding on 12/25/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace networkDelayTime {
    class Solution {
    public:
        /**
         Shortest path: Dijkstra
         */
        int networkDelayTime(vector<vector<int>>& times, int N, int K) {
            vector<int> dist(N + 1, -1);
            dist[K] = 0;
            while (true) {
                int minIndex = -1;
                int minDist = 600100;
                for (const auto& v : times) {
                    if (dist[v[0]] >= 0 && dist[v[1]] < 0) {
                        if (minDist > dist[v[0]] + v[2]) {
                            minDist = dist[v[0]] + v[2];
                            minIndex = v[1];
                        }
                    }
                }
                if (minIndex < 0) {
                    break;
                }
                dist[minIndex] = minDist;
            }
            
            int minTime = 0;
            for (int i = 1; i <= N; ++i) {
                if (dist[i] < 0) {
                    return -1;
                }
                if (minTime < dist[i]) {
                    minTime = dist[i];
                }
            }
            return minTime;
        }
        
        int networkDelayTime2(vector<vector<int>>& times, int N, int K) {
            int res = -1;
            vector<map<int,int>> conn(N+1);
            for (auto& v : times) {
                conn[v[0]][v[1]] = v[2];
            }
            queue<pair<int,int>> q;
            vector<int> t(N+1, INT_MAX);
            t[0] = -1;
            t[K] = 0;
            q.emplace(K, 0);
            while (q.size()) {
                auto [c, ct] = q.front();
                q.pop();
                for (auto [n, w] : conn[c]) {
                    if (ct + w < t[n]) {
                        t[n] = ct + w;
                        q.emplace(n, t[n]);
                    }
                }
            }
            for (auto i : t) {
                if (i == INT_MAX) {
                    return -1;
                }
                res = max(res, i);
            }
            return res;
        }
    };
}
/*
int main() {
    vector<vector<int>> times{
        {2,1,1},
        {2,3,1},
        {3,4,1}
    };
    int N = 4;
    int K = 2;
    cout << networkDelayTime::Solution().networkDelayTime2(times, N, K) << endl;
    return 0;
}
 //*/
