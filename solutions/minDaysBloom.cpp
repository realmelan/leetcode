//
//  minDaysBloom.cpp
//  leetcode
//
//  Created by Song Ding on 11/5/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minDaysBloom {
/*
// TODO: copy problem statement here
 Given an array of roses. roses[i] means rose i will bloom on day roses[i]. Also given an int k, which is the minimum number of adjacent bloom roses required for a bouquet, and an int n, which is the number of bouquets we need. Return the earliest day that we can get n bouquets of roses.

 Example:
 Input: roses = [1, 2, 4, 9, 3, 4, 1], k = 2, n = 2
 Output: 4
 Explanation:
 day 1: [b, n, n, n, n, n, b]
 The first and the last rose bloom.

 day 2: [b, b, n, n, n, n, b]
 The second rose blooms. Here the first two bloom roses make a bouquet.

 day 3: [b, b, n, n, b, n, b]

 day 4: [b, b, b, n, b, b, b]
 Here the last three bloom roses make a bouquet, meeting the required n = 2 bouquets of bloom roses. So return day 4.
*/
class Solution {
public:
    // TODO: copy function signature here
    int minDaysBloom(vector<int>& bloomDay, int m, int k) {
        int N = bloomDay.size();
        vector<int> klarge(N, 0);
        deque<int> q;
        for (int i = 0; i < N; ++i) {
            while (q.size() && q.front() <= i-k) {
                q.pop_front();
            }
            while (q.size() && bloomDay[q.back()] < bloomDay[i]) {
                q.pop_back();
            }
            q.push_back(i);
            klarge[i] = bloomDay[q.front()];
        }
        vector<int> dp(N, 0);
        for (int i = 1; i <= m; ++i) {
            vector<int> next(N, INT_MAX);
            for (int j = i*k-1; j < N; ++j) {
                next[j] = min(j>=1?next[j-1]:INT_MAX, max(klarge[j], (j>=k?dp[j-k]:0)));
            }
            dp.swap(next);
        }
        return dp.back();
    }
    int minDaysBloom_binarysearch(vector<int>& bloomDay, int m, int k) {
        int N = bloomDay.size();
        if (N < m*k) {
            return -1;
        }
        vector<int> klarge(N, 0);
        deque<int> q;
        for (int i = 0; i < N; ++i) {
            while (q.size() && q.front() <= i-k) {
                q.pop_front();
            }
            while (q.size() && bloomDay[q.back()] < bloomDay[i]) {
                q.pop_back();
            }
            q.push_back(i);
            klarge[i] = bloomDay[q.front()];
        }
        auto p = minmax_element(begin(bloomDay), end(bloomDay));
        int l = *p.first-1, r = *p.second;
        while (r-l>1) {
            int mid = (l+r)/2;
            int cnt = 0;
            for (int i = k-1; i < N;) {
                if (klarge[i] <= mid) {
                    ++cnt;
                    i += k;
                } else {
                    ++i;
                }
            }
            if (cnt >= m) {
                r = mid;
            } else {
                l = mid;
            }
        }
        return r;
    }
    
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> roses;
        int k;
        int n;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{1, 2, 4, 9, 3, 4, 1}, 2, 2},
        {{1,10,3,10,2},3,1},
        {{1,10,2,9,3,8,4,7,5,6},4,2}
    };
    // TODO: provide expected results here
    vector<int> answers {
        4,
        3,
        9,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minDaysBloom::Solution().minDaysBloom_binarysearch(dp.roses, dp.k, dp.n);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
