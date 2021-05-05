// findCheapestPrice.cpp
// leetcode
//
// Created by  Song Ding on 6/4/18.
// Copyright © 2018 Song Ding. All rights reserved.
//

/*
 There are n cities connected by m flights. Each fight starts from city u and arrives at v with a price w.
 
 Now given all the cities and fights, together with starting city src and the destination dst, your task is to find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.
 
 Example 1:
 Input:
 n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 src = 0, dst = 2, k = 1
 Output: 200
 Explanation:
 The graph looks like this:
 
 
 The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
 Example 2:
 Input:
 n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 src = 0, dst = 2, k = 0
 Output: 500
 Explanation:
 The graph looks like this:
 
 
 The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
 Note:
 
 The number of nodes n will be in range [1, 100], with nodes labeled from 0 to n - 1.
 The size of flights will be in range [0, n * (n - 1) / 2].
 The format of each flight will be (src, dst, price).
 The price of each flight will be in the range [1, 10000].
 k is in the range of [0, n - 1].
 There will not be any duplicated flights or self cycles.
*/
#include "common.h"
using namespace std;

namespace findCheapestPrice {

class Solution {
public:
    /**
     * Dijkstra algorithm
     */
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        int i = 0;
        ++K;
        unordered_map<int, unordered_map<int, int>> fmap;
        for (const auto& v : flights) {
            fmap[v[0]][v[1]] = v[2];
        }
        map<int, int> res;
        map<int, int> next;
        res[src] = 0;
        next[src] = 0;
        while (i++ < K) {
            // for all nodes in cur, expand and see whether any new nodes
            // are added or any price update
            map<int, int> updated;
            for (auto& p : next) {
                int price = p.second;
                int last = p.first;
                auto it = fmap.find(last);
                if (it != fmap.end()) {
                    for (const auto& f : it->second) {
                        int fdst = f.first;
                        int fprice = price + f.second;
                        auto nit = res.find(fdst);
                        if (nit == res.end() || nit->second > fprice) {
                            updated[fdst] = fprice;
                            res[fdst] = fprice;
                        }
                    }
                }
            }
            if (updated.empty()) {
                break;
            }
            next.swap(updated);
        }
        auto it = res.find(dst);
        if (it != res.end()) {
            return it->second;
        } else {
            return -1;
        }
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int n = 3;
    vector<vector<int>> flights{{0,1,100},{1,2,100},{0,2,500}};
    int src = 0;
    int dst = 2;
    int K = 1;
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = findCheapestPrice::Solution().findCheapestPrice(n, flights, src, dst, K);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
