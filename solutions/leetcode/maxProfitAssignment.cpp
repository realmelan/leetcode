// maxProfitAssignment.cpp
// leetcode
//
// Created by  Song Ding on 6/5/18.
// Copyright © 2018 Song Ding. All rights reserved.
//

/*
 We have jobs: difficulty[i] is the difficulty of the ith job, and profit[i] is the profit of the ith job.
 
 Now we have some workers. worker[i] is the ability of the ith worker, which means that this worker can only complete a job with difficulty at most worker[i].
 
 Every worker can be assigned at most one job, but one job can be completed multiple times.
 
 For example, if 3 people attempt the same job that pays $1, then the total profit will be $3.  If a worker cannot complete any job, his profit is $0.
 
 What is the most profit we can make?
 
 Example 1:
 
 Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
 Output: 100
 Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get profit of [20,20,30,30] seperately.
 Notes:
 
 1 <= difficulty.length = profit.length <= 10000
 1 <= worker.length <= 10000
 difficulty[i], profit[i], worker[i]  are in range [1, 10^5]
 */

#include "common.h"
using namespace std;

namespace maxProfitAssignment {

class Solution {
public:
    /**
     * Apparently let worker[i] do the job within his ability but having the most profit.
     * build a map which maps a difficulty to the most profit.
     */
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int res = 0;
        vector<pair<int,int>> t;
        int n = difficulty.size();
        for (int i = 0; i < n; ++i) {
            t.push_back(make_pair(difficulty[i], profit[i]));
        }
        sort(t.begin(), t.end(), [](const pair<int,int>& a, const pair<int,int>& b){
            if (a.first != b.first) {
                return a.first < b.first;
            } else {
                return a.second < b.second;
            }
        });
        int mp = 0;
        map<int, int> diff2Profit;
        for (int i = 0; i < n; ++i) {
            int diff = -t[i].first;
            int prof = t[i].second;
            if (mp < prof) {
                mp = prof;
            }
            diff2Profit[diff] = mp;
        }
        
        n = worker.size();
        for (int i = 0; i < n; ++i) {
            int diff = -worker[i];
            auto it = diff2Profit.lower_bound(diff);
            if (it != diff2Profit.end()) {
                res += it->second;
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
    
    vector<int> difficulty {68,35,52,47,86};
    vector<int> profit {67,17,1,81,3};
    vector<int> worker {92,10,85,84,82};
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = maxProfitAssignment::Solution().maxProfitAssignment(difficulty, profit, worker);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
