// minRefuelStops.cpp
// leetcode
//
// Created by  Song Ding on 12/3/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minRefuelStops {

class Solution {
public:
    /**
     * Find maximum gas the car can take when it arrives at i-th gas station and have
     * made j stops at all gas stations (including the i-th gas station).
     * then gas(i,j) = max(gas(i-1, j) - (station[i][0] - station[i-1][0]), gas(i-1,j-1)
     *  - (station[i][0] - station[i-1][0]) + station[i][1] if it can make from the previous
     *  station to the i-th station).
     */
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        stations.push_back({target, 0});
        if (startFuel < stations[0][0]) {
            return -1;
        }
        
        map<int, int> gasAtStation;
        gasAtStation[0] = startFuel - stations[0][0];
        gasAtStation[1] = startFuel - stations[0][0] + stations[0][1];
        int n = stations.size();
        for (int i = 1; i < n; ++i) {
            map<int, int> next;
            int useGas = stations[i][0] - stations[i-1][0];
            // reverse order would reduce loop iterations.
            for (const auto& p : gasAtStation) {
                int stops = p.first;
                int gas = p.second - useGas;
                if (gas < 0) {
                    continue;
                }
                if (next[stops] < gas) {
                    next[stops] = gas;
                }
                
                ++stops;
                gas += stations[i][1];
                if (next[stops] < gas) {
                    next[stops] = gas;
                }
            }
            gasAtStation.swap(next);
        }
        
        if (gasAtStation.size()) {
            return gasAtStation.begin()->first;
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
    vector<int> target {
        1,
        100,
        100
    };
    vector<int> startFuel {
        1,
        1,
        10
    };
    vector< vector<vector<int>> > stations {
        {},
        {{10,100}},
        {{10,60},{20,30},{30,30},{60,40}}
    };

    vector< int  > answers {
        0,
        -1,
        2
    };
    int i = 2;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = minRefuelStops::Solution().minRefuelStops(target[i], startFuel[i], stations[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
