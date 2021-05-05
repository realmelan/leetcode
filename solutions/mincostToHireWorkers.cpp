//
//  mincostToHireWorkers.cpp
//  leetcode
//
//  Created by Song Ding on 2/17/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace mincostToHireWorkers {
/*
// TODO: copy problem statement here
 857. Minimum Cost to Hire K Workers
 Hard

 1090

 126

 Add to List

 Share
 There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].

 Now we want to hire exactly K workers to form a paid group.  When hiring a group of K workers, we must pay them according to the following rules:

 Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
 Every worker in the paid group must be paid at least their minimum wage expectation.
 Return the least amount of money needed to form a paid group satisfying the above conditions.

  

 Example 1:

 Input: quality = [10,20,5], wage = [70,50,30], K = 2
 Output: 105.00000
 Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.
 Example 2:

 Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
 Output: 30.66667
 Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately.
  

 Note:

 1 <= K <= N <= 10000, where N = quality.length = wage.length
 1 <= quality[i] <= 10000
 1 <= wage[i] <= 10000
 Answers within 10^-5 of the correct answer will be considered correct.
*/
class Solution {
public:
    // TODO: copy function signature here
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        int n = quality.size();
        auto cmp = [](const auto& v1, const auto& v2) {
            return (double)v1[1]/v1[0] > (double)v2[1]/v2[0];
        };
        priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> q(cmp);
        for (int i = 0; i < n; ++i) {
            q.push({quality[i],wage[i]});
        }
        // find first K-1 lowest w/q entries
        // sum keeps the lowest K-1 quality score so far
        int sum = 0, i = 0;
        priority_queue<int> qq;
        for (; i < K-1; ++i) {
            auto w = q.top();
            sum += w[0];
            qq.push(w[0]);
            q.pop();
        }
        // for each worker
        double res = INT_MAX;
        while (q.size()) {
            auto w = q.top();
            q.pop();
            res = min(res, (double)w[1]/w[0] * sum + w[1]);
            
            sum += w[0];
            qq.push(w[0]);
            sum -= qq.top();
            qq.pop();
        }
        return res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> quality;
        vector<int> wage;
        int K;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{10,20,5}, {70,50,30},2},
    };
    // TODO: provide expected results here
    vector<double> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = mincostToHireWorkers::Solution().mincostToHireWorkers(dp.quality, dp.wage, dp.K);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
