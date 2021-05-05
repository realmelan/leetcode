// mincostToHireWorkers.cpp
// leetcode
//
// Created by  Song Ding on 10/11/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace mincostToHireWorkers {

class Solution {
public:
    /**
     * Sort the workers by wage/quality and for each worker as base, find the K
     * workers with minimum sum of quality, who have higher wage/quality than base worker.
     */
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        int N = quality.size();
        vector<pair<int,int>> wq;
        for (int i = 0; i < N; ++i) {
            wq.push_back(make_pair(quality[i], wage[i]));
        }
        sort(wq.begin(), wq.end(), [](const pair<int,int>& a, const pair<int,int>& b){
            return (double)a.second / a.first < (double)b.second / b.first;
        });
        
        double res = INFINITY;
        int i = 0;
        priority_queue<int> minQuality;
        int minSumQuality = 0;
        for (; i < K - 1; ++i) {
            minQuality.push(wq[i].first);
            minSumQuality += wq[i].first;
        }
        for (; i < N; ++i) {
            int sumQuality = minSumQuality + wq[i].first;
            double total = (double)wq[i].second / wq[i].first * sumQuality;
            if (total < res) {
                res = total;
            }
            
            minQuality.push(wq[i].first);
            int largeQuality = minQuality.top();
            minQuality.pop();
            minSumQuality = sumQuality - largeQuality;
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> quality{4,4,4,5};
    vector<int> wage{13,12,13,12};
    int K = 2;

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = mincostToHireWorkers::Solution().mincostToHireWorkers(quality, wage, K);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
