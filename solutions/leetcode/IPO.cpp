//
//  IPO.cpp
//  leetcode
//
//  Created by  Song Ding on 2/8/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace IPO {
    class Solution {
    public:
        /**
         * greedy: always pick max profit project given current capital.
         * use a priority queue to pick the most profit project.
         */
        int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
            struct proj {
                int capital;
                int profit;
            };
            int n = Profits.size();
            vector<struct proj> projs;
            for (int i = 0; i < n; ++i) {
                projs.push_back({Capital[i],Profits[i]});
            }
            sort(projs.begin(), projs.end(), [](const proj& a, const proj& b){
                return a.capital != b.capital ? a.capital < b.capital : a.profit > b.profit;
            });
            auto maxprofit = [&projs](int a, int b){
                return projs[a].profit < projs[b].profit;
            };
            priority_queue<int, vector<int>, decltype(maxprofit)> ws(maxprofit);
            int j = 0;
            for (int i = 0; i < k; ++i) {
                while (j < n && projs[j].capital <= W) {
                    ws.push(j);
                    ++j;
                }
                int c = ws.top();
                ws.pop();
                W += projs[c].profit;
            }
            return W;
        }
        /**
         Greedy solution: since total capital is increasing with each finished
         project, so always pick the one with higher profit, that is available.
         */
        int findMaximizedCapital2(int k, int W, vector<int>& Profits, vector<int>& Capital) {
            int i = 0;
            vector<pair<int,int>> pc; // sorted by capital
            vector<int>& p = Profits;
            vector<int>& c = Capital;
            
            int n = p.size();
            for (int i = 0; i < n; ++i) {
                pc.push_back(make_pair(p[i], c[i]));
            }
            sort(pc.begin(), pc.end(), [](const pair<int,int>& a, const pair<int,int>& b){
                if (a.first > b.first) {
                    return true;
                } else if (a.first < b.first) {
                    return false;
                } else {
                    return a.second < b.second;
                }
            });
            int w = W;
            while (i < k) {
                int mp = -1;
                int mpi = -1;
                for (int j = 0; j < n; ++j) {
                    if (pc[j].second >= 0 && pc[j].second <= w) {
                        mp = pc[j].first;
                        mpi = j;
                        break;
                    }
                }
                if (mp < 0) {
                    break;
                }
                w += mp;
                pc[mpi].second = -1;
                ++i;
            }
            return w;
        }
    };
}

/*
int main() {
    int k = 2;
    int w = 0;
    vector<int> p{1,2,3};
    
    vector<int> c{0,1,1};
    
    cout << IPO::Solution().findMaximizedCapital(k, w, p, c) << endl;
    return 0;
}
// */
