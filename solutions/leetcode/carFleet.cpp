// carFleet.cpp
// leetcode
//
// Created by  Song Ding on 10/3/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace carFleet {

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        if (n <= 1) {
            return n;
        }
        vector<pair<int,int>> cars;
        for (int i = 0; i < n; ++i) {
            cars.push_back(make_pair(position[i], speed[i]));
        }
        sort(cars.begin(), cars.end(), [](const pair<int,int>& a, const pair<int,int>& b){
            return a.first > b.first;
        });
        
        int res = 1;
        double t = (double)(target - cars[0].first) / cars[0].second;
        for (int i = 1; i < n; ++i) {
            double t1 = (double)(target - cars[i].first) / cars[i].second;
            if (t1 > t) {
                ++res;
                t = t1;
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int target = 12;
    vector<int> position{10,8,0,5,3};
    vector<int> speed{2,4,1,1,3};

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = carFleet::Solution().carFleet(target, position, speed);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
