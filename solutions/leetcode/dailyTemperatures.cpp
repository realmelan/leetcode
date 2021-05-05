// dailyTemperatures.cpp
// leetcode
//
// Created by  Song Ding on 6/19/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace dailyTemperatures {

class Solution {
public:
    /**
     * Starting from the last day, keep a stack of highest temperatures
     * encountered and its index.
     *
     * when a temperature is met, check in the stack to see whether there
     * are low temperatures and pop them if any.
     */
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res;
        stack<pair<int,int>> peakT;
        int n = temperatures.size();
        for (int i = n - 1; i >= 0; --i) {
            while (peakT.size() && peakT.top().first <= temperatures[i]) {
                peakT.pop();
            }
            if (peakT.empty()) {
                res.insert(res.begin(), 0);
            } else {
                res.insert(res.begin(), peakT.top().second - i);
            }
            peakT.push(make_pair(temperatures[i], i));
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> temperatures {
        73, 74, 75, 71, 69, 72, 76, 73
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = dailyTemperatures::Solution().dailyTemperatures(temperatures);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
